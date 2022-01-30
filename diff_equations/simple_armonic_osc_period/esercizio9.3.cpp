#include "equadiff.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TAxis.h"



int main(int argc, char** argv){
    
    if (argc!=2){
        cerr << "Uso del programma: " << argv[0] << " <passo> " << endl;
        return -1;
    }
    double h = atof(argv[1]);
    
    //==============================================
    //        soluzione dell'equazione
    //==============================================
    
    TApplication app ("app", 0, 0);
    TGraph* traiettoria = new TGraph;
    TCanvas* c = new TCanvas ("c","Risultati", 1200, 400);
    c->Divide(2,1);
    
    pendolo* mypendolo = new pendolo (1.);
    runge_kutta* myrunge = new runge_kutta;

    
    double tmax = 70.; //tempo massimo 70 secondi
    vector <double> x {0., 1.}; //condizioni al contorno
    double t = 0.;
    
    //grafico della soluzione
    int i = 0;
    while (t<=tmax){
        traiettoria->SetPoint(i, t, x[0]); //plotta la prima componente
                                 //di x che contiene la posizione
        x = myrunge->passo(x,t,h,mypendolo); //aggiorno x
        t = t + h; // aggiorno t
        ++i;
    }
    
    //setto assi grafico della soluzione
    c->cd(1);
    traiettoria->GetXaxis()->SetTitle("t[s]");
    traiettoria->GetYaxis()->SetTitle("x[rad]");
    traiettoria->Draw("APL");
    traiettoria->SetTitle("Traiettoria oscillatore armonico");
    
    
    
    //==============================================
    //   grafico periodo al variare dell'ampiezza
    //==============================================
    
    TGraph *periodo = new TGraph;
    
    int n_punti = 35;
    double passo = 0.0001;
    double ampiezza = 0.5;
    double v_precedente = 0.;
    
    for (int i = 0; i<n_punti; i++){
        x[0] = - ampiezza  ; //aggiorno l'ampiezza
        x[1] = 0.;
        t = 0.;
        
        while (x[1]>=0.){
            v_precedente = x[1]; //salvo la velocità al passo precedente
            x = myrunge->passo (x,t,passo,mypendolo); //aggiorno x
            t = t + passo;
            }
        
        periodo -> SetPoint(i, x[0], t-h-v_precedente*passo/(x[1]-v_precedente));
        ampiezza = ampiezza + 0.07; //N.B. l'algoritmo non è implementato per
                                   //valori di ampiazza iniziale che hanno un'energia
                                   // potenziale tale da far compiere un giro
                                   //della morte al pendolo
    }
    

    
    //setto assi grafico della soluzione
    c->cd(2);

    periodo->SetMarkerStyle(20);
    periodo->GetXaxis()->SetTitle("A[rad]");
    periodo->GetYaxis()->SetTitle("T[s]");
    periodo->Draw("APL");
    periodo->SetTitle("Periodo");
    
  
    delete mypendolo;
    delete myrunge;
    
    app.Run();
    
    
    return 0;
}
