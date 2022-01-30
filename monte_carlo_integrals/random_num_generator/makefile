LIBS:=`root-config --libs`
INCS:=`root-config --cflags`

esercizio10.0: esercizio10.0.o randomgen.o
	g++ -std=c++11 esercizio10.0.o randomgen.o ${LIBS} -o esercizio10.0

esercizio10.0.o: esercizio10.0.cpp randomgen.h
	g++ -c -std=c++11 esercizio10.0.cpp -o esercizio10.0.o ${INCS} 

%.o: %.cpp %.h
	g++ -c -std=c++11 $< -o $@

clean:
	rm *.o
	rm esercizio10.0
