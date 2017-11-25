//��������� ������������ ����������� ������� ��������� ���, ������ ����������� �������
//������� ����� ������ ��� ������� ���������� �������
#include <iostream>
#include <Windows.h>
#include <mutex>
#include <thread>
#include <vector>
#include <ctime>   
#include <complex.h>
#include <fstream>


using namespace std;
///////////////////////////////////////
int m = 1000, n = 1000, q = 1000;
///////////////////////////////////////
vector < vector <int>> mas_1(m, vector<int>(n));
vector < vector <int>> mas_2(n, vector<int>(q));
vector < vector <long long int>> res(m, vector<long long int>(q));

HANDLE mtx;

std::vector<std::exception_ptr>  g_exceptions;

///////////////////////���������� �������� ������/////////////////////////////
void fillMatrix(vector <vector <int>> &mas, int i, int j) 
{
	for (int _i = 0; _i < i; ++_i)
	{
		for (int _j = 0; _j < j; ++_j)
		{
			mas[_i][_j] = _i + _j;
		}
	}
}

/////////////////////��������� ������� � ������������ /////////////////////////
void clearMatrix(vector <vector <long long int>> &mas, int i, int j) 
{
	for (int _i = 0; _i < i; ++_i)
	{
		for (int _j = 0; _j < j; ++_j)
		{
			mas[_i][_j] = 0;
		}
	}
}
///////////////////�������� ����� �������//////////////////////
void coutMatrix(vector <vector <long long int>> mas, int i, int j)
{
	for (int _i = 0; _i < i; _i++)
	{
		for (int _j = 0; _j < j; _j++)
		{
			cout << mas[_i][_j] << " ";
		}
		cout << endl;
	}
	cout << endl << endl;
}
////////////////���������� ������������ ������///////////////
void countingMatrixRpws(int i) { //i - ����� ������ ������ ������� � ������� ������

	for (int j = 0; j < q; j++) {
		res[i][j] = 0;
		for (int k = 0; k < n; k++) {
			res[i][j] += mas_1[i][k] * mas_2[k][j];
		}
	}
}
///////////////�������� ������ � �������� �������///////////////
void throw_function(int n, int count_thread, int i)
{
	///////////������ ������� ���������////////////
	int l, r; //����� � ������ �������������� 

	if (i == -4)
	{
		l = n - n % count_thread;
		r = n;
	}
	else {
		l = n / count_thread * i;
		r = l + n / count_thread;
	}
	
	//////���������������� ���������� ������, �� ��� ��� ���� �� ����� ������� ��� ������
	WaitForSingleObject(mtx, INFINITE); 

	/////////////���������� �������///////////////
	while (l < r) {
		countingMatrixRpws(l);
		l++;
	}	
}
////////////////���������� ������//////////////////////
void ko(int n, int count_thread, int i)
{
	try
	{
		throw_function(n, count_thread, i);//���� ��� ok, �� ��������� ��������������� � ������� ������� ������
	}
	catch (...)
	{
		mutex mx;
		std::lock_guard<std::mutex> lock(mx);
		g_exceptions.push_back(std::current_exception());
	}
}


int main() {
	
	remove("D:\\��� ���\\_3 ����\\������\\1_laba_TAP\\Graphic\\data_graphic.txt");
	ofstream vmdelet_out;     //������� ����� ������ � ����
	vmdelet_out.open("D:\\��� ���\\_3 ����\\������\\1_laba_TAP\\Graphic\\data_graphic.txt", ios::app);  // ��������� ���� ��� ������ 

	//��������� �������� �������
	fillMatrix(mas_1, m, n);
	fillMatrix(mas_2, n, q);
	

	int count_thread = 1;     // ��������� ���������� �������
	////////////////////////////
	const int step = 2;       // ��� � ������� ����� ������������� ���������� �������
	const int iteration = 14; // ���������� ���������(������� ��� ������� ���)
	////////////////////////////
	
	for (int j = 0; j < iteration; j++) {

		//������ ��� ������ ������ 
		g_exceptions.clear();

		//������ �������
		vector<thread> threads(count_thread);
		
		//������� ���������� �������, ������� �������� ������� ������� ������ ����� �������� ���� �������
		mtx = CreateMutex(NULL, TRUE, NULL);
		
		if (n % count_thread != 0) {
			threads.push_back(thread(ko, n, count_thread, -4));
		}
		for (int i = 0; i < count_thread; i++)
		{
			threads.push_back(thread(ko, n, count_thread, i));
		}
		//coutMatrix(res, m, q); /////////////////////////////////////////////////

		//������� �������, ��������� ������� �������
		ReleaseMutex(mtx);

		double start_time = clock();
		
		//�������� ��������� ������
		for (auto& it : threads)
		{
			if (it.joinable())
			{
				it.join();
			}
		}

		double end_time = (clock() - start_time) / 1000;
		cout << "Count thread: " << count_thread << " | time: " << end_time << endl << endl; //������� ��������� � �������
		//coutMatrix(res, m, q);/////////////////////////////////////////////
		vmdelet_out << count_thread << " " << end_time << endl; //������� ��������� � ����, ��� ���������� ��������

		//����������� ���������� �������, � �������� ������� ����������� ��� ������� ������������
		count_thread += step;
		clearMatrix(res, m, q); //�� ������� � ������� �������� ��������� ������������

		//////////////////���������� �����k//////////////////////
		for (auto &e : g_exceptions)
		{
			try
			{
				if (e != nullptr)
					std::rethrow_exception(e);
			}
			catch (const std::exception &e)
			{
				std::cout << e.what() << std::endl;
			}
		}
		g_exceptions.clear();
		////////////////////////////////////////////////////////
	}
	
	//��������� ����� ������ � ����
	vmdelet_out.close();
		
	return 0;
}

