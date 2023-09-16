#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define STRUTIL_IMPLEMENTATION
#include "strutil.h"

#define ARRAY_IMPLEMENTATION
#include "array.h"

double drand() {
	return rand()/(1.0+RAND_MAX);
}

int main(void) {

	srand(time(NULL));

	FILE *fin=NULL;

	char *line=NULL;
	size_t llen=0;
	ssize_t rlen=0;

	size_t n=0;

  Array *t=NULL;


	char *sel=NULL;

	fin=fopen("kjv.csv","r");

	while((rlen=getline(&line,&llen,fin))!=-1) {

		if(drand()<1.0/++n) {
			if(sel!=NULL) free(sel);
			sel=strdup(line);
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

	t=tokenize(sel,"|");

	printf("%s %s:%s -> %s\n",A(t,0,char*),A(t,1,char*),A(t,2,char*),A(t,3,char*));

  Array_Free(&t,tokfree);

	free(sel);

	return 0;
}

