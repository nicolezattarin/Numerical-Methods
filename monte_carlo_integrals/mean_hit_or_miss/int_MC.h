#ifndef __integrale_mc_h__
#define __integrale_mc_h__

#include "randomgen.h"
#include "funzioni.h"

class integrale_mc {
public:
    integrale_mc (unsigned int seed){m_rand = new randomgen(seed);};
                    //uso il costruttore di randomgen

	double int_media (double a, double b, funzionebase* f, int n_punti);
	double int_HoM (double a, double b, double fmax, funzionebase* f, int punti);
    
private: 
    randomgen* m_rand; //la classe deve contenere un generatore di numeri casuale,
    //il generatore viene costruito una volta sola e mi fornisce un valore sempre diverso,
    //se lo costruissi nei metodi verrebbe costruito sempre con lo stesso seed e i numeri
    //generati sarebbero sempre gli stessi

};

#endif
