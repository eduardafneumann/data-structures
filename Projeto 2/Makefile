all: main.o set.o avl.o item.o auxiliar.o
	gcc -o main main.o set.o avl.o item.o auxiliar.o -O2 -std=c99

run: main
	./main

main.o: main.c set.h
	gcc -Wall -Wextra -g -c main.c

set.o: set.c set.h
	gcc -Wall -Wextra -g -c set.c

avl.o: avl.c avl.h
	gcc -Wall -Wextra -g -c avl.c

item.o: item.c item.h
	gcc -Wall -Wextra -g -c item.c

auxiliar.o: auxiliar.c auxiliar.h
	gcc -c auxiliar.c -O2

clear:
	rm *.o main