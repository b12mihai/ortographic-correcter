#include <iostream>
#include "util.h"
#include "corector.h"

int main()
{
	dictionar dict = get_from_file();
	int i, j, k;
	
	string input = citeste_termeni();
	string bun = remove_white_space(input);
	int lung = bun.length();
	
	cout << calculeaza_solutie(bun, lung, dict) << endl;
	
	return 0;
}
