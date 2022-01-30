#include "fvect.h"
#define g 9.81

    vector <double> oscillatore_semplice::eval (const vector <double> &x, double t) const{
    vector<double> result (x.size()); // creo un vettore con la
                                // stessa dimensione di quello passato
    
    result[0] = x[1];
    result[1] = - (omega * omega) * x[0];
    return result;
    
    //x contiene come prima coordinata x e come seconda v
    //ritorna un vector  (xpunto, vpunto) = (v, omega^2 x)
   // la seocnda componente di x diventa la prima del return
}

    vector<double> pendolo::eval ( const vector <double> &x,double t) const{
    vector<double> result(x.size()); // creo un vettore con la
                                   // stessa dimensione di quello passato
       
       result[0] = x[1];
       result[1] = - (g / m_l) * sin ( x[0] );
       return result;
       
       //x contiene come prima coordinata theta e come seconda omega
       //ritorna un vector  (thetapunto, omegapuntp)
      // la seocnda componente di x diventa la prima del return
}

