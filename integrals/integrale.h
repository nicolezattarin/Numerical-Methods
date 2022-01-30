#ifndef __integrale_h__
#define __integrale_h__

#include "funzioni.h"

class integrale {
public:
	integrale (double a, double b, const funzionebase* f);
    integrale (double a, double b, const funzionebase* f, double prec);
    //conviene inserire la precisione nel costruttore per
    //poter far riferimento aòl valore contenuto nella classe

	double midpoint (int N);
    double midpoint(); //precisione
	double simpson (int N);
    double simpson (); //precisione 
    double trapezi_non_ottimizzata(); //precisione
    double trapezi (int N); //numero di passi
    double trapezi (); //ottimizzato con precisione

	double Geth(int N) const{ return ( abs(m_b-m_a) )/N;};
    
private: 
	double m_a, m_b; // estremi di integrazione
	double m_int; // integrale da restituire
    double m_passo_precedente; // nel metodo dei trapezi serve per memorizzare
                   // l'ultima approssimazione dell'integrale

	int m_segno; // positio se a<b
	double m_h; // passo
    double precision; //precisione desiderata
	const funzionebase* m_f; // funzione definita nella 
				// classe astratta, in modo che
				// possa definirla ogni volta

};

#endif
