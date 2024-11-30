#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "quantifier.h"
#include "liste.h"
#include "syllogism.h"
#include "saisie.h"
#include "validation.h"
#include "tableau.h"


//Arthur
//Demande de choisir quel module lancer
//Puis lance le module choisi
void choose_input(T_liste uql, T_liste eql, user_proposition user_syllogism[3], analysis_proposition analysis_syllogism[3], analysis_proposition** tab){
    
    printf("Tapez 1 pour choisir le module de saisie pour experts\n");
    printf("Tapez 2 pour choisir le module de saisie pour novices\n");
    printf("Tapez 3 pour ajouter un quantificateur\n");
    printf("Tapez 4 pour choisir le module d'affichage de tous les syllogismes\n");
    
    int a = 0;

    while((a < 1) || (a > 4))
    {
        a = read_int();
    }

    //Module saisie d'un syllogisme
    if((a == 1) || (a == 2))
    {   
        //Saisie du syllogisme
        if(a == 1)
        {
            printf("Module de saisie pour experts choisi\n");
            input_advanced_syllogism(uql, eql, user_syllogism);
        }
        else if (a == 2)
        {
            printf("Module de saisie pour novices choisi\n");
            input_simple_syllogism(uql, eql, user_syllogism);
        }

            //Validation du syllogisme saisi
            convert_to_analysis(user_syllogism, analysis_syllogism);
        
            bool v_tab[10];
            validation(analysis_syllogism, user_syllogism, v_tab);
            
            //Affichage du syllogisme
            display_syllogism(user_syllogism);
    }
    
    //Ajout d'un quantificateur
    else if(a == 3)
    {   
        printf("Ajout d'un quantificateur choisi\n");
        new_quantifier(&uql, &eql);

        //Retour au choix d'un module
        choose_input(uql, eql, user_syllogism, analysis_syllogism, tab);
    }

    //Modle d'affichage de tous les syllogismes
    else
    {
        printf("Module d'affichage de tous les syllogismes choisi\n");
        
        //Affichage de tous les syllogismes
        validationTab(tab);

        //Affichage d'un exemple pour chaque syllogisme valide
        displayValid();

    }
}

int main()
{
    //Création des listes de quantificateurs universels et existentiels
    T_liste quant_list_u = create_list_quantifier();
    T_liste quant_list_e = create_list_quantifier();

    //initialisation des listes
    quant_list_u = init_list_quanti(quant_list_u, true);
    quant_list_e = init_list_quanti(quant_list_e, false);

    //Création des tableaux représentant le syllogisme
    user_proposition user_syllogism[3];
    analysis_proposition analysis_syllogism[3];

    //Création du tableau de tous les syllogismes
    analysis_proposition** tab = fill_tab();

    //Choix du module et lancement du module
    choose_input(quant_list_u, quant_list_e, user_syllogism, analysis_syllogism, tab);
    

    //Libération des ressources
    free_list(quant_list_u);
    free_list(quant_list_e);
    free_user_syl(user_syllogism);
    free_tab(tab);

    return 0;
}
