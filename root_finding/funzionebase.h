#include <iostream>
#include <cmath>
using namespace std;

#ifndef __funzione_h__
#define __funzione_h__

class funzionebase{
public:
	virtual double eval (double x) const = 0;
};

class parabola: public funzionebase {
public:
	parabola();
	parabola(double a, double b, double c);
	~parabola();

	virtual double eval (double x) const;

	void setparameters (double _a, double _b, double _c);
	double getparameter_a () const;
	double getparameter_b () const;
	double getparameter_c () const;

private:
	double m_a;
	double m_b;
	double m_c;
};

class f_tan: public funzionebase {
    
public:
    virtual double eval (double x) const;
};


#endif
