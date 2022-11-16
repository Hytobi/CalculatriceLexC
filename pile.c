#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "pile.h"

Pile *creerPile()
{
    Pile *p = (Pile *)malloc(sizeof(Pile));
    p->size = 0;
    return p;
}
int estVide(Pile *p)
{
    return p->size == 0;
}
void viderPile(Pile *p)
{
    p->size = 0;
}
void empiler(Pile *p, float val)
{
    assert(p->size < MAX);
    p->tab[p->size] = val;
    p->size++;
}
float depiler(Pile *p)
{
    assert(p->size > 0);
    p->size--;
    return p->tab[p->size];
}
float sommet(Pile *p)
{
    assert(p->size > 0);
    return p->tab[p->size - 1];
}
void detruirePile(Pile *p)
{
    free(p);
}