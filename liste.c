#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "liste.h"

void initListe(T_liste *l){
    *l=NULL;
}

bool listeVide(T_liste l){
    return (l==NULL);
}

T_liste ajoutEnTete(T_liste l, const char * mydata)
{
    T_liste tmp = (T_liste)malloc(sizeof(struct T_cell));
    tmp->data = (char *)malloc(sizeof(char));

    *(tmp->data) = mydata;

    tmp->suiv = l;

    tmp->prec = NULL;

    if(!(listeVide(l))){
       l->prec = tmp;
    }

    return tmp;
    free(tmp);
    free(tmp->data);
}

T_liste getptrNextCell(T_liste l)
{
    if((listeVide(l)) || (l->suiv == NULL)){
        return NULL;
    }else{
        T_liste tmp = l;

        tmp = tmp->suiv;
        return tmp;

        free(tmp);
    }
}

char ** getPtrData(T_liste l)
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
    //erreur si liste vide
    if(listeVide(l)){
        printf("Erreur afficheListeV2 : liste vide");
    }else{

        //copie de la liste
        T_liste tmp = l;

        //cr�ation d'une variable qui contiendra le pointeur des donn�es d'une cellule
        char** ptrData;

        //parcours de la liste
        while(!(listeVide(tmp))){
            ptrData = getPtrData(tmp);

            //affichage des donn�es de la cellule
            printf(*ptrData);

            tmp = getptrNextCell(tmp);
        }

        //lib�ration des pointeurs
        free(tmp);
    }
}