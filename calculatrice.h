#ifndef CALCULATRICE_H
#define CALCULATRICE_H

#include "pile.h"
#define SIZE 100

typedef enum _tokens
{
    DOT,
    QMARK,
    EXMARK,
    DOLLAR,
    OP,
    NUM,
    VAR
} tokens;

typedef enum _etats
{
    WAIT,
    DISCMD,
    STOCMD,
    EVALCMD,
    SKIP
} etats;

typedef enum _op
{
    PLUS,
    MOINS,
    MULT,
    DIV
} op;

#endif
