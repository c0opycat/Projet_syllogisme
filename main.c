#include "syllogism.h"
#include "validation.h"

#include <stdio.h>

int main()
{
    T_liste quant_list_u = create_list_quantifier();
    T_liste quant_list_e = create_list_quantifier();

    T_quantifier test1 = {"Aucun", true, false};
    T_quantifier test2 = {"Tous", true, true};
    T_quantifier test3 = {"Chacun", false, true};

    quant_list_u = add_quantifier(test1, quant_list_u);
    quant_list_u = add_quantifier(test2, quant_list_u);
    quant_list_e = add_quantifier(test3, quant_list_e);

    user_proposition user_syllogism[3];
    analysis_proposition analysis_syllogism[3];

    choose_input(quant_list_u, quant_list_e, user_syllogism);

    convert_to_analysis(user_syllogism, analysis_syllogism);

    display_syllogism(user_syllogism);
    display_analysis(analysis_syllogism);

    bool v_tab[9];
    validation(analysis_syllogism, user_syllogism, v_tab);

    free_user_syl(user_syllogism);
    free_list(quant_list_u);
    free_list(quant_list_e);
    //display_syllogism(user_syllogism);

    return 0;
}
