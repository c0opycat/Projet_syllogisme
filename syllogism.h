#ifndef SYLLOGISM_H_INCLUDED
#define SYLLOGISM_H_INCLUDED

#include "liste.h"


//Structure de données représentant un syllogisme lors de sa saisie
typedef struct
{
    char * first_term;
    char * second_term;
    T_quantifier quantifier;
}user_proposition;


//Structure de données représentant un syllogisme lors de son analyse
typedef struct
{
    char first_term;
    char second_term;
    bool universal;
    bool affirmative;
}analysis_proposition;



void display_syllogism(user_proposition user_syllogism[3]);
void display_analysis(analysis_proposition p[3]);

void choose_input(T_liste uql, T_liste eql, user_proposition user_syllogism[3]);

void convert_to_analysis(user_proposition user_syllogism[3], analysis_proposition analysis_syllogism[3]);

void free_user_syl(user_proposition p[3]);


#endif // SYLLOGISM_H_INCLUDED
