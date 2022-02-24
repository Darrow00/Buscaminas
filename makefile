jugar: jugar.o buscaminas.o
	g++ -o jugar jugar.o buscaminas.o

jugar.o: jugar.cpp
	g++ -c -o jugar.o jugar.cpp

buscaminas.o: buscaminas.cpp buscaminas.h
	g++ -c -o buscaminas.o buscaminas.cpp
