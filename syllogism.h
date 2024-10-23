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
bool choose_universal_quantifiers();
T_quantifier choose_quantifier(T_liste ql);
user_proposition input_advanced_syllogism(T_liste uql, T_liste eql, user_proposition user_syllogism[3]);
void input_simple_syllogism(T_liste uql, T_liste eql, user_proposition user_syllogism[3]);
void choose_input(T_liste uql, T_liste eql, user_proposition user_syllogism[3]);
void display_syllogism(user_proposition user_syllogism[3]);

void convert_to_analysis(user_proposition user_syllogism[3], analysis_proposition analysis_syllogism[3]);


#endif // SYLLOGISM_H_INCLUDED
