#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "utils.h"
#include "quantifier.h"
#include "liste.h"
#include "syllogism.h"

#define MYVAL int
#define MYPCHAR char*
#define MYCHAR char
#define MYBOOL bool

//Arthur
//Fonction de saisie d'un syllogisme avec le module a 7 demandes
//modifie le tableau user_syllogism passé en parametres
void input_advanced_syllogism(T_liste uql, T_liste eql, user_proposition user_syllogism[3]){
    MYVAL type = 0;

    ////Enregistrement des quantificateur des différentres parties du syllogisme
    printf("-----Première proposition-----\n");

    set_quantifier(&(user_syllogism[0].quantifier), uql, eql);

    printf("-----Deuxième proposition-----\n");

    set_quantifier(&(user_syllogism[1].quantifier), uql, eql);

    printf("-----Conclusion-----\n");

    set_quantifier(&(user_syllogism[2].quantifier), uql, eql);

    //Enregistrement du sujet du syllogisme
    printf("Veuillez entrer le sujet de la conclusion : \n");
    
    MYPCHAR sujet = read_str();
    
    //Enregistrement du prédicat du syllogisme
    printf("Veuillez entrer le prédicat de la conclusion : \n");
    
    MYPCHAR predicat = read_str();

    //Enregistrement du moyen terme du syllogisme
    printf("Veuillez entrer le moyen terme : \n");
    
    MYPCHAR terme = read_str();

    //Enregistrement du type du syllogisme
    printf("Entrez le type de votre syllogisme : \n");
    while(!(type > 0 && type < 5))
    {
        type = read_int();
    }

    if(type == 1 || type == 3)
    {
        set_user_prop(&(user_syllogism[0]), terme, predicat);
    }
    if(type == 1 || type == 2)
    {
        set_user_prop(&(user_syllogism[1]), sujet, terme);
    }
    if(type == 2 || type == 4)
    {
        set_user_prop(&(user_syllogism[0]), predicat, terme);
    }
    if(type == 3 || type == 4)
    {
        set_user_prop(&(user_syllogism[1]), terme, sujet);
    }
    
    set_user_prop(&(user_syllogism[2]), sujet, predicat);
}

//Leïla
//Fonction de saisie à 8 demandes (modifie le tableau user_syllogism en parametre)
void input_simple_syllogism(T_liste uql, T_liste eql, user_proposition user_syllogism[3])
{
    MYCHAR s_or_p = 'a';
    MYVAL s_or_p2 = 0;
    MYBOOL f1_or_f2;

    printf("-----Module à 8 demandes-----\n");
    printf("-----Première proposition-----\n");

    set_quantifier(&(user_syllogism[0].quantifier), uql, eql);

    printf("Veuillez entrer le sujet de la première proposition\n");
    
    MYPCHAR term1 = read_str();

    printf("Veuillez entrer le prédicat de la première proposition\n");
    
    MYPCHAR term2 = read_str();

    set_user_prop(&(user_syllogism[0]), term1, term2);

    printf("-----Deuxième proposition-----\n");

    set_quantifier(&(user_syllogism[1].quantifier), uql, eql);

    printf("Le sujet est-il le sujet ou le prédicat de la première proposition ? \n");
    printf("[o]:oui [n]:non\n");

    while((s_or_p != 'o') && (s_or_p != 'n'))
    {
        s_or_p = read_char();
    }

    if(s_or_p == 'o')
    {
        f1_or_f2 = false;

        printf("Veuillez choisir le sujet :\n");
        printf("[1]:%s\n", get_user_fst_term(user_syllogism[0]));
        printf("[2]:%s\n", get_user_scd_term(user_syllogism[0]));

        while((s_or_p2 != 1) && (s_or_p2 != 2))
        {
            s_or_p2 = read_int();
        }

        printf("Veuillez entrer le prédicat :\n");
        
        MYPCHAR term3 = read_str();

        if(s_or_p2 == 1)
        {
            set_user_prop(&(user_syllogism[1]), term1, term3);
        }
        else
        {
            set_user_prop(&(user_syllogism[1]), term2, term3);
        }
    }
    else
    {
        f1_or_f2 = true;

        printf("Veuillez entrer le sujet : \n");
        
        MYPCHAR term3 = read_str();

        printf("Veuillez choisir le prédicat :\n");
        printf("[1]:%s\n", get_user_fst_term(user_syllogism[0]));
        printf("[2]:%s\n", get_user_scd_term(user_syllogism[0]));

        while((s_or_p2 != 1) && (s_or_p2 != 2))
        {
            s_or_p2 = read_int();
        }

        if(s_or_p2 == 1)
        {
            set_user_prop(&(user_syllogism[1]), term3, term1);
        }
        else
        {
            set_user_prop(&(user_syllogism[1]), term3, term2);
        }
    }

    printf("-----Conclusion-----\n");

    set_quantifier(&(user_syllogism[2].quantifier), uql, eql);

    if(f1_or_f2)
    {
        printf("Le sujet de la conclusion est donc le sujet de la deuxième proposition.\n");

        if(get_user_figure(user_syllogism) == 1)
        {
            set_user_prop(&(user_syllogism[2]), get_user_fst_term(user_syllogism[1]), get_user_scd_term(user_syllogism[0]));
        }
        else
        {
            set_user_prop(&(user_syllogism[2]), get_user_fst_term(user_syllogism[1]), get_user_fst_term(user_syllogism[0]));
        }
    }
    else
    {
        printf("Le sujet de la conclusion est donc le prédicat de la deuxième proposition.\n");

        if(get_user_figure(user_syllogism) == 3)
        {
            set_user_prop(&(user_syllogism[2]), get_user_scd_term(user_syllogism[1]), get_user_scd_term(user_syllogism[0]));
        }
        else
        {
            set_user_prop(&(user_syllogism[2]), get_user_scd_term(user_syllogism[1]), get_user_fst_term(user_syllogism[0]));
        }
    }
}
