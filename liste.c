#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#include "liste.h"

void initListe(T_liste *l){
    *l=NULL;
}

bool listeVide(T_liste l){
    return (l==NULL);
}

T_liste ajoutEnTete(T_liste l, T_quantifier mydata)
{
    T_liste tmp = (T_liste)malloc(sizeof(T_cellule));
    tmp->data = (T_quantifier*)malloc(sizeof(T_quantifier));
    tmp->data->quantifier_str = (char*)malloc(sizeof(char) * strlen(mydata.quantifier_str));

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
    //erreur si liste vide
    if(listeVide(l)){
        printf("Erreur afficheListeV2 : liste vide");
    }else{

        //copie de la liste
        T_liste tmp = l;

        //cr�ation d'une variable qui contiendra le pointeur des donn�es d'une cellule
        T_quantifier* ptrData;

        //parcours de la liste
        while(!(listeVide(tmp))){
            ptrData = getPtrData(tmp);

            //affichage des donn�es de la cellule
            printf(ptrData->quantifier_str);

            tmp = getptrNextCell(tmp);
        }

        //lib�ration des pointeurs
        free(tmp);
    }

    
}

void main()
{
    T_liste test;
    initListe(&test);
    T_quantifier myd = {"Hello", false};
    test = ajoutEnTete(test, myd);
    afficheListe(test);
}