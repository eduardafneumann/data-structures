#include <stdio.h>
#include <stdlib.h>

#include "set/set.h"

int main()
{
    SET *A, *B;
    int n_a, n_b, x;
    int op;

    A = set_create();
    B = set_create();

    scanf("%d %d", &n_a, &n_b);

    for(int i = 0; i < n_a; i++){
        scanf("%d",&x);
        set_insert(A, x);
    }

    for(int i = 0; i < n_b; i++){
        scanf("%d",&x);
        set_insert(B, x);
    }

    set_print(A);
    set_print(B);

    scanf("%d", &op);

    switch(op){
        case 1: {
            int num;
            scanf("%d", &num);
            if(set_contains(A, num)) 
                printf("Element is contained in the set.\n");
            else
                printf("Element is not contained in the set.\n");
            break;
        }
        case 2: {
            SET *C = set_union(A, B);
            set_print(C);
            set_erase(&C);
            break;
        }
        case 3: {
            SET *C = set_intersection(A, B);
            set_print(C);
            set_erase(&C);
            break;
        }
        case 4: {
            int num;
            scanf("%d", &num);
            set_remove(A, num);
            set_print(A);
        }
    }

    set_erase(&A);
    set_erase(&B);

    return 0;
}
