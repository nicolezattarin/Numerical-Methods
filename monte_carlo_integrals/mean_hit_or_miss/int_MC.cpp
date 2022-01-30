#include "int_MC.h"

double integrale_mc::int_media (double a, double b, funzionebase* f, int n_punti){
    //riceve in ingreso il numero di punti che voglio usare e un puntatore alla funzione di cui calcolare l'integrale(compatibile con i puntatori delle figlie)
    double sum = 0.;
    for(int i = 0; i< n_punti; i++){
        sum += f->eval(m_rand->uniforme(a,b));
    }
    return (fabs(b-a)*sum)/n_punti;
}

double integrale_mc::int_HoM (double a, double b, double fmax, funzionebase* f, int n_punti){
    //ha bisogno di sapere il massimo della funzione
    int n_hit = 0;
    int n_tot = 0;
    double y = 0.;
    double x = 0.;
    double f_x = 0.;

    for(int i = 0; i< n_punti; i++){
        n_tot ++;
        y = m_rand->uniforme(0,fmax);
        x = m_rand->uniforme(a,b);
        f_x = f->eval(x);
        if (f_x > y) n_hit ++;
    }
    return fabs(b-a) * fmax * (static_cast <double> (n_hit)/static_cast <double>(n_tot));
    
}
