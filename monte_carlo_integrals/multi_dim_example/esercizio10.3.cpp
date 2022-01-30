#include "int_MC.h"
#include "TApplication.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TGraph.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
int main (){
    
 //PREDISPONGO LE VARIABILI
    double sigma = 0.01;
    double n_punti = 10000;
    int n_integrali = 10000;
    f1* myfunction = new f1; //creo la funzione
    integrale_mc* myint = new integrale_mc(2); //prende come arg il seed
    vector<double> a {1,2}; //estremo inferiore e superiore di integrazione
    vector<double> b {1,2};

//INTEGRALE CAMPIONE: N_VOLUTO = SIGMA_TEST^2 * N_TEST / SIGMA_VOLUTA^2
    
    //calcolo integrale a con n_punti e ne estraggo la SD
    TApplication app ("myapp",0,0);
    vector <double> x(2);
    
    //int_media(a, b, funzione, punti)
    TH1F* h1 = new TH1F("h1", "Distribuzione degli integrali", 100, 10, 11);
    for (int i = 0; i<n_integrali; ++i) h1->Fill(myint->int_media(a, b, myfunction, n_punti));
    int N_nota_precisione = pow(h1->GetStdDev(),2) * n_punti / pow(sigma,2);
    h1->StatOverflows(kTRUE);
    
    //OUTPUT NUERO DI PUNTI NECESSARI
    cout << "Per avere una precisione di " << sigma
         << " è necessario integrare con " << N_nota_precisione
         << " punti" << endl;
    
    
    // CALCOLO GLI INTEGRALI DI PRECISIONE FISSATA
    
    TCanvas* c = new TCanvas("c", "DIstribuzione con data precisione", 600,400);
    TH1F* h = new TH1F("h", "Distribuzione degli integrali", 100, 10.2, 10.3);
    for (int i = 0; i<n_integrali; ++i) {
        h->Fill(myint->int_media(a, b, myfunction, N_nota_precisione));
        if (i % 500 == 0) cout << "Ho calcolato " << i << " integrali" << endl;
    }
    h->StatOverflows(kTRUE);

    h->GetXaxis()->SetTitle("Valore dell'integrale");
    h->GetYaxis()->SetTitle("Numero di integrali");
    h->Draw();
    
    delete myfunction;
    delete myint;

    app.Run();
    return 0;
}
