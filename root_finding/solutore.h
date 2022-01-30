
#ifndef __solutore_h__
#define __solutore_h__

#include <iostream>
#include "funzionebase.h"
#include <cmath>

//=====================================================
//                  Classe astratta
//=====================================================

class solutore {
public:
	virtual double cercazeri (double a, double b, const funzionebase* f) = 0;
    
	void set_precision (double epsilon) {m_prec = epsilon;}
    double get_precision () const {return m_prec;}

	void set_a (double a){m_a = a;}
	void set_b (double b){m_b = b;}
    
private:
	double m_a, m_b, m_prec;
	const funzionebase* m_f;
};


//=====================================================
//                  BISEZIONE
//=====================================================

class bisezione: public solutore {
public:

	bisezione(unsigned int it, double precision) {
        n_iterazioni = it;
        set_precision (precision);
    }
    
    void SetN (unsigned int);
	virtual double cercazeri(double a, double b, const funzionebase* f);
    
protected:
	unsigned int n_iterazioni;
};

//=====================================================
//              Funzione per capire segno
//=====================================================

int segno (double);

#endif
