#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "liste.h"
#include "quantifier.h"
#include "syllogism.h"
#include "validation.h"
#include "utils.h"

//convertit le résultat booleén d'un test de validité en une chaîne de caractère affichable
MYPCHAR boolToStr(MYBOOL valid){
    if(valid)
    {return "est respectée";}
    else {return "n'est pas respectée";}
}

//Règles du moyen terme : vérifie si le moyen terme est universel dans une prémisse au moins
MYBOOL Rmt (analysis_proposition AS[3])
{
    MYBOOL valid = false;

    for (int i = 0; i < 2; i++)
    {
        if (isE(AS[i]) || (isA(AS[i]) && fstTerm(AS[i]) == 'M') || (isO(AS[i]) && scdTerm(AS[i]) == 'M'))
        {
            valid = true;
            return valid;
        }
    }

    return valid;
}

//Règle du latius hos : vérifie que si un terme est universel dans la conclusion il l'est dans la prémisse
MYBOOL Rlhfst(analysis_proposition AS[3])
{
    MYBOOL valid = true;

    if (isFstTermU(AS[2]))
    {
        MYCHAR a = fstTerm(AS[2]);
        if ((isFstTermU(AS[1])&&fstTerm(AS[1])==a) || (isSecTermU(AS[1])&&scdTerm(AS[1])==a))
        {  
            valid = true;
        }
        else valid = false;
    }
    
    return valid;
}

MYBOOL Rlhsec(analysis_proposition AS[3])
{
    MYBOOL valid = true;
    if (isSecTermU(AS[2]))
    {
        MYCHAR a = scdTerm(AS[2]);
        if ((isFstTermU(AS[0])&&fstTerm(AS[0])==a) || (isSecTermU(AS[0])&&scdTerm(AS[0])==a))
        {
            valid = true;
        }
        else valid = false;
    }
    
    return valid;
}

MYBOOL Rlh (analysis_proposition AS[3])
{
    return Rlhfst(AS) && Rlhsec(AS);
}

//Règle des deux négations : Vérifie si au moins une des deux prémisses est positive
MYBOOL Rnn (analysis_proposition AS[3])
{
    MYBOOL valid = (isAffirmative(AS[0]) || isAffirmative(AS[1]));
    return valid;
}
//Règle de passation de la négation :Vérifie que si une prémisse est négative, la conclusion est négative
MYBOOL Rpn (analysis_proposition AS[3])
{
    if (isNegative(AS[0]) || isNegative(AS[1]))
    {
        MYBOOL valid = (isNegative(AS[2]));
        return valid;
    }
    else
    {
        //printf("le test de la règle de la passation de la négation n'est pas pertinente pour la validité de ce syllogisme\n");
        return true;
    }
}
//Règle de passation de la double affirmation : vérifie si les deux prémisses sont affirmative que la conclusion le soit
MYBOOL Raa (analysis_proposition AS[3])
{
    if (isAffirmative(AS[0]) && isAffirmative(AS[1]))
    {
        MYBOOL valid = (isAffirmative(AS[2]));
        return valid;
    }
    else
    {
        //printf("le test de la règle de la passation de la négation n'est pas pertinente pour la validité de ce syllogisme\n");
        return true;
    }
}
//Règle des deux particularités Vérifie si au moins une des prémisses est universelle
MYBOOL Rpu (analysis_proposition AS[3])
{
    MYBOOL valid = (isUniversal(AS[0]) || isUniversal(AS[1]));
    return valid;

}
//Règle des la passation de particularité : Vérifie que si une prémisse est particulière, la conclusion aussi
MYBOOL Rpp (analysis_proposition AS[3])
{
    if (isParticular(AS[0]) || isParticular(AS[1]))
    {
        MYBOOL valid = (isParticular(AS[2]));
        return valid;
    }
    else
    {
        //printf("le test de la règle de la passation de la particularité n'est pas pertinente pour la validité de ce syllogisme\n");
        return true;
    }
}
//Module de validation de l'hypothèse d'existence
MYBOOL Ruu (analysis_proposition AS[3])
{
    if (isUniversal(AS[0]) && isUniversal(AS[1]))
    {
        if (isParticular(AS[2]))
        {
        return false;
        }
        else return true;
    }
    //L'hypothèse d'existence n'est pas pertinente
    else return true;
}


//Fonction de validation appelant les premières règles
void validationStep1 (analysis_proposition AS[3], bool v_tab[10])
{
    v_tab[0]=Rmt(AS);
    v_tab[1]=Rlh(AS);
    v_tab[2]=Rnn(AS);
    v_tab[3]=Rpn(AS);
    v_tab[4]=Raa(AS);
    v_tab[5]=Rpu(AS);
    v_tab[6]=Rpp(AS);
    v_tab[7]=Ruu(AS);
    v_tab[8]=(v_tab[0] && v_tab[1] && v_tab[2] && v_tab[3] && v_tab[4] && v_tab[5] && v_tab[6]&&v_tab[7]);
    v_tab[9] = true;
}

//Module de validation de l'intérêt
    //Pour les syllogisme ayant une conclusion particulière
    //Teste la validité avec une conclusion universelle

MYBOOL Ri(analysis_proposition AS[3])
{
    if (isParticular(AS[2]))
    {
        MYBOOL r_tab[10];

        AS[2].universal = true;
        validationStep1(AS, r_tab);

        AS[2].universal = false;

        if (r_tab[8])
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
void validationStep2 (analysis_proposition AS[3], bool v_tab[10])
{
    if (v_tab[8])
    {
        v_tab[9] = Ri(AS);
    }
}

//Fonction d'affichage du respect de chaque règle de validation d'un syllogisme
void displayResults (bool v_tab[10],user_proposition US[3])
{
    if (v_tab[0])
    {
        printf("la règle du moyen terme %s\n",boolToStr(v_tab[0]));
    }
    if (!v_tab[1])
    {
        printf("la règle du latius hos %s\n",boolToStr(v_tab[1]));
    }
    if (!v_tab[2])
    {
        printf("la règle des deux négations %s\n",boolToStr(v_tab[2]));
    }
    if (!v_tab[3])
    {
        printf("la règle de la passation de la négation %s\n",boolToStr(v_tab[3]));
    }
    if (!v_tab[4])
    {
        printf("la règle de la double affirmation %s\n",boolToStr(v_tab[4]));
    }
    if (!v_tab[5])
    {
        printf("la règle des deux particularités %s\n",boolToStr(v_tab[5]));
    }
    if (!v_tab[6])
    {
        printf("la règle de la passation de la particularité %s\n",boolToStr(v_tab[6]));
    }
    if (!v_tab[7])
    {
        printf("Attention : L'hypothèse d'existence %s\n",boolToStr(v_tab[6]));
    }
    if (!v_tab[9])
    {
        printf("Il n'est pas intéressant car sa conclusion pourrait être universelle\n");
    }
    
    if (v_tab[8])
    {
        printf("Le syllogisme\n");
        display_syllogism(US);
        printf("est valide\n");
    }
    else
    {
        printf("Le syllogisme\n");
        display_syllogism(US);
        printf("est invalide\n");
    }
}

//Fonction de validation complète d'un syllogisme
//Et affichage du résultat
void validation(analysis_proposition AS[3], user_proposition US[3], bool v_tab[10])
{
    validationStep1(AS,v_tab);
    validationStep2(AS,v_tab);
    displayResults(v_tab, US);
}