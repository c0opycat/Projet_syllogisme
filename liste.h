#ifndef LISTE
#define LISTE

#include <stdbool.h>

typedef struct T_cell{
    struct T_cell *suiv;
    struct T_cell *prec;
    char *data;              //attention faire un malloc sur ce champ avant de s'en servir
} T_cellule;

typedef T_cellule *T_liste;

void initListe(T_liste *l);

bool listeVide( T_liste l);

T_liste ajoutEnTete(T_liste l, const char * mydata); //Bien mettre � NULL les champs suiv et prec non utilis�s s'il y en a

T_liste getptrNextCell(T_liste l);

char ** getPtrData(T_liste l);

void afficheListe( T_liste l);


#endif 
