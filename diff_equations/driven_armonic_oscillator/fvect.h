
#ifndef __funzionevettoriale_h__
#define __funzionevettoriale_h__

#include "myalgebra.h"
#include <cmath>
using namespace std;



//==============================================
//               CLASSE MADRE
//==============================================

class funzionevettorialebase {
public:
    virtual vector<double> eval (const vector<double> &x, double t) const = 0;
    // quando la implemento mi restituisce il
    // valore della derivata in x al tempo t
};




//==============================================
//          OSCILLATORE SEMPLICE
//==============================================

class oscillatore_semplice: public funzionevettorialebase {
 
public:
    oscillatore_semplice(double w) { omega = w;};
    virtual vector<double> eval (const vector <double> &x, double t) const;
    
private:
    double omega;
};





//==============================================
//                   PENDOLO
//==============================================

class pendolo: public funzionevettorialebase {
 
public:
    pendolo(double l) { m_l = l;};
    virtual vector<double> eval (const vector <double> &x, double t) const;
    
private:
    double m_l;
};




//==============================================
//        OSCILLATORE CON FORZANTE
//==============================================

class oscillatore: public funzionevettorialebase {
 
public:
    oscillatore(double omega, double omega_0, double gamma)
    { m_omega_0 = omega_0; m_omega = omega; m_gamma = gamma;};
    
    virtual vector<double> eval (const vector <double> &x, double t) const;
    
    void SetOmega (double omega) {m_omega = omega;}
    double GetOmega () {return m_omega;}
    double GetGamma (){return m_gamma;}

private:
    double m_omega_0;
    double m_gamma;
    double m_omega;

};
#endif // funzionevettorialebase
