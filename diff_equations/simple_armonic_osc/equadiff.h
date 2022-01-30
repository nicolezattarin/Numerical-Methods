#ifndef __equazionedifferenzialebase_h__
#define __equazionedifferenzialebase_h__

#include "fvect.h"
#include "myalgebra.h"

using namespace std;

class equazionedifferenzialebase {
public:
   virtual vector<double> passo (const vector<double> &x, double t, double h, funzionevettorialebase* v) const = 0;
    
};

class eulero: public equazionedifferenzialebase {
 
public:
    virtual vector<double> passo (const vector<double> &x, double t, double h, funzionevettorialebase* v) const;
};

class runge_kutta: public equazionedifferenzialebase {

public:
    virtual vector<double> passo (const vector<double> &x, double t, double h, funzionevettorialebase* v) const;
};

#endif // __equazionedifferenzialebase_h__

