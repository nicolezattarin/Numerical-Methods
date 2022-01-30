#include <iostream>
#include <cmath>
#include <iomanip>

#include "funzionebase.h"
#include "solutore.h"

using namespace std;

int main (){

    
    double precision = pow(10,-6);
    double n_iterazioni = 1000;
    int cifre_significative = -log10 ( precision );

	f_tan* myfunction = new f_tan;
	bisezione* mycercazeri = new bisezione( n_iterazioni, precision ); // il costruttore di bisezioneil numero di iterazioni e precisione


    for (int i = 1; i<=20; i++){
	cout << "Soluzione nell'intervallo (" << i <<"π, "<<i << "π + π/2 ):  " << setprecision(cifre_significative) << mycercazeri->cercazeri(i*M_PI, i*M_PI+M_PI/2, myfunction) << endl;
    }
    delete myfunction;
    delete mycercazeri;
    
	return 0;
}
