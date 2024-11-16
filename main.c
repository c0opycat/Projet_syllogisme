#include "quantifier.h"
#include "liste.h"
#include "syllogism.h"
#include "validation.h"

int main()
{
    //Création des listes de quantificateurs universels et existentiels
    T_liste quant_list_u = create_list_quantifier();
    T_liste quant_list_e = create_list_quantifier();

    quant_list_u = init_list_quanti(quant_list_u, true);
    quant_list_e = init_list_quanti(quant_list_e, false);

    //Création des tableaux représentant le syllogisme
    user_proposition user_syllogism[3];
    analysis_proposition analysis_syllogism[3];

    //Saisie et analyse d'un syllogisme
    choose_input(quant_list_u, quant_list_e, user_syllogism);
    display_syllogism(user_syllogism);

    convert_to_analysis(user_syllogism, analysis_syllogism);
    
    bool v_tab[10];
    validation(analysis_syllogism, user_syllogism, v_tab);


    //Libération des ressources
    free_user_syl(user_syllogism);
    free_list(quant_list_u);
    free_list(quant_list_e);

    return 0;
}
