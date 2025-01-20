#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include <stdbool.h>


//Types élémentaires
typedef int MYVAL;
typedef bool MYBOOL;
typedef char MYCHAR;
typedef char* MYPCHAR;

//Structure de données représentant un quantificateur
typedef struct T_quant{
	MYPCHAR quantifier_str;
    MYBOOL universal;
	MYBOOL affirmative;
}T_quantifier;

//Structure de données représentant une cellule
typedef struct T_cell{
    struct T_cell *suiv;
    struct T_cell *prec;
    T_quantifier* data;
} T_cellule;

//Structure de données représentant une liste
typedef T_cellule *T_liste;


//Structure de données représentant une proposition lors de sa saisie
typedef struct up
{
    MYPCHAR first_term;
    MYPCHAR second_term;
    T_quantifier quantifier;
}user_proposition;

//Structure de données représentant une proposition lors de son analyse
typedef struct ap
{
    MYCHAR first_term;
    MYCHAR second_term;
    MYBOOL universal;
    MYBOOL affirmative;
}analysis_proposition;

//Structure de données représentant un syllogisme lors de la saisie
typedef struct us
{
    user_proposition up[3];
}user_syllogism;

//Structure de données représentant un syllogisme lors de l'analyse
typedef struct as
{
    analysis_proposition ap[3];
}analysis_syllogism;


#endif