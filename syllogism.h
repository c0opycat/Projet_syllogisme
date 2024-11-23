#ifndef SYLLOGISM_H_INCLUDED
#define SYLLOGISM_H_INCLUDED

#include <stdbool.h>
#include "liste.h"
#include "quantifier.h"

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

//Getter
char* get_user_fst_term(user_proposition user_prop);
char* get_user_scd_term(user_proposition user_prop);
T_quantifier get_user_quantifier(user_proposition user_prop);
bool isUniversal (analysis_proposition analysis_syllogism);
bool isParticular (analysis_proposition analysis_syllogism);
bool isAffirmative (analysis_proposition analysis_syllogism);
bool isNegative (analysis_proposition analysis_syllogism);
char fstTerm (analysis_proposition analysis_syllogism);
char scdTerm (analysis_proposition analysis_syllogism);

//Setter
void set_user_fst_term(user_proposition* user_prop, char* term);
void set_user_scd_term(user_proposition* user_prop, char* term);
void set_user_prop(user_proposition* user_prop, char* fst, char* scd);
void set_analysis_fst_term(analysis_proposition* analysis_prop, char term);
void set_analysis_scd_term(analysis_proposition* analysis_prop, char term);
void set_analysis_prop(analysis_proposition* analysis_prop, char fst, char scd);
void set_analysis_prop_quantifier(analysis_proposition* analysis_prop, bool universal);
void set_analysis_prop_qualifier(analysis_proposition* analysis_prop, bool affirmative);

bool isA(analysis_proposition AS);
bool isE(analysis_proposition AS);
bool isI(analysis_proposition AS);
bool isO(analysis_proposition AS);
char get_char_type(analysis_proposition AS);
bool isFstTermU(analysis_proposition AS);
bool isSecTermU(analysis_proposition AS);
int get_user_figure(user_proposition user_syllogism[3]);
int get_analysis_figure(analysis_proposition analysis_syllogism[3]);

void display_syllogism(user_proposition user_syllogism[3]);

void convert_to_analysis(user_proposition user_syllogism[3], analysis_proposition analysis_syllogism[3]);

void free_user_syl(user_proposition p[3]);


#endif // SYLLOGISM_H_INCLUDED
