//

#ifndef CONVERSION_H
#define CONVERSION_H

#include "stdafx.h"
#include <string>
#include <vector>
using namespace std;

struct fact { //structure of the fact
	string Unit1, Unit2;
	double OneUnit1; // OneUnit1 = u2/u1
};

struct solution { //structure of the solution
	string Unit1, Unit2;
	double u1, u2;
};

class Conversion
{
	private:
		char *path_in, *path_out;
		vector<fact> facts; // contain reading facts
		vector<solution> solutions; //vect of solutions
	public:
		Conversion(char* path1, char* path2) : path_in(path1), path_out(path2) {} 
		void conv(); //parsing and conversion in every string
		string science_notation (vector<solution>::const_iterator, bool); // power of a number in scientific notation (default: e-nnn, require: e-nn)
		bool find_str(vector<string>, string); // search Unit in net, return "false" if found.
		void print_write_solutions(); // print and filing all solutions
		void print_facts(); // print all facts
};

#endif