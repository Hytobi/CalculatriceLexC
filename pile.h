#ifndef PILE_H
#define PILE_H

#define MAX 100 // taille maximale de la pile

typedef struct _pile
{
    float tab[MAX];
    int size;
} Pile;

Pile *creerPile();
int estVide(Pile *p);
void viderPile(Pile *p);
void empiler(Pile *p, float val);
float depiler(Pile *p);
float sommet(Pile *p);
void detruirePile(Pile *p);

#endif