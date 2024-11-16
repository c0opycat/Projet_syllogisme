#ifndef QUANTIFIER_H_INCLUDED
#define QUANTIFIER_H_INCLUDED

#include <stdbool.h>
#include "liste.h"

T_liste create_list_quantifier();
T_liste add_quantifier(const T_quantifier quantifier, T_liste ql);
void new_quantifier(T_liste *qlu, T_liste *qle);

void display_quantifier(const T_liste ql);

T_liste init_list_quanti(T_liste l, bool isUniversal);

bool choose_universal_quantifiers();
T_quantifier choose_quantifier(T_liste ql);

#endif