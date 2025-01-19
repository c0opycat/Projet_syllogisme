#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "syllogism.h"
#include "validation.h"

#define MYPCHAR char*
#define MYCHAR char
#define MYVAL int
#define MYBOOL bool

//Fonction qui détermine la qualité et la quantité d'une proposition en fonction de son type
//Modifie la poposition passée en paramètre
void impl_prop_type(analysis_proposition* p, MYCHAR type)
{
    MYBOOL universal;
    MYBOOL affirmative;

    switch(type)
    {
        case 'A':
        {
            universal = true;
            affirmative = true;
            break;
        }

        case 'I':
        {
            universal = false;
            affirmative = true;
            break;
        }

        case 'E':
        {
            universal = true;
            affirmative = false;
            break;
        }

        default:
        {
            universal = false;
            affirmative = false;
            break;
        }
    }

    set_analysis_prop_quantifier(p, universal);
    set_analysis_prop_qualifier(p, affirmative);
}

//Fonction qui détermine la qualité et la quantité des propositions d'un syllogisme en fonction de leurs types
//Modifie la poposition passée en paramètre
void impl_type(analysis_proposition* syl, MYCHAR type1, MYCHAR type2, MYCHAR type3)
{
    impl_prop_type(&(syl[0]), type1);
    impl_prop_type(&(syl[1]), type2);
    impl_prop_type(&(syl[2]), type3);
}

//Fonction qui créé un syllogisme de 3 analysis_proposition en fonction de sa figure et de son mode
void create_syllogism(analysis_proposition* syl, MYVAL figure, MYCHAR type1, MYCHAR type2, MYCHAR type3)
{
    if(figure == 1 || figure == 3)
    {
        set_analysis_prop(&(syl[0]), 'M', 'P');
    }
    if(figure == 1 || figure == 2)
    {
        set_analysis_prop(&(syl[1]), 'S', 'M');
    }
    if(figure == 2 || figure == 4)
    {
        set_analysis_prop(&(syl[0]), 'P', 'M');
    }
    if(figure == 3 || figure == 4)
    {
        set_analysis_prop(&(syl[1]), 'M', 'S');
    }

    set_analysis_prop(&(syl[2]), 'S', 'P');

    impl_type(syl, type1, type2, type3);
}

//Fonction qui retourne le type de la première proposition en fonction de l'indice du syllogisme dans le tableau (par figure)
MYCHAR get_syl_type1(MYVAL i)
{
    if((i >= 0) && (i <= 15))
    {
        return 'A';
    }
    else if((i >= 16) && (i <= 31))
    {
        return 'I';
    }
    else if((i >= 32) && (i <= 47))
    {
        return 'E';
    }
    else
    {
        return 'O';
    }
}

//Fonction qui retourne le type de la seconde proposition en fonction de l'indice du syllogisme dans le tableau (par figure)
MYCHAR get_syl_type2(MYVAL i)
{
    if(((i % 16) >= 0) && ((i % 16) <= 3))
    {
        return 'A';
    }
    else if(((i % 16) >= 4) && ((i % 16) <= 7))
    {
        return 'I';
    }
    else if(((i % 16) >= 8) && ((i % 16) <= 11))
    {
        return 'E';
    }
    else
    {
        return 'O';
    }
}

//Fonction qui retourne le type de la conclusion en fonction de l'indice du syllogisme dans le tableau (par figure)
MYCHAR get_syl_type3(MYVAL i)
{
    if((i % 4) == 0)
    {
        return 'A';
    }
    else if((i % 4) == 1)
    {
        return 'I';
    }
    else if((i % 4) == 2)
    {
        return 'E';
    }
    else
    {
        return 'O';
    }
}

//Fonction auxiliaire de fill_tab qui remplit le tableau des indices min à max (correspond à une figure)
void fill_tab_aux(analysis_proposition** tab, MYVAL min, MYVAL max, MYVAL figure)
{
    char type1, type2, type3;

    MYVAL i = 0;
    
    for(int j = min; j <= max; j++)
    {
        type1 = get_syl_type1(i);
        type2 = get_syl_type2(i);
        type3 = get_syl_type3(i);
        
        create_syllogism(tab[j], figure, type1, type2, type3);

        i++;
    }
}

//Fonction de remplissage d'un tableau représentant tous les syllogismes
//Renvoie le tableau (tableau à 2 dimensions)
analysis_proposition** fill_tab()
{
    //Tableau à 2 dimensions pour les 256 syllogismes chacun composé de 3 propositions
    analysis_proposition** tab;

    //Allocation du tableau à 2 dimensions
    tab = (analysis_proposition**)malloc(sizeof(analysis_proposition*) * 256);
    for(int i = 0; i < 256; i++)
    {
        tab[i] = (analysis_proposition*)malloc(sizeof(analysis_proposition) * 3);
    }

    //Remplissage du tableau par figure
    fill_tab_aux(tab, 0, 63, 1);
    fill_tab_aux(tab, 64, 127, 2);
    fill_tab_aux(tab, 128, 191, 3);
    fill_tab_aux(tab, 192, 255, 4);

    return tab;
}

//Fonction de validation appelant les premières règles
void validationStep1Tab(analysis_proposition AS[3], MYBOOL v_tab[11])
{
    v_tab[0]=Rmt(AS);
    v_tab[1]=Rlh(AS);
    v_tab[2]=Rnn(AS);
    v_tab[3]=Rpn(AS);
    v_tab[4]=Raa(AS);
    v_tab[5]=Rpu(AS);
    v_tab[6]=Rpp(AS);
    v_tab[7]=Ruu(AS);
    v_tab[8]=(v_tab[0] && v_tab[1] && v_tab[2] && v_tab[3] && v_tab[4] && v_tab[5] && v_tab[6]); //Sans l'hypothèse d'existence
    v_tab[9]=(v_tab[8] && v_tab[7]); //Avec
    v_tab[10] = true; //true par défaut, remplacé par le résultat de Ri si v_tab[9]
}

//Module de validation de l'intérêt
    //Pour les syllogisme ayant une conclusion particulière
    //Teste la validité avec une conclusion universelle
MYBOOL RiTab(analysis_proposition AS[3])
{
    if (isParticular(AS[2]))
    {
        MYBOOL r_tab[11];
        
        AS[2].universal = true;

        validationStep1Tab(AS, r_tab);

        AS[2].universal = false;

        if (r_tab[9] == true)
        {
            return false;
        }
        else 
        {
            return true;
        }
    }
    //Le syllogisme ne remplit pas les conditions pour cette vérification 
    else return true;
}

//Fonction appelant la règle d'interêt d'un syllogisme dans le cas où ce syllogisme est valide
void validationStep2Tab(analysis_proposition AS[3], MYBOOL v_tab[11])
{
    if (v_tab[9])
    {   
        v_tab[10] = RiTab(AS);
    }
}

//Fonction d'affichage d'un syllogisme du tableau de syllogismes
void displayTab(MYBOOL v_tab[11], analysis_proposition AS[3])
{
    printf("Figure %d ; ", get_analysis_figure(AS));

    // printf("Type première proposition : %c ; ", get_char_type(AS[0]));
    // printf("Type seconde proposition : %c ; ", get_char_type(AS[1]));
    // printf("Type conclusion : %c ; ", get_char_type(AS[2]));

    // printf("Le syllogisme ");
    // if (v_tab[9])
    // {
    //     printf("est valide ; ");
    // }
    // else
    // {
    //     printf("est invalide ; ");
    // }

    // printf("Validité sans hypothèse d'existence : ");
    // if (v_tab[8])
    // {
    //     printf("true ; ");
    // }
    // else 
    // {
    //     printf("false ; ");
    // }

    // if (!v_tab[10])
    // {
    //     printf("Il n'est pas intéressant car sa conclusion pourrait être universelle ; ");
    // }

    printf("%c", get_char_type(AS[0]));
    printf("%c", get_char_type(AS[1]));
    printf("%c ; ", get_char_type(AS[2]));

    if (v_tab[9])
    {
        printf(" Valide  ");
    }
    else
    {
        printf("Invalide ");
    }
    printf("avec hypothèse d'existence ; ");

    if (v_tab[8])
    {
        printf(" Valide  ");
    }
    else 
    {
        printf("Invalide ");
    }
    printf("sans hypothèse d'existence ; ");

    if (!v_tab[10])
    {
        printf(" Inintéressant");
    }
    
    printf("\n");
}

//Fonction de validation complète d'un syllogisme
//Et affichage du résultat
void validationTab(analysis_proposition** AS)
{   
    MYBOOL v_tab[11];

    for(int i = 0; i < 256; i++)
    {
        validationStep1Tab(AS[i],v_tab);
        validationStep2Tab(AS[i],v_tab);
        printf("%3d : ", i + 1);
        displayTab(v_tab, AS[i]);
    }
}

//Affiche une exemple pour chaque syllogisme valide
void displayValid()
{
    printf("\nExemple pour chaque syllogisme valide :\n");
    printf("Figure 1 :\n");
    printf("    AAA : Tous les félidés sont sympathiques; Tous les chats sont des félidés; Donc tous les chats sont sympathiques.\n");
    printf("    AAI : Tous les félidés sont sympathiques; Tous les chats sont des félidés; Donc quelques chats sont sympathiques.\n");
    printf("    AII : Tous les félidés sont sympathiques; Quelques chats sont des félidés; Donc quelques chats sont sympathiques.\n");
    printf("    EAE : Aucun félidé n'est sympatique; Tous les chats sont des félidés; Donc aucun chat n'est sympatique\n");
    printf("    EAO : Aucun félidé n'est sympatique; Tous les chats sont des félidés; Donc quelques chats ne sont pas sympatiques\n");
    printf("    EIO : Aucun félidé n'est sympatique; Quelques chats sont des félidés; Donc quelques chats ne sont pas sympatiques\n");

    printf("Figure 2 :\n");
    printf("    AEE : Tous les chats sont sympathiques; Ancun félidé n'est sympathique; Donc aucun félidé n'est un chat.\n");
    printf("    AEO : Tous les chats sont sympathiques; Ancun félidé n'est sympathique; Donc quelques félidés ne sont pas des chats.\n");
    printf("    AOO : Tous les chats sont sympathiques; Quelques félidés ne sont pas sympathiques; Donc quelques félidés ne sont pas des chats.\n");
    printf("    EAE : Aucun chat n'est sympathique; Tous les félidés sont sympathiques; Donc aucun félidé n'est un chat.\n");
    printf("    EAO : Aucun chat n'est sympathique; Tous les félidés sont sympathiques; Donc quelques félidés ne sont pas des chats.\n");
    printf("    EIO : Aucun chat n'est sympathique; Quelques félidés sont sympathiques; Donc quelques félidés ne sont pas des chats.\n");

    printf("Figure 3 :\n");
    printf("    AAI : Tous les chats sont sympathiques; Tous les chats sont des félidés; Donc quelques félidés sont sympathiques.\n");
    printf("    AII : Tous les chats sont sympathiques; Quelques chats sont des félidés; Donc quelques félidés sont sympathiques.\n");
    printf("    EAO : Aucun chat n'est sympathique; Tous les chats sont des félidés; Donc quelques félidés ne sont pas sympathiques.\n");
    printf("    EIO : Aucun chat n'est sympathique; Quelques chats sont des félidés; Donc quelques félidés ne sont pas sympathiques.\n");
    printf("    IAI : Quelques chats ne sont pas sympathiques; Tous les chats sont des félidés; Donc quelques félidés ne sont pas sympathiques.\n");
    printf("    OAO : Quelques chats sont sympathiques; Tous les chats sont des félidés; Donc quelques félidés sont sympathiques.\n");

    printf("Figure 4:\n");
    printf("    AAI : Tous les chats sont sympathiques; Tous les animaux sympathiques sont des félidés; Donc quelques félidés sont des chats.\n");
    printf("    AEE : Tous les chats sont sympathiques; Aucun animal sympathique n'est un félidé; Donc aucun félidé n'est un chat.\n");
    printf("    AEO : Tous les chats sont sympathiques; Aucun animal sympathique n'est un félidé; Donc quelques félidés ne sont pas des chats.\n");
    printf("    EAO : Aucun chat n'est sympathique; Tous les animaux sympathiques sont des félidés; Donc quelques félidés ne sont pas des chats.\n");
    printf("    EIO : Aucun chat n'est sympathique; Quelques animaux sympathiques sont des félidés; Donc quelques félidés ne sont pas des chats.\n");
    printf("    IAI : Quelques chats sont sympathiques; Tous les animaux sympathiques sont des félidés; Donc quelques félidés sont des chats.\n");
    
}

//Fonction de libération de la mémoire allouée pour le tableau
void free_tab(analysis_proposition** tab)
{
    for(int i = 0; i < 256; i ++)
    {
        free(tab[i]);
    }

    free(tab);
}