#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liste.h"

void initListe(T_liste *l){
    *l=NULL;
}

bool listeVide(T_liste l){
    return (l==NULL);
}

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

T_liste getptrNextCell(T_liste l)
{
    if((listeVide(l)) || (l->suiv == NULL)){
        return NULL;
    }else{
        return l->suiv;
    }
}

T_quantifier* getPtrData(T_liste l)
{
    if(listeVide(l)){
        printf("Erreur getPtrData : liste vide\n");
        return NULL;
    }else{
        return l->data;
    }
}

void afficheListe(T_liste l)
{
    if(listeVide(l)){

        printf("Erreur afficheListe : liste vide");
    }else{

        T_liste tmp = l;

        T_quantifier* ptrData;

        while(!(listeVide(tmp))){

            ptrData = getPtrData(tmp);

            printf("%s\n", ptrData->quantifier_str);

            tmp = getptrNextCell(tmp);
        }

        free(tmp);
    }
}

int getNbreCell(T_liste l)
{
    if(listeVide(l)){
        return 0;
    }else{
        int i = 0;

        //copie et parcours de la liste avec incr�mentation du nombre de cellule
        T_liste tmp = l;
        while(!(listeVide(tmp))){
            i += 1;
            tmp = tmp->suiv;
        }

        free(tmp);

        return i;
    }
}

void afficheListePos(T_liste l)
{
    if(listeVide(l)){

        printf("Erreur afficheListe : liste vide");
    }else{

        T_liste tmp = l;

        int tmpLen = getNbreCell(tmp);

        T_quantifier* ptrData;

        for(int i = 1; i <= tmpLen; i++){

            ptrData = getPtrData(tmp);

            //ATTENTION : commence à partir de 1
            printf("%d : %s\n", i, ptrData->quantifier_str);

            tmp = getptrNextCell(tmp);
        }

        free(tmp);
    }
}

//Arthur
//Fonction qui libère les ressourcres des listes
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
