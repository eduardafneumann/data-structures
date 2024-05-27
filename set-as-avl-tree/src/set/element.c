#include <stdlib.h>
#include <stdio.h>
#include "element.h"

struct element_
{
   int key;
};

ELEMENT *element_create(int key)
{
   ELEMENT *element;

   element = (ELEMENT *)malloc(sizeof(ELEMENT));

   if (element != NULL)
   {
      element->key = key;
      return (element);
   }
   return (NULL);
}

bool element_erase(ELEMENT **element)
{
   if (*element != NULL)
   {
      free(*element);
      *element = NULL;
      return (true);
   }
   return (false);
}

int element_get_key(ELEMENT *element)
{
   if (element != NULL)
      return (element->key);
   exit(1);
}

bool element_set_key(ELEMENT *element, int key)
{
   if (element != NULL)
   {
      element->key = key;
      return (true);
   }
   return (false);
}

void element_print(ELEMENT *element)
{
   if (element != NULL)
      printf("[%d] ", element->key);
}

int element_comparar(ELEMENT *element1, ELEMENT *element2)
{
   if (element1->key == element2->key)
      return 0;
   else if (element1->key > element2->key)
      return 1;
   else
      return -1;
}
