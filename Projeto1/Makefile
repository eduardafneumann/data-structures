all: main.o pilha.o item.o grafo.o vertice.o lista.o
	gcc -o main main.o pilha.o item.o grafo.o vertice.o lista.o

run: main
	./main

main.o: main.c pilha.h item.h
	gcc -c main.c

pilha.o: pilha.c pilha.h
	gcc -c pilha.c

item.o: item.c item.h
	gcc -c item.c

grafo.o: grafo.c grafo.h
	gcc -c grafo.c

vertice.o: vertice.c vertice.h
	gcc -c vertice.c

lista.o: lista.c lista.h
	gcc -c lista.c

clear:
	rm *.o main