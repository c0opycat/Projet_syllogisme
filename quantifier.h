#ifndef QUANTIFIER_H_INCLUDED
#define QUANTIFIER_H_INCLUDED

#include <stdbool.h>
#include "types.h"
#include "liste.h"
#include "utils.h"

MYPCHAR get_quant_str(T_quantifier quant);
MYBOOL get_quant_universal(T_quantifier quant);
MYBOOL get_quant_affirmative(T_quantifier quant);

T_liste create_list_quantifier();
T_liste add_quantifier(const T_quantifier quantifier, T_liste ql);
void new_quantifier(T_liste *qlu, T_liste *qle);

void display_quantifier(const T_liste ql);

T_liste initialiserListeDepuisFichier(const MYPCHAR filename);

MYBOOL choose_universal_quantifiers();
T_quantifier choose_quantifier(T_liste ql);
void set_quantifier(T_quantifier* q, T_liste uql, T_liste eql);

void sauvegarderQuantificateur(FILE* file, T_quantifier* quant);
T_liste ajouterEtSauvegarder(T_liste liste, T_quantifier* quant, const MYPCHAR filename) ;
T_quantifier* lireQuantificateur(FILE* file);
T_liste initialiserListeDepuisFichier(const MYPCHAR filename);

#endif