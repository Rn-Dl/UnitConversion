#include "stdafx.h"
#include "Conversion.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

string Conversion::science_notation(vector<solution>::const_iterator r, bool u) {
	stringstream print;
		(u == 0) ? print<<setprecision(6)<<scientific<<r->u1 : print<<setprecision(6)<<scientific<<r->u2;
	string t = print.str(); t.erase(t.size()-3,1);
	return t;
}

void Conversion::conv()
{
	char temp_Unit1[20], temp_Unit2[20];
	double temp_u1;
	string temp_u2; 

	ifstream f_txt(path_in, ios::in);
	if(!f_txt)
	{
		cerr<<"Error reading file"<<endl;
		system("pause");
		exit(1);
	}

	while(f_txt)
	{
		f_txt>>temp_u1;
		f_txt>>temp_Unit1;
		f_txt.ignore(2, '=');
		f_txt>>temp_u2;
		f_txt>>temp_Unit2;
		f_txt.ignore(50,'\n');
		if(strcmp(temp_Unit1,temp_Unit2) == NULL)
			continue;
		if (temp_u2 != "?") {
			double temp_U2 = atof (temp_u2.c_str());
			bool l = true;
			if (facts.size() != 0) {
				for (vector<fact>::const_iterator it = facts.begin(); it != facts.end(); ++it) 
					if( (it->Unit1 == temp_Unit1 || it->Unit2 == temp_Unit1) && (it->Unit1 == temp_Unit2 || it->Unit2 == temp_Unit2)) 
					{ l = false; break; }
			}
			if (l == true || facts.empty() == true) {
				fact f;
				f.Unit1 = temp_Unit1;
				f.Unit2 = temp_Unit2;
				f.OneUnit1 = temp_U2 / temp_u1;
				facts.push_back(f);
			}
		}
		else {
			string temp = temp_Unit1;
			vector<string> net;
			net.push_back(temp);
			solution r;
			r.u1 = temp_u1;
			r.u2 = temp_u1;
			r.Unit1 = temp_Unit1;
			r.Unit2 = temp_Unit2;
			while(temp != temp_Unit2)
			{
				string pre_temp = temp;
				for (vector<fact>::const_iterator it = facts.begin(); it != facts.end(); ++it) {
					if (it->Unit1 == temp && find_str(net, it->Unit2) ) {
						temp = it->Unit2;
						net.push_back(temp);
						r.u2 *= it->OneUnit1;
						break;
					}
					if (it->Unit2 == temp && find_str(net, it->Unit1) ) {
						temp = it->Unit1;
						net.push_back(temp);
						r.u2 *= 1/it->OneUnit1;
						break;
					}
				}
				if (pre_temp == temp) {
					r.u1 = r.u2 = 0;
					break;
				}
			}
			solutions.push_back(r);
		}
	}
	f_txt.close();
}

void Conversion::print_write_solutions()
{
	ofstream f_txt(path_out, ios::out);
	int Max = 1000000;
	double Min = 0.1;
	cout<<endl;
	for (vector<solution>::const_iterator it = solutions.begin(); it != solutions.end(); ++it) {
		if ( it->u1 == 0 && it->u2 == 0 ) {
			cout<<"Conversion is impossible"<<endl;
			f_txt<<"Conversion is impossible"<<endl;
		}
		else {
			if ( it->u1>=Max || it->u1<Min )
				cout<<science_notation(it, false);
			else 
				cout<<fixed<<setprecision(6)<<it->u1;
			cout<<" "<<it->Unit1<<" = ";
			if ( it->u2>=Max || it->u2<Min )
				cout<<science_notation(it, true);
			else 
				cout<<fixed<<setprecision(6)<<it->u2;
			cout<<" "<<it->Unit2<<endl;
			//
			if ( it->u1>=Max || it->u1<Min )
				f_txt<<science_notation(it, false);
			else 
				f_txt<<fixed<<setprecision(6)<<it->u1;
			f_txt<<" "<<it->Unit1<<" = ";
			if ( it->u2>=Max || it->u2<Min )
				f_txt<<science_notation(it, true);
			else 
				f_txt<<fixed<<setprecision(6)<<it->u2;
			f_txt<<" "<<it->Unit2<<endl;
		}
	}
	cout<<endl;
	f_txt.close();
}

void Conversion::print_facts()
{
	for (vector<fact>::const_iterator it = facts.begin(); it != facts.end(); ++it)
		cout<<"1 "<<it->Unit1<<" = "<<it->OneUnit1<<" "<<it->Unit2<<endl;
}

bool Conversion::find_str(vector<string> V, string Str)
{
	bool fl = true;
	for (vector<string>::const_iterator it = V.begin(); it != V.end(); ++it) {
		if (*it == Str) {
			fl = false;
			break;
		}
	}
	return fl;
}