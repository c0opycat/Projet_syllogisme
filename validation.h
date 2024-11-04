#ifndef VALIDATION_H_INCLUDED
#define VALIDATION_H_INCLUDED

#include "liste.h"
#include "syllogism.h"

bool isUniversal (analysis_proposition analysis_syllogism);
bool isParticular (analysis_proposition analysis_syllogism);
bool isAffirmative (analysis_proposition analysis_syllogism);
bool isNegative (analysis_proposition analysis_syllogism);
char fstTerm (analysis_proposition analysis_syllogism);
char secTerm (analysis_proposition analysis_syllogism);
char * boolToStr(bool valid);
bool Rmt (analysis_proposition AS[3]);
bool Rlh (analysis_proposition AS[3]);
bool Rnn (analysis_proposition AS[3]);
bool Rpn (analysis_proposition AS[3]);
bool Raa (analysis_proposition AS[3]);
bool Rpu (analysis_proposition AS[3]);
bool Rpp (analysis_proposition AS[3]);
void Ruu (analysis_proposition AS[3]);
bool Ri(analysis_proposition AS[3]);
bool * validation (analysis_proposition AS[3],user_proposition US[3]);