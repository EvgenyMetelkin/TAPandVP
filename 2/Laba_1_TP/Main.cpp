#include <fstream>

#include "Function.h"

int main()
{
	system("chcp 1251"); 
	cout << "Разбор файла 'JavaScript' на лексемы..." << endl;

	
	remove("Lecsem.txt"); // открываем файл для записи 
	lec_out.open("Lecsem.txt", ios::app);  

	ifstream file("JS.txt"); // файл из которого читаем 
	string buff_file;        // строка в которую будем класть информацию считанную из файла

	string buff_char = "";  
	string condition = "0";  // строка текущего состояния

	while (getline(file, buff_file)) { // пока не достигнут конец файла построчно считывать из файла JS d в переменную buff_file
		buff_file +='\n';
		for (unsigned int i = 0, len = buff_file.length(); i < len; i++) {
			
			string symbol_type = typeIdentification(buff_file[i]); // определяем тип поступившего символа

			condition = currentCondition(condition, symbol_type, buff_char); // определяем следующее состояние и если необходимо выполняем семантическую процедуру
			
			buff_char += buff_file[i];	
		}
		cout << endl;     //вывод в консоль
		lec_out << endl;  //вывод в файл
	}

	writeVariables();


	//закрываем потоки ввода и вывода в файлы
	lec_out.close();
	file.close();

	return 0;
}