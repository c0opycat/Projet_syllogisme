#include "syllogism.h"


void impl_type(char type, analysis_proposition* p);
void create_syllogism(analysis_proposition* res, int figure, char type1, char type2, char type3);
void fill_tab_aux(analysis_proposition*** tab, int min, int max, int figure);
analysis_proposition** fill_tab();
void validationTab(analysis_proposition** AS);