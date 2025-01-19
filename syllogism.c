#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "syllogism.h"
#include "quantifier.h"

#define MAX_STR_LEN 100
#define MYPCHAR char*
#define MYCHAR char
#define MYVAL int
#define MYBOOL bool

//Getter
//Retourne le premier terme d'une user_proposition
MYPCHAR get_user_fst_term(user_proposition user_prop)
{
    return user_prop.first_term;
}

//Retourne le second terme d'une user_proposition
MYPCHAR get_user_scd_term(user_proposition user_prop)
{
    return user_prop.second_term;
}

//Retourne le quantificateur d'une user_proposition
T_quantifier get_user_quantifier(user_proposition user_prop)
{
    return user_prop.quantifier;
}

//Retourne true si la proposition est universelle
MYBOOL isUniversal (analysis_proposition analysis_syllogism)
{
    return analysis_syllogism.universal;
}

//Retourne true si la proposition est particulière
MYBOOL isParticular (analysis_proposition analysis_syllogism)
{
    return !(analysis_syllogism.universal);
}

//Retourne true si la proposition est affirmative
MYBOOL isAffirmative (analysis_proposition analysis_syllogism)
{
    return analysis_syllogism.affirmative;
}

//Retourne true si la proposition est négative
MYBOOL isNegative (analysis_proposition analysis_syllogism)
{
    return !(analysis_syllogism.affirmative);
}

//Retourne le type (SPM) du premier terme
MYCHAR fstTerm (analysis_proposition analysis_syllogism)
{
    return analysis_syllogism.first_term;
}

//Retourne le type (SPM) du second terme
MYCHAR scdTerm (analysis_proposition analysis_syllogism)
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
void set_analysis_prop_quantifier(analysis_proposition* analysis_prop, MYBOOL universal)
{
    analysis_prop->universal = universal;
}

//Setter du qualificateur d'une analysis_proposition
void set_analysis_prop_qualifier(analysis_proposition* analysis_prop, MYBOOL affirmative)
{
    analysis_prop->affirmative = affirmative;
}


//Retourne true si la proposition est de type A
MYBOOL isA(analysis_proposition AS)
{
    return (AS.universal == true && AS.affirmative == true);
}


//Retourne true si la proposition est de type E
MYBOOL isE(analysis_proposition AS)
{
    return (AS.universal == true && AS.affirmative == false);
}

//Retourne true si la proposition est de type I
MYBOOL isI(analysis_proposition AS)
{
    return (AS.universal == false && AS.affirmative == true);
}

//Retourne true si la proposition est de type O
MYBOOL isO(analysis_proposition AS)
{
    return (AS.universal == false && AS.affirmative == false);
}

//retourne le type de la proposition
MYCHAR get_char_type(analysis_proposition AS)
{
    if(isA(AS))
    {
        return 'A';
    }

    else if(isE(AS))
    {
        return 'E';
    }
    else if(isI(AS))
    {
        return 'I';
    }
    else
    {
        return 'O';
    }
}

//Retourne true si le sujet de la proposition est universel
MYBOOL isFstTermU(analysis_proposition AS)
{
    return (isA(AS)||isE(AS));
}

//Retourne true si le sujet de la proposition est existentiel
MYBOOL isSecTermU(analysis_proposition AS)
{
    return (isE(AS)||isO(AS));
}

//Fonction qui détermine et renvoie la figure du syllogisme
MYVAL get_user_figure(user_proposition user_syllogism[3])
{
    MYVAL type;

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

//Fonction qui détermine et renvoie la figure du syllogisme
MYVAL get_analysis_figure(analysis_proposition analysis_syllogism[3])
{
    MYVAL type;

    if(fstTerm(analysis_syllogism[0]) == scdTerm(analysis_syllogism[1]))
    {
        type = 1;
    }
    else if(scdTerm(analysis_syllogism[0]) == scdTerm(analysis_syllogism[1]))
    {
        type = 2;
    }
    else if(fstTerm(analysis_syllogism[0]) == fstTerm(analysis_syllogism[1]))
    {
        type = 3;
    }
    else if(scdTerm(analysis_syllogism[0]) == fstTerm(analysis_syllogism[1]))
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


//Leïla et Arthur
//Converti un tableau de 3 user_proposition et un tableau de 3 analysis_proposition
void convert_to_analysis(user_proposition user_syllogism[3], analysis_proposition analysis_syllogism[3])
{
    MYVAL type = get_user_figure(user_syllogism);

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

    MYVAL type = get_user_figure(p);

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


