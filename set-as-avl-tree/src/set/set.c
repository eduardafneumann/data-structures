#include "set/set.h"

#include <stdio.h>
#include <stdlib.h>

#include "set/element.h"
#include "utils/utils.h"

typedef struct nodede_
{
    ELEMENT *element;
    struct nodede_ *left;
    struct nodede_ *right;
    int depth;
} Node;

typedef struct set_
{
    Node *root;
} SET;

int depth(Node *node)
{
    if (node == NULL)
        return -1;
    else
        return node->depth;
}

Node *nodede_create(int key)
{
    ELEMENT *element = element_create(key);

    Node *node = malloc(sizeof(Node));
    validate_alocation(node);

    if (element != NULL)
    {
        node->element = element;
        node->left = NULL;
        node->right = NULL;
        node->depth = 0;
        return node;
    }

    return NULL;
}

void nodede_erase(Node **node)
{
    if (*node != NULL)
    {
        element_erase(&((*node)->element));
        free(*node);
        *node = NULL;
    }
}

SET *set_create()
{
    SET *set = malloc(sizeof(SET));
    validate_alocation(set);
    set->root = NULL;

    return set;
}

void erase_recursive(Node *root)
{
    if (root == NULL)
        return;

    erase_recursive(root->left);
    erase_recursive(root->right);

    nodede_erase(&root);
}

void set_erase(SET **set)
{
    if (*set != NULL)
    {
        erase_recursive((*set)->root);
        free(*set);
        (*set) = NULL;
    }
}

Node *right_rotation(Node *unbalanced)
{
    // The left child of the unbalanced node will be the new subtree root
    Node *future_root = unbalanced->left;

    // The unbalanced node will become the right child of the future subtree root, and the
    // current right child of the current root will become the left child of the unbalanced node
    Node *tree_t2 = future_root->right;
    future_root->right = unbalanced;
    unbalanced->left = tree_t2;

    // The unbalanced node and the new subtree root changed depth
    unbalanced->depth = max(depth(unbalanced->left), depth(unbalanced->right)) + 1;
    future_root->depth = max(depth(future_root->left), depth(future_root->right)) + 1;

    return future_root;
}

Node *left_rotation(Node *unbalanced)
{
    // The right child of the unbalanced node will be the new subtree root
    Node *future_root = unbalanced->right;

    // The unbalanced node will become the left child of the future subtree root, and the
    // current left child of the current root will become the right child of the unbalanced node
    Node *tree_t2 = future_root->left;
    future_root->left = unbalanced;
    unbalanced->right = tree_t2;

    // The unbalanced node and the new subtree root changed depth
    unbalanced->depth = max(depth(unbalanced->left), depth(unbalanced->right)) + 1;
    future_root->depth = max(depth(future_root->left), depth(future_root->right)) + 1;

    return future_root;
}

Node *right_left_rotation(Node *unbalanced)
{
    unbalanced->right = right_rotation(unbalanced->right);
    return (left_rotation(unbalanced));
}

Node *left_right_rotation(Node *unbalanced)
{
    unbalanced->left = left_rotation(unbalanced->left);
    return (right_rotation(unbalanced));
}

Node *insert_recursive(Node *root, int key)
{
    if (root == NULL) // Insert in the root
        root = nodede_create(key);

    else if (element_get_key(root->element) > key) // Propagate recursion on the left
        root->left = insert_recursive(root->left, key);

    else if (element_get_key(root->element) < key) // Propagate recursion on the right
        root->right = insert_recursive(root->right, key);

    // Coming back from recursion

    root->depth = max(depth(root->left), depth(root->right)) + 1;
    int balancing_factor = depth(root->left) - depth(root->right);

    // Unbalanced to the right
    if (balancing_factor == -2)
    {
        if (element_get_key(root->right->element) < key)
            root = left_rotation(root);
        else
            root = right_left_rotation(root);
    }

    // Unbalanced to the right
    if (balancing_factor == 2)
    {
        if (element_get_key(root->left->element) > key)
            root = right_rotation(root);
        else
            root = left_right_rotation(root);
    }

    return root;
}

void set_insert(SET *set, int key)
{
    if (set != NULL)
        set->root = insert_recursive(set->root, key);
}

// Swap the 'root' node by the max node of the left subtree
void swap_max_left(Node *swap, Node *root, Node *old)
{
    // If still exists a node more to the right (and therefore with a bigger key)
    if (swap->right != NULL)
    {
        swap_max_left(swap->right, root, swap);
        return;
    }

    if (root == old) // If it is the root's left child
        old->left = swap->left;
    else // Otherwise, it will be old's right child
        old->right = swap->left;
    root->element = swap->element;

    // Removes the element
    free(swap);

    swap = NULL;
}

Node *remove_recursive(Node *root, int key)
{
    if (root == NULL)
        return NULL;

    if (element_get_key(root->element) == key)
    {
        if (root->left == NULL || root->right == NULL)
        {
            Node *erase = root;

            if (root->left == NULL)
                root = root->right;
            else
                root = root->left;

            nodede_erase(&erase);
        }
        else // Both children exist
        {                           
            // Looks for the right-most node on the left subtree to put in the root              
            swap_max_left(root->left, root, root);
        }
    }
    else // The element to be removed is not the root, must propagate recursion
    {
        if (element_get_key(root->element) > key)
            root->left = remove_recursive(root->left, key);
        else
            root->right = remove_recursive(root->right, key);
    }

    // Coming back from recursion

    if (root != NULL)
    {
        root->depth = max(depth(root->left), depth(root->right)) + 1;
        int balancing_factor = depth(root->left) - depth(root->right);

        // Unbalanced to the right
        if (balancing_factor == -2) 
        {
            if (depth(root->right->left) - depth(root->right->right) <= 0)
                root = left_rotation(root);
            else
                root = right_left_rotation(root);
        }

        // Unbalanced to the left
        if (balancing_factor == 2)
        {
            if (depth(root->left->left) - depth(root->left->right) >= 0)
                root = right_rotation(root);
            else
                root = left_right_rotation(root);
        }
    }

    return root;
}

void set_remove(SET *set, int key)
{
    if (set != NULL)
        set->root = remove_recursive(set->root, key);
}

void print_recursive(Node *node)
{
    if (node == NULL)
        return;

    print_recursive(node->left);
    element_print(node->element);
    print_recursive(node->right);
}

void set_print(SET *set)
{
    if (set != NULL)
    {
        printf("----------\n");
        print_recursive(set->root);
        printf("\n----------\n");
    }
}

bool contains_recursive(Node *root, int key)
{
    if (root == NULL)
        return false;

    if (element_get_key(root->element) == key)
        return true;

    if (key < element_get_key(root->element))
        return contains_recursive(root->left, key);
    else
        return contains_recursive(root->right, key);
}

bool set_contains(SET *set, int key)
{
    return contains_recursive(set->root, key);
}

void intersection_recursive(SET *set, SET *intersection, Node *root)
{
    if (root == NULL)
        return;

    if (set_contains(set, element_get_key(root->element)))
        set_insert(intersection, element_get_key(root->element));

    intersection_recursive(set, intersection, root->left);
    intersection_recursive(set, intersection, root->right);
}

SET *set_intersection(SET *set1, SET *set2)
{
    SET *intersection = set_create();

    intersection_recursive(set1, intersection, set2->root);
    return intersection;
}

void copy_recursive(SET *copia, Node *root)
{
    if (root == NULL)
        return;

    set_insert(copia, element_get_key(root->element));

    copy_recursive(copia, root->left);
    copy_recursive(copia, root->right);
}

SET *set_copy(SET *set)
{
    SET *copia = set_create();
    copy_recursive(copia, set->root);
    return copia;
}

void union_recursive(Node *root, SET *union_set)
{
    if (root == NULL)
        return;

    if (!set_contains(union_set, element_get_key(root->element)))
        set_insert(union_set, element_get_key(root->element));

    union_recursive(root->left, union_set);
    union_recursive(root->right, union_set);
}

SET *set_union(SET *set1, SET *set2)
{
    SET *union_set = set_copy(set1);
    union_recursive(set2->root, union_set);

    return union_set;
}
