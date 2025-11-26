#include <stdio.h>
#include "reader.h"

static FILE *inputStream = NULL;

int lineNo = 1;
int colNo = 0;
int currentChar = ' ';

int readChar(void) {
    int ch = fgetc(inputStream);

    if (ch == EOF) {
        currentChar = EOF;
        return EOF;
    }

    currentChar = ch;

    // Xử lý xuống dòng
    if (ch == '\n') {
        lineNo++;
        colNo = 0;      // chuẩn: colNo = 0, để ký tự đầu tiên tiếp theo trở thành colNo = 1
    } else {
        colNo++;        // mỗi ký tự đọc vào đều tăng colNo
    }

    return currentChar;
}

int openInputStream(char *fileName) {
    inputStream = fopen(fileName, "r");
    if (inputStream == NULL)
        return -1;

    lineNo = 1;
    colNo = 0;
    readChar();   // đọc ký tự đầu tiên
    return 0;
}

void closeInputStream(void) {
    if (inputStream != NULL)
        fclose(inputStream);
}
