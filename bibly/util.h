#ifndef UTIL_H
#define UTIL_H



#define _GNU_SOURCE

#include <string.h>
#include <math.h>
#include <sys/types.h>



#define INFO_IMPLEMENTATION
#include "info.h"

#define STRUTIL_IMPLEMENTATION
#include "strutil.h"

#define ARRAY_IMPLEMENTATION
#include "array.h"



size_t getbnum(Array *infos,char *bname);
char *getbname(Array *infos,size_t bnum);
void search(char *text);



#ifdef UTIL_IMPLEMENTATION



size_t getbnum(Array *infos,char *bname) {
  size_t j,k;
  if(bname && *bname) {
    for(j=0;j<infos->n;j++) {
      if(strcasecmp(bname,A(infos,j,Info*)->bname)==0) {
        return A(infos,j,Info*)->bnum;
      }
      for(k=0;k<A(infos,j,Info*)->bsnames->n;k++) {
        if(strcasecmp(bname,A(A(infos,j,Info*)->bsnames,k,char*))==0) {
          return A(infos,j,Info*)->bnum;
        }
      }
    }
  }
  return 0;
}



char *getbname(Array *infos,size_t bnum) {
  size_t j;
  for(j=0;j<infos->n;j++) {
    if(bnum==A(infos,j,Info*)->bnum) {
      return A(infos,j,Info*)->bname;
    }
  }
  return NULL;
}



void search(char *text) {

	trim(text);
 	if(text && *text) {

		FILE *fp=fopen("kjv.csv","r");

		char *line=NULL;
		size_t llen=0;
		ssize_t rlen=0;

		while((rlen=getline(&line,&llen,fp))!=-1) {
			Array *tokens=Array_New(0,Token*);

			rmnl(line);
			trim(line);

			tokens=tokenize(line,"|");

			char *bname=A(tokens,0,char*);
			size_t cnum=atoi(A(tokens,1,char*));
			size_t vnum=atoi(A(tokens,2,char*));
			char *vers=A(tokens,3,char*);

			char passage[1024];

			sprintf(passage,"%s %zu:%zu %s",bname,cnum,vnum,vers);

			if(strcasestr(passage,text)) {

				printf("%s %zu:%zu -> %s\n\n",bname,cnum,vnum,vers);
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
}



#endif /* UTIL_IMPLEMEMTATION */



#endif /* UTIL_H */



