#include "util.h"
#include "corector.h"

#include <iostream>

vector <prop> p;

int Levenshtein_dist(string s, dictionar::iterator it)
{
	int m = s.length();
	int n = it->first.length();
	string s2 = it->first;
	int frecv = it->second;
	int i, j;
	int d[m + 1][n + 1];
		
	for(i = 0; i <= m; ++i) {
		d[i][0] = i;
	}
	for (i = 0; i <= n; i++) {
		d[0][i] = i;
	}
	
	for(i = 1; i <= m; ++i) {
		for(j = 1; j <= n; ++j) {
			
			d[i][j] = minim(d[i - 1][j] + 1,
						 d[i][j - 1] + 1,
						 d[i - 1][j - 1] +
						 ((s.at(i - 1) == s2.at(j - 1)) ? 0 : 1)
						);
						
		}
		
		/* Verific daca distanta e mai mica */
		if ( (d[i][n] < p[i - 1].deviatie) || 
			/* Daca abatarea e egala atunci corectia indicata e cuvantul
			 * cu frecventa maxima
			 */
			((d[i][n] == p[i - 1].deviatie) && (p[i - 1].freq < frecv) ) 
			) {
			
			/* Corectia indicata va fi cea cu abatarea minima, frecventa
			 * maxima
			 */
			p[i - 1] = set_prop(s2, frecv, d[i][n]);
			
		}
	}
	
	return d[m][n];
}

void corecteaza_cuvant(string cuvant, dictionar dict) 
{
	dictionar::iterator iter;
	
	for(iter = dict.begin(); iter != dict.end(); ++iter) {
		Levenshtein_dist(cuvant, iter);
	}
}

vector < vector<prop> > calculeaza_candidati(string bun, int lung, dictionar dict)
{
	int i, j, k;
		
	vector < vector<prop> > m(lung + 1);
	p = new_vector_prop(lung + 1);
		
	for(i = 0; i < lung; ++i) {
		corecteaza_cuvant(bun.substr(i, lung), dict);
		k = 0;
		
		for(j = i; j <= lung; ++j) {
			
			m[j].resize(lung + 1);
			m[j][i].deviatie = p[k].deviatie;
			m[j][i].freq = p[k].freq;
			m[j][i].cuvant = p[k].cuvant;
			/* Restaureaza frecvente si deviatii pentru comparare cu un nou
			 * candidat posibil din dictionar
			 */
			p[k].freq = -1;
			p[k].deviatie = INF;
			++k;
		}
	}
	
	return m;
}

string calculeaza_solutie(string bun, int lung, dictionar dict)
{
	vector<sol> s;
	sol aux;
	int i, j;
	
	vector < vector<prop> > m = calculeaza_candidati(bun, lung, dict);
	
	aux = set_sol(m[0][0].cuvant, m[0][0].deviatie, m[0][0].freq, 1);
	s.push_back(aux);
	
	string tmp("");
	
	for(i = 1; i < lung; ++i) {
		aux = set_sol(m[i][0].cuvant, 
					m[i][0].deviatie, 
					m[i][0].freq, 
					1);
		s.push_back(aux);
		
		/* Se cauta eventuale solutii mai bune */
		for(j = 0; j < i; ++j) {
			/* Exista o solutie cu abatere mai mica? */
			if(s[j].deviatie <= s[i].deviatie) {
				tmp = s[j].corectie + " " + m[i][j + 1].cuvant;
				if ( /* Verifica daca solutia are abatere mai mica */
				    (m[i][j + 1].deviatie + s[j].deviatie < s[i].deviatie) 
				    ||
					/* Altfel verific daca are cumva mai putine cuvinte */
					((m[i][j + 1].deviatie + s[j].deviatie == s[i].deviatie
					 ) && 
					  (s[j].numar_cuvinte + 1 < s[i].numar_cuvinte)
					) ||
					 
					/* Altfel verific daca are frecventa totala maxima */
					((m[i][j + 1].deviatie + s[j].deviatie == s[i].deviatie
					 ) && (s[j].numar_cuvinte + 1 == s[i].numar_cuvinte) && 
					 (s[i].freq < m[i][j + 1].freq + s[j].freq)) ||
					
					/*Altfel se alege cel minim lexicografic */
					((m[i][j + 1].deviatie + s[j].deviatie == s[i].deviatie
					 ) && 
					(s[j].numar_cuvinte + 1  == s[i].numar_cuvinte) && 
					(s[i].freq == m[i][j + 1].freq + s[j].freq) && 
					s[i].corectie.compare(tmp) > 0
					) 
				) {
					/* Daca e TRUE la una din cele de mai sus, am gasit o
					 * solutie mai buna si o retinem
					 */
					s[i] = set_sol(tmp, 
								s[j].deviatie + m[i][j + 1].deviatie,
								s[j].freq + m[i][j + 1].freq,
								s[j].numar_cuvinte + 1
								);
				}
				     
				
			}
		}
	}
	
	return s[lung - 1].corectie;
}


sol set_sol(string str, int dev, int freq, int nr_cuv)
{
	sol s;
	
	s.corectie = str;
	s.deviatie = dev;
	s.freq = freq;
	s.numar_cuvinte = nr_cuv;
	
	return s;
}
