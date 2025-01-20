#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "types.h"
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
MYBOOL Rmt (analysis_syllogism AS)
{
    MYBOOL valid = false;

    for (MYVAL i = 0; i < 2; i++)
    {
        if (isE(get_i_aprop(AS, i)) || (isA(get_i_aprop(AS, i)) && fstTerm(get_i_aprop(AS, i)) == 'M') || (isO(get_i_aprop(AS, i)) && scdTerm(get_i_aprop(AS, i)) == 'M'))
        {
            valid = true;
            return valid;
        }
    }

    return valid;
}

//Règle du latius hos : vérifie que si un terme est universel dans la conclusion il l'est dans la prémisse
MYBOOL Rlhfst(analysis_syllogism AS)
{
    MYBOOL valid = true;

    if (isFstTermU(get_conc_aprop(AS)))
    {
        MYCHAR a = fstTerm(get_conc_aprop(AS));
        if ((isFstTermU(get_scd_aprop(AS)) && fstTerm(get_scd_aprop(AS)) == a) || (isSecTermU(get_scd_aprop(AS)) && scdTerm(get_scd_aprop(AS)) == a))
        {  
            valid = true;
        }
        else valid = false;
    }
    
    return valid;
}

MYBOOL Rlhsec(analysis_syllogism AS)
{
    MYBOOL valid = true;
    if (isSecTermU(get_conc_aprop(AS)))
    {
        MYCHAR a = scdTerm(get_conc_aprop(AS));
        if ((isFstTermU(get_fst_aprop(AS)) && fstTerm(get_fst_aprop(AS)) == a) || (isSecTermU(get_fst_aprop(AS)) && scdTerm(get_fst_aprop(AS)) == a))
        {
            valid = true;
        }
        else valid = false;
    }
    
    return valid;
}

MYBOOL Rlh (analysis_syllogism AS)
{
    return Rlhfst(AS) && Rlhsec(AS);
}

//Règle des deux négations : Vérifie si au moins une des deux prémisses est positive
MYBOOL Rnn (analysis_syllogism AS)
{
    MYBOOL valid = (isAffirmative(get_fst_aprop(AS)) || isAffirmative(get_scd_aprop(AS)));
    return valid;
}
//Règle de passation de la négation :Vérifie que si une prémisse est négative, la conclusion est négative
MYBOOL Rpn (analysis_syllogism AS)
{
    if (isNegative(get_fst_aprop(AS)) || isNegative(get_scd_aprop(AS)))
    {
        MYBOOL valid = (isNegative(get_conc_aprop(AS)));
        return valid;
    }
    else
    {
        //printf("le test de la règle de la passation de la négation n'est pas pertinente pour la validité de ce syllogisme\n");
        return true;
    }
}
//Règle de passation de la double affirmation : vérifie si les deux prémisses sont affirmative que la conclusion le soit
MYBOOL Raa (analysis_syllogism AS)
{
    if (isAffirmative(get_fst_aprop(AS)) && isAffirmative(get_scd_aprop(AS)))
    {
        MYBOOL valid = (isAffirmative(get_conc_aprop(AS)));
        return valid;
    }
    else
    {
        //printf("le test de la règle de la passation de la négation n'est pas pertinente pour la validité de ce syllogisme\n");
        return true;
    }
}
//Règle des deux particularités Vérifie si au moins une des prémisses est universelle
MYBOOL Rpu (analysis_syllogism AS)
{
    MYBOOL valid = (isUniversal(get_fst_aprop(AS)) || isUniversal(get_scd_aprop(AS)));
    return valid;

}
//Règle des la passation de particularité : Vérifie que si une prémisse est particulière, la conclusion aussi
MYBOOL Rpp (analysis_syllogism AS)
{
    if (isParticular(get_fst_aprop(AS)) || isParticular(get_scd_aprop(AS)))
    {
        MYBOOL valid = (isParticular(get_conc_aprop(AS)));
        return valid;
    }
    else
    {
        //printf("le test de la règle de la passation de la particularité n'est pas pertinente pour la validité de ce syllogisme\n");
        return true;
    }
}
//Module de validation de l'hypothèse d'existence
MYBOOL Ruu (analysis_syllogism AS)
{
    if (isUniversal(get_fst_aprop(AS)) && isUniversal(get_scd_aprop(AS)))
    {
        if (isParticular(get_conc_aprop(AS)))
        {
        return false;
        }
        else return true;
    }
    //L'hypothèse d'existence n'est pas pertinente
    else return true;
}


//Fonction de validation appelant les premières règles
void validationStep1 (analysis_syllogism AS, MYBOOL v_tab[10], MYCHAR hyp_existence)
{
    v_tab[0]=Rmt(AS);
    v_tab[1]=Rlh(AS);
    v_tab[2]=Rnn(AS);
    v_tab[3]=Rpn(AS);
    v_tab[4]=Raa(AS);
    v_tab[5]=Rpu(AS);
    v_tab[6]=Rpp(AS);

    if(hyp_existence == 'o')
    {
        v_tab[7]=Ruu(AS);
        v_tab[8]=(v_tab[0] && v_tab[1] && v_tab[2] && v_tab[3] && v_tab[4] && v_tab[5] && v_tab[6] && v_tab[7]);
    }
    else
    {
        v_tab[7] = true;
        v_tab[8]=(v_tab[0] && v_tab[1] && v_tab[2] && v_tab[3] && v_tab[4] && v_tab[5] && v_tab[6]);
    }

    v_tab[9] = true;
}

//Module de validation de l'intérêt
    //Pour les syllogisme ayant une conclusion particulière
    //Teste la validité avec une conclusion universelle

MYBOOL Ri(analysis_syllogism AS, MYCHAR hyp_existence)
{
    if (isParticular(get_conc_aprop(AS)))
    {
        MYBOOL r_tab[10];

        set_analysis_prop_quantifier(get_p_conc_aprop(&AS), true);
        validationStep1(AS, r_tab, hyp_existence);

        set_analysis_prop_quantifier(get_p_conc_aprop(&AS), true);

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
void validationStep2 (analysis_syllogism AS, MYBOOL v_tab[10], MYCHAR hyp_existence)
{
    if (v_tab[8])
    {
        v_tab[9] = Ri(AS, hyp_existence);
    }
}

//Fonction d'affichage du respect de chaque règle de validation d'un syllogisme
void displayResults (MYBOOL v_tab[10],user_syllogism US)
{
    if (!v_tab[0])
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
        printf("Attention : L'hypothèse d'existence %s\n",boolToStr(v_tab[7]));
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
void validation(analysis_syllogism AS, user_syllogism US, MYBOOL v_tab[10])
{
    MYCHAR hyp_existence = 'a';
    MYCHAR interet = 'a';
    printf("Voulez-vous tester la règle d'hypothèse d'existence ?\n");
    printf("[o]:oui [n]:non\n");
    hyp_existence = read_char();
    validationStep1(AS, v_tab, hyp_existence);

    printf("Voulez-vous tester l'interêt du syllogisme ?\n");
    printf("[o]:oui [n]:non\n");
    interet = read_char();

    if(interet == 'o')
    {
        validationStep2(AS, v_tab, hyp_existence);
    }

    displayResults(v_tab, US);
}