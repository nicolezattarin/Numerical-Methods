LIBS:=`root-config --libs`
INCS:=`root-config --cflags`

esercizio8.2: esercizio8.2.o funzioni.o integrale.o
	g++ esercizio8.2.o funzioni.o integrale.o ${LIBS} -o esercizio8.2

esercizio8.2.o: esercizio8.2.cpp funzioni.h integrale.h
	g++ -c esercizio8.2.cpp -o esercizio8.2.o ${INCS} 

%.o: %.cpp %.h
	g++ -c $< -o $@

clean:
	rm *.o
	rm esercizio8.2
