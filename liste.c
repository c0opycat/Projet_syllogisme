#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "liste.h"
#include "types.h"
#include "utils.h"



//Initialisation d'une liste
void initListe(T_liste *l){
    *l=NULL;
}

//Retourne true si la liste est vide
MYBOOL listeVide(T_liste l){
    return (l==NULL);
}


//Ajout d'un élément en tête d'une liste
T_liste ajoutEnTete(T_liste l, const T_quantifier mydata)
{
    T_liste tmp = (T_liste)malloc(sizeof(T_cellule));
    tmp->data = (T_quantifier*)malloc(sizeof(T_quantifier));

    *(tmp->data) = mydata;

    tmp->suiv = l;

    tmp->prec = NULL;

    if(!(listeVide(l))){

        l->prec = tmp;
    }

    return tmp;
}

T_liste ajouterEnFin(T_liste liste, T_quantifier* nouvDonnee) {
    // Créer une nouvelle cellule
    T_cellule* nouvelleCell = malloc(sizeof(T_cellule));
    
    // Vérifier l'allocation de mémoire pour la cellule
    if (nouvelleCell == NULL) {
        printf("Erreur d'allocation mémoire pour la nouvelle cellule\n");
        return liste;
    }
    
    // Allouer de la mémoire pour les données du quantificateur
    nouvelleCell->data = malloc(sizeof(T_quantifier));
    
    // Vérifier l'allocation de mémoire pour les données
    if (nouvelleCell->data == NULL) {
        printf("Erreur d'allocation mémoire pour les données\n");
        free(nouvelleCell);
        return liste;
    }
    
    // Copier les données du quantificateur
    memcpy(nouvelleCell->data, nouvDonnee, sizeof(T_quantifier));
    
    // Initialiser les pointeurs de la nouvelle cellule
    nouvelleCell->suiv = NULL;
    nouvelleCell->prec = NULL;
    
    // Si la liste est vide, la nouvelle cellule devient la tête
    if (liste == NULL) {
        return nouvelleCell;
    }
    
    // Trouver le dernier élément de la liste
    T_cellule* dernier = liste;
    while (dernier->suiv != NULL) {
        dernier = dernier->suiv;
    }
    
    // Chaînage de la nouvelle cellule
    dernier->suiv = nouvelleCell;
    nouvelleCell->prec = dernier;
    
    return liste;
}

//Retourne le pointeur vers la cellule suivante de la liste
T_liste getptrNextCell(T_liste l)
{
    if((listeVide(l)) || (l->suiv == NULL)){
        return NULL;
    }else{
        return l->suiv;
    }
}

//Retourne le pointeur vers l'élément contenu dans la cellule
T_quantifier* getPtrData(T_liste l)
{
    if(listeVide(l)){
        printf("Erreur getPtrData : liste vide\n");
        return NULL;
    }else{
        return l->data;
    }
}


//Retourne le nombre d'éléments dans la liste
MYVAL getNbreCell(T_liste l)
{
    if(listeVide(l)){
        return 0;
    }else{
        MYVAL i = 0;

        //copie et parcours de la liste avec incrémentation du nombre de cellule
        T_liste tmp = l;
        while(!(listeVide(tmp))){
            i += 1;
            tmp = tmp->suiv;
        }

        free(tmp);

        return i;
    }
}

//Affiche chaque élément de la liste avec sa position
void afficheListePos(T_liste l)
{
    if(listeVide(l)){

        printf("Erreur afficheListe : liste vide\n");
    }else{

        T_liste tmp = l;

        MYVAL tmpLen = getNbreCell(tmp);

        T_quantifier* ptrData;

        for(MYVAL i = 1; i <= tmpLen; i++){

            ptrData = getPtrData(tmp);

            //ATTENTION : commence à partir de 1
            printf("%d : %s\n", i, ptrData->quantifier_str);

            tmp = getptrNextCell(tmp);
        }

        free(tmp);
    }
}

//Arthur
//Fonction qui libère les ressourcres d'une liste
void free_list(T_liste l) {
    T_liste current = l;
    T_liste next;

    while (getptrNextCell(current) != NULL) {
        next = getptrNextCell(current);

        if (current->data != NULL) {
            free(current->data);
        }

        free(current);
        current = next;
    }

    //libération de la dernière case
    free(current);
}
