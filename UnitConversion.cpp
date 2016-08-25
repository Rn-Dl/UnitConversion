// UnitConversion.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Conversion.h"
#include <iostream>
#include <fstream>
#include <iomanip>
//#include <locale>
using namespace std;

char* path_in;
char* path_out;

int main(int argc, char* argv[])
{
	//setlocale(LC_ALL, "Russian");

	if (argc==3) {
		path_in = argv[1];
		path_out = argv[2];
	}
	else {
		path_in = "in.txt";
		path_out = "out.txt";
	}

	Conversion obj1(path_in,path_out);
	obj1.conv();
	obj1.print_facts();
	obj1.print_write_solutions();

	return 0;
}