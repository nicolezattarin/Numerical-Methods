#include "randomgen.h"

double randomgen::rand(){
    
    int n = (m_a * m_seed + m_c) % (m_m); //creo n, un numero tra 0 e m-1
    m_seed = static_cast<unsigned int>(n);
//    aggiorno il valore di seed,
//    che è un membro privato della classe randomgen
    return static_cast<double >(n)/(m_m);
};

double randomgen::uniforme(double min, double max){
    return min + (max-min) * rand(); //traslazione nell'intervallo voluto
};

//metodo della funzione inversa
double randomgen::esponenziale(double lambda){
    return -1./(lambda)* log(1-rand());
};

//metodo della funzione inversa: Integro gauss passando in due
//variabili e cambiando in coordinate polari
double randomgen::gauss(double mean, double sigma){
    double s = rand();
    double t = rand();
    double x = sqrt(-2*log(s))*cos(2.* M_PI*t);
//fino a qui ho calcolato una gaussiana centrata in zero
    return mean + x * sigma; // traslo e dilato
};

//Gauss con Accept reject
double randomgen::gauss_AR (double mean, double sigma, double a, double b){
    bool flag = true;
    double y,x,f;
    while (flag){
        y = (1./(sigma * sqrt(2*M_PI))) * rand(); //genero y tra 0 e il massimo della gaussiana
        x =  a + (b-a) * rand(); //Genero x nell'intervallo a,b
        f = (1./(sigma * sqrt(2*M_PI)))* exp( -pow((x-mean),2) /(2*sigma*sigma)); //calcolo il valore vero della funzione nel punto corrispondente alla x generata
        if(f>y) flag = false; //verifico che la y sia minore del valore assunto dalla funzione
}
    return x; //x sarà distribuito comme f
};
