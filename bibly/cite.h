#ifndef CITE_H
#define CITE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



#define INFO_IMPLEMENTATION
#include "info.h"

#define STRUTIL_IMPLEMENTATION
#include "strutil.h"

#define UTIL_IMPLEMENTATION
#include "util.h"



typedef struct Cite Cite;

struct Cite {
  size_t bnum;
  size_t scnum;
  size_t ecnum;
  size_t svnum;
  size_t evnum;
};



Cite *Cite_New(size_t bnum,size_t scnum,size_t ecnum,size_t svnum,size_t evnum);

void Cite_Free(void **cite);
void Cite_Append(Array *cites,Cite *cite);

void Cite_Print(Array *infos,Cite *cite);

void Cites_Print(Array *infos,Array *cites);



#ifdef CITE_IMPLEMENTATION



#endif /* CITE_IMPLEMENTATION */



Cite *Cite_New(size_t bnum,size_t scnum,size_t ecnum,size_t svnum,size_t evnum) {
  Cite *cite=malloc(sizeof(Cite));
  if(cite) {
    cite->bnum=bnum;
    cite->scnum=scnum;
    cite->ecnum=ecnum;
    cite->svnum=svnum;
    cite->evnum=evnum;
  }
  return cite;
}



void Cite_Free(void **cite) {
	free(*cite);
	*cite=NULL;
}




void Cite_Append(Array *cites,Cite *cite) {
   Array_Push(cites,cite,Cite*);
}



void Cite_Print(Array *infos,Cite *cite) {

  FILE *fp=fopen("kjv.csv","r");

  char *line=NULL;
  size_t llen=0;
  ssize_t rlen=0;

  char *bname=getbname(infos,cite->bnum);
  size_t scnum=cite->scnum;
  size_t ecnum=cite->ecnum?cite->ecnum:scnum;
  size_t svnum=cite->svnum;
  size_t evnum=cite->evnum?cite->evnum:svnum;

  while((rlen=getline(&line,&llen,fp))!=-1) {

		rmnl(line);

    Array *tokens=NULL;

    tokens=tokenize(line,"|");

    char *hbname=A(tokens,0,char*);
    size_t hcnum=atoi(A(tokens,1,char*));
    size_t hvnum=atoi(A(tokens,2,char*));
    char *htext=A(tokens,3,char*);

    if(
        strcasecmp(bname,hbname)==0 &&
        ((svnum==0 && evnum==0 && hcnum>=scnum && hcnum<=ecnum) ||
        (hcnum==scnum && hvnum>=svnum && hvnum<=evnum) ||
        (ecnum==0 && evnum==0 && hcnum==scnum && hvnum==svnum))
    ) {

			printf("%s %zu:%zu -> %s\n\n",hbname,hcnum,hvnum,htext);

    }

    Array_Free(&tokens,tokfree);

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



void Cites_Print(Array *infos,Array *cites) {
  size_t i;
  printf("\n");
  for(i=0;i<cites->n;i++) {
    Cite_Print(infos,A(cites,i,Cite*));
  }
}



#endif /* CITE_H */


