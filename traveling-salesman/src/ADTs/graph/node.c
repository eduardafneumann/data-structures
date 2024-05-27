#include <stdlib.h>
#include <stdio.h>

#include "ADTs/graph/node.h"

struct node_
{
   int next_city, weight;
};

Node *node_create(int next_city, int weight)
{
   Node *node = malloc(sizeof(Node)); validate_alocation(node);
   node->next_city = next_city;
   node->weight = weight;
   return (node);
}

bool node_erase(Node **node)
{
   if (*node != NULL)
   {
      free(*node);
      *node = NULL;
      return (true);
   }
   return (false);
}

int node_get_city(Node *node)
{
   if (node != NULL)
      return (node->next_city);
   return ERRO;
}

int node_get_weight(Node *node)
{
   if (node != NULL)
      return (node->weight);
   return ERRO;
}

bool node_set_city(Node *node, int city)
{
   if (node != NULL)
   {
      node->next_city = city;
      return (true);
   }
   return (false);
}

bool node_set_weight(Node *node, int weight)
{
   if (node != NULL)
   {
      node->weight = weight;
      return (true);
   }
   return (false);
}

void node_print(Node *node)
{
   if (node != NULL)
      printf(" node: city %d, weight %d ", node->next_city, node->weight);
}

size_t node_size()
{
   return sizeof(Node *);
}