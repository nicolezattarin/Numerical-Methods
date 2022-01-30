LIBS:=`root-config --libs`
INCS:=`root-config --cflags`

esercizio10.3: esercizio10.3.o randomgen.o int_MC.o funzioni_RN.o funzioni.o
	g++ -std=c++11 esercizio10.3.o randomgen.o funzioni_RN.o int_MC.o funzioni.o ${LIBS} -o esercizio10.3

esercizio10.3.o: esercizio10.3.cpp randomgen.h funzioni_RN.h int_MC.h funzioni.h
	g++ -c -std=c++11 esercizio10.3.cpp -o esercizio10.3.o ${INCS} 

%.o: %.cpp %.h
	g++ -c -std=c++11 $< -o $@

clean:
	rm *.o
	rm esercizio10.3
