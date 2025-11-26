#include "charcode.h"
#include <ctype.h>

CharCode charCodes[256];

void initCharCodes() {
  for (int i = 0; i < 256; i++)
    charCodes[i] = CHAR_UNKNOWN;

  for (int c = 'A'; c <= 'Z'; c++) charCodes[c] = CHAR_LETTER;
  for (int c = 'a'; c <= 'z'; c++) charCodes[c] = CHAR_LETTER;

  for (int c = '0'; c <= '9'; c++) charCodes[c] = CHAR_DIGIT;

  charCodes[' '] = CHAR_SPACE;
  charCodes['\t'] = CHAR_SPACE;
  charCodes['\n'] = CHAR_SPACE;
  charCodes['\r'] = CHAR_SPACE;

  charCodes['+'] = CHAR_PLUS;
  charCodes['-'] = CHAR_MINUS;
  charCodes['*'] = CHAR_TIMES;
  charCodes['/'] = CHAR_SLASH;
  charCodes['<'] = CHAR_LT;
  charCodes['>'] = CHAR_GT;
  charCodes['!'] = CHAR_EXCLAIMATION;
  charCodes['='] = CHAR_EQ;
  charCodes[','] = CHAR_COMMA;
  charCodes['.'] = CHAR_PERIOD;
  charCodes[':'] = CHAR_COLON;
  charCodes[';'] = CHAR_SEMICOLON;
  charCodes['\''] = CHAR_SINGLEQUOTE;
  charCodes['('] = CHAR_LPAR;
  charCodes[')'] = CHAR_RPAR;
}
