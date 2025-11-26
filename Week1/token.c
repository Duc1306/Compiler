#include <string.h>
#include <stdlib.h>
#include "token.h"

typedef struct {
  char *string;
  TokenType tokenType;
} Keyword;

Keyword keywords[] = {
  {"PROGRAM", KW_PROGRAM},
  {"CONST", KW_CONST},
  {"TYPE", KW_TYPE},
  {"VAR", KW_VAR},
  {"INTEGER", KW_INTEGER},
  {"CHAR", KW_CHAR},
  {"ARRAY", KW_ARRAY},
  {"OF", KW_OF},
  {"FUNCTION", KW_FUNCTION},
  {"PROCEDURE", KW_PROCEDURE},
  {"BEGIN", KW_BEGIN},
  {"END", KW_END},
  {"CALL", KW_CALL},
  {"IF", KW_IF},
  {"THEN", KW_THEN},
  {"ELSE", KW_ELSE},
  {"WHILE", KW_WHILE},
  {"DO", KW_DO},
  {"FOR", KW_FOR},
  {"TO", KW_TO},
  {NULL, TK_NONE}
};

TokenType checkKeyword(char *string) {
  for (int i=0; keywords[i].string != NULL; i++) {
    if (strcasecmp(string, keywords[i].string) == 0)
      return keywords[i].tokenType;
  }
  return TK_NONE;
}

Token *makeToken(TokenType tokenType, int lineNo, int colNo) {
  Token *token = (Token*)malloc(sizeof(Token));
  token->tokenType = tokenType;
  token->lineNo = lineNo;
  token->colNo = colNo;
  token->string[0] = '\0';
  token->value = 0;
  return token;
}
