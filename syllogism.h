#ifndef SYLLOGISM_H_INCLUDED
#define SYLLOGISM_H_INCLUDED

#include "liste.h"

typedef struct
{
    char * first_term;
    char * second_term;
    T_quantifier quantifier;
}user_proposition;

typedef struct
{
    char first_term;
    char second_term;
    bool universal;
    bool affirmative;
}analysis_proposition;


T_liste create_list_quantifier();
T_liste add_quantifier(const T_quantifier quantifier, T_liste ql);

void display_quantifier(const T_liste ql);

T_quantifier choose_quantifier(T_liste ql);

char* syl_to_string(user_proposition user_syllogism[3]);

void display_syllogism(user_proposition user_syllogism[3]);
void display_analysis(analysis_proposition p[3]);

void choose_input(T_liste uql, T_liste eql, user_proposition user_syllogism[3]);

void convert_to_analysis(user_proposition user_syllogism[3], analysis_proposition analysis_syllogism[3]);

void free_user_syl(user_proposition p[3]);


#endif // SYLLOGISM_H_INCLUDED
