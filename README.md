# Data Structures in C

## Traveling Salesman

The implementation to solve the traveling salesman problem using brute force is in the 'traveling-salesman' folder. It used Lists, Stacks and Graphs to achieve this, all implemented in C. To compile the code, run `make` inside the root folder. To execute, run `make run < test-cases/<desired-test>`, and the output is the solution path to the given test case.

## Set as AVL tree

The implementation of sets as AVL Trees in C is on the folder 'set-as-avl-tree'. This way, the insertion and removal of itens has complexity O(log(n)), better than linear structures. 

There are 4 operations possible in the program:

- [1] Check if a given set contains a given element
- [2] Print the union of two given sets
- [3] Print the intersection of two given sets
- [4] Remove a given element from a given set


The input should contain two sets of integers and 1 operation. If the operation is [1] or [4], one element should also be included in the input. 

To compile the code, run `make` inside the root folder. To execute, run `make run < test-cases/<desired-test>`.