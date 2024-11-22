#ifndef VALIDATION_H_INCLUDED
#define VALIDATION_H_INCLUDED

char get_char_type(analysis_proposition AS);
bool Rmt (analysis_proposition AS[3]);
bool Rlh (analysis_proposition AS[3]);
bool Rnn (analysis_proposition AS[3]);
bool Rpn (analysis_proposition AS[3]);
bool Raa (analysis_proposition AS[3]);
bool Rpu (analysis_proposition AS[3]);
bool Rpp (analysis_proposition AS[3]);
bool Ruu (analysis_proposition AS[3]);
bool Ri (analysis_proposition AS[3]);
void validation(analysis_proposition AS[3],user_proposition US[3], bool v_tab[10]);

#endif