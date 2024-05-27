#include <stdlib.h>
#include <stdio.h>

#include "ADTs/element.h"

struct element_
{ 
   int key;
};

Element *element_create(int key)
{
   Element *element = malloc(sizeof(Element)); validate_alocation(element);
   element->key = key;
   return(element);
   return(NULL);
}

bool element_erase(Element **element)
{
   if (*element != NULL){
      free (*element);
      *element = NULL;
      return(true);
   }
   return(false);
}

int element_get_key(Element *element)
{
   if (element != NULL)
      return(element->key);

   exit(1);
}

bool element_set_key(Element *element, int key)
{
   if (element != NULL){
      element->key = key;
      return (true);
   }
   return (false);
}

void element_print(Element *element)
{
   if (element != NULL){
      printf("%d ", element->key + 1);
   }
     
}

size_t element_size()
{
   return sizeof(Element*);
}