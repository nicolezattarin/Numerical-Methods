
#ifndef __funzionevettoriale_h__
#define __funzionevettoriale_h__

#include "myalgebra.h"
#include <cmath>
using namespace std;

class funzionevettorialebase {
public:
    virtual vector<double> eval (const vector<double> &x, double t) const = 0;
    // quando la implemento mi restituisce il
    // valore della derivata in x al tempo t
};

class oscillatore_semplice: public funzionevettorialebase {
 
public:
    oscillatore_semplice(double w) { omega = w;};
    virtual vector<double> eval (const vector <double> &x, double t) const;
    
private:
    double omega;
};

class pendolo: public funzionevettorialebase {
 
public:
    pendolo(double l) { m_l = l;};
    virtual vector<double> eval (const vector <double> &x, double t) const;
    
private:
    double m_l;
};

#endif // funzionevettorialebase
