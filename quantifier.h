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
void set_quantifier(T_quantifier* q, T_liste uql, T_liste eql);

void sauvegarderQuantificateur(FILE* file, T_quantifier* quant);
T_liste ajouterEtSauvegarder(T_liste liste, T_quantifier* quant, const char* filename) ;
T_quantifier* lireQuantificateur(FILE* file);
T_liste initialiserListeDepuisFichier(const char* filename);

#endif