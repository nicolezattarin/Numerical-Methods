LIBS:=`root-config --libs`
INCS:=`root-config --cflags`

esercizio10.2: esercizio10.2.o randomgen.o int_MC.o funzioni.o
	g++ -std=c++11 esercizio10.2.o randomgen.o int_MC.o funzioni.o ${LIBS} -o esercizio10.2

esercizio10.2_analisi: esercizio10.2_analisi.o
	g++ -std=c++11 esercizio10.2_analisi.o ${LIBS} -o esercizio10.2_analisi

esercizio10.2.o: esercizio10.2.cpp randomgen.h int_MC.h funzioni.h
	g++ -c -std=c++11 esercizio10.2.cpp -o esercizio10.2.o ${INCS} 

esercizio10.2_analisi.o: esercizio10.2_analisi.cpp
	g++ -c -std=c++11 esercizio10.2_analisi.cpp -o esercizio10.2_analisi.o ${INCS}

%.o: %.cpp %.h
	g++ -c -std=c++11 $< -o $@

clean:
	rm *.o
	rm esercizio10.2
	rm esercizio10.2_analisi
