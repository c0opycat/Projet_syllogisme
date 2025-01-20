#ifndef VALIDATION_H_INCLUDED
#define VALIDATION_H_INCLUDED

#include "types.h"
#include "utils.h"


MYCHAR get_char_type(analysis_proposition AS);

MYBOOL Rmt (analysis_syllogism AS);
MYBOOL Rlh (analysis_syllogism AS);
MYBOOL Rnn (analysis_syllogism AS);
MYBOOL Rpn (analysis_syllogism AS);
MYBOOL Raa (analysis_syllogism AS);
MYBOOL Rpu (analysis_syllogism AS);
MYBOOL Rpp (analysis_syllogism AS);
MYBOOL Ruu (analysis_syllogism AS);
MYBOOL Ri (analysis_syllogism AS, MYCHAR hyp_existence);

void validation(analysis_syllogism AS,user_syllogism US, MYBOOL v_tab[10]);

#endif