#include "syllogism.h"
#include "utils.h"

void impl_type(analysis_proposition* syl, MYCHAR type1, MYCHAR type2, MYCHAR type3);

void create_syllogism(analysis_proposition* syl, MYVAL figure, MYCHAR type1, MYCHAR type2, MYCHAR type3);

MYCHAR get_syl_type1(MYVAL i);
MYCHAR get_syl_type2(MYVAL i);
MYCHAR get_syl_type3(MYVAL i);

void fill_tab_aux(analysis_proposition** tab, MYVAL min, MYVAL max, MYVAL figure);
analysis_proposition** fill_tab();

void validationTab(analysis_proposition** AS);
void displayValid();

void free_tab(analysis_proposition** tab);