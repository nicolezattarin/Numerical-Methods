#include "equadiff.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TF1.h"



int main(int argc, char** argv){
    
    if (argc!=2){
        cerr << "Uso del programma: " << argv[0] << " <passo> " << endl;
        return -1;
    }
    double h = atof(argv[1]);
    
    //==============================================
    //        soluzione dell'equazione (Runge-kutta)
    //==============================================
    TApplication app ("app", 0, 0);
    TGraph traiettoria ;
    TCanvas c ("c","Risultati ottenuti", 1200, 800);
    c.Divide(2,2);

    oscillatore_semplice * myoscillatore = new oscillatore_semplice (1.);
    runge_kutta myrunge;
    
    double tmax = 70.; //tempo massimo 70 secondi
    vector <double> x {0., 1.}; //condizioni al contorno
    double t = 0.;
    
    
    //grafico della soluzione
    int i = 0;
    while (t<=tmax){
        traiettoria.SetPoint(i, t, x[0]); //plotta la prima componente
                                 //di x che contiene la posizione
        x = myrunge.passo(x,t,h,myoscillatore); //aggiorno x
        t += h; // aggiorno t
        i++;
    }

    //setto assi grafico della soluzione
    c.cd(1);
    traiettoria.GetXaxis()->SetTitle("t[s]");
    traiettoria.GetYaxis()->SetTitle("x[m]");
    traiettoria.Draw("APL");
    traiettoria.SetTitle("Traiettoria oscillatore armonico");
    
    
        
    //==============================================
    //       Errore accumulato (runge vs eulero)
    //==============================================
    
    TGraph g_errori_runge, g_errori_eulero;
    eulero myeulero;
    
    double passo_errore = 0.1;
    const int n_punti = 10;
    vector <double> y {0., 1.}; //vettore per eulero

    for (int i=0; i< n_punti; ++i){
        cout << "Sto calcolando l'errore con passo " << passo_errore << endl;
        t = 0;
        x[0] = 0.;
        x[1] = 1.;
        y[0] = 0.;
        y[1] = 1.;
        
        while (t<=tmax){ //percorro tutta la traiettoria per trovare
                        // l'errore accumulato al tempo tmax
            x = myrunge.passo(x, t, passo_errore,myoscillatore);
            y = myeulero.passo(x, t, passo_errore,myoscillatore);
            t = t + passo_errore;
        }
        g_errori_runge.SetPoint(i, passo_errore, fabs( x[0] - sin(t) ) );
        g_errori_eulero.SetPoint(i, passo_errore, fabs( y[0] - sin(t) ) );
        passo_errore = passo_errore / 2;
    }
    
    //==========================================================
    //       controllo che i primi punti scalano come kh^4
    //=========================================================
    
    TF1 myfitfunction ("myfit", "[0]*pow(x,[1])",0.003125,0.1);
    myfitfunction.SetParameter(0,0.5);
    myfitfunction.SetParameter(1,4);

    g_errori_runge.Fit("myfit","R");// “R” Use the range specified in the function range
    

    //setto assi grafico della soluzione
    c.cd(4);
    c.cd(4)->SetLogx();
    c.cd(4)->SetLogy();
    
    g_errori_runge.GetXaxis()->SetTitle("Passo [s]");
    g_errori_runge.GetYaxis()->SetTitle("Errore a 70 s");
    g_errori_runge.SetTitle("Andamento dell'errore al variare del passo: Runge-Kutta");

    g_errori_runge.SetMarkerStyle(20);
    g_errori_runge.Draw();

    c.cd(3);
    c.cd(3)->SetLogx();
    c.cd(3)->SetLogy();
    
    g_errori_eulero.GetXaxis()->SetTitle("Passo [s]");
    g_errori_eulero.GetYaxis()->SetTitle("Errore a 70 s");
    g_errori_eulero.SetTitle("Andamento dell'errore al variare del passo: Eulero");

    g_errori_eulero.SetMarkerStyle(20);
    g_errori_eulero.Draw();
    
    app.Run();
    return 0;
}
