#include "TApplication.h"
#include "TH1F.h"
#include "TF1.h"

#include "TCanvas.h"
#include "TGraph.h"
#include <fstream>
#include <iostream>
using namespace std;

int main(){
    
     
    //    =========================================================================
    //                                 METODO HIT OR MISS
    //    =========================================================================

    double temp = 0.;
    int n_integrali = 10000; //numero di integrali contenuti in ogni file
    
    //file da cui legegre
    ifstream f_10E2HOM ("f_10E2HOM.dat");
    ifstream f_10E3HOM ("f_10E3HOM.dat");
    ifstream f_10E4HOM ("f_10E4HOM.dat");
    ifstream f_10E5HOM ("f_10E5HOM.dat");
    ifstream f_10E6HOM ("f_10E6HOM.dat");
    if( !f_10E2HOM.good() || !f_10E3HOM.good() || !f_10E4HOM.good() || !f_10E5HOM.good() || !f_10E6HOM.good() ){
        cerr << "Errore nell'apertura dei file " << endl;
        return 1;
    }
//ISTOGRAMMI
    TApplication app ("myapp", 0, 0);
    TCanvas* c = new TCanvas ("c", "Distribuzione integrali: metodo Hit or Miss", 1800,1200);
    c->Divide(2,3);

    TH1F* h1 = new TH1F ("h1","Distribuzione con 100 punti",100,1.5,2.5);
    TH1F* h2 = new TH1F("h2","Distribuzione con 1000 punti",100,1.8,2.2);
    TH1F* h3 = new TH1F("h3","Distribuzione con 10000 punti",100,1.93,2.07);
    TH1F* h4 = new TH1F("h4","Distribuzione con 100000 punti",100,1.98,2.02);
    TH1F* h5 = new TH1F("h5","Distribuzione con 1000000 punti",100,1.99,2.01);
    
    //
    h1->StatOverflows(kTRUE);
    h2->StatOverflows(kTRUE);
    h3->StatOverflows(kTRUE);
    h4->StatOverflows(kTRUE);
    h5->StatOverflows(kTRUE);

    //lettura da tutti i file e riempimento istogrammi
    for (int i = 0; i<n_integrali; ++i ){
        f_10E2HOM >> temp;
        h1->Fill(temp);
        f_10E3HOM >> temp;
        h2->Fill(temp);
        f_10E4HOM >> temp;
        h3->Fill(temp);
        f_10E5HOM >> temp;
        h4->Fill(temp);
        f_10E6HOM >> temp;
        h5->Fill(temp);
    }
    //Disegno gli istogrammi
        c->cd(1);
        h1->GetXaxis()->SetTitle("Valore dell'integrale");
        h1->GetYaxis()->SetTitle("Numero di integrali");
        h1->Draw();
   
        c->cd(2);
        h2->GetXaxis()->SetTitle("Valore dell'integrale");
        h2->GetYaxis()->SetTitle("Numero di integrali");
        h2->Draw();
        
        c->cd(3);
        h3->GetXaxis()->SetTitle("Valore dell'integrale");
        h3->GetYaxis()->SetTitle("Numero di integrali");
        h3->Draw();
    
        c->cd(4);
        h4->GetXaxis()->SetTitle("Valore dell'integrale");
        h4->GetYaxis()->SetTitle("Numero di integrali");
        h4->Draw();
    
        c->cd(5);
        h5->GetXaxis()->SetTitle("Valore dell'integrale");
        h5->GetYaxis()->SetTitle("Numero di integrali");
        h5->Draw();
    
    // chiudo file
        f_10E2HOM.close();
        f_10E3HOM.close();
        f_10E4HOM.close();
        f_10E5HOM.close();
        f_10E6HOM.close();
        
    //    Andamento DELL'ERRORE: ricavo l'errore
        TCanvas* c1 = new TCanvas ("c1", "Andamento dell'errore", 1200,400);
        c1->Divide(2,1);
        c1->cd(1);
        c1->cd(1)->SetLogx();

    //grafico dell'errore in funzione di N.
        TGraph* errori_HOM = new TGraph;
        errori_HOM->SetTitle("Metodo Hit or Miss");
        errori_HOM->SetPoint(0, 100, h1->GetStdDev()); //chiedo la devstd degli istogrammim
        errori_HOM->SetPoint(1, 1000, h2->GetStdDev());
        errori_HOM->SetPoint(2, 10000, h3->GetStdDev());
        errori_HOM->SetPoint(3, 100000, h4->GetStdDev());
        errori_HOM->SetPoint(4, 1000000, h5->GetStdDev());
    
        errori_HOM->GetXaxis()->SetTitle("Numero di punti");
        errori_HOM->GetYaxis()->SetTitle("Errore");
        errori_HOM->SetMarkerStyle(20);
        errori_HOM->Draw("APL");

    
    //    FIT
    TF1* f1 = new TF1("f1","[0]/pow(x,0.5)",0.,1000000.);
    f1->SetParameter(0,1);
    errori_HOM->Fit("f1");
    f1->Draw("same");
    double k_HOM = f1->GetParameter(0);
    
    // FISSATA LA PRECISIONE CALCOLO IL NUMERO DI INTEGRALI DA CALCOLARE
    //trovo k dal fit e da questo calcolo il numero N di punti necessari per
    //avere una precisione sigma come N = k^2/sigma^2
    double sigma_HOM = 0.001; //scelgo la precisione voluta
    int n_punti_originari = 10000;
    int N_punti_necessari_HOM = static_cast<int>( pow(k_HOM,2)/pow(sigma_HOM,2));
    
    cout << "Con il metodo Hit or Miss sono necessari " << N_punti_necessari_HOM << " per avere una precisione di " << sigma_HOM << endl;

    
    
     
    //    =========================================================================
    //                                 METODO MEDIA
    //    =========================================================================

        temp = 0.;

        //file da cui legegre
        ifstream f_10E2Mean ("f_10E2Mean.dat");
        ifstream f_10E3Mean ("f_10E3Mean.dat");
        ifstream f_10E4Mean ("f_10E4Mean.dat");
        ifstream f_10E5Mean ("f_10E5Mean.dat");
        ifstream f_10E6Mean ("f_10E6Mean.dat");
        if( !f_10E2Mean.good() || !f_10E3Mean.good() || !f_10E4Mean.good() || !f_10E5Mean.good() || !f_10E6Mean.good() ){
            cerr << "Errore nell'apertura dei file " << endl;
            return 1;
        }
    //ISTOGRAMMI
        TH1F* k1 = new TH1F("k1","Distribuzione con 100 punti",100,1.4,2.6);
        TH1F* k2 = new TH1F("k2","Distribuzione con 1000 punti",100,1.8,2.2);
        TH1F* k3 = new TH1F("k3","Distribuzione con 10000 punti",100,1.95,2.05);
        TH1F* k4 = new TH1F("k4","Distribuzione con 100000 punti",100,1.985,2.02);
        TH1F* k5 = new TH1F("k5","Distribuzione con 1000000 punti",100,1.996,2.004);
        
        k1->StatOverflows(kTRUE);
        k2->StatOverflows(kTRUE);
        k3->StatOverflows(kTRUE);
        k4->StatOverflows(kTRUE);
        k5->StatOverflows(kTRUE);
    
        for (int i = 0; i<n_integrali; ++i ){
            f_10E2Mean >> temp;
            k1->Fill(temp);
            f_10E3Mean >> temp;
            k2->Fill(temp);
            f_10E4Mean >> temp;
            k3->Fill(temp);
            f_10E5Mean >> temp;
            k4->Fill(temp);
            f_10E6Mean >> temp;
            k5->Fill(temp);
        }
            TCanvas* c2 = new TCanvas ("c2", "Distribuzione integrali: metodo della media", 1800,1200);
            
            c2->Divide(3,2);
            c2->cd(1);

            k1->GetXaxis()->SetTitle("Valore dell'integrale");
            k1->GetYaxis()->SetTitle("Numero di integrali");
            k1->Draw();
        
            c2->cd(2);
            k2->GetXaxis()->SetTitle("Valore dell'integrale");
            k2->GetYaxis()->SetTitle("Numero di integrali");
            k2->Draw();
            
            c2->cd(3);
            k3->GetXaxis()->SetTitle("Valore dell'integrale");
            k3->GetYaxis()->SetTitle("Numero di integrali");
            k3->Draw();
        
            c2->cd(4);
            k4->GetXaxis()->SetTitle("Valore dell'integrale");
            k4->GetYaxis()->SetTitle("Numero di integrali");
            k4->Draw();
        
            c2->cd(5);
            k5->GetXaxis()->SetTitle("Valore dell'integrale");
            k5->GetYaxis()->SetTitle("Numero di integrali");
            k5->Draw();
        
            f_10E2Mean.close();
            f_10E3Mean.close();
            f_10E4Mean.close();
            f_10E5Mean.close();
            f_10E6Mean.close();
            
        //    ERRORE DELL'ERRORE
            TGraph *errori_mean = new TGraph;
            errori_mean->SetTitle("Metodo della media");
            c1->cd(2)->SetLogx();

            errori_mean->SetPoint(0, 100, k1->GetStdDev());
            errori_mean->SetPoint(1, 1000, k2->GetStdDev());
            errori_mean->SetPoint(2, 10000, k3->GetStdDev());
            errori_mean->SetPoint(3, 100000, k4->GetStdDev());
            errori_mean->SetPoint(4, 1000000, k5->GetStdDev());
        
            errori_mean->GetXaxis()->SetTitle("Numero di punti");
            errori_mean->GetYaxis()->SetTitle("Errore");
            errori_mean->SetMarkerStyle(20);
            c1->cd(2);
            errori_mean->Draw("APL");
        
        //    FIT
        TF1* f2 = new TF1("f2","[0]/pow(x,0.5)",0.,1000000.);
        f2->SetParameter(0,1);
        errori_mean->Fit("f2");
        f2->Draw("same");
        double k_mean = f2->GetParameter(0);
        
        // FISSATA LA PRECISIONE CALCOLO IL NUMERO DI INTEGRALI DA CALCOLARE
        //trovo k dal fit e da questo calcolo il numero N di punti necessari per
        //avere una precisione sigma come N = k^2/sigma^2
        double sigma_mean = 0.001; //scelgo la precisione voluta
        int N_punti_necessari_mean = static_cast<int>( pow(k_mean,2)/pow(sigma_mean,2));
    
        cout << "Con il metodo della media sono necessari " << N_punti_necessari_mean << " per avere una precisione di " << sigma_mean << endl;
    
    //FACCIO PARTIRE ROOT
    app.Run();
    
    return 0;
}
