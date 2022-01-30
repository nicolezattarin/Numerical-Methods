esercizio7.3: esercizio7.3.o funzionebase.o solutore.o
	g++ $^ -o $@

esercizio7.3.o: esercizio7.3.cpp funzionebase.h solutore.h
	g++ -c $< -o $@

%.o: %.cpp %.h
	g++ -c $< -o $@

clean:
	rm *.o
	rm esercizio7.3
