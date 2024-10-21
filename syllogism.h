#ifndef SYLLOGISME
#define SYLLOGISME

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

T_liste add_quantifier(const T_quantifier quantifier, T_liste  ql );
void display_quantifier(const T_liste  ql);
bool choose_universal_quantifiers();
T_quantifier choose_quantifier(T_liste ql);
void input_simple_syllogism(T_liste uql, T_liste eql);

#endif