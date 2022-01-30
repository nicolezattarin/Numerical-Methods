#include "randomgen.h"
#include "TApplication.h"
#include "TH1F.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TGraph.h"
#include <iomanip>

using namespace std;
int main (int argc, char** argv){
    
    if (argc!= 3) {
        cout <<"Uso del programma " << argv[0] << "<N elementi di partenza>, <numero di elementi della serie su cui fare la somma>"<< endl;
        cout << "Si raccomanda di scegliere N minore o uguale a 1.000.000.000 " << endl;
        return 1;
    }
    TApplication app ("app", 0, 0);
    randomgen* mygen = new randomgen (1); //inserisco il numero di partenza
    int N_bins = 100;
    int n_serie = atof(argv[1]); //numero di elementi distribuiti unif in [0,1]
    int n_somma = atof(argv[2]); //numero di elementi su cui fare la somma
    int n_punti = n_serie /n_somma ; //numero di elementi della distribuzione delle somme

//    =========================================
//                limite centrale
//    =========================================
    TCanvas* c = new TCanvas ( "c" , "Distribuzioni", 1200, 800 );
    c->Divide(2,2);
    
    TH1F* h1 = new TH1F ( "h1" , "Distribuzione delle somme", N_bins, 0, n_somma);
    TH1F* h2 = new TH1F ( "h2" , "Distribuzione dei numeri", N_bins, 0.,1. );
    
    h1->StatOverflows(kTRUE);
    h2->StatOverflows(kTRUE);
    
    double sum = 0.;
    
    for (int k = 0; k< n_punti;k++){
        sum = 0.;
        for (int i = 0; i< n_somma; i++){ //sommo su un numero n_somma di elementi della serie generata
            double temp = mygen->rand();
            h2->Fill(temp);
            sum = sum + temp;
        }
        h1->Fill(sum);
    }
    h1->GetXaxis()->SetRangeUser(h1->GetMean()-4*h1->GetStdDev(),h1->GetMean()+4*h1->GetStdDev());
    
    //    ===================================================
    //              verifico che la varianza scala con n
    //    ===================================================
    
    TGraph* errore = new TGraph;
    TH1F* h_test = new TH1F ( "htest" , "Distribuzione somme test", N_bins, 0.,1. );
    h_test->StatOverflows(kTRUE);
    
    double n_somma_errore = 15;
    for(int j = 0; j<10; j++){ // scorro il numero di istogrammi di cui voglio calcolare la StdDev
        for (int k = 0; k<n_punti; k++){ //scorro sul numeor di elementi della serie unif in (0,1)
            sum = 0.;
            for (int i = 0; i< n_somma_errore; i++){ //sommo su un numero n_somma di elementi della serie generata
                double temp = mygen->rand();
                sum = sum + temp;
            }
            h_test->Fill(sum);
        }
        errore->SetPoint(j, n_somma_errore, pow(h_test->GetStdDev(),2));
        n_somma_errore*=1.1;
        h_test->Reset();
    }
    
    
    //fitto con l'andamento atteso: le varianza scalano con n
    //N.B. all'aumentare del numero di eleenti su cui sommo il grafico degli errori
    //tende ad essere meglio approssimato da una retta con coefficiente N
    //mi aspettio che p[0] = 0 e p[1] = sigma_distribuzione_unif
    
    
    TF1* myfitfunction=new TF1 ("fitf", "pol1", 0, n_somma_errore);
    errore->Fit("fitf");
    double p0 = myfitfunction->GetParameter(0);
    double p1 = myfitfunction->GetParameter(1);
    cout << endl << endl;
    cout << "Andamento dell'errore osservato: " << setprecision(3) << p0 << " + "  <<p1 << " N"<< endl;
    cout << "Andamento dell'errore atteso: " << setprecision(3) << pow(h2->GetStdDev(),2) << " N"<< endl;
    
    c->cd(3);
    errore->GetXaxis()->SetTitle("# di elementi su cui si somma");
    errore->GetYaxis()->SetTitle("Varianza della serie delle somme");
    errore->SetMarkerStyle(20);
    errore->SetTitle("Andamento dell'errore con N");
    errore->Draw("APL");

    c->cd(1);
    h1->GetXaxis() -> SetTitle ( "x [u.a.]" );
    h1->GetYaxis() -> SetTitle ( "y [u.a.]" );
    h1->Draw();
    
    c->cd(2);
    h2->GetXaxis() -> SetTitle ( "x [u.a.]" );
    h2->GetYaxis() -> SetTitle ( "y [u.a.]" );
    h2->Draw();
    
    
//    STAMPO A VIDEO
    
    cout <<endl << endl <<"Varianza distribuzione delle somme "
         <<pow(h1->GetStdDev(),2)<< endl;
    cout <<"Varianza distribuzione uniforme "
         << pow(h2->GetStdDev(),2)<< endl;
    cout << "Rapporto delle varianze: "
         << pow(h1->GetStdDev(),2) /pow(h2->GetStdDev(),2) << endl;
    cout << "Rapporto delle varianze atteso : "
         << n_somma << endl;
    cout << "Media distribuzione uniforme : "
         << h2->GetMean() << endl;
    cout << "Media distribuzione somma : "
         << h1->GetMean() << endl;
    cout << "Rapporto delle medie: "
         << h1->GetMean() /h2->GetMean() << endl;
    cout << "Rapporto delle medieatteso : "
         << n_somma << endl;
    
    
    app.Run();
    
    return 0;
}
