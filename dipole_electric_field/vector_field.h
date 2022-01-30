
#ifndef __vector_field_h__
#define __vector_field_h__

#include "position.h"

class vector_field: public position {
    
public:
    
    vector_field (const position&); //costruttore default
    vector_field(const position&, double fx, double fy, double fz); //const con arg e position
    vector_field(double x, double y, double z, double fx, double fy, double fz); //const con arg senza position
    vector_field(const vector_field& v); //copy constructor
    ~vector_field(){}

    //overloading opeatore +
    vector_field& operator+= (const vector_field&); //ritorna un puntatore a sè stesso
    vector_field operator+ (const vector_field&) const; //somma il
//    corrente con quello passato come arg, la somma viene assegnata a
//    un terzo vettore costruito appositamente

    //accesso e modifica delle componenti
    double GetFx() const;
    double GetFy() const;
    double GetFz() const;
    void SetFx(double x);
    void SetFy(double y);
    void SetFz(double z);
    
    double module() const; //lunghezza del vettore

    
private:
    double m_fx, m_fy, m_fz; // coordinate del vettore
    //position m_x m_y m_z contiene il punto di applicazione del vettore

};

#endif

