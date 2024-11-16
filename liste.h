#ifndef LISTE_H_INCLUDED
#define LISTE_H_INCLUDED

#include <stdbool.h>
#include <quantifier.h>


typedef struct T_cell{
    struct T_cell *suiv;
    struct T_cell *prec;
    T_quantifier* data;   
} T_cellule;

typedef T_cellule *T_liste;

void initListe(T_liste *l);

bool listeVide( T_liste l);

T_liste ajoutEnTete(T_liste l, const T_quantifier mydata);

T_liste getptrNextCell(T_liste l);

T_quantifier* getPtrData(T_liste l);

int getNbreCell(T_liste l);

// void afficheListe( T_liste l);

void afficheListePos(T_liste l);

void free_list(T_liste l); 



#endif // LISTE_H_INCLUDED
