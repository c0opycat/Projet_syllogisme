#ifndef SYLLOGISM_H_INCLUDED
#define SYLLOGISM_H_INCLUDED

#include <stdbool.h>
#include "liste.h"
#include "quantifier.h"
#include "utils.h"

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
MYPCHAR get_user_fst_term(user_proposition user_prop);
MYPCHAR get_user_scd_term(user_proposition user_prop);
T_quantifier get_user_quantifier(user_proposition user_prop);
MYBOOL isUniversal (analysis_proposition analysis_syllogism);
MYBOOL isParticular (analysis_proposition analysis_syllogism);
MYBOOL isAffirmative (analysis_proposition analysis_syllogism);
MYBOOL isNegative (analysis_proposition analysis_syllogism);
MYCHAR fstTerm (analysis_proposition analysis_syllogism);
MYCHAR scdTerm (analysis_proposition analysis_syllogism);

//Setter
void set_user_fst_term(user_proposition* user_prop, MYPCHAR term);
void set_user_scd_term(user_proposition* user_prop, MYPCHAR term);
void set_user_prop(user_proposition* user_prop, MYPCHAR fst, MYPCHAR scd);
void set_analysis_fst_term(analysis_proposition* analysis_prop, MYCHAR term);
void set_analysis_scd_term(analysis_proposition* analysis_prop, MYCHAR term);
void set_analysis_prop(analysis_proposition* analysis_prop, MYCHAR fst, MYCHAR scd);
void set_analysis_prop_quantifier(analysis_proposition* analysis_prop, MYBOOL universal);
void set_analysis_prop_qualifier(analysis_proposition* analysis_prop, MYBOOL affirmative);

MYBOOL isA(analysis_proposition AS);
MYBOOL isE(analysis_proposition AS);
MYBOOL isI(analysis_proposition AS);
MYBOOL isO(analysis_proposition AS);
MYCHAR get_char_type(analysis_proposition AS);
MYBOOL isFstTermU(analysis_proposition AS);
MYBOOL isSecTermU(analysis_proposition AS);
MYVAL get_user_figure(user_proposition user_syllogism[3]);
MYVAL get_analysis_figure(analysis_proposition analysis_syllogism[3]);

void display_syllogism(user_proposition user_syllogism[3]);

void convert_to_analysis(user_proposition user_syllogism[3], analysis_proposition analysis_syllogism[3]);

void free_user_syl(user_proposition p[3]);

MYVAL save_syllogism(user_proposition p[3], const MYPCHAR filename);
void list_syllogisms(const MYPCHAR filename);
MYVAL load_syllogism_pos(user_proposition p[3], const MYPCHAR filename, int position);
int count_syllogisms(const MYPCHAR filename);


#endif // SYLLOGISM_H_INCLUDED
