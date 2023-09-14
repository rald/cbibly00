#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


int main() {

	Info **infos=NULL;
	size_t ninfos=0;

	Token **tokens=NULL;
	size_t ntokens=0;

	Cite **cites=NULL;
	size_t ncites=0;

	Info_Load(&infos,&ninfos,"kjv.inf");

	char *line=NULL;
	size_t llen=0;
	ssize_t rlen=0;

	printf("> ");

	while((rlen=getline(&line,&llen,stdin))!=-1) {

		lex(&tokens,&ntokens,line);

		parse(infos,ninfos,tokens,ntokens,&cites,&ncites);

		Cites_Print(infos,ninfos,cites,ncites);

		Tokens_Free(&tokens,&ntokens);
		Cites_Free(&cites,&ncites);

		free(line);
		line=NULL;
		llen=0;
		rlen=0;

		printf("> ");
	}

	free(line);
	line=NULL;
	llen=0;
	rlen=0;

	Infos_Free(&infos,&ninfos);

	return 0;
}
