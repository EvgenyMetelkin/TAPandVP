#include <fstream>

#include "Function.h"

int main()
{
	system("chcp 1251"); 
	cout << "������ ����� 'JavaScript' �� �������..." << endl;

	
	remove("Lecsem.txt"); // ��������� ���� ��� ������ 
	lec_out.open("Lecsem.txt", ios::app);  

	ifstream file("JS.txt"); // ���� �� �������� ������ 
	string buff_file;        // ������ � ������� ����� ������ ���������� ��������� �� �����

	string buff_char = "";  
	string condition = "0";  // ������ �������� ���������

	while (getline(file, buff_file)) { // ���� �� ��������� ����� ����� ��������� ��������� �� ����� JS d � ���������� buff_file
		buff_file +='\n';
		for (unsigned int i = 0, len = buff_file.length(); i < len; i++) {
			
			string symbol_type = typeIdentification(buff_file[i]); // ���������� ��� ������������ �������

			condition = currentCondition(condition, symbol_type, buff_char); // ���������� ��������� ��������� � ���� ���������� ��������� ������������� ���������
			
			buff_char += buff_file[i];	
		}
		cout << endl;     //����� � �������
		lec_out << endl;  //����� � ����
	}

	writeVariables();


	//��������� ������ ����� � ������ � �����
	lec_out.close();
	file.close();

	return 0;
}