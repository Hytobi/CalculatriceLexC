%{
    #include "pile.h"
    #include "calculatrice.h"
%}

OPERATEUR   [\*\+\-\/]
ENTIER      [1-9][0-9]*
IDVAR       m[0-9]*

%%

\.          { return DOT; /* Le point qui termine une ligne de commande */ }
\?          { return QMARK; /* Le point d'interrogation qui commence une ligne de commande d'évaluation */ }
\!          { return EXMARK; /* Le point d'exclamation qui commence une ligne de commande de sauvegarde */ }
\$          { return DOLLAR; /* Le ``dollar'' ($) qui commence une ligne de commande d'affichage du contenu d'une variable */ }
{OPERATEUR} { return OP; /* Un symbole d'opérateur arithmétique */ }
{ENTIER}    { return NUM; /* Une constante entière en notation décimale */ }
{IDVAR}     { return VAR; /* Un nom de variable */ }
[ \t]+      { ; /* Ignorer les espaces et les tabulations */ }
\n          { yylineno++; /* Compter les lignes */ }
.           { printf("Caractère non reconnu\n"); /* traitement de l'erreur */ }

%%

int yywrap() { 
    return 1; 
}