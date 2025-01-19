#ifndef SYLLOGISM_H_INCLUDED
#define SYLLOGISM_H_INCLUDED

#include <stdbool.h>
#include "types.h"
#include "liste.h"
#include "quantifier.h"
#include "utils.h"


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
user_proposition get_fst_uprop(user_syllogism us);
user_proposition get_scd_uprop(user_syllogism us);
user_proposition get_conc_uprop(user_syllogism us);
user_proposition get_i_uprop(user_syllogism us, MYVAL i);
user_proposition* get_p_fst_uprop(user_syllogism* us);
user_proposition* get_p_scd_uprop(user_syllogism* us);
user_proposition* get_p_conc_uprop(user_syllogism* us);
user_proposition* get_p_i_uprop(user_syllogism* us, MYVAL i);
analysis_proposition get_fst_aprop(analysis_syllogism as);
analysis_proposition get_scd_aprop(analysis_syllogism as);
analysis_proposition get_conc_aprop(analysis_syllogism as);
analysis_proposition get_i_aprop(analysis_syllogism as, MYVAL i);
analysis_proposition* get_p_fst_aprop(analysis_syllogism* as);
analysis_proposition* get_p_scd_aprop(analysis_syllogism* as);
analysis_proposition* get_p_conc_aprop(analysis_syllogism* as);
analysis_proposition* get_p_i_aprop(analysis_syllogism* as, MYVAL i);

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
MYVAL get_user_figure(user_syllogism us);
MYVAL get_analysis_figure(analysis_syllogism as);

void display_syllogism(user_syllogism us);

void convert_to_analysis(user_syllogism us, analysis_syllogism* as);

void free_user_syl(user_syllogism us);

MYVAL save_syllogism(user_syllogism* us, const MYPCHAR filename);
void list_syllogisms(const MYPCHAR filename);
MYVAL load_syllogism_pos(user_syllogism* us, const MYPCHAR filename, MYVAL position);
MYVAL count_syllogisms(const MYPCHAR filename);


#endif //SYLLOGISM_H_INCLUDED
