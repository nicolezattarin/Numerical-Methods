#include "integrale.h"
//======================================================
//              costruttori
//======================================================

integrale:: integrale (double a, double b, const funzionebase* f){
    m_a = a;
    m_b = b;
    m_f = f;
    if (a>b) m_segno = -1;
    else m_segno = 1;

}

integrale::integrale (double a, double b, const funzionebase* f, double prec){
    m_a = a;
    m_b = b;
    m_f = f;
    if (a>b) m_segno = -1;
    else m_segno = 1;
    precision = prec;
}


//======================================================
//              midpoint numero di passi
//======================================================

double integrale :: midpoint (int N){
    m_int = 0; // inizializzo a zero la somma

    // valuto h per questo N
    m_h = (fabs(m_b-m_a))/N;

    for (int i = 0; i< N; ++i){
    m_int +=  m_f->eval( m_a + i*m_h + (m_h/2.) );
    }
    return m_int*m_h*m_segno;
}

//======================================================
//              midpoint precisione
//======================================================

double integrale::midpoint(){
    int N = 1;
    double x = midpoint(N); //calcolo l'integrale con N passi
    double y = midpoint(2*N); //calcolo l'integrale con 2N passi
    while ( ((4./3.)*fabs(x-y)) > precision ){ //vado avanti fino a
                            //quando la precisione non è quella voluta
        N = 2*N; //a passi di
        x = midpoint(N);
        y = midpoint(2*N);
    }
    return y;
}

//======================================================
//              simpson numero di passi
//======================================================

    double integrale::simpson (int N){
    if (N%2 != 0 ){
        cerr << "Il numero di steps deve essere pari per utilizzare il metodo di Simpson" << endl;
        exit (1);
    }

    m_int = 0; // inizializzo a zero la somma

    // valuto h
    m_h = (abs(m_b-m_a))/N;

    for (int i = 0; i<= N; ++i){
        if (i == 0 || i== N) m_int += m_f->eval(m_a + m_h*i);
        else if (i%2 == 0) m_int += 2.*m_f->eval(m_a + m_h*i);
        else m_int += 4.*m_f->eval(m_a + m_h*i);
    }
    return m_int * m_h * m_segno * (1./3.);

}


//======================================================
//              simpson precisione
//======================================================

    double integrale::simpson (){
    int N = 2; //devo partire da un numero pari,moltiplicando per 2 avrò semère pari
    double x = simpson(N); //calcolo l'integrale con N passi
    double y = simpson(2*N); //calcolo l'integrale con 2N passi
    while ( ((16./15.)*abs(x-y)) > precision ){ //vado avanti fino a
                            //quando la precisione non è quella voluta
        N = 2*N;
        x = simpson(N);
        y = simpson(2*N);
    }
    return y;
}


//======================================================
//              trapezi precisione
//======================================================

double integrale :: trapezi (){ //la precisione è registrata nella classe
    
    m_passo_precedente = 0; // inizializzo a zero la somma del passo i-1
    m_int = 0; // inizializzo a zero la somma
    double h_precedente = 0;
    int N = 2;
    
    //faccio il primo passo per N=1 e h=b-a: ho i primi due punti
    m_passo_precedente = (m_f->eval(m_a)+m_f->eval(m_b))/2.; // con N = 1
    
    //faccio il secondo passo in modo da poter valutare la differenza gli integrali tra N e 2N
    m_h = fabs(m_b-m_a)/N; // valuto h per N corrispondente
    m_int = m_passo_precedente+m_f->eval((m_a+m_b)/2); // con N = 2

    while ((4./3.)*fabs(m_int*m_h - m_passo_precedente*m_h*2)>precision){ //posso anda
        m_passo_precedente = m_int; // salvo il valore dell'integrale per passare a quello dopo
        N=N*2; //aggiorno N
        m_h = fabs(m_b-m_a)/N; // valuto h per N corrispondente
        for (int i = 0; (m_a+m_h+i*2*m_h)<m_b; ++i) m_int += m_f->eval(m_a+m_h+2*m_h*i);
        //cicla il for fino a quando non arrivo all'estremo finale
        //dell'intervallo di integrazione le valutazioni nei punti medi tra i punti precedenti
    }
    return m_int * m_segno * m_h;
}

double integrale::trapezi_non_ottimizzata (){
    int N = 1;
    double x = trapezi(N); //calcolo l'integrale con N passi
    double y = trapezi(2*N); //calcolo l'integrale con 2N passi
    while (((4./3.)*abs(x-y)) > precision ){ //vado avanti fino a
                            //quando la precisione non è quella voluta
        N = 2*N;
        x = trapezi(N);
        y = trapezi(2*N);
    }
    return y;
}

//======================================================
//              trapezi numero di passi
//======================================================

double integrale::trapezi (int N) //di appoggio
{
    m_h = (fabs(m_b-m_a) )/N;// valuto h
    m_int = 0; // inizializzo a zero la somma
    
    for (int i=0; i<=N; ++i){ //ricordati l'uguale, devo prendere anche N
        if (i==0 || i== N) m_int += (m_f->eval( m_a + m_h * i))/2.;
        else m_int += m_f->eval(m_a + m_h * i);
    }
    
    return m_int * m_h * m_segno;
}






