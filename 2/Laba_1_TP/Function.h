#pragma once
#include <iostream>
#include <map>
#include <string>

using namespace std;
#include "ProceduresNumber.h"

string typeIdentification(char symbol)
{
	if (symbol == 'e' || symbol == 'E') // ��� �� � �� ����� �������� ���������, �� �������� ������...
	{
		return "9";
	}
	if ((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z'))
	{
		return "1";
	}
	if (symbol >= '0' && symbol <= '9')
	{
		return "2";
	}
	map <char, string> list_symbol =
	{
		{ ' ',    "3" },
		{ '+',    "4" },
		{ '-',    "4" },
		{ ',',    "5" },
		{ ';',    "5" },
		{ '(',    "5" },
		{ ')',    "5" },
		{ ':',    "5" },
		{ '<',    "6" },
		{ '>',    "6" },
		{ '/',    "7" },
		{ '=',    "8" },
		{ '{',    "10" },
		{ '}',    "11" },
		{ '.',    "12" },
		{ '\'',   "13" },
		{ '"',    "14" },
		{ '*',    "15" },
		{ '^',    "15" },
		{ '[',    "15" },
		{ ']',    "15" },
		{ '\n',   "16" },
		{ '!',    "17" },
		{ '|',    "17" }
	};

	auto rez = list_symbol.find(symbol);

	if (rez != list_symbol.end()) {
		return rez->second;
	}
	else {
		cout << "Invalid symbol in input" << endl;
		return "0"; // �� ���� �������� �� ���������� ������ 
	}
}

string currentCondition(string condition, string symbol_type, string &buff) {
	//cout << condition << "_" << symbol_type << " " << buff <<  endl;
	map <string, string> currentCondition = {
		//       �                 �                 " "                + -            , ; : ( )               < >                 /                =                  e E                    {                 }                 .                    '                    "                * ^ [ ]             \n                   !
		{  "0_1", "1"    },{  "0_2", "3"    },{  "0_3", "9"    },{  "0_4", "10"   },{  "0_5", "9"    },{  "0_6", "11"   },{  "0_7", "17"    },{  "0_8", "11"   },{  "0_9", "1"   },{  "0_10", "9"    },{  "0_11", "9"    },{  "0_12", "7"    },{  "0_13", "14"   },{ "0_14", "15"    },{  "0_15", "10"   },{  "0_16", "9"    },{  "0_17", "13"   },
		{  "1_1", "1"    },{  "1_2", "2"    },{  "1_3", "9P2"  },{  "1_4", "10P2" },{  "1_5", "9P2"  },{  "1_6", "11P2" },{  "1_7", "17P2"  },{  "1_8", "11P2" },{  "1_9", "1"   },{  "1_10", "9P2"  },{  "1_11", "9P2"  },                    {  "1_13", "14P2" },{  "1_14", "15P2" },{  "1_15", "10P2" },{  "1_16", "9P2"  },{  "1_17", "13P2" },
		{  "2_1", "2"    },{  "2_2", "2"    },{  "2_3", "9P1"  },{  "2_4", "10P1" },{  "2_5", "9P1"  },{  "2_6", "11P1" },{  "2_7", "17P1"  },{  "2_8", "11P1" },{  "2_9", "2"   },{  "2_10", "9P1"  },{  "2_11", "9P1"  },                    {  "2_13", "14P1" },{  "2_14", "15P1" },{  "2_15", "10P1" },{  "2_16", "9P1"  },{  "2_17", "13P1" },
						   {  "3_2", "3"    },{  "3_3", "9P3"  },{  "3_4", "10P3" },{  "3_5", "9P3"  },{  "3_6", "11P3" },{  "3_7", "17P3"  },{  "3_8", "11P3" },{  "3_9", "4"   },{  "3_10", "9P3"  },{  "3_11", "9P3"  },{  "3_12", "7"    },{  "3_13", "14P3" },{  "3_14", "15P3" },{  "3_15", "10P3" },{  "3_16", "9P3"  },{  "3_17", "13P3" },
						   {  "4_2", "6"    },                   {  "4_4", "5"    },																										    																		   											  		   					
						   {  "5_2", "6"    },																																				    																		   											  		   					
						   {  "6_2", "6"    },{  "6_3", "9P3"  },{  "6_4", "10P3" },{  "6_5", "9P3"  },{  "6_6", "11P3" },{  "6_7", "17P3"  },{  "6_8", "11P3" },                  {  "6_10", "9P3"  },{  "6_11", "9P3"  },{  "6_12", "7P3"  },{  "6_13", "14P3" },{  "6_14", "15P3" },{  "6_15", "10P3" },{  "6_16", "9P3"  },{  "6_17", "13P3" },
						   {  "7_2", "8"    },                                                                                                                                                                                                                                                             			                              
						   {  "8_2", "8"    },{  "8_3", "9P3"  },{  "8_4", "10P3" },{  "8_5", "9P3"  },{  "8_6", "11P3" },{  "8_7", "17P3"  },{  "8_8", "11P3" },{  "8_9", "4"   },{  "8_10", "9P3"  },{  "8_11", "9P3"  },{  "8_12", "7P3"  },{  "8_13", "14P3" },{  "8_14", "15P3" },{  "8_15", "10P3" },{  "8_16", "9P3"  },{  "8_17", "13P3" },
		{  "9_1", "1P4"  },{  "9_2", "3P4"  },{  "9_3", "9P4"  },{  "9_4", "10P4" },{  "9_5", "9P4"  },{  "9_6", "11P4" },{  "9_7", "17P4"  },{  "9_8", "11P4" },{  "9_9", "1P4" },{  "9_10", "9P4"  },{  "9_11", "9P4"  },{  "9_12", "7P4"  },{  "9_13", "14P4" },{  "9_14", "15P4" },{  "9_15", "10P4" },{  "9_16", "9P4"  },{  "9_17", "13P4" },
		{ "10_1", "1P5"  },{ "10_2", "3P5"  },{ "10_3", "9P5"  },{ "10_4", "10P5" },{ "10_5", "9P5"  },{ "10_6", "11P5" },{ "10_7", "17P5"  },{ "10_8", "11P5" },{ "10_9", "1P5" },{ "10_10", "9P5"  },{ "10_11", "9P5"  },{ "10_12", "7P5"  },{ "10_13", "14P5" },{ "10_14", "15P5" },{ "10_15", "10P5" },{ "10_16", "9P5"  },{ "10_17", "13P5" },
		{ "11_1", "1P5"  },{ "11_2", "3P5"  },{ "11_3", "9P5"  },{ "11_4", "10P5" },{ "11_5", "9P5"  },{ "11_6", "11P5" },{ "11_7", "17P5"  },{ "11_8", "12"   },{ "11_9", "1P5" },{ "11_10", "9P5"  },{ "11_11", "9P5"  },{ "11_12", "7P5"  },{ "11_13", "14P5" },{ "11_14", "15P5" },{ "11_15", "10P5" },{ "11_16", "9P5"  },{ "11_17", "13P5" },
		{ "12_1", "1P5"  },{ "12_2", "3P5"  },{ "12_3", "9P5"  },{ "12_4", "10P5" },{ "12_5", "9P5"  },{ "12_6", "11P5" },{ "12_7", "17P5"  },{ "12_8", "11P5" },{ "12_9", "1P5" },{ "12_10", "9P5"  },{ "12_11", "9P5"  },{ "12_12", "7P5"  },{ "12_13", "14P5" },{ "12_14", "15P5" },{ "12_15", "10P5" },{ "12_16", "9P5"  },{ "12_17", "13P5" },
		                                                                                                                                      { "13_8", "12"   }, 																																					                              
		{ "14_1", "14"   },{ "14_2", "14"   },{ "14_3", "14"   },{ "14_4", "14"   },                   { "14_6", "14"   },{ "14_7", "14"    },{ "14_8", "14"   },{ "14_9", "14"  },{ "14_10", "14"   },{ "14_11", "14"   },{ "14_12", "14"   },{ "14_13", "16"   },{ "14_14", "14"   },{ "14_15", "14"   },					   { "14_17", "14"   },
		{ "15_1", "15"   },{ "15_2", "15"   },{ "15_3", "15"   },{ "15_4", "15"   },{ "15_5", "15"   },{ "15_6", "15"   },{ "15_7", "15"    },{ "15_8", "15"   },{ "15_9", "15"  },{ "15_10", "15"   },{ "15_11", "15"   },{ "15_12", "15"   },{ "15_13", "15"   },{ "15_14", "16"   },{ "15_15", "15"   },{ "15_16", "15"   },{ "15_17", "15"   },
		{ "16_1", "1P6"  },{ "16_2", "3P6"  },{ "16_3", "9P6"  },{ "16_4", "10P6" },{ "16_5", "9P6"  },{ "16_6", "11P6" },{ "16_7", "17P6"  },{ "16_8", "11P6" },{ "16_9", "1P6" },{ "16_10", "9P6"  },{ "16_11", "9P6"  },{ "16_12", "7P6"  },{ "16_13", "14P6" },{ "16_14", "15P6" },{ "16_15", "10P6" },{ "16_16", "9P6"  },{ "16_17", "13P6" },
		{ "17_1", "1P5"  },{ "17_2", "3P5"  },{ "17_3", "9P5"  },{ "17_4", "10P5" },{ "17_5", "9P5"  },                   { "17_7", "18P7"  },                   { "17_9", "1P5" },{ "17_10", "9P5"  },{ "17_11", "9P5"  },{ "17_12", "7P5"  },{ "17_13", "14P5" },{ "17_14", "15P5" },                    { "17_16", "9P5"  },                   
		{ "18_1", "18"   },{ "18_2", "18"   },{ "18_3", "18"   },{ "18_4", "18"   },{ "18_5", "18"   },{ "18_6", "18"   },{ "18_7", "18"    },{ "18_8", "18"   },{ "18_9", "18"  },{ "18_10", "18"   },{ "18_11", "18"   },{ "18_12", "18"   },{ "18_13", "18"   },{ "18_14", "18"   },{ "18_15", "18"   },{ "18_16", "19"   },{ "18_17", "18"   },
		{ "19_1", "1P7"  },{ "19_2", "3P7"  },{ "19_3", "9P7"  },{ "19_4", "10P7" },{ "19_5", "9P7"  },{ "19_6", "11P7" },{ "19_7", "17P7"  },{ "19_8", "11P7" },{ "19_9", "1P7" },{ "19_10", "9P7"  },{ "19_11", "9P7"  },{ "19_12", "7P7"  },{ "19_13", "14P7" },{ "19_14", "15P7" },{ "19_15", "10P7" },{ "19_16", "9P7"  },{ "19_17", "0"    },
	};

	auto rez = currentCondition.find(condition + "_" + symbol_type);
	if (rez == currentCondition.end()) { cout << " ������������� ������ " << rez -> second; }
	string curCondCod = rez->second, curCond = "", numbProced = ""; //
	bool proced = false;

	for(int i = 0, len = curCondCod.length(); i < len; i++)
	{
		if(curCondCod[i] == 'P'){
			proced = true;
		}
		else{
			if(!proced){
				curCond += curCondCod[i];
			}
			else{
				numbProced += curCondCod[i];
			}
		}
	}

	semantickProced(numbProced, buff);

	return curCond;
}
