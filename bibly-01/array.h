#ifndef ARRAY_H
#define ARRAY_H



#include <stdio.h>


#define DIE_IMPLEMENTATION
#include "die.h"



#define A(array,index,type) (((type)array->d)[index])



typedef struct Array Array;
typedef void(FnFree)(void **data);

struct Array {
  void **d;
  size_t n;
};

Array *Array_New(size_t n);

void Array_Free(Array **array,FnFree *fnFree);

void Array_Realloc(Array *array,size_t n);

void Array_Push(Array *array,void *data);

#ifdef ARRAY_IMPLEMENTATION



Array *Array_New(size_t n) {
  Array *array=malloc(sizeof(*array));
  if(array) {
    array->d=NULL;
    array->n=0;

    if(n>0) {
      Array_Realloc(array,n);
    }

  }
  return array;
}



void Array_Free(Array **array,FnFree *fnFree) {
  int i;
  for(i=0;i<(*array)->n;i++) {
    fnFree(&((*array)->d[i]));
  }
  free(*array);
  *array=NULL;
}


void Array_Realloc(Array *array,size_t n) {
  void *tmp=realloc(array->d,sizeof(*(array->d))*n);
  if(tmp) {
    array->d=tmp;
    array->n=n;
  } else {
    die(1,"Error: Array_Realloc: realloc");
  }
}



void Array_Push(Array *array,void *data) {
  Array_Realloc(array,array->n+1);  array->d[array->n++]=data;
}



#endif /* ARRAY_IMPLEMENTATION*/



#endif /* ARRAY_H */


