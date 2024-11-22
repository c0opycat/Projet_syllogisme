#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "syllogism.h"
#include "validation.h"


// typedef struct as
// {
//     char first_term;
//     char second_term;
//     bool universal;
//     bool affirmative;
// }analysis_proposition;

void impl_type(char type, analysis_proposition* p)
{
    switch(type)
    {
        case 'A':
        {
            p->universal = true;
            p->affirmative = true;
            break;
        }

        case 'I':
        {
            p->universal = false;
            p->affirmative = true;
            break;
        }

        case 'E':
        {
            p->universal = true;
            p->affirmative = false;
            break;
        }

        default:
        {
            p->universal = false;
            p->affirmative = false;
            break;
        }
    }
}

void create_syllogism(analysis_proposition* res, int figure, char type1, char type2, char type3)
{
    switch (figure)
    {
        case 1:
        {
            res[0].first_term = 'M';
            res[0].second_term = 'P';
            res[1].first_term = 'S';
            res[1].second_term = 'M';
            res[2].first_term = 'S';
            res[2].second_term = 'P';
            break;
        }
        case 2:
        {
            res[0].first_term = 'P';
            res[0].second_term = 'M';
            res[1].first_term = 'S';
            res[1].second_term = 'M';
            res[2].first_term = 'S';
            res[2].second_term = 'P';
            break;
        }
        case 3:
        {
            res[0].first_term = 'M';
            res[0].second_term = 'P';
            res[1].first_term = 'M';
            res[1].second_term = 'S';
            res[2].first_term = 'S';
            res[2].second_term = 'P';
            break;
        }
        default:
        {
            res[0].first_term = 'P';
            res[0].second_term = 'M';
            res[1].first_term = 'M';
            res[1].second_term = 'S';
            res[2].first_term = 'S';
            res[2].second_term = 'P';
            break;
        }
    }

    impl_type(type1, &(res[0]));
    impl_type(type2, &(res[1]));
    impl_type(type3, &(res[2]));
}

void fill_tab_aux(analysis_proposition*** tab, int min, int max, int figure)
{
    char type1, type2, type3;

    int i = 0;
    
    for(int j = min; j <= max; i++)
    {
        if(i >= 0 && i <= 15)
        {
            type1 = 'A';
        }
        else if(i >= 16 && i <= 31)
        {
            type1 = 'I';
        }
        else if(i >= 32 && i <= 47)
        {
            type1 = 'E';
        }
        else
        {
            type1 = 'O';
        }

        if(i % 16 >= 0 && i % 16 <= 3)
        {
            type2 = 'A';
        }
        else if(i % 16 >= 4 && i % 16 <= 7)
        {
            type2 = 'I';
        }
        else if(i % 16 >= 8 && i % 16 <= 11)
        {
            type2 = 'E';
        }
        else
        {
            type2 = 'O';
        }

        if(i % 4 == 0)
        {
            type3 = 'A';
        }
        else if(i % 4 == 1)
        {
            type3 = 'I';
        }
        else if(i % 4 == 2)
        {
            type3 = 'E';
        }
        else
        {
            type3 = 'O';
        }

        i++;

        create_syllogism(*(tab[j]), figure, type1, type2, type3);
    }
}

analysis_proposition** fill_tab()
{
    analysis_proposition** tab;

    printf("dddd");


    tab = (analysis_proposition**)malloc(sizeof(analysis_proposition*) * 256);
    for(int i = 0; i < 256; i++)
    {
        *tab = (analysis_proposition*)malloc(sizeof(analysis_proposition) * 3);
    }

    printf("ssssss");

    fill_tab_aux(&tab, 0, 63, 1);
    fill_tab_aux(&tab, 64, 127, 2);
    fill_tab_aux(&tab, 128, 191, 3);
    fill_tab_aux(&tab, 192, 255, 4);

    printf("zzzzz");
    return tab;
}

//Fonction de validation appelant les premières règles
void validationStep1Tab(analysis_proposition AS[3], bool v_tab[11])
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
    v_tab[9]=(v_tab[0] && v_tab[1] && v_tab[2] && v_tab[3] && v_tab[4] && v_tab[5] && v_tab[6]&& v_tab[7]); //Avec
}

//Fonction appelant la règle d'interêt d'un syllogisme dans le cas où ce syllogisme est valide
void validationStep2Tab(analysis_proposition AS[3], bool v_tab[11])
{
    if (v_tab[9] == true)
    {
        v_tab[10] = Ri(AS);
    }
}

//Fonction qui détermine et renvoie la figure du syllogisme
int get_type_analysis(analysis_proposition analysis_syllogism[3])
{
    int type;

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

//Fonction d'affichage du respect de chaque règle de validation d'un syllogisme
void displayTab(bool v_tab[11], analysis_proposition AS[3])
{
    printf("Figure : %d ;", get_type_analysis(AS));

    printf("Type première proposition : %c ;", get_char_type(AS[0]));
    printf("Type seconde proposition : %c ;", get_char_type(AS[1]));
    printf("Type conclusion : %c ;", get_char_type(AS[2]));

    if (v_tab[9] == true)
    {
        printf("Le syllogisme ");
        printf("est valide ;");
    }
    else
    {
        printf("Le syllogisme ");
        printf("est invalide ;");
    }

    printf("Validité sans hypothèse d'existence : ");
    if (v_tab[8])
    {
        printf("true ;");
    }
    else 
    {
        printf("false ;");
    }

    if (!v_tab[10])
    {
        printf("Il n'est pas intéressant car sa conclusion pourrait être universelle ;");
    }
    
    printf("/n");
}

//Fonction de validation complète d'un syllogisme
//Et affichage du résultat
void validationTab(analysis_proposition** AS)
{   
    bool v_tab[11];

    for(int i = 0; i < 256; i++)
    {
        validationStep1Tab(AS[i],v_tab);
        validationStep2Tab(AS[i],v_tab);
        displayTab(v_tab, AS[i]);
    }
    
}


