LIBS:=`root-config --libs`
INCS:=`root-config --cflags`

esercizio9.4: esercizio9.4.o equadiff.o fvect.o
	g++ -std=c++11 esercizio9.4.o equadiff.o fvect.o ${LIBS} -o esercizio9.4

esercizio9.4.o: esercizio9.4.cpp equadiff.h fvect.h
	g++ -c -std=c++11 esercizio9.4.cpp -o esercizio9.4.o ${INCS} 

%.o: %.cpp %.h myalgebra.h
	g++ -c -std=c++11 $< -o $@

clean:
	rm *.o
	rm esercizio9.4
