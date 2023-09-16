#ifndef INFO_H
#define INFO_H

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define STRUTIL_IMPLEMENTATION
#include "strutil.h"

#define ARRAY_IMPLEMENTATION
#include "array.h"



typedef struct Info Info;

struct Info {
  size_t bnum;
  char *bname;
  Array *bsnames;
  Array *verscnt;
};


Info *Info_New();

void Info_Free(void **info);

void Info_Append(Array *infos,Info *info);

void Info_Load(Array *infos,char *filename);

void Info_Print(Info *info);

void verscntFree(void **data);



#ifdef INFO_IMPLEMENTATION



Info *Info_New() {
  Info *info=malloc(sizeof(*info));
  if(info) {
    info->bnum=0;
    info->bname=NULL;
    info->bsnames=Array_New(0,Info*);
    info->verscnt=Array_New(0,Info*);
  }
  return info;
}


void Info_Free(void **info) {

	free(((Info*)info)->bname);
	((Info*)info)->bname=NULL;

	Array_Free(&((Info*)info)->bsnames,tokfree);
	((Info*)info)->bnum=0;

	Array_Free(&((Info*)info)->verscnt,verscntFree);
	((Info*)info)->verscnt->n=0;

 	free(*info);
	*info=NULL;
}

void verscntFree(void **data) {
  free(*data);
  *data=NULL;
}


void Info_Append(Array *infos,Info *info) {
  Array_Push(infos,info,Info*);
}



void Info_Load(Array *infos,char *filename) {

  FILE *fp=NULL;

  char *line=NULL;
  size_t llen=0;
  ssize_t rlen=0;

  size_t i;

  if((fp=fopen(filename,"r"))==NULL) die(1,"Error: Info_Load: fopen: %s",strerror(errno));

  while((rlen=getline(&line,&llen,fp))!=-1) {

	  Array *tokens0=NULL;
	  Array *tokens1=NULL;

    tokens0=tokenize(line,"|");

    Info *info=Info_New();

    info->bname=strdup(A(tokens0,0,char*));

    info->bsnames=tokenize(A(tokens0,1,char*),"/");

    info->bnum=atoi(A(tokens0,2,char*));

    tokens1=tokenize(A(tokens0,4,char*),",");

    info->verscnt=Array_New(atoi(A(tokens0,3,char*)),size_t);

    for(i=0;i<atoi(A(tokens0,3,char*));i++) {
      size_t *j=malloc(sizeof(*j));
      *j=(size_t)atoi(A(tokens1,i,char*));
      A(info->verscnt,i,size_t*)=j;
    }

    Info_Append(infos,info);

    Array_Free(&tokens1,tokfree);
    Array_Free(&tokens0,tokfree);

		free(line);
	 	line=NULL;
	  llen=0;
	  rlen=0;
  }

	free(line);
 	line=NULL;
  llen=0;
  rlen=0;

	fclose(fp);

}



void Infos_Print(Array *infos) {
  size_t i,j;

  for(i=0;i<infos->n;i++) {
    printf("%s|",A(infos,i,Info*)->bname);

    for(j=0;j<A(infos,i,Info*)->bsnames->n;j++) {
      if(j!=0) printf("/");
      printf("%s",A(A(infos,i,Info*)->bsnames,j,char*));
    }

    printf("|%zu|%zu|",A(infos,i,Info*)->bnum,A(infos,i,Info*)->verscnt->n);

    for(j=0;j<A(infos,i,Info*)->verscnt->n;j++) {
      if(j!=0) printf(",");
      printf("%zu",A(A(infos,i,Info*)->verscnt,j,size_t));
    }

    printf("\n");
  }
}



#endif /* INFO_IMPLEMENTATION */



#endif /* INFO_H */


