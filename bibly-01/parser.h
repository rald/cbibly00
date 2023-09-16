#define CITE_IMPLEMENTATION
#include "cite.h"
#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdbool.h>

#define STRUTIL_IMPLEMENTATION
#include "strutil.h"

#define TOKEN_IMPLEMENTATION
#include "token.h"

#define CITE_IMPLEMENTATION
#include "cite.h"

#define ARRAY_IMPLEMENTATION
#include "array.h"


void parse(Array *infos,Array *tokens,Array *cites);



#ifdef PARSER_IMPLEMENTATION



static size_t i=0;
static Cite *cite=NULL;



void p0(Array *infos,Array *tokens,Array *cites);

void p1(Array *infos,Array *tokens,Array *cites);

void p2(Array *infos,Array *tokens,Array *cites);

void p3(Array *infos,Array *tokens,Array *cites);



void p3(Array *infos,Array *tokens,Array *cites) {

  while(i<tokens->n && A(tokens,i,Token**)->type==TOKENTYPE_COMMA) {
    i+=1;
    if(i<tokens->n && A(tokens,i,Token**)->type==TOKENTYPE_STRING) {
      cite->bnum=0;
      cite->scnum=0;
      cite->ecnum=0;
      cite->svnum=0;
      cite->evnum=0;

      p0(infos,tokens,cites);
    } else if(i+1<tokens->n && A(tokens,i,Token**)->type==TOKENTYPE_INTEGER && A(tokens,i+1,Token**)->type==TOKENTYPE_STRING) {
      cite->bnum=0;
      cite->scnum=0;
      cite->ecnum=0;
      cite->svnum=0;
      cite->evnum=0;

      p0(infos,tokens,cites);
    } else if(i+1<tokens->n && A(tokens,i,Token**)->type==TOKENTYPE_INTEGER  && A(tokens,i+1,Token**)->type==TOKENTYPE_COLON) {
      cite->scnum=0;
      cite->ecnum=0;
      cite->svnum=0;
      cite->evnum=0;

      p1(infos,tokens,cites);

      Cite_Append(cites,Cite_New(cite->bnum,cite->scnum,cite->ecnum,cite->svnum,cite->evnum));

    } else if(i<tokens->n && A(tokens,i,Token**)->type==TOKENTYPE_INTEGER) {

      cite->ecnum=0;
      cite->svnum=0;
      cite->evnum=0;

      p2(infos,tokens,cites);

      Cite_Append(cites,Cite_New(cite->bnum,cite->scnum,cite->ecnum,cite->svnum,cite->evnum));
    }

  }
}



void p2(Array *infos,Array *tokens,Array *cites) {
  if(A(tokens,i,Token**)->type!=TOKENTYPE_EOF) {
    if(
        i+2<tokens->n
        && A(tokens,i,Token**)->type==TOKENTYPE_INTEGER
        && A(tokens,i+1,Token**)->type==TOKENTYPE_DASH
        && A(tokens,i+2,Token**)->type==TOKENTYPE_INTEGER
    ) {
      cite->svnum=atoi(A(tokens,i,Token**)->text);
      cite->evnum=atoi(A(tokens,i+2,Token**)->text);
      i+=3;
    } else if (
        i<tokens->n
        && A(tokens,i,Token**)->type==TOKENTYPE_INTEGER
    ) {
      cite->svnum=atoi(A(tokens,i,Token**)->text);
      cite->evnum=0;
      i+=1;
    }
  }
}



void p1(Array *infos,Array *tokens,Array *cites) {
  if(A(tokens,i,Token**)->type!=TOKENTYPE_EOF) {
    if(
        i+2<tokens->n
        && A(tokens,i,Token**)->type==TOKENTYPE_INTEGER
        && A(tokens,i+1,Token**)->type==TOKENTYPE_DASH
        && A(tokens,i+2,Token**)->type==TOKENTYPE_INTEGER
    ) {
      cite->scnum=atoi(A(tokens,i,Token**)->text);
      cite->ecnum=atoi(A(tokens,i+2,Token**)->text);
      i+=3;
    } else if (
        i<tokens->n
        && A(tokens,i,Token**)->type==TOKENTYPE_INTEGER
    ) {
      cite->scnum=atoi(A(tokens,i,Token**)->text);
      cite->ecnum=0;
      i+=1;

      if(i<tokens->n && A(tokens,i,Token**)->type==TOKENTYPE_COLON) {
        i+=1;
        p2(infos,tokens,cites);
      }
    }
  }
}



void p0(Array *infos,Array *tokens,Array *cites) {

  if(A(tokens,i,Token**)->type!=TOKENTYPE_EOF) {

		if(i<tokens->n && A(tokens,i,Token**)->type==TOKENTYPE_COMMA) {
			p3(infos,tokens,cites);

		} else {

	    char bname[STRING_MAX];
	    bname[0]='\0';

	    if(i<tokens->n && A(tokens,i,Token**)->type==TOKENTYPE_STRING) {
	      strcpy(bname,A(tokens,i,Token**)->text);
	      i+=1;
	    } else if(i+1<tokens->n && A(tokens,i,Token**)->type==TOKENTYPE_INTEGER && A(tokens,i+1,Token**)->type==TOKENTYPE_STRING) {
	      sprintf(bname,"%s %s",A(tokens,i,Token**)->text,A(tokens,i+1,Token**)->text);
	      i+=2;
	    }

	    if((cite->bnum=getbnum(infos,bname))) {

	      p1(infos,tokens,cites);

	     	Cite_Append(cites,Cite_New(cite->bnum,cite->scnum,cite->ecnum,cite->svnum,cite->evnum));

	      p3(infos,tokens,cites);

			}
		}
  }
}



void parse(Array *infos,Array *tokens,Array *cites) {
	i=0;

	cite=Cite_New(0,0,0,0,0);

	p0(infos,tokens,cites);

	Cite_Free((void**)&cite);
}




#endif /* PARSER_IMPLEMENTATION */



#endif /* PARSER_H */




