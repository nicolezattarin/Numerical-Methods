#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

#ifndef __funzione_h__
#define __funzione_h__

class funzionebase{
public:
	virtual double eval (double x) const = 0;
};

class seno: public funzionebase {
public:
	virtual double eval (double x) const;
};

class f1: public funzionebase {
public:
    virtual double eval (double x) const{
        return exp(x)+exp(-x);
    }
};


#endif
