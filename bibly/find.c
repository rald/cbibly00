#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define STRUTIL_IMPLEMENTATION
#include "strutil.h"

int main(int argc,char **argv) {


	char *line=NULL;
	size_t llen=0;
	ssize_t rlen=0;
	FILE *fin=NULL;
	size_t i;

  if(argc<2) {
    printf("syntax: %s \"search text\"",argv[0]);
    return 1;
  }

	fin=fopen("kjv.csv","r");

	while((rlen=getline(&line,&llen,fin))!=-1) {

    for(i=1;i<argc;i++) {
      if(strcasestr(line,argv[i])) {

      	Array *t=NULL;

      	t=tokenize(line,"|");

      	printf("%s %s:%s -> %s\n",A(t,0,char*),A(t,1,char*),A(t,2,char*),A(t,3,char*));

        Array_Free(&t,tokfree);

        break;
      }
    }

		free(line);
		line=NULL;
		llen=0;
		rlen=0;
	}

	free(line);
	line=NULL;
	llen=0;
	rlen=0;

	return 0;
}
