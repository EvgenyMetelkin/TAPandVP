#pragma once
#include <iostream>
#include <map>
#include <string>

using namespace std;
#include "Transaction.h"

string ProcedureNumber_1(string& buff) // ���������� 
{
	cout << "I" << variable(buff) << " ";
	lec_out << "I" << variable(buff) << " ";

	buff.clear();
	return "0";
}

string ProcedureNumber_2(string& buff) // ��������� ����� ��� ����������
{
	string result = functionWord(buff);
	if (result != "0")
	{
		cout << "W" << result << " ";
		lec_out << "W" << result << " ";
	}
	else
	{
		cout << "I" << variable(buff) << " ";
		lec_out << "I" << variable(buff) << " ";
	}

	buff.clear();

	return "0";
}

string ProcedureNumber_3(string &buff) // �������� ���������
{
	cout << "N" << constantNumeric(buff) << " ";
	lec_out << "N" << constantNumeric(buff) << " ";

	buff.clear();

	return "0";
}

string ProcedureNumber_4(string &buff)
{
	if (buff != " " && buff != "\n")
	{
		cout << "R" << punctuation(buff) << " ";
		lec_out << "R" << punctuation(buff) << " ";
	}
	buff.clear();

	return "0";
}

string ProcedureNumber_5(string &buff) // ��������
{
	cout << "O" << operation(buff) << " ";
	lec_out << "O" << operation(buff) << " ";

	buff.clear();

	return "0";
}

string ProcedureNumber_6(string &buff) // ��������� ���������
{
	buff.erase(buff.begin());

	buff.pop_back();

	cout << "C" << constantSymbol(buff) << " ";
	lec_out << "C" << constantSymbol(buff) << " ";

	buff.clear();

	//buff = post;

	return "0";
}

string ProcedureNumber_7(string &buff) // ������
{
	buff.clear();

	return "0";
}

//string ProcedureNumber_8(string &buff) // ������
//{
//	//char post = buff[buff.size()];
//
//	buff.pop_back();
//	buff.pop_back();
//
//	if (buff != "")
//	{
//		cout << "N" << constantNumeric(buff) << " ";
//	}
//	cout << "O16 ";
//
//	buff.clear();
//
//	return "0";
//}

void semantickProced(const string& cs, string& buff) {
	if (cs == "1")
	{
		ProcedureNumber_1(buff);
	}
	else if (cs == "2")
	{
		ProcedureNumber_2(buff);
	}
	else if (cs == "3")
	{
		ProcedureNumber_3(buff);
	}
	else if (cs == "4")
	{
		ProcedureNumber_4(buff);
	}
	else if (cs == "5")
	{
		ProcedureNumber_5(buff);
	}
	else if (cs == "6")
	{
		ProcedureNumber_6(buff);
	}
	else if (cs == "7")
	{
		ProcedureNumber_7(buff);
	}
	/*else if (cs == "8")
	{
	ProcedureNumber_8(buff);
	}*/

}