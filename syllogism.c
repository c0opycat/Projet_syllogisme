#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "liste.h"
#include "syllogism.h"

user_proposition user_syllogism[3];
analysis_proposition analysis_syllogism[3];

//Arthur et Leïla
T_liste add_quantifier(const T_quantifier quantifier, T_liste ql)
{
    //ql = ajoutEnTete(ql, quantifier);
    return ajoutEnTete(ql, quantifier);
}

//Arthur et Leïla
void display_quantifier(const T_liste ql)
{
    afficheListePos(ql);
}

//Leïla
bool choose_universal_quantifiers()
{
    bool res = false;

    int a = 0;
    
    printf("Tapez 1 pour ouvrir la liste des quantificateurs universels\n");
    printf("Tapez 2 pour ouvrir la liste des quantificateurs existentiels\n");

    while((a != 1) && (a != 2))
    {
        scanf("%d", &a);
    }

    if(a == 1)
    {
        res = true;
    }
    return res;
}

//Leïla
T_quantifier choose_quantifier(T_liste ql)
{
    const int ql_len = getNbreCell(ql);
    int choice = 0;

    afficheListePos(ql);

    while((choice < 1) || (choice > ql_len))
    {
        printf("\nVeuillez choisir un quantificateur et rentrer son numéro : \n");
        scanf("%d", &choice);
    }

    T_liste tmp = ql;

    for(int i = 1; i <= choice; i++)
    {
        tmp = getptrNextCell(tmp);
    }
    
    return *(tmp->data);
}

//ma fonction est très très moche au niveau de la gestion de la mémoire et juste en général mdr
//je te conseille de pas la regarder 
void input_simple_syllogism(T_liste uql, T_liste eql)
{
    bool uqList;
    T_quantifier quantifier;
    char term[100]; //GERER MIEUX L'ESPACE DE LA CHAINE DE CAR MAIS PAS CONNUE A L'AVANCE 
    char s_or_p = 'a';
    int s_or_p2 = 0;

    printf("-----Première proposition-----\n");
    
    uqList = choose_universal_quantifiers();

    if(uqList)
    {
        quantifier = choose_quantifier(uql);
    }
    else
    {
        quantifier = choose_quantifier(eql);
    }

    //ne marche pas à partir d'ici lol
    user_syllogism[0].quantifier = quantifier;

    printf("Veuillez entrer le sujet (et le verbe qui suit)\n");
    scanf("%s", term);

    user_syllogism[0].first_term = term;

    printf("Veuillez entrer le prédicat\n");
    scanf("%s", term);

    user_syllogism[0].second_term = term;
    
    printf("-----Deuxième proposition-----\n");
    
    uqList = choose_universal_quantifiers();

    if(uqList)
    {
        quantifier = choose_quantifier(uql);
    }
    else
    {
        quantifier = choose_quantifier(eql);
    }

    user_syllogism[1].quantifier = quantifier;

    printf("Le sujet est-il le sujet ou le prédicat de la première proposition ? \n");
    printf("[o]:oui [n]:non\n"); 

    while((s_or_p != 'o') && (s_or_p != 'n'))
    {
        scanf("%c", &s_or_p);
    }

    if(s_or_p == 'o')
    {
        printf("Veuillez choisir le sujet\n");
        printf("[1]:%s\n", user_syllogism[0].first_term);
        printf("[2]:%s\n", user_syllogism[0].second_term);

        while((s_or_p2 != 1) && (s_or_p2 != 2))
        {
            scanf("%d", &s_or_p2);
        }
        
        if(s_or_p2 == 1)
        {
            user_syllogism[1].first_term = user_syllogism[0].first_term;
        }
        else
        {
            user_syllogism[1].first_term = user_syllogism[0].second_term;
        }

        printf("Veuillez entrer le prédicat \n");
        scanf("%s", term);
        user_syllogism[1].second_term = term;   
    }
    else
    {
        printf("Veuillez entrer le sujet (et le verbe qui suit)\n");
        scanf("%s", term);

        user_syllogism[1].first_term = term;

        printf("Veuillez choisir le prédicat\n");
        printf("[1]:%s\n", user_syllogism[0].first_term);
        printf("[2]:%s\n", user_syllogism[0].second_term);

        while((s_or_p2 != 1) && (s_or_p2 != 2))
        {
            scanf("%d", &s_or_p2);
        }
        
        if(s_or_p2 == 1)
        {
            user_syllogism[1].second_term = user_syllogism[0].first_term;
        }
        else
        {
            user_syllogism[1].second_term = user_syllogism[0].second_term;
        }
    }

    printf("-----Conclusion-----\n");
    
    uqList = choose_universal_quantifiers();

    if(uqList)
    {
        quantifier = choose_quantifier(uql);
    }
    else
    {
        quantifier = choose_quantifier(eql);
    }

    user_syllogism[2].quantifier = quantifier;

    printf("Le sujet est-il le sujet ou le prédicat de la deuxième propostion ?\n");
    printf("[s]:sujet  [p]:prédicat\n");

    while((s_or_p != 's') && (s_or_p != 'p'))
    {
        scanf("%c", &s_or_p);
    }

    if(s_or_p == 's')
    {
        user_syllogism[2].first_term = user_syllogism[1].first_term;
        
        if(user_syllogism[0].first_term == user_syllogism[1].second_term)
        {
            user_syllogism[2].second_term = user_syllogism[0].second_term;
        }
        else
        {
            user_syllogism[2].second_term = user_syllogism[0].first_term;
        }
    }
    else
    {
        user_syllogism[2].first_term = user_syllogism[1].second_term;

        if(user_syllogism[1].first_term == user_syllogism[0].first_term)
        {
            user_syllogism[2].second_term = user_syllogism[0].second_term;
        }
        else
        {
            user_syllogism[2].second_term = user_syllogism[0].first_term;
        }
    }

    printf("%s\n", user_syllogism[0].first_term);
    printf("%s\n", user_syllogism[0].second_term);
    printf("%s\n", user_syllogism[1].first_term);
    printf("%s\n", user_syllogism[1].second_term);
    printf("%s\n", user_syllogism[2].first_term);
    printf("%s\n", user_syllogism[2].second_term);
}

int main()
{
    for(int i = 0; i < 3; i ++)
    {
        user_syllogism[i].first_term = (char*)malloc(sizeof(char) * 100); //GERER LA MEMOIRE
        user_syllogism[i].second_term = (char*)malloc(sizeof(char) * 100); //GERER LA MEMOIRE
    }

    T_liste quant_list1;
    T_liste quant_list2;
    initListe(&quant_list1);
    initListe(&quant_list2);

    T_quantifier test1 = {"Aucun", false};
    T_quantifier test2 = {"Tous", true};

    quant_list1 = add_quantifier(test1, quant_list1);
    quant_list2 = add_quantifier(test2, quant_list2);

    //display_quantifier(quant_list);

    input_simple_syllogism(quant_list2, quant_list1);

    return 0;
}
