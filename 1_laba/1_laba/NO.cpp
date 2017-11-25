//Программа многопоточно перемножает матрицы несколько раз, разным количеством потоков
//Выводит время работы для каждого количества потоков
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

///////////////////////заполнение исходных матриц/////////////////////////////
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

/////////////////////обнуление матрицы с результатами /////////////////////////
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
///////////////////красивый вывод матрицы//////////////////////
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
////////////////построчное перемножение матриц///////////////
void countingMatrixRpws(int i) { //i - номер строки первой матрицы и столбца второй

	for (int j = 0; j < q; j++) {
		res[i][j] = 0;
		for (int k = 0; k < n; k++) {
			res[i][j] += mas_1[i][k] * mas_2[k][j];
		}
	}
}
///////////////Создание потока и подъсчет матрицы///////////////
void throw_function(int n, int count_thread, int i)
{
	///////////задаем границы подъсчета////////////
	int l, r; //левая и правая соответственно 

	if (i == -4)
	{
		l = n - n % count_thread;
		r = n;
	}
	else {
		l = n / count_thread * i;
		r = l + n / count_thread;
	}
	
	//////приостанавливаем выполнение потока, до тех пор пока не будут созданы все потоки
	WaitForSingleObject(mtx, INFINITE); 

	/////////////вычисление матрицы///////////////
	while (l < r) {
		countingMatrixRpws(l);
		l++;
	}	
}
////////////////Обработчик ошибок//////////////////////
void ko(int n, int count_thread, int i)
{
	try
	{
		throw_function(n, count_thread, i);//если все ok, то переходим непосредственно к главной функции потока
	}
	catch (...)
	{
		mutex mx;
		std::lock_guard<std::mutex> lock(mx);
		g_exceptions.push_back(std::current_exception());
	}
}


int main() {
	
	remove("D:\\ТТИ ЮФУ\\_3 курс\\ТЯПиВП\\1_laba_TAP\\Graphic\\data_graphic.txt");
	ofstream vmdelet_out;     //создаем поток вывода в файл
	vmdelet_out.open("D:\\ТТИ ЮФУ\\_3 курс\\ТЯПиВП\\1_laba_TAP\\Graphic\\data_graphic.txt", ios::app);  // открываем файл для записи 

	//заполняем исходные матрицы
	fillMatrix(mas_1, m, n);
	fillMatrix(mas_2, n, q);
	

	int count_thread = 1;     // начальное количество потоков
	////////////////////////////
	const int step = 2;       // шаг с которым будет увеличиваться количество потоков
	const int iteration = 14; // количество испытаний(сколько раз сделаем шаг)
	////////////////////////////
	
	for (int j = 0; j < iteration; j++) {

		//объект для записи ошибок 
		g_exceptions.clear();

		//массив потоков
		vector<thread> threads(count_thread);
		
		//создаем залоченный мьютекс, который запустит подсчет матрицы только после создания всех потоков
		mtx = CreateMutex(NULL, TRUE, NULL);
		
		if (n % count_thread != 0) {
			threads.push_back(thread(ko, n, count_thread, -4));
		}
		for (int i = 0; i < count_thread; i++)
		{
			threads.push_back(thread(ko, n, count_thread, i));
		}
		//coutMatrix(res, m, q); /////////////////////////////////////////////////

		//анлочим мъютекс, запускаем подсчет матрицы
		ReleaseMutex(mtx);

		double start_time = clock();
		
		//коректно завершаем потоки
		for (auto& it : threads)
		{
			if (it.joinable())
			{
				it.join();
			}
		}

		double end_time = (clock() - start_time) / 1000;
		cout << "Count thread: " << count_thread << " | time: " << end_time << endl << endl; //выводим результат в консоль
		//coutMatrix(res, m, q);/////////////////////////////////////////////
		vmdelet_out << count_thread << " " << end_time << endl; //выводим результат в файл, для построения граффика

		//увеличиваем количество потоков, и зануляем матрицу результатов для чистоты эксперемента
		count_thread += step;
		clearMatrix(res, m, q); //та матрица в которой хранится результат перемножения

		//////////////////Обаработка ошибоk//////////////////////
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
	
	//закрываем поток вывода в файл
	vmdelet_out.close();
		
	return 0;
}

