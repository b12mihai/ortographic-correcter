#ifndef __CORECTOR_H__
#define __CORECTOR_H__

#pragma once

#include "util.h"

/** Structura utila pentru solutionarea termenilor fara spatii/spatii aiurea
	(creata conform descrierii din cerinta pentru tratarea celor 4 cazuri)
 */
struct sol {
	string corectie; /**< o posibila corectie a cuvantului. Rezultat final */
	int deviatie; /**< abatarea totala minima */
	int freq; /**< frecventa totala maxima */
	int numar_cuvinte; /**< numar minim de cuvinte */
};

/*! \brief creaza o structura solutie noua cu parametrii dati
 * pentru a nu fi nevoie sa fac de fiecare data 4 asocieri.
 * \param str cuvant
 * \param dev deviatie/abatare
 * \param freq frecventa
 * \param nr_cuv numar de cuvinte
 * \return o struct sol noua cu parametrii de mai sus
 */
sol set_sol(string str, int dev, int freq, int nr_cuv);


/*! \brief Calculeaza distanta de editare cu algoritmul
 * Damerau-Levenshtein
 * \param s cuvantul care trebuie corectat
 * \param it intrarea din dictionar care reprezinta un cuvant valid si 
 * frecventa acestuia in dictionar
 * \return distanta de editare 
 */
int Levenshtein_dist(string s, dictionar::iterator it);
 
/*! \brief Cauta dupa corectii in dictionarul dict ale lui cuvant
 * Atunci cand se doreste corectarea unui singur cuvant scris gresit, 
 * se pot folosi dictionarul si distanta de editare. 
 * \param cuvant cuvantul care trebuie corectat
 * \param dict maparea string-frecventa care reprezinta dictionarul
 * \return void
 */ 
void corecteaza_cuvant(string cuvant, dictionar dict);


/*! \brief Aici se construieste matricea de candidati cu toate proprietatile 
 * lor. Sub diagonala principala se retin cei care candideaza pentru pozitia 
 * de solutie valida
 * \param input_fara_spatii - Sirul de intrare cu spatiile sterse
 * \param len - lungimea sirului de intrare
 * \param dict - maparea cuvant-frecventa din dictionar
 * \return matricea de candidati
 */
vector < vector<prop> > calculeaza_candidati(string input_fara_spatii, 
									int len, 
									dictionar dict);

/*! \brief Calculeaza posibila corectie a stringului de intrare folosind 
 * rezultatele retinute din calculeaza_candidati
 * \param input_fara_spatii - Sirul de intrare cu spatiile sterse
 * \param len - lungimea sirului de intrare
 * \param dict - maparea cuvant-frecventa din dictionar
 * \return Corectura stringului de intrare.
 */
string calculeaza_solutie(string input_fara_spatii, 
					 int len, 
					 dictionar dict);

#endif
