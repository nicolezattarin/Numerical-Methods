LIBS:=`root-config --libs`
INCS:=`root-config --cflags`

esercizio9.3: esercizio9.3.o equadiff.o fvect.o
	g++ -std=c++11 esercizio9.3.o equadiff.o fvect.o ${LIBS} -o esercizio9.3

esercizio9.3.o: esercizio9.3.cpp equadiff.h fvect.h
	g++ -c -std=c++11 esercizio9.3.cpp -o esercizio9.3.o ${INCS} 

%.o: %.cpp %.h myalgebra.h
	g++ -c -std=c++11 $< -o $@

clean:
	rm *.o
	rm esercizio9.3
