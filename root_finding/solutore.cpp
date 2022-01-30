#include "solutore.h"

//=====================================================
//              Funzione per capire segno
//=====================================================

int segno (double x){
	if (x < 0) return -1;
	else return 1;
}

//=====================================================
//                  BISEZIONE
//=====================================================


void bisezione :: SetN (unsigned int N){
    n_iterazioni = N;
}


double bisezione::cercazeri(double a, double b, const funzionebase* f){

// controllo che a < b nel caso non sia così lo scambio
    if (a > b) {
        double temp = a;
        a =  b;
        b = temp;
    }

// valuto la funzione negli estremi dell'intervallo richiesto
double y_a = f->eval(a);
double y_b = f->eval(b);
double c = a + 0.5 * (b-a); // punto medio
double y_c = f->eval(c);  // funzione nel punto medio
int i = 0; // creo un controllo sul numero di iterazioni
    
        
// controllo che esista lo zero
if (segno (y_a) * segno(y_b) > 0 ) {
            cerr << "Non esiste uno zero nell'intervallo indicato o, se esiste, non è unico " << endl;
            exit(1);
        }

if (c == 0) return c;   // se c trova subito il punto in cui si
                        // trova lo zero restituisco quel valore
    
    // se raggiungo le precisione richiesta esco dal ciclo, altrimenti il controllo lo si fa con il numero di iterazioni
    
while (abs (a-b)>=get_precision() || i<n_iterazioni ){ // controllo precisione e n iterazioni
	
    if (segno (y_a) * segno(y_c) == -1){
		b = c;
		y_a = f->eval(a);
		y_b = f->eval(b);
        
		c = a + 0.5 * (b-a);
		y_c = f->eval(c);
	}
	else { 
		a = c;
		y_a = f->eval(a);
		y_b = f->eval(b);
        
		c = a + 0.5 * (b-a);
		y_c = f->eval(c);
    }
	i++;
	}
	
	
 return c;
}
