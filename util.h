#ifndef __UTIL_H__
#define __UTIL_H__

#pragma once

/* Altele simpatice pe http://graphics.stanford.edu/~seander/bithacks.html */
#define MAXIM(x, y) (x) ^ (((x) ^ (y)) & -((x) < (y)))
#define MINIM(x, y) (y) ^ (((x) ^ (y)) & -((x) < (y))) 

#define DICT_SIZE 8000
#define DENTRY_SIZE 33
#define INSTR_SIZE 65

#define DICTFILE "dict.txt"

#define INF 0x3f3f3f3f

#include <map>
#include <vector>
#include <string>

using namespace std;

typedef map<string, int> dictionar;

/** Proprietatile unui cuvant:
 */
struct prop {
	string cuvant; /**< cuvantul caruia ii sunt asociate proprietatile */
	int freq; /**< frecventa cuvantului din dictionar cu care acesta seamana */
	int deviatie; /**< abaterea fata de originalul din dictionar */
};

/** Variabila globala pentru memorarea proprietatilor candidatilor la solutia
 * finala 
 */
extern vector <prop> p;

/*! \brief creaza o structura proprietate noua cu parametrii dati
 * pentru a nu fi nevoie sa fac de fiecare data 3 asocieri.
 * \param str cuvant
 * \param dev deviatie/abatare
 * \param freq frecventa
 * \return o struct prop noua cu parametrii de mai sus
 */
prop set_prop(string cuvant, int freq, int deviatie);

/*! \brief Determina minimul a 3 numere intregi
 * folosind macro-ul MINIM
 */
int minim(int a, int b, int c);

/*! \brief Sterge toate spatiile albe dintr-un string 
 * \param str stringul ale carui spatii albe trebuie sterse. Nu va fi modificat
 * dupa apelul functiei
 * \return stringul initial fara nici un space 
 */
string remove_white_space(string str);

/*! \brief Aloca memorie si initializeaza un vector de structura 
 * cu niste date imposibil de intalnit pentru comparari
 * frecventa cu -1 si deviatia cu infinit
 * \param dim dimensiunea pentru care as vrea sa aloc aceasta memorie
 * \return vector cu proprietati string = "", freq = -1, abatare = INF
 */
vector<prop> new_vector_prop(int dim);

/*! \brief Memoreaza o mapare cuvant - frecventa din fisier cu structura ca a
 * lui dict.txt
 */
dictionar get_from_file();

/*! \brief Citeste sirul care trebuie corectat de la stdin = tastatura 
 * \return un obiect string, pe care il voi folosi mai departe
 */
string citeste_termeni();

#endif
