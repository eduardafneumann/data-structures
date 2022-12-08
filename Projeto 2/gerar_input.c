#include<stdio.h>
#include<stdlib.h>

#define SET1 10
#define SET2 16
#define MAX 3000

void main(){
    printf("%d\n", SET1);
    printf("%d\n", SET2);
    for(int i=0; i<SET1; i++){
        int a = rand()%MAX;
        printf("%d\n", a);
    }
    for(int i=0; i<SET2; i++){
        int a = rand()%MAX;
        printf("%d\n", a);
    }
    //printf("%d\n%d\n", 1, rand()%MAX);
    //printf("%d\n", 2);
    printf("%d\n", 3);
    //printf("%d\n%d\n", 4, rand()%MAX);
}