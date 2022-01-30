#include "int_MC.h"
#include "TApplication.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TGraph.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
int main (){
 
    
    seno* mysin = new seno; //creo la funzione
    int n_punti= 100;//inizializzo il numero di punti
    int n_integrali = 10000;
    integrale_mc* myint = new integrale_mc(1); //prende come arg il seed
    
    //scrivo su file i risultati delgi integrali
    //myint->int_HoM(a, b, massimo della funzione, puntatore a funzionebase, numero di punti con cui calcolare l'integrale)
    
    
    for(int k = 2; k<=6; k++ ){
        string filename_HOM = "f_10E"+  to_string(k) + "HOM.dat";
        ofstream out_HOM (filename_HOM);
        
        string filename_mean = "f_10E"+  to_string(k) + "Mean.dat";
        ofstream out_mean (filename_mean);
        
        if( !out_HOM.good() || !out_mean.good() ){
            cerr << "Errore nell'apertura dei file " << endl;
            return -1;
        }
        
        cout << endl << "Sto calcolando " << n_punti << endl;

        for (int i = 0; i< n_integrali; i++){
            out_HOM << myint->int_HoM(0, M_PI, 1, mysin, n_punti) << endl;
            out_mean << myint->int_media(0, M_PI, mysin, n_punti) << endl;

               if (i % 1000 == 0) cout << "Ho calcolato " << i << " integrali" << endl;
               }
        
        n_punti = n_punti*10;
        out_HOM.close();
        out_mean.close();
    }

    delete mysin;
    delete myint;
    return 0;
}
