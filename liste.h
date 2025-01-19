#ifndef LISTE_H_INCLUDED
#define LISTE_H_INCLUDED

#include <stdbool.h>
#include "utils.h"
#include "types.h"


void initListe(T_liste *l);

MYBOOL listeVide( T_liste l);

T_liste ajoutEnTete(T_liste l, const T_quantifier mydata);

T_liste ajouterEnFin(T_liste liste, T_quantifier* nouvDonnee);

T_liste getptrNextCell(T_liste l);

T_quantifier* getPtrData(T_liste l);

MYVAL getNbreCell(T_liste l);

void afficheListePos(T_liste l);

void free_list(T_liste l);



#endif // LISTE_H_INCLUDED
