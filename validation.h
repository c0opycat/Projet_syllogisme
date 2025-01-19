#ifndef VALIDATION_H_INCLUDED
#define VALIDATION_H_INCLUDED

#include "utils.h"

MYCHAR get_char_type(analysis_proposition AS);

MYBOOL Rmt (analysis_proposition AS[3]);
MYBOOL Rlh (analysis_proposition AS[3]);
MYBOOL Rnn (analysis_proposition AS[3]);
MYBOOL Rpn (analysis_proposition AS[3]);
MYBOOL Raa (analysis_proposition AS[3]);
MYBOOL Rpu (analysis_proposition AS[3]);
MYBOOL Rpp (analysis_proposition AS[3]);
MYBOOL Ruu (analysis_proposition AS[3]);
MYBOOL Ri (analysis_proposition AS[3]);

void validation(analysis_proposition AS[3],user_proposition US[3], MYBOOL v_tab[10]);

#endif