#ifndef SYLLOGISM_H_INCLUDED
#define SYLLOGISM_H_INCLUDED

#include "liste.h"
#include <stdbool.h>

//Structure de données représentant un syllogisme lors de sa saisie
typedef struct us
{
    char * first_term;
    char * second_term;
    T_quantifier quantifier;
}user_proposition;

//Structure de données représentant un syllogisme lors de son analyse
typedef struct as
{
    char first_term;
    char second_term;
    bool universal;
    bool affirmative;
}analysis_proposition;

bool isUniversal (analysis_proposition analysis_syllogism);
bool isParticular (analysis_proposition analysis_syllogism);
bool isAffirmative (analysis_proposition analysis_syllogism);
bool isNegative (analysis_proposition analysis_syllogism);
char fstTerm (analysis_proposition analysis_syllogism);
char scdTerm (analysis_proposition analysis_syllogism);

void display_analysis(analysis_proposition p[3]);
void display_syllogism(user_proposition user_syllogism[3]);

void choose_input(T_liste uql, T_liste eql, user_proposition user_syllogism[3]);

void convert_to_analysis(user_proposition user_syllogism[3], analysis_proposition analysis_syllogism[3]);

void free_user_syl(user_proposition p[3]);


#endif // SYLLOGISM_H_INCLUDED
