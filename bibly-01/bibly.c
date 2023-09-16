#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define PROMPT "> "



#define DIE_IMPLEMENTATION
#include "die.h"

#define INFO_IMPLEMENTATION
#include "info.h"

#define TOKEN_IMPLEMENTATION
#include "token.h"

#define LEXER_IMPLEMENTATION
#include "lexer.h"

#define PARSER_IMPLEMENTATION
#include "parser.h"

#define CITE_IMPLEMENTATION
#include "cite.h"

#define ARRAY_IMPLEMENTATION
#include "array.h"



int main() {

  Array *infos=Array_New(0);
  Array *tokens=Array_New(0);
  Array *cites=Array_New(0);

	Info_Load(infos,"kjv.inf");

	char *line=NULL;
	size_t llen=0;
	ssize_t rlen=0;

	printf(PROMPT);

	while((rlen=getline(&line,&llen,stdin))!=-1) {

		lex(tokens,line);

		parse(infos,tokens,cites);

		Cites_Print(infos,cites);

		Array_Free(&tokens,Token_Free);
		Array_Free(&cites,Cite_Free);

		free(line);
		line=NULL;
		llen=0;
		rlen=0;

		printf(PROMPT);
	}

	free(line);
	line=NULL;
	llen=0;
	rlen=0;

	Array_Free(&infos,Info_Free);

	return 0;
}
