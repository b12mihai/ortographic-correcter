#include <fstream>
#include <cstring>
#include "util.h"

int minim(int a, int b, int c)
{
	return MINIM(MINIM(a, b), c);
}

string remove_white_space(string str)
{
	string str2(" ");
	size_t found;

	while((found = str.find(str2)) != string::npos)
		str.erase(found, str2.length());

	return str;
}

dictionar get_from_file()
{
	string cuv;
	int frecv;
	dictionar d;
	FILE *f;
	ifstream fin;

	fin.open(DICTFILE, ifstream::in);

	while(fin >> cuv >> frecv) {
		d.insert(pair<string, int>(cuv, frecv));
	}

	fin.close();

	return d;
}

prop set_prop(string cuvant, int freq, int deviatie)
{
	prop newstruct;
	newstruct.deviatie = deviatie;
	newstruct.freq = freq;
	newstruct.cuvant = cuvant;
	return newstruct;
}

vector<prop> new_vector_prop(int dim)
{
	vector<prop> p;
	prop tmp;
	int i;
	
	for(i = 0; i < dim; ++i) {
		tmp = set_prop("", -1, INF);
		p.push_back(tmp);
	}
	
	return p;
}

string citeste_termeni()
{
	char in[INSTR_SIZE];
	fgets(in, INSTR_SIZE, stdin);
	in[strlen(in) - 1] = '\0';

	return string(in);
}

