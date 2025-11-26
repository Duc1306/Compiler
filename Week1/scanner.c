#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "reader.h"
#include "charcode.h"
#include "token.h"
#include "error.h"

int state = 0;

void printToken(Token *token)
{
    printf("%d-%d:", token->lineNo, token->colNo);

    switch (token->tokenType)
    {
    case TK_IDENT:
        printf("TK_IDENT(%s)\n", token->string);
        break;

    case TK_NUMBER:
        printf("TK_NUMBER(%d)\n", token->value);
        break;

    case TK_CHAR:
        printf("TK_CHAR('%s')\n", token->string);
        break;

    case TK_EOF:
        printf("TK_EOF\n");
        break;

    /* KEYWORDS */
    case KW_PROGRAM:
        printf("KW_PROGRAM\n");
        break;
    case KW_CONST:
        printf("KW_CONST\n");
        break;
    case KW_TYPE:
        printf("KW_TYPE\n");
        break;
    case KW_VAR:
        printf("KW_VAR\n");
        break;
    case KW_INTEGER:
        printf("KW_INTEGER\n");
        break;
    case KW_CHAR:
        printf("KW_CHAR\n");
        break;
    case KW_ARRAY:
        printf("KW_ARRAY\n");
        break;
    case KW_OF:
        printf("KW_OF\n");
        break;
    case KW_FUNCTION:
        printf("KW_FUNCTION\n");
        break;
    case KW_PROCEDURE:
        printf("KW_PROCEDURE\n");
        break;
    case KW_BEGIN:
        printf("KW_BEGIN\n");
        break;
    case KW_END:
        printf("KW_END\n");
        break;
    case KW_CALL:
        printf("KW_CALL\n");
        break;
    case KW_IF:
        printf("KW_IF\n");
        break;
    case KW_THEN:
        printf("KW_THEN\n");
        break;
    case KW_ELSE:
        printf("KW_ELSE\n");
        break;
    case KW_WHILE:
        printf("KW_WHILE\n");
        break;
    case KW_DO:
        printf("KW_DO\n");
        break;
    case KW_FOR:
        printf("KW_FOR\n");
        break;
    case KW_TO:
        printf("KW_TO\n");
        break;

    /* SPECIAL SYMBOLS */
    case SB_SEMICOLON:
        printf("SB_SEMICOLON\n");
        break;
    case SB_COLON:
        printf("SB_COLON\n");
        break;
    case SB_PERIOD:
        printf("SB_PERIOD\n");
        break;
    case SB_COMMA:
        printf("SB_COMMA\n");
        break;
    case SB_ASSIGN:
        printf("SB_ASSIGN\n");
        break;
    case SB_EQ:
        printf("SB_EQ\n");
        break;
    case SB_NEQ:
        printf("SB_NEQ\n");
        break;
    case SB_LT:
        printf("SB_LT\n");
        break;
    case SB_LE:
        printf("SB_LE\n");
        break;
    case SB_GT:
        printf("SB_GT\n");
        break;
    case SB_GE:
        printf("SB_GE\n");
        break;
    case SB_PLUS:
        printf("SB_PLUS\n");
        break;
    case SB_MINUS:
        printf("SB_MINUS\n");
        break;
    case SB_TIMES:
        printf("SB_TIMES\n");
        break;
    case SB_SLASH:
        printf("SB_SLASH\n");
        break;
    case SB_LPAR:
        printf("SB_LPAR\n");
        break;
    case SB_RPAR:
        printf("SB_RPAR\n");
        break;
    case SB_LSEL:
        printf("SB_LSEL\n");
        break;
    case SB_RSEL:
        printf("SB_RSEL\n");
        break;

    default:
        printf("UNKNOWN TOKEN\n");
    }
}

/* FULL getToken() - EXACT Automaton */
Token *getToken(void)
{
    Token *token;
    int ln, cn;
    char c;

    while (1)
    {

        switch (state)
        {

        /* -----------------------
           STATE 0: START
        ----------------------- */
        case 0:
            if (currentChar == EOF)
            {
                state = 1;
                break;
            }

            switch (charCodes[currentChar])
            {
            case CHAR_SPACE:
                state = 2;
                break;

            case CHAR_LETTER:
                ln = lineNo;
                cn = colNo;
                state = 3;
                break;

            case CHAR_DIGIT:
                ln = lineNo;
                cn = colNo;
                state = 7;
                break;

            case CHAR_PLUS:
                state = 9;
                break;
            case CHAR_MINUS:
                state = 10;
                break;
            case CHAR_TIMES:
                state = 11;
                break;
            case CHAR_SLASH:
                state = 12;
                break;

            case CHAR_LT:
                state = 13;
                break;
            case CHAR_GT:
                state = 16;
                break;
            case CHAR_EXCLAIMATION:
                state = 20;
                break;
            case CHAR_EQ:
                state = 19;
                break;

            case CHAR_COMMA:
                state = 23;
                break;
            case CHAR_SEMICOLON:
                state = 27;
                break;
            case CHAR_PERIOD:
                state = 26;
                break;
            case CHAR_COLON:
                state = 22;
                break;

            case CHAR_SINGLEQUOTE:
                ln = lineNo;
                cn = colNo;
                state = 31;
                break;

            case CHAR_LPAR:
                ln = lineNo;
                cn = colNo;
                state = 35;
                break;

            case CHAR_RPAR:
                state = 42;
                break;

            default:
                error(ERR_INVALIDSYMBOL, lineNo, colNo);
            }
            break;
        case 1:
            return makeToken(TK_EOF, lineNo, colNo);

        /* skip space */
        case 2:
            readChar();
            state = 0;
            break;

        /* identifier */
        case 3:
            token = makeToken(TK_IDENT, ln, cn);
            token->string[0] = '\0';
            state = 4;
            break;

        case 4:
            if (charCodes[currentChar] == CHAR_LETTER ||
                charCodes[currentChar] == CHAR_DIGIT)
            {

                int len = strlen(token->string);
                if (len < MAX_IDENT_LEN)
                {
                    token->string[len] = currentChar;
                    token->string[len + 1] = '\0';
                }
                else
                    error(ERR_IDENTTOOLONG, ln, cn);

                readChar();
            }
            else
            {
                TokenType t = checkKeyword(token->string);
                if (t != TK_NONE)
                    token->tokenType = t;
                state = 0;
                return token;
            }
            break;

        /* number */
        case 7:
            token = makeToken(TK_NUMBER, ln, cn);
            token->string[0] = '\0';
            state = 8;
            break;

        case 8:
            if (charCodes[currentChar] == CHAR_DIGIT)
            {
                int len = strlen(token->string);
                if (len < MAX_IDENT_LEN)
                {
                    token->string[len] = currentChar;
                    token->string[len + 1] = '\0';
                }
                else
                    error(ERR_NUMBERTOOLONG, ln, cn);

                readChar();
            }
            else
            {
                token->value = atoi(token->string);
                state = 0;
                return token;
            }
            break;

            /* one-char tokens */
        case 9:
        { // +
            int ln = lineNo;
            int cn = colNo;
            readChar();
            return makeToken(SB_PLUS, ln, cn);
        }
        case 10:
        { // -
            int ln = lineNo;
            int cn = colNo;
            readChar();
            return makeToken(SB_MINUS, ln, cn);
        }
        case 11:
        { // *
            int ln = lineNo;
            int cn = colNo;
            readChar();
            return makeToken(SB_TIMES, ln, cn);
        }
        case 12:
        { // /
            int ln = lineNo;
            int cn = colNo;
            readChar();
            return makeToken(SB_SLASH, ln, cn);
        }
        case 23:
        { // ,
            int ln = lineNo;
            int cn = colNo;
            readChar();
            return makeToken(SB_COMMA, ln, cn);
        }
        case 27:
        { // ;
            int ln = lineNo;
            int cn = colNo;
            readChar();
            return makeToken(SB_SEMICOLON, ln, cn);
        }
        case 26:
        { // .
            int ln = lineNo;
            int cn = colNo;
            readChar();
            return makeToken(SB_PERIOD, ln, cn);
        }
        case 42:
        { // )
            int ln = lineNo;
            int cn = colNo;
            readChar();
            return makeToken(SB_RPAR, ln, cn);
        }
        case 41:
        { // (
            int ln = lineNo;
            int cn = colNo;
            readChar();
            return makeToken(SB_LPAR, ln, cn);
        }
        case 19:
        { // =
            int ln = lineNo;
            int cn = colNo;
            readChar();
            return makeToken(SB_EQ, ln, cn);
        }
        /* ASSIGN := */
        case 22:
            readChar();
            if (charCodes[currentChar] == CHAR_EQ)
            {
                readChar();
                return makeToken(SB_ASSIGN, lineNo, colNo - 2);
            }
            return makeToken(SB_COLON, lineNo, colNo - 1);

        /* < and <= */
        case 13:
            readChar();
            if (charCodes[currentChar] == CHAR_EQ)
                state = 14;
            else
                state = 15;
            break;

        case 14:
            readChar();
            return makeToken(SB_LE, lineNo, colNo - 1);

        case 15:
            return makeToken(SB_LT, lineNo, colNo - 1);

        /* > and >= */
        case 16:
            readChar();
            if (charCodes[currentChar] == CHAR_EQ)
            {
                readChar();
                return makeToken(SB_GE, lineNo, colNo - 2);
            }
            return makeToken(SB_GT, lineNo, colNo - 1);

        /* != */
        case 20:
            readChar();
            if (charCodes[currentChar] == CHAR_EQ)
            {
                readChar();
                return makeToken(SB_NEQ, lineNo, colNo - 2);
            }
            error(ERR_INVALIDSYMBOL, lineNo, colNo - 1);

        /* CHAR CONSTANT */
        case 31:
            readChar();
            if (currentChar == EOF)
                state = 34;
            else if (isprint(currentChar))
                state = 32;
            else
                state = 34;
            break;

        case 32:
            c = currentChar;
            readChar();

            if (charCodes[currentChar] == CHAR_SINGLEQUOTE)
                state = 33;
            else
                state = 34;

            break;

        case 33:
            token = makeToken(TK_CHAR, lineNo, colNo - 1);
            token->string[0] = c;
            token->string[1] = '\0';
            readChar();
            state = 0;
            return token;

        case 34:
            error(ERR_INVALIDCHARCONSTANT, lineNo, colNo - 2);

        case 35:
        { // '('
            int ln = lineNo;
            int cn = colNo;

            readChar(); // đọc ký tự tiếp theo để biết LSEL hay COMMENT
            if (currentChar == '.')
            {
                readChar();
                return makeToken(SB_LSEL, ln, cn);
            }
            if (currentChar == '*')
            {
                state = 38; // comment
                break;
            }

            // Nếu không phải . hoặc * → đây là SB_LPAR
            return makeToken(SB_LPAR, ln, cn);
        }

        case 36:
            readChar();
            return makeToken(SB_LSEL, lineNo, colNo - 2);

        /* comment (* ... *) */
        case 38:
            readChar();
            if (currentChar == EOF)
                error(ERR_ENDOFCOMMENT, lineNo, colNo);
            if (charCodes[currentChar] == CHAR_TIMES)
                state = 39;
            break;

        case 39:
            readChar();
            if (currentChar == EOF)
                error(ERR_ENDOFCOMMENT, lineNo, colNo);
            if (charCodes[currentChar] == CHAR_RPAR)
            {
                readChar();
                state = 0;
            }
            else
                state = 38;
            break;

        } 

    } 
}


int scan(char *fileName)
{

    if (openInputStream(fileName) < 0)
        return -1;

    initCharCodes();

    Token *token = getToken();

    while (token->tokenType != TK_EOF)
    {
        printToken(token);
        free(token);
        state = 0;
        token = getToken();
    }

    if (token->tokenType != TK_EOF)
        printToken(token);

    free(token);
    closeInputStream();
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        printf("Usage: scanner <filename>\n");
        return -1;
    }

    return scan(argv[1]);
}
