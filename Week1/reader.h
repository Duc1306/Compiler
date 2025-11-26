#ifndef __READER_H__
#define __READER_H__

extern int lineNo;
extern int colNo;
extern int currentChar;

int readChar(void);
int openInputStream(char *fileName);
void closeInputStream(void);

#endif
