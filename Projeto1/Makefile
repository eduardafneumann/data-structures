all: main.o pilha.o item.o grafo.o vertice.o lista.o solucao.o alocacao.o
	gcc -o main main.o pilha.o item.o grafo.o vertice.o lista.o solucao.o alocacao.o -O2

run: main
	./main

main.o: main.c pilha.h item.h
	gcc -c main.c -O2

pilha.o: pilha.c pilha.h
	gcc -c pilha.c -O2

item.o: item.c item.h
	gcc -c item.c -O2

grafo.o: grafo.c grafo.h alocacao.h
	gcc -c grafo.c -O2

vertice.o: vertice.c vertice.h alocacao.h
	gcc -c vertice.c -O2

lista.o: lista.c lista.h alocacao.h
	gcc -c lista.c -O2

solucao.o: solucao.c solucao.h pilha.h alocacao.h
	gcc -c solucao.c -O2

alocacao.o: alocacao.c alocacao.h
	gcc -c alocacao.c -O2

clear:
	rm *.o main
