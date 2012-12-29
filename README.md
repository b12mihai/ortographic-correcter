Corector Ortrografic
=====================

O tema din cadrul cursului de Proiectarea Algoritmilor

Descriere funcții
==================

A se vedea comentariile scrise prin cod, în fișierele .h.
În cadrul implementărilor sunt comentarii pe anumite bucăți de cod. 

Distanța de editare
====================

Pentru corectarea unui singur cuvânt folosind dicționarul, am ales algoritmul
Damerau-Levenshtein [1] pentru calculul distanței de editare. Respectând 
indicațiile din temă am luat doar cele trei operații elementare:

	* inserarea unui caracter oriunde în șir
	* ștergerea oricărui caracter din șir
	* înlocuirea unui caracter cu orice alt caracter

Cea de-a patra menționată la [1], transpoziția, nu a fost luată în calcul. 

Fie două șiruri x = x_1 x_2 ... x_m și y = y_1 y_2 ... y_n cu strlen(x) = m și
strlen(y) = n. Se construiește o matrice d de (m + 1) linii și (n + 1) coloane
cu următoarea semnificație: d[i][j] = distanța de editare dintre șirurile 
x_1 x_2 ... x_j și y_1 y_2 ... y_i.

Linia 0 se inițializează cu valorile 0, 1, 2, ... , m (pentru a transforma
șirul x_1 x_2 ... x_j în stringul vid e nevoie de j operații de ștergere)

Coloana 0 se inițializează cu 0, 1, 2, ... , n (pentru a transforma
stringul vid în y_1 y_2 ... y_i e nevoie de i operații de inserare)

Pentru a obține distanța de editare între două cuvinte x_1 x_2 ... x_j și 
y_1 y_2 ... y_i avem 3 posibilități:

1)  dacă x_j == y_i atunci nu e nevoie de nici o transformare și
atunci putem avea d[i][j] = d[i - 1][j - 1]. Dacă cumva x_j != y_i atunci 
x_j se înlocuiește cu y_i și putem avea d[i][j] = d[i - 1][j - 1] + 1

2) y_1 y_2 ... y_{i - 1} e obținut din x_1 x_2 ... x_j prin
d[i - 1][j] operații elementare => y_1 y_2 ... y_i e obținut din x_1 x_2 ... x_j
prin d[i - 1][j] + 1 operații elementare (dacă ultima din ele e inserare)

3) numărul minim de operații pentru a obține y_1 y_2 ... y_i din 
x_1 x_2 ... x_{j - 1} este d[i][j - 1] => y_1 y_2 ... y_i e obținut din
x_1 x_2 ... x_j prin d[i][j - 1] + 1 operații elementare (dacă ultima din ele
este ștergere)

Notând diff(i, j) = if x_j == y_i then 0 else 1 rezultă formula folosită în
implementare:

	d[i][j] = min{1 + dist[i - 1][j], 1 + d[i][j - 1], diff(i, j) + d[i - 1][j - 1]}

Complexitate: 

	O(m * n)

Algorimtul, ideile și complexitatea au fost extrase și din [2]

În plus, în implementare, rețin într-un vector proprietățile corecturii posibile
a șirului inițial: frecvența și abaterea obținută din matricea d. 

După ce se apelează funcția corecteaza_cuvant care iterează pe tot dicționarul
pentru a găsi corecții ale cuvântului dat ca argument, vectorul de proprietăți
va fi actualizat cu acele soluții candidat care au abatere minimă și frecvență 
maximă. 

Abordarea algoritmică a problemei
=================================

Toți acești candidați din vectorul calculat cu distanța de editare, cu tot cu 
proprietățile lor, vor fi reținuți într-o matrice, pe baza căreia se face 
corectura. Ideea este că în acea matrice, doar sub diagonala principală se vor
afla candidații.

Cum se calculează matricea de candidați? Se șterg toate spațiile, așa cum e 
sugerat și în enunțul temei și apoi la fiecare pas este șters primul caracter
din stringul astfel obținut și pentru el rezultă un vector de candidați care
reprezintă o posibilă corectură a acestui string. Toți aceștia sunt memorați.
Iată un exemplu pentru error free text (cuvantul original si fiecare cuvant
cu care calculeaza distanta de editare):

	errorfreetext---->a 1   or 1   era 1   error 1   error 0   error 1   error 2   error 3   error 4   correct 5   correct 6   correct 7   enforcement 7    INF   
	rrorfreetext---->a 1   or 1   pro 1   error 1   roof 2   proper 3   more 4   free 4   correct 4   correct 5   correct 6   agreement 7   enforcement INF   
	rorfreetext---->a 1   to 1   for 1   roof 1   roof 2   more 3   free 3   correct 3   correct 4   correct 5   agreement 6   agreement INF   
	orfreetext---->of 1   or 0   of 1   of 2   rare 2   free 2   free 3   free 4   arrested 4   agreement 5   agreement INF   
	rfreetext---->a 1   of 1   of 2   rare 1   free 1   free 2   free 3   free 4   agreement 4   agreement INF   
	freetext---->of 1   for 1   are 1   free 0   free 1   free 2   free 3   greatest 3   agreement INF   
	reetext---->a 1   re 0   see 1   feet 1   feet 2   better 3   recent 3   greatest INF   
	eetext---->a 1   he 1   get 1   pete 1   peter 2   text 2   recent INF   
	etext---->a 1   et 0   eye 1   even 2   text 1   text INF   
	text---->a 1   the 1   tax 1   text 0   text INF   
	ext---->a 1   sex 1   next 1   text INF   
	xt---->a 1   it 1   next INF   
	t---->a 1   it INF   

Matricea de candidați este:

	a             
	or a            
	era or a           
	error pro to of          
	error error for or a         
	error roof roof of of of        
	error proper roof of of for a       
	error more more rare rare are re a      
	error free free free free free see he a     
	correct correct correct free free free feet get et a    
	correct correct correct free free free feet pete eye the a   
	correct correct correct arrested free free better peter even tax sex a  
	enforcement agreement agreement agreement agreement greatest recent text text text next it a 

Observație: dacă inputul este un singur cuvânt (misspelled sau corect dat) care
poate fi găsit în dicționar, acea matrice va avea pe ultima linie, prima coloană
chiar varianta corectă a cuvântului.

Din păcate din cauza abordării cu programare dinamică a căutării soluției se
întâmplă următorul fenomen interesant pentru inputul sloution

	[mihai@blackhole:]$ make run
	./tema1pa
	sloution 

Matricea de candidați este:           
	a								
	so	a							
	so	to	of						
	slow	lou	of	a					
	slot	out	out	it	a				
	south	out	out	to	to	i			
	south	louis	out	to	to	in	of		
	solution	solution	option	union	lion	in	on	a	

În matrice, la coordonatele line = strlen(input), column = 0, 
se va găsi solution, care, în opinia mea, e soluția mai potrivită. 

Totuși soluția finală este: slot i on, pentru că intră în joc acel algoritm care 
încearcă să pună spații. 

Altfel, dacă stringul de intrare va avea mai multe cuvinte, va trebui sa căutăm
în matricea de candidați diverse potriviri. 

În funcția calculeaza_solutie, pentru un string ale cărui spații albe au fost
șterse, dar ordinea caracterelor din șirul original păstrată se caută
introducerea spațiilor albe conform specificațiilor din temă. 

Exemplu tot pentru "error free text" ca input (fără ghilimele):

	"a" "or" "era" "error" "error" "error" "error for" "error are" "error free" 
	"error free" "error free the" "error free tax" "error free text" 

Concluzie: pe parcursul desfășurării algoritmului încearcă să rețină primele
elemente de pe prima coloană a matricei de candidați, constată că nu sunt bune
și ajunge la ”error”, care soluție validă. Acesta rămâne, preț de 6 iterații pe
liniile matricei de candidați (error e între liniile 3 și 6 pe prima coloană), 
sunt calculate abaterile, frecvențele și se constată că error trebuie păstrat, 
deci se va încerca să i se adauge un alt cuvânt. Sunt căutat în linia pe care
se află error și apoi în liniile de sub ultima linie în care se află error. O
dată găsit free (care ținut minte că are abaterea minimă și frecvența maximă) 
și astfel se caută pentru ultimul cuvânt, repetându-se procesul descris mai sus. 


Link-uri și alte referințe
==========================

[1] http://en.wikipedia.org/wiki/Damerau%E2%80%93Levenshtein_distance

[2] S. Dasgupta, C.H. Papadimitriou, and U.V. Vazirani, "Algorithms", 2006

[3] Thomas Cormen ș.a. - Introduction to algorithms pp 406-407

[4] Peter Norvig's spell checker: http://norvig.com/spell-correct.html

[5] Hack Peter Norvig's spell checker to correct a phrase:
http://stackoverflow.com/questions/5398722/using-the-levenshtein-distance-in-a-spell-checker

[6] http://jeremykun.wordpress.com/2011/12/19/metrics-on-words/

[7] http://jeremykun.wordpress.com/2012/01/15/word-segmentation/

