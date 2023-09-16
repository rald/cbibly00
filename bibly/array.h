#ifndef ARRAY_H
#define ARRAY_H



#include <stdio.h>



#define DIE_IMPLEMENTATION
#include "die.h"



#define A(a,i,t) ((t*)a->d)[i]



#define Array_Realloc(a,c,t) realloc(a->d,sizeof(t)*c)



#define Array_New(c,t) ({ \
  Array *a=malloc(sizeof(*a)); \
  do { \
    if(a) { \
      a->d=NULL; \
      a->n=0; \
      if(c>0) { \
        a->d=Array_Realloc(a,c,t); \
      } \
    } else { \
      die(1,"Error: Array_New: malloc"); \
    } \
  } while(0); \
  a; \
})



#define Array_Push(a,v,t) ({ \
  do { \
    a->d=Array_Realloc(a,a->n+1,t); \
    a->d[a->n++]=v; \
  } while(0); \
})


typedef struct Array Array;
typedef void(FnFree)(void **data);

struct Array {
  void **d;
  size_t n;
};



void Array_Free(Array **array,FnFree *fnFree);



#ifdef ARRAY_IMPLEMENTATION



void Array_Free(Array **array,FnFree *fnFree) {
  int i;
  if(*array) {
    for(i=0;i<(*array)->n;i++) {
      if((*array)->d[i]) fnFree(&(*array)->d[i]);
    }
    (*array)->n=0;
    free(*array);
    *array=NULL;
  }
}



#endif /* ARRAY_IMPLEMENTATION*/



#endif /* ARRAY_H */


