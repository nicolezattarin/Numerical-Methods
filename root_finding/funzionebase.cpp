#include "funzionebase.h"

parabola:: parabola(double a, double b, double c){
	m_a = a;
	m_b = b;
	m_c = c;
	}
double parabola :: eval (double x) const{
	return m_a* x *x + m_b*x +m_c;
}

void parabola :: setparameters (double _a, double _b, double _c){
	m_a = _a;
	m_b = _b;
	m_c = _c;
}

double parabola :: getparameter_a ()const{ return m_a;};
double parabola :: getparameter_b ()const{ return m_b;};
double parabola :: getparameter_c ()const{ return m_c;};


double f_tan :: eval (double x) const {
    return sin(x) - x * cos(x);
}
