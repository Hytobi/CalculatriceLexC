#include <stdio.h>
#include <stdlib.h>
#include "pile.h"
#include "calculatrice.h"

#define ERREUR()                                       \
    {                                                  \
        printf("Syntax error at line %d\n", yylineno); \
        etat = SKIP;                                   \
    }

extern int yylex();
extern int yylineno;
extern char *yytext;
float bucket[SIZE];
Pile *pile;
etats etat;

void point()
{
    switch (etat)
    {
    case WAIT:
        exit(EXIT_SUCCESS);
        break;
    case EVALCMD:
        bucket[0] = sommet(pile);
        printf("%.6f\n", bucket[0]);
        viderPile(pile);
        etat = WAIT;
        break;
    default:
        etat = WAIT;
    }
}
void interrogation()
{
    switch (etat)
    {
    case WAIT:
        etat = EVALCMD;
        break;
    case SKIP:
        break;
    default:
        ERREUR();
    }
}

void exclamation()
{
    switch (etat)
    {
    case WAIT:
        etat = STOCMD;
        break;
    case SKIP:
        break;
    default:
        ERREUR();
    }
}

void dollar()
{
    switch (etat)
    {
    case WAIT:
        etat = DISCMD;
        break;
    case SKIP:
        break;
    default:
        ERREUR();
    }
}

void operation()
{
    switch (etat)
    {
    case EVALCMD:
        char monOpChar = yytext[0];
        op monOp;
        switch (monOpChar)
        {
        case '+':
            monOp = PLUS;
            break;
        case '-':
            monOp = MOINS;
            break;
        case '*':
            monOp = MULT;
            break;
        case '/':
            monOp = DIV;
            break;
        }
        bucket[1] = sommet(pile);
        depiler(pile);
        bucket[0] = sommet(pile);
        depiler(pile);

        switch (monOp)
        {
        case PLUS:
            empiler(pile, bucket[0] + bucket[1]);
            break;
        case MOINS:
            empiler(pile, bucket[0] - bucket[1]);
            break;
        case MULT:
            empiler(pile, bucket[0] * bucket[1]);
            break;
        case DIV:
            empiler(pile, bucket[0] / bucket[1]);
            break;
        default:
            ERREUR();
        }
        break;
    case SKIP:
        break;
    default:
        ERREUR();
    }
}

void nombre()
{
    switch (etat)
    {
    case EVALCMD:
        empiler(pile, atof(yytext));
        break;
    case SKIP:
        break;
    default:
        ERREUR();
    }
}

void variable()
{
    switch (etat)
    {
    case STOCMD:
        bucket[atoi(++yytext)] = bucket[0];
        break;
    case DISCMD:
        ++yytext;
        printf("%.6f\n", bucket[atoi(++yytext)]);
        etat = WAIT;
        break;
    case EVALCMD:
        empiler(pile, bucket[atoi(++yytext)]);
        break;
    case SKIP:
        break;
    default:
        ERREUR();
    }
}

int main()
{
    pile = creerPile();
    etat = WAIT;
    tokens ntoken;

    while (1)
    {
        ntoken = yylex();

        if (ntoken < 0)
            break;
        switch (ntoken)
        {
        case DOT:
            point();
            break;
        case QMARK:
            interrogation();
            break;
        case EXMARK:
            exclamation();
            break;
        case DOLLAR:
            dollar();
            break;
        case OP:
            operation();
            break;
        case NUM:
            nombre();
            break;
        case VAR:
            variable();
            break;
        default:
            printf("Syntax error at line %d", yylineno);
            etat = SKIP;
        }
    }

    detruirePile(pile);
    return EXIT_SUCCESS;
}