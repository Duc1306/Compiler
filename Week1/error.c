#include <stdio.h>
#include <stdlib.h>
#include "error.h"

void error(ErrorCode err, int lineNo, int colNo) {
  printf("Error at %d-%d: ", lineNo, colNo);

  switch (err) {
  case ERR_ENDOFCOMMENT:
    printf("End of comment expected!\n");
    break;
  case ERR_IDENTTOOLONG:
    printf("Identifier too long!\n");
    break;
  case ERR_NUMBERTOOLONG:
    printf("Number too long!\n");
    break;
  case ERR_INVALIDCHARCONSTANT:
    printf("Invalid char constant!\n");
    break;
  case ERR_INVALIDSYMBOL:
    printf("Invalid symbol!\n");
    break;
  }

  exit(-1);
}
