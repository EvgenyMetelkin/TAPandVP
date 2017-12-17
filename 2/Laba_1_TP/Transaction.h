#pragma once
#include <iostream>
#include <map>
#include <string>

using namespace std;

ofstream lec_out;     //������� ����� ������ � ����	


inline string search(string buff, map <string, string> &Words) // ������������� �����
{
	for (auto it = Words.begin(); it != Words.end(); ++it)
	{
		if (it->first == buff)
			return it->second;
	}

	return "0";
}

string functionWord(string buff)
{
	map <string, string> functionWord = {
		{ "var",        "1" },
		{ "return",     "2" },
		{ "new",        "4" },
		{ "array",      "5" },
		{ "goto",       "7" },
		{ "if",         "8" },
		{ "else",       "9" },
		{ "function",  "10" }
	};

	return search(buff, functionWord);
}

string punctuation(string buff)
{
	map <string, string> punctuation = {
		{ ",",   "1" },
		{ ";",   "2" },
		{ " ",   "3" },
		{ "(",   "4" },
		{ ")",   "5" },
		{ "{",   "6" },
		{ "}",   "7" },
		{ ".",   "8" },
		{ "'",   "9" },
		{ "\"",  "10" }
	};

	return search(buff, punctuation);
}

string operation(string buff)
{
	map <string, string> operation = {
		{ "+",   "1" },
		{ "-",   "2" },
		{ "*",   "3" },
		{ "/",   "4" },
		{ "^",   "5" },
		{ "<",   "6" },
		{ ">",   "7" },
		{ "==",  "8" },
		{ "!=",  "9" },
		{ "<=",  "10" },
		{ ">=",  "11" },
		{ "=",   "12" },
		{ ":",   "13" },
		{ "[",   "14" },
		{ "]",   "15" }
	};

	return search(buff, operation);
}

map <string, string> variables; // ��������� ���������, ��� ���� ����� �� ��������� ������ ��� ���������� �������

string variable(string buff)  // ��� ���������� 
{
	string result = search(buff, variables); // ������� ����������� �� ������ ��� �����

	if (result != "0") {  // ����������� 
		return result;
	}
	else {  // �� �����������
		string size_map = to_string(variables.size() + 1);
		variables.insert(pair<string, string>(buff, size_map)); // ��������� ����� ��� 

		return size_map;
	}
}

map <string, string> constants_numeric;

string constantNumeric(string buff)  // �������� ���������
{
	string result = search(buff, constants_numeric); 

	if (result != "0") {
		return result;
	}
	else {
		string size_map = to_string(constants_numeric.size() + 1);
		constants_numeric.insert(pair<string, string>(buff, size_map));

		return size_map;
	}
}

map <string, string> constants_symbol;

string constantSymbol(string buff)  // ���������� ���������
{
	string result = search(buff, constants_symbol);

	if (result != "0") {
		return result;
	}
	else {
		string size_map = to_string(constants_symbol.size() + 1);
		constants_symbol.insert(pair<string, string>(buff, size_map));

		return size_map;
	}
}

void writeToFile(map <string, string> &Words, char cymbol) 
{
	for (auto it = Words.begin(); it != Words.end(); ++it) {
		cout << cymbol << it->second << " - " << it->first << endl;
	}
}

void writeVariables() // ������ � ����� ���� ���������� � �� ��������
{
	freopen("Variables.txt", "w", stdout); // ������ ����� ����������
	writeToFile(variables, 'I');

	freopen("Const_numeric.txt", "w", stdout); // ������ �������� ���������
	writeToFile(constants_numeric, 'N');

	freopen("Const_symbol.txt", "w", stdout); // ������ ��������� ���������
	writeToFile(constants_symbol, 'C');


}