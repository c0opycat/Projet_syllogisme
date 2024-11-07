#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "liste.h"
#include "syllogism.h"
#include "validation.h"

//Getter
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
char secTerm (analysis_proposition analysis_syllogism)
{
    return analysis_syllogism.second_term;
}

//convertit le résultat booleén d'un test de validité en une chaîne de caractère affichable
char * boolToStr(bool valid){
    if(valid)
    {return "est respectée";}
    else {return "n'est pas respectée";}
}

//Règles du moyen terme : vérifie si une des prémisses a un quantificateur universel
bool Rmt (analysis_proposition AS[3])
{
    bool valid = (isUniversal(AS[0]) || isUniversal(AS[1]));
    printf("la règle du moyen terme %s\n",boolToStr(valid));
    return valid;
}

//Règles du latius hos : vérifie que si un terme est universel dans la conclusion il l'est dans la prémisse
bool Rlh (analysis_proposition AS[3])
{
    if (isUniversal(AS[2]))
    {
        bool valid = (isUniversal(AS[0]) || isUniversal(AS[1]));
        printf("la règle du latius hos %s\n",boolToStr(valid));
        return valid;
    }
    else
    {
        printf("la règle du latius hos n'est pas pertinente pour la validité de ce syllogisme\n");
        return true;
    }
}
//Règle des deux négations : Vérifie si au moins une des deux prémisses est positive
bool Rnn (analysis_proposition AS[3])
{
    bool valid = (isAffirmative(AS[0]) || isAffirmative(AS[1]));
    printf("la règle des deux négations %s\n",boolToStr(valid));
    return valid;
}
//Règle de passation de la négation :Vérifie que si une prémisse est négative, la conclusion est négative
bool Rpn (analysis_proposition AS[3])
{
    if (isNegative(AS[0]) || isNegative(AS[1]))
    {
        bool valid = (isNegative(AS[2]));
        printf("la règle de la passation de la négation %s\n",boolToStr(valid));
        return valid;
    }
    else
    {
        printf("le test de la règle de la passation de la négation n'est pas pertinente pour la validité de ce syllogisme\n");
        return true;
    }
}
//Règle de passation de la double affirmation : vérifie si les deux prémisses sont affirmative que la conclusion le soit
bool Raa (analysis_proposition AS[3])
{
    if (isAffirmative(AS[0]) && isAffirmative(AS[1]))
    {
        bool valid = (isAffirmative(AS[2]));
        printf("la règle de la double affirmation %s\n",boolToStr(valid));
        return valid;
    }
    else printf("le test de la règle de la passation de la négation n'est pas pertinente pour la validité de ce syllogisme\n");
    return true;
}
//Règle des deux particularités Vérifie si au moins une des prémisses est universelle
bool Rpu (analysis_proposition AS[3])
{
    bool valid = (isUniversal(AS[0]) || isUniversal(AS[1]));
    printf("la règle des deux particularités %s\n",boolToStr(valid));
    return valid;

}
//Règle des la passation de particularité : Vérifie que si une prémisse est particulière, la conclusion aussi
bool Rpp (analysis_proposition AS[3])
{
    if (isParticular(AS[0]) || isParticular(AS[1]))
    {
        bool valid = (isParticular(AS[2]));
        printf("la règle de la passation de la particularité %s\n",boolToStr(valid));
        return valid;
    }
    else printf("le test de la règle de la passation de la particularité n'est pas pertinente pour la validité de ce syllogisme\n");
    return true;
}
//Module de validation de l'hypothèse d'existence
void Ruu (analysis_proposition AS[3])
{
    if (isUniversal(AS[0]) && isUniversal(AS[1]))
    {
        if (isParticular(AS[2]))
        {printf("Les deux prémisses étant universelles, le syllogisme serait valide si la conclusion était universelle\n");}
    }
}

//Module de validation de l'intérêt
    //Pour les syllogisme ayant une conclusion particulière
    //Teste la validité avec une conclusion universelle

bool Ri(analysis_proposition AS[3])
{
    printf("La conclusion est faible, une conclusion universelle est possible\n");
    return true;
}

//Fonction de validation appelant les règles
void validation (analysis_proposition AS[3],user_proposition US[3], bool v_tab[9])
{
    bool res;
    res = Rmt(AS);

    v_tab[0]=res;
    v_tab[1]=Rlh(AS);
    v_tab[2]=Rnn(AS);
    v_tab[3]=Rpn(AS);
    v_tab[4]=Raa(AS);
    v_tab[5]=Rpu(AS);
    v_tab[6]=Rpp(AS);
    v_tab[8]=(v_tab[0] && v_tab[1] && v_tab[2] && v_tab[3] && v_tab[4] && v_tab[5] && v_tab[6]);

    if (v_tab[8] == true)
    {
        printf("Le syllogisme\n");
        display_syllogism(US);
        printf("est valide\n");
        Ruu(AS);
        v_tab[7] = Ri(AS);
    }
    else 
    {  
        printf("Le syllogisme\n");
        display_syllogism(US);
        printf("est invalide\n");
        v_tab[7] = false;
    }
}