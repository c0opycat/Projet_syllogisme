#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "utils.h"
#include "quantifier.h"
#include "liste.h"
#include "syllogism.h"

#define MAX_STR_LEN 100

//Getter
//Retourne le premier terme d'une user_proposition
char* get_user_fst_term(user_proposition user_prop)
{
    return user_prop.first_term;
}

//Retourne le second terme d'une user_proposition
char* get_user_scd_term(user_proposition user_prop)
{
    return user_prop.second_term;
}

//Retourne le quantificateur d'une user_proposition
T_quantifier get_user_quantifier(user_proposition user_prop)
{
    return user_prop.quantifier;
}

//Retourne true si la proposition est universelle
bool isUniversal (analysis_proposition analysis_syllogism)
{
    return analysis_syllogism.universal;
}

//Retourne true si la proposition est particulière
bool isParticular (analysis_proposition analysis_syllogism)
{
    return !(analysis_syllogism.universal);
}

//Retourne true si la proposition est affirmative
bool isAffirmative (analysis_proposition analysis_syllogism)
{
    return analysis_syllogism.affirmative;
}

//Retourne true si la proposition est négative
bool isNegative (analysis_proposition analysis_syllogism)
{
    return !(analysis_syllogism.affirmative);
}

//Retourne le type (SPM) du premier terme
char fstTerm (analysis_proposition analysis_syllogism)
{
    return analysis_syllogism.first_term;
}

//Retourne le type (SPM) du second terme
char scdTerm (analysis_proposition analysis_syllogism)
{
    return analysis_syllogism.second_term;
}

//Setter
//Setter du premier terme d'une user_proposition
void set_user_fst_term(user_proposition* user_prop, char* term)
{
    user_prop->first_term = term;
}

//Setter du second terme d'une user_proposition
void set_user_scd_term(user_proposition* user_prop, char* term)
{
    user_prop->second_term = term;
}

//Setter des termes d'une user_proposition
void set_user_prop(user_proposition* user_prop, char* fst, char* scd)
{
    set_user_fst_term(user_prop, fst);
    set_user_scd_term(user_prop, scd);
}

//Setter du premier terme d'une analysis_proposition
void set_analysis_fst_term(analysis_proposition* analysis_prop, char term)
{
    analysis_prop->first_term = term;
}

//Setter du second terme d'une analysis_proposition
void set_analysis_scd_term(analysis_proposition* analysis_prop, char term)
{
    analysis_prop->second_term = term;
}

//Setter des termes d'une analysis_proposition
void set_analysis_prop(analysis_proposition* analysis_prop, char fst, char scd)
{
    set_analysis_fst_term(analysis_prop, fst);
    set_analysis_scd_term(analysis_prop, scd);
}

//Setter du quantificateur d'une analysis_proposition
void set_analysis_prop_quantifier(analysis_proposition* analysis_prop, bool universal)
{
    analysis_prop->universal = universal;
}

//Setter du qualificateur d'une analysis_proposition
void set_analysis_prop_qualifier(analysis_proposition* analysis_prop, bool affirmative)
{
    analysis_prop->affirmative = affirmative;
}


//Fonction qui détermine et renvoie la figure du syllogisme
int get_type(user_proposition user_syllogism[3])
{
    int type;

    if(get_user_fst_term(user_syllogism[0]) == get_user_scd_term(user_syllogism[1]))
    {
        type = 1;
    }
    else if(get_user_scd_term(user_syllogism[0]) == get_user_scd_term(user_syllogism[1]))
    {
        type = 2;
    }
    else if(get_user_fst_term(user_syllogism[0]) == get_user_fst_term(user_syllogism[1]))
    {
        type = 3;
    }
    else if(get_user_scd_term(user_syllogism[0]) == get_user_fst_term(user_syllogism[1]))
    {
        type = 4;
    }

    return type;
}

//Arthur
//affichage d'un syllogisme de 3 user_proposition
void display_syllogism(user_proposition p[3]){
   for(int i = 0; i < 3; i++)
   {
    printf("%s %s %s\n", get_user_quantifier(p[i]).quantifier_str, get_user_fst_term(p[i]), get_user_scd_term(p[i]));
   }
}

//Arthur
//Fonction de saisie d'un syllogisme avec le module a 7 demandes
//modifie le tableau user_syllogism passé en parametres
void input_advanced_syllogism(T_liste uql, T_liste eql, user_proposition user_syllogism[3]){
    int type = 0;

    ////Enregistrement des quantificateur des différentres parties du syllogisme
    printf("-----Première proposition-----\n");

    set_quantifier(&(user_syllogism[0].quantifier), uql, eql);

    printf("-----Deuxième proposition-----\n");

    set_quantifier(&(user_syllogism[1].quantifier), uql, eql);

    printf("-----Conclusion-----\n");

    set_quantifier(&(user_syllogism[2].quantifier), uql, eql);

    //Enregistrement du sujet du syllogisme
    printf("Veuillez entrer le sujet de la conclusion : \n");
    
    char* sujet = read_str();
    
    //Enregistrement du prédicat du syllogisme
    printf("Veuillez entrer le prédicat de la conclusion : \n");
    
    char* predicat = read_str();

    //Enregistrement du moyen terme du syllogisme
    printf("Veuillez entrer le moyen terme : \n");
    
    char* terme = read_str();

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
    char s_or_p = 'a';
    int s_or_p2 = 0;
    bool f1_or_f2;

    printf("-----Module à 8 demandes-----\n");
    printf("-----Première proposition-----\n");

    set_quantifier(&(user_syllogism[0].quantifier), uql, eql);

    printf("Veuillez entrer le sujet de la première proposition\n");
    
    char* term1 = read_str();

    printf("Veuillez entrer le prédicat de la première proposition\n");
    
    char* term2 = read_str();

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
        
        char* term3 = read_str();

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
        
        char* term3 = read_str();

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
 
        if(get_type(user_syllogism) == 1)
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

        if(get_type(user_syllogism) == 3)
        {
            set_user_prop(&(user_syllogism[2]), get_user_scd_term(user_syllogism[1]), get_user_scd_term(user_syllogism[0]));
        }
        else
        {   
            set_user_prop(&(user_syllogism[2]), get_user_scd_term(user_syllogism[1]), get_user_fst_term(user_syllogism[0]));
        }
    }
}


//Arthur
//Demande de choisir entre le module a 7 demandes et celui a 9 demandes
//Puis lance le module choisi
void choose_input(T_liste uql, T_liste eql, user_proposition user_syllogism[3]){
    
    printf("Tapez 1 pour choisir le module pour experts\nTapez 2 pour choisir le module pour novices\nTapez 3 pour ajouter un quantificateur\n");
    int a = 0;

    while((a != 1) && (a != 2) && (a != 3))
    {
        a = read_int();
    }

    if(a == 1)
    {
        printf("Module pour experts choisi\n");
        input_advanced_syllogism(uql, eql, user_syllogism);
    }
    else if (a == 2)
    {
        printf("Module pour novices choisi\n");
        input_simple_syllogism(uql, eql, user_syllogism);
    }
    else
    {
        printf("Ajout d'un quantificateur choisi\n");
        new_quantifier(&uql, &eql);
        choose_input(uql, eql, user_syllogism);
    }
}

//Leïla et Arthur
//Converti un tableau de 3 user_proposition et un tableau de 3 analysis_proposition
void convert_to_analysis(user_proposition user_syllogism[3], analysis_proposition analysis_syllogism[3])
{
    int type = get_type(user_syllogism);

    if(type == 1 || type == 3)
    {
        set_analysis_prop(&(analysis_syllogism[0]), 'M', 'P');
    }
    if(type == 1 || type == 2)
    {
        set_analysis_prop(&(analysis_syllogism[1]), 'S', 'M');
    }
    if(type == 2 || type == 4)
    {
        set_analysis_prop(&(analysis_syllogism[0]), 'P', 'M');
    }
    if(type == 3 || type == 4)
    {
        set_analysis_prop(&(analysis_syllogism[1]), 'M', 'S');
    }
    
    set_analysis_prop(&(analysis_syllogism[2]), 'S', 'P');

    for(int i = 0; i < 3; i++)
    {
        set_analysis_prop_quantifier(&(analysis_syllogism[i]), isUniversal(analysis_syllogism[i]));
        set_analysis_prop_quantifier(&(analysis_syllogism[i]), isAffirmative(analysis_syllogism[i]));
    } 
}

//Arthur
//Fonction qui permet de libérer les ressources de nos user_proposition
void free_user_syl(user_proposition p[3])
{ 
    free(p[2].first_term);
    free(p[2].second_term);

    int type = get_type(p);

    if(type == 1)
    {
        free(p[0].first_term);
    }
    else if(type == 2)
    {
        free(p[0].second_term);
    }
    else if(type == 3)
    {
        free(p[0].first_term);
    }
    else if(type == 4)
    {
        free(p[0].second_term);
    }
}


