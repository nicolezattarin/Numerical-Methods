#include "integrale.h"
#include "TApplication.h"
#include "TGraph.h"
#include <iomanip>
#include "TCanvas.h"

int main(int argc, char** argv){
    if (argc!= 2){
        cerr << "Uso del programma " << argv[0] << " <precisione desiderata> " << endl;
        return 1;
    }
    
    seno* myseno = new seno;
    double precision = atof(argv[1]);

    integrale* myintegrale = new integrale(0, M_PI, myseno, precision);
    cout << "Integrale del seno tra 0 e π: "
         << fixed << setprecision(-log10(precision))
         << myintegrale->trapezi() <<" +/- " << precision<< endl;

    delete myseno;
    delete myintegrale;

	return 0;
}
