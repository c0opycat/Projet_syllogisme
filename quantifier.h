#ifndef QUANTIFIER_H_INCLUDED
#define QUANTIFIER_H_INCLUDED

#include <stdbool.h>
#include "liste.h"

//Structure de données représentant un quantificateur
typedef struct T_quant{
	char* quantifier_str;
    bool universal;
	bool affirmative;
}T_quantifier;

T_liste create_list_quantifier();
T_liste add_quantifier(const T_quantifier quantifier, T_liste ql);

void display_quantifier(const T_liste ql);

T_liste init_list_quanti(T_liste l, bool isUniversal);

T_quantifier choose_quantifier(T_liste ql);

#endif