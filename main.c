#include <stdio.h>
#include <stdlib.h>

#include "quantifier.h"
#include "liste.h"
#include "syllogism.h"
#include "validation.h"
#include "tableau.h"

int main()
{
    /*
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
    */

    printf("Debut");

    analysis_proposition p[3];

    // for(int i = 0; i < 256; i++)
    // {
    //     analysis_proposition p;
    //     impl_type(1, &p);
    // }

    create_syllogism(p, int figure, char type1, char type2, char type3);

    printf("Fin");

    // for(int i = 0; i < 256; i++)
    // {  
    //     display_analysis(tab[i]); 
    // }

    return 0;
}
