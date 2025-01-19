#include "syllogism.h"
#include "types.h"
#include "utils.h"

void impl_type(analysis_syllogism* syl, MYCHAR type1, MYCHAR type2, MYCHAR type3);

void create_syllogism(analysis_syllogism* syl, MYVAL figure, MYCHAR type1, MYCHAR type2, MYCHAR type3);

MYCHAR get_syl_type1(MYVAL i);
MYCHAR get_syl_type2(MYVAL i);
MYCHAR get_syl_type3(MYVAL i);

void fill_tab_aux(analysis_syllogism* tab, MYVAL min, MYVAL max, MYVAL figure);
analysis_syllogism* fill_tab();

void validationTab(analysis_syllogism* AS);
void displayValid();

void free_tab(analysis_syllogism* tab);