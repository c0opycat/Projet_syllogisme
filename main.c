#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "types.h"
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
void choose_input(T_liste uql, T_liste eql, user_syllogism* us, analysis_syllogism* as, analysis_syllogism* tab){
    
    printf("Tapez 1 pour choisir le module de saisie pour experts\n");
    printf("Tapez 2 pour choisir le module de saisie pour novices\n");
    printf("Tapez 3 pour ajouter un quantificateur\n");
    printf("Tapez 4 pour choisir le module d'affichage de tous les syllogismes\n");
    printf("Tapez 5 pour afficher les syllogismes sauvegardés\n");
    
    MYVAL a = 0;

    while((a < 1) || (a > 5))
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
            input_advanced_syllogism(uql, eql, us);
        }
        else if (a == 2)
        {
            printf("Module de saisie pour novices choisi\n");
            input_simple_syllogism(uql, eql, us);
        }

            //Validation du syllogisme saisi
            convert_to_analysis(*us, as);
        
            MYBOOL v_tab[10];
            validation(*as, *us, v_tab);

            printf("Voulez sauvegarder ce syllogisme ? [o]:oui [n]:non\n");
            while (a != 'o' && a != 'n')
            {
                a = read_char();
            }
            if (a == 'o')
            {
               int res = save_syllogism(us, "SylloSave/syllogism.bin");
               assert(res == 1);
            }
            
    }
    
    //Ajout d'un quantificateur
    else if(a == 3)
    {
        printf("Ajout d'un quantificateur choisi\n");
        new_quantifier(&uql, &eql);

        //Retour au choix d'un module
        choose_input(uql, eql, us, as, tab);
    }

    //Modle d'affichage de tous les syllogismes
    else if (a == 4)
    {
        printf("Module d'affichage de tous les syllogismes choisi\n");
        
        //Affichage de tous les syllogismes
        validationTab(tab);

        //Affichage d'un exemple pour chaque syllogisme valide
        displayValid();

    }
    else
    {
        printf("Module d'affichage des syllogismes sauvegardés choisi\n");      
     
        list_syllogisms("SylloSave/syllogism.bin");

        printf("Tapez le numero du syllogisme pour charger un syllogisme\n");
        MYVAL nb_syllo = count_syllogisms("SylloSave/syllogism.bin");
        MYVAL pos = -1;
        while((pos < 1) || (pos > nb_syllo))
        {
            pos = read_int();
        }
        user_syllogism load_syllogism;
        load_syllogism_pos(&load_syllogism, "SylloSave/syllogism.bin", pos);
        printf("Syllogisme chargé :\n");
        display_syllogism(load_syllogism);

        printf("Souhaitez lancez la validation de ce syllogisme ? [o]:oui [n]:non\n");
        while (a != 'o' && a != 'n')
        {
            a = read_char();
        }
        if (a == 'o')
        {
            analysis_syllogism analysis_s;
            convert_to_analysis(load_syllogism, &analysis_s);
            MYBOOL v_tab[10];
            validation(analysis_s, load_syllogism, v_tab);
        }
        else
        {
            choose_input(uql, eql, us, as, tab);
        }

    }
}

int main()
{

    MYPCHAR filenameqlu = "QuantSave/quantifierUniversal.bin";
    MYPCHAR filenameqle = "QuantSave/quantifierExistential.bin";

    //permet d'initialiser les quantifiacateur de base
    // T_liste tmp1 = create_list_quantifier();
    // T_liste tmp2 = create_list_quantifier();

    // init_list_quanti(tmp1, true);
    // init_list_quanti(tmp2, false);
    
    //Création des listes de quantificateurs universels et existentiels

    T_liste quant_list_e = initialiserListeDepuisFichier(filenameqle);
    T_liste quant_list_u = initialiserListeDepuisFichier(filenameqlu);


    //Création des tableaux représentant le syllogisme
    user_syllogism us;
    analysis_syllogism as;

    //Création du tableau de tous les syllogismes
    analysis_syllogism* tab = fill_tab();

    //Choix du module et lancement du module
    choose_input(quant_list_u, quant_list_e, &us, &as, tab);
    

    //Libération des ressources
    free_list(quant_list_u);
    free_list(quant_list_e);
    free_user_syl(us);
    free_tab(tab);

    return 0;
}
