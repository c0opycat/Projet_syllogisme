#ifndef SYLLOGISME
#define SYLLOGISME

#include "liste.h"

typedef struct
{
    char * first_term;
    char * second_term;
    char * quantity;
    char * quality;
}user_proposition;

typedef struct 
{
    char first_term;
    char second_term;
    bool universal;
    bool affirmative;
}analysis_proposition;

// user_proposition user_syllogism[3];
// analysis_proposition analysis_syllogism[3];

T_liste add_quantifier(const char * quantifier, T_liste  ql );
void display_quantifier(const T_liste  ql);


#endif