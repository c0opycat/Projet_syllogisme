#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "liste.h"
#include "syllogism.h"

#define MAX_STR_LEN 100


T_liste create_list_quantifier(){
    T_liste l;
    initListe(&l);
    return l;
}


//Arthur et Le�la
T_liste add_quantifier(const T_quantifier quantifier, T_liste ql)
{
    //ql = ajoutEnTete(ql, quantifier);
    return ajoutEnTete(ql, quantifier);
}

//Arthur et Le�la
void display_quantifier(const T_liste ql)
{
    afficheListePos(ql);
}

//Le�la
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

//Le�la
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

    for(int i = 1; i < choice; i++)
    {
        tmp = getptrNextCell(tmp);
    }

    return *(tmp->data);
}

//Arthur
void pq(T_quantifier q){
    printf("%s - ", q.quantifier_str);
    if(q.affirmative){
        printf("True\n");
    }else{
        printf("False\n");
    }
}



//affichage d'un syllogisme
//Arthur
void display_syllogism(user_proposition p[3]){
   int len = 2;
    for (int i = 0; i <= len; i++)
    {
        if(i <= 1)
        {
            printf("----------Prémisse %d----------\n", i);
            printf("%s - %s - %s\n", p[i].quantifier.quantifier_str , p[i].first_term, p[i].second_term);
        }
        else
        {
            printf("----------Conclusion----------\n");
            printf("%s - %s - %s\n", p[i].quantifier.quantifier_str , p[i].first_term, p[i].second_term);
        }

    }
}

//Fonction de saisie d'un syllogisme avec le module a 7 demandes
//Arthur
void input_advanced_syllogism(T_liste uql, T_liste eql, user_proposition user_syllogism[3]){
    bool uqList;
    T_quantifier quantifier;
    char sujet_tmp[MAX_STR_LEN], predicat_tmp[MAX_STR_LEN], terme_tmp[MAX_STR_LEN];
    int type = 0;

    ////Enregistrement des quantificateur des diff�rentres parties du syllogisme
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
    user_syllogism[0].quantifier = quantifier;

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

    //Enregistrement du sujet du syllogisme
    printf("Veuillez entrez le sujet de la conclusion : \n");
    scanf("%s", sujet_tmp);

    int len = strlen(sujet_tmp);
    char * sujet = (char*)malloc((len + 1) * sizeof(char));
    strcpy(sujet, sujet_tmp);

    //Enregistrement du pr�dicat du syllogisme
    printf("Veuillez entrez le prédicat de la conclusion : \n");
    scanf("%s", predicat_tmp);

    len = strlen(predicat_tmp);
    char * predicat = (char*)malloc((len + 1) * sizeof(char));
    strcpy(predicat, predicat_tmp);

    //Enregistrement du moyen terme du syllogisme
    printf("Veuillez entrez le moyen terme de la conclusion : \n");
    scanf("%s", terme_tmp);

    len = strlen(terme_tmp);
    char * terme = (char*)malloc((len + 1) * sizeof(char));
    strcpy(terme, terme_tmp);

    //Enregistrement du type du syllogisme
    printf("Entrez le type de voter syllogisme : \n");
    while(!(type > 0 && type < 5))
    {
        scanf("%d", &type);
    }

    if(type == 1)
    {
        user_syllogism[0].first_term = terme;
        user_syllogism[0].second_term = predicat;
        user_syllogism[1].first_term = sujet;
        user_syllogism[1].second_term = terme;
        user_syllogism[2].first_term = sujet;
        user_syllogism[2].second_term = predicat;
        display_syllogism(user_syllogism);
    }
    if (type == 2)
    {
        user_syllogism[0].first_term = predicat;
        user_syllogism[0].second_term = terme;
        user_syllogism[1].first_term = sujet;
        user_syllogism[1].second_term = terme;
        user_syllogism[2].first_term = sujet;
        user_syllogism[2].second_term = predicat;
        display_syllogism(user_syllogism);
    }
    if (type == 3)
    {
        user_syllogism[0].first_term = terme;
        user_syllogism[0].second_term = predicat;
        user_syllogism[1].first_term = terme;
        user_syllogism[1].second_term = sujet;
        user_syllogism[2].first_term = sujet;
        user_syllogism[2].second_term = predicat;
        display_syllogism(user_syllogism);
    }
    if (type == 4)
    {
        user_syllogism[0].first_term = predicat;
        user_syllogism[0].second_term = terme;
        user_syllogism[1].first_term = terme;
        user_syllogism[1].second_term = sujet;
        user_syllogism[2].first_term = sujet;
        user_syllogism[2].second_term = predicat;
        display_syllogism(user_syllogism);
    }
}

//Le�la
void input_simple_syllogism(T_liste uql, T_liste eql, user_proposition user_syllogism[3])
{
    bool uqList;
    T_quantifier quantifier;
    char term1_fst_prop[MAX_STR_LEN], term2_fst_prop[MAX_STR_LEN], term_scd_prop[MAX_STR_LEN];
    char s_or_p = 'a';
    int s_or_p2 = 0;
    printf("-----Module 9 demandes-----\n");
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

    user_syllogism[0].quantifier = quantifier;

    printf("Veuillez entrer le sujet de la première proposition\n");
    scanf("%s", term1_fst_prop);

    char* term1 = (char*)malloc(sizeof(char) * strlen(term1_fst_prop));
    term1 = term1_fst_prop;
    user_syllogism[0].first_term = term1;

    printf("Veuillez entrer le prédicat de la premi�re proposition\n");
    scanf("%s", term2_fst_prop);

    char* term2 = (char*)malloc(sizeof(char) * strlen(term2_fst_prop));
    term2 = term2_fst_prop;
    user_syllogism[0].second_term = term2;

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
        scanf("%s", term_scd_prop);

        char* term3 = (char*)malloc(sizeof(char) * strlen(term_scd_prop));
        term3 = term_scd_prop;
        user_syllogism[1].second_term = term3;
    }
    else
    {
        printf("Veuillez entrer le sujet\n");
        scanf("%s", term_scd_prop);

        char* term3 = (char*)malloc(sizeof(char) * strlen(term_scd_prop));
        term3 = term_scd_prop;
        user_syllogism[1].first_term = term3;

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

    display_syllogism(user_syllogism);
}


//Arthur
void choose_input(T_liste uql, T_liste eql, user_proposition user_syllogism[3]){
    printf("Tapez 1 pour choisire le module à 7 demandes\nTapez 2 pour choisire le module à 9 demandes\n");
    int a;
    while((a != 1) && (a != 2))
    {
        scanf("%d", &a);
    }

    if(a == 1){
        printf("Module à 7 demandes choisi\n");
        input_advanced_syllogism(uql, eql, user_syllogism);
    }else{
        printf("Module à 9 demandes choisi\n");
        input_simple_syllogism(uql, eql, user_syllogism);
    }
}


/*
void convert_to_analysis(user_proposition user_syllogism[3], analysis_proposition analysis_syllogism[3])
{

}
*/


int main()
{
    T_liste quant_list1 = create_list_quantifier();
    T_liste quant_list2 = create_list_quantifier();

    T_quantifier test1 = {"Aucun", false};
    T_quantifier test2 = {"Tous", true};

    quant_list1 = add_quantifier(test1, quant_list1);
    quant_list2 = add_quantifier(test2, quant_list2);

    display_quantifier(quant_list1);
    display_quantifier(quant_list2);

    //input_simple_syllogism(quant_list2, quant_list1);
    //input_advenced_syllogim(quant_list2, quant_list1, user_syllogism);

    user_proposition user_syllogism[3];
    //choose_input(quant_list2, quant_list1, user_syllogism);

    input_advanced_syllogism(quant_list2, quant_list1, user_syllogism);


    printf("\n------Affichage Main------\n\n");
    display_syllogism(user_syllogism);

    //printf("sujet prémisser 1 : %s\n", user_syllogism[0].first_term);

    return 0;
}
