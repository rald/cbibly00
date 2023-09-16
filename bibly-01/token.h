#ifndef TOKEN_H
#define TOKEN_H

#include "common.h"

#define DIE_IMPLEMENTATION
#include "die.h"

typedef enum TokenType {
  TOKENTYPE_UNKNOWN=0,
  TOKENTYPE_STRING,
  TOKENTYPE_INTEGER,
  TOKENTYPE_SPACE,
  TOKENTYPE_COLON,
  TOKENTYPE_DASH,
  TOKENTYPE_COMMA,
  TOKENTYPE_EOF,
  TOKENTYPE_MAX
} TokenType;

char *tokenNames[]={
  "TOKENTYPE_UNKNOWN",
  "TOKENTYPE_STRING",
  "TOKENTYPE_INTEGER",
  "TOKENTYPE_SPACE",
  "TOKENTYPE_COLON",
  "TOKENTYPE_DASH",
  "TOKENTYPE_COMMA",
  "TOKENTYPE_EOF"
};

typedef struct Token Token;

struct Token {
  TokenType type;
  char *text;
};


Token *Token_New(TokenType type,char *text);

void Token_Free(void **token);

void Token_Append(Array *token,TokenType type,char *text);

char *Token_ToString(Token *token);



#ifdef TOKEN_IMPLEMENTATION



Token *Token_New(TokenType type,char *text) {
  Token *token=malloc(sizeof(Token));
  if(token) {
    token->type=type;
    token->text=text?strdup(text):NULL;
  } else {
    die(1,"Error: Token_New: malloc");
  }
  return token;
}



void Token_Free(void **token) {
  free(((Token*)token)->text);
  ((Token*)token)->text=NULL;
}



void Token_Append(Array *tokens,TokenType type,char *text) {
  Array_Push(tokens,Token_New(type,text));
}


char *Token_ToString(Token *token) {
  char *str=malloc(sizeof(char)*STRING_MAX);
  sprintf(str,"{ type: %s, text: \"%s\" }",tokenNames[token->type],token->text);
  return str;
}



#endif /* TOKEN_IMPLEMENTATION */



#endif /* TOKEN_H */
