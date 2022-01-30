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
    TGraph *traiettoria = new TGraph;
    TCanvas* c = new TCanvas ("c","Risultati", 1200, 400);


    oscillatore * myoscillatore = new oscillatore (10., 10., 1./30.); //oscillatore(omega, omega0, gamma)
    runge_kutta* myrunge = new runge_kutta;
    
    double tmax = 10 * (1/myoscillatore->GetGamma()); //integro la soluzione per un tempo
                                                    //pari almeno a 10 volte 1/gamma in modo
                                                    // che si stabilizzi
    vector <double> x {0., 0.}; //condizioni al contorno
    double t = 0.;
    
    
    //grafico della soluzione
    int i = 0;
    while (t<=tmax/10){ //non visualizzo l'oscillazione fino a quando si
                        //stabilizza perchè il quel caso risulta così
                        //fitta da non essere visivamente chiara
        traiettoria -> SetPoint(i, t, x[0]); //plotta la prima componente
                                 //di x che contiene la posizione
        x = myrunge->passo(x,t,h,myoscillatore); //aggiorno x
        t = t + h; // aggiorno t
        i++;
    }
    
    //setto assi grafico della soluzione
    c->Divide(2,1);
    c->cd(1);
    traiettoria->GetXaxis()->SetTitle("t[s]");
    traiettoria->GetYaxis()->SetTitle("x[m]");
    traiettoria->Draw();
    traiettoria->SetTitle("Oscillatore armonico");
    
    
    
    
    //==============================================
    //                risonanza
    //==============================================
    
    
    TGraph *lorentiziana = new TGraph;
    
    t = 0.;
    const int n_punti = 30;
    double omega = 9.15; //calcolo al variare di omega l'ampiezza
    
    for (int i = 0; i<n_punti; ++i){
        //setto la pulsazione
        omega = omega + 0.05;
        myoscillatore->SetOmega(omega); //setto la pulsazione
        x[0] = 0.;
        x[1] = 0.; //parto da oscillatore
                   //con velocità a posizione nulle
        t = 0.;
    
        //scorro con il tempo fino a quando la soluzione non è stabile  tmax = 1/gamma
        while (t<=tmax ){ //tmax è costruito in modo da essere uguale
                          //a un t in cui la soluzione inizia a stabilizzarsi
            x=myrunge->passo (x,t,h,myoscillatore);
            t+=h; //arrivo con il tempo funo al momento in
                     //cui l'oscillazione è stabile
        }

//se sono in una parte della curva con velocità positiva proseguo fino al picco
        if (x[1]>=0.){
            while ( x[1]>= 0.){
                x=myrunge->passo (x,t,h,myoscillatore);
                t+=h;
            }
        }
        else { //se sono in una parte della curva con velocità negativa proseguo fino al minimo

            while ( x[1]<=0. ){
                x=myrunge->passo (x,t,h,myoscillatore);
                t+=h;
            }
        }
        lorentiziana -> SetPoint (i, myoscillatore->GetOmega(), fabs(x[0]) );
        
    }
    
    
    //setto assi grafico della soluzione
    c->cd(2);
    lorentiziana->GetXaxis()->SetTitle("Pulsazione [rad/s]");
    lorentiziana->GetYaxis()->SetTitle("Ampiezza [m]");
    lorentiziana->Draw("APL");
    lorentiziana->SetMarkerStyle(20);
    lorentiziana->SetTitle("Curva di risonanza");
    
        
    delete myoscillatore;
    delete myrunge;
    
    app.Run();
    
    
    return 0;
}
