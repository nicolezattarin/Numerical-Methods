#include "randomgen.h"
#include "TApplication.h"
#include "TH1F.h"
#include "TCanvas.h"

using namespace std;
int main (){
    

    TApplication app ("app", 0, 0);
    randomgen* mygen = new randomgen (1); //inserisco il numero di partenza
    int N_bins = 100;
    int n_punti = 10000;//numero di valori da generare per ogni istogramma
    
//    =========================================
//                UNIF. in (0,1)
//    =========================================

    TCanvas* c= new TCanvas( "c" , "Distribuzioni", 1000, 1400 );
    c->Divide(2,3);
    
    c->cd(1);
    TH1F* h1 = new TH1F ( "h1" , "Distribuzione tra 0 e 1", N_bins, -0.1, 1.1 );
    for ( int i = 0 ; i < n_punti ; ++i) h1->Fill(mygen->rand());
    h1->GetXaxis() -> SetTitle ( "x [u.a.]" );
    h1->GetYaxis() -> SetTitle ( "y [u.a.]" );
    h1->Draw();
    
    
        
    //    =========================================
    //                UNIF. in (min, max)
    //    =========================================

        c->cd(2);
        TH1F* h2 = new TH1F( "h2" ,  "Distribuzione tra 1 e 20", N_bins, 4.9, 10.1 );
        for ( int i=0; i<n_punti ; ++i) h2->Fill(mygen->uniforme(5,10));
        h2->GetXaxis() -> SetTitle ( "x [u.a.]" );
        h2->GetYaxis() -> SetTitle ( "y [u.a.]" );
        h2->Draw();
        
        
    //    =========================================
    //                esponenziale
    //    =========================================

        c->cd(3);
        TH1F* h3 = new TH1F ( "h3" ,  "Distribuzione esponenziale", N_bins, 0., 5. );
        for ( int i = 0 ; i < n_punti ; ++i)  h3->Fill(mygen->esponenziale(1));
        h3->GetXaxis() -> SetTitle ( "x [u.a.]" );
        h3->GetYaxis() -> SetTitle ( "y [u.a.]" );
        h3->Draw();
        
    //    =========================================
    //                gauss
    //    =========================================
        double media = 1.;
        double sigma = 1;
        c->cd(4);
        TH1F* h4 = new TH1F ( "h4" ,  "Distribuzione gaussiana: metodo funzione inversa", N_bins, media-sigma*4, media +sigma*4 );
        for ( int i = 0 ; i < n_punti ; ++i) h4->Fill(mygen->gauss(media,sigma));
        h4->GetXaxis() -> SetTitle ( "x [u.a.]" );
        h4->GetYaxis() -> SetTitle ( "y [u.a.]" );
        h4->Draw();
    
    
    //    =========================================
    //                gauss accept reject
    //    =========================================

        c->cd(5);
        TH1F* h5 = new TH1F( "h5" ,  "Distribuzione gaussiana: metodo Accept-Reject", N_bins, media-sigma*4,  media+sigma*4 );
        for ( int i = 0 ; i < n_punti ; ++i) h5->Fill(mygen->gauss_AR(media,sigma ,media-sigma*4,media+sigma*4));
        h5->GetXaxis() -> SetTitle ( "x [u.a.]" );
        h5->GetYaxis() -> SetTitle ( "y [u.a.]" );
        h5->Draw();
           
    
    
    delete mygen;
    app.Run();
    
    return 0;
}
