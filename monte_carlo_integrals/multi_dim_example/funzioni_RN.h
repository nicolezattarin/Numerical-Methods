
#ifndef __funzione_Rn_h__
#define __funzione_Rn_h__

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace std;

class funzionebase_Rn {
public:
	virtual double eval (const vector<double>& x) const = 0;
};

class f1: public funzionebase_Rn {
public:
    virtual double eval (const vector<double>& x) const;
};


#endif
