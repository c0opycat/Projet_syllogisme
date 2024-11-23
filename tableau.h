#include "syllogism.h"


void impl_type(analysis_proposition* syl, char type1, char type2, char type3);

void create_syllogism(analysis_proposition* syl, int figure, char type1, char type2, char type3);

char get_syl_type1(int i);
char get_syl_type2(int i);
char get_syl_type3(int i);

void fill_tab_aux(analysis_proposition** tab, int min, int max, int figure);
analysis_proposition** fill_tab();

void validationTab(analysis_proposition** AS);

void free_tab(analysis_proposition** tab);