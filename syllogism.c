#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "quantifier.h"
#include "liste.h"
#include "syllogism.h"

#define MAX_STR_LEN 100

//Arthur
//fonction pour vider le buffer
void clear_input_buffer() {
    int c;
    // Lire et jeter tous les caractères dans le tampon jusqu'à rencontrer un '\n' ou EOF
    while ((c = getchar()) != '\n' && c != EOF);
}


//Leïla
//fonction pour lire une chaîne de caractères (espaces inclus)
//retourne 0 si la chaîne a été lu correctement
int myfgets(char* chaine)
{
    char* rc = NULL;

    //récupère la chaîne de caractère
    if(fgets(chaine, MAX_STR_LEN, stdin) != NULL)
    {
        //on cherche le \n dans la chaîne
        rc = strchr(chaine, '\n');

        if(rc != NULL)
        {
            //s'il est trouvé, on le remplace par \0 signifiant la fin de la chaîne
            *rc = '\0';
        }
        else
        {
            //on vide le buffer si toute la chaîne n'a pas pu être récupérée
            clear_input_buffer();
        }

        return 0;
    }
    else
    {
        //on vide le buffer s'il y a eu une erreur
        clear_input_buffer();

        return 1;
    }
}


//Arthur
//affichage d'un syllogisme de 3 user_proposition
void display_syllogism(user_proposition p[3]){
   for(int i = 0; i < 3; i++)
   {
    printf("%s %s %s\n", p[i].quantifier.quantifier_str, p[i].first_term, p[i].second_term);
   }
}

//Arthur
//Fonction d'affichage des valeurs contenues dans les 3 analysis_proposition
void display_analysis(analysis_proposition p[3]){
    int count = 2;
    printf("------Display_analysis------\n");
    for (int i = 0; i <= count; i++)
    {
        printf("First term : %c\nSecond term : %c\nAffirmative(0 = false) : %d\nUniversal(0 = false) : %d\n", p[i].first_term, p[i].second_term, p[i].affirmative, p[i].universal );
        printf("--------------\n");
    }

}


//Arthur
//Fonction de saisie d'un syllogisme avec le module a 7 demandes
//modifie le tableau user_syllogism passé en parametres
void input_advanced_syllogism(T_liste uql, T_liste eql, user_proposition user_syllogism[3]){
    bool uqList;
    T_quantifier quantifier;
    char sujet_tmp[MAX_STR_LEN], predicat_tmp[MAX_STR_LEN], terme_tmp[MAX_STR_LEN];
    int type = 0;

    ////Enregistrement des quantificateur des différentres parties du syllogisme
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
    printf("Veuillez entrer le sujet de la conclusion : \n");
    myfgets(sujet_tmp);

    int len = strlen(sujet_tmp);
    char * sujet = (char*)malloc((len + 1) * sizeof(char));
    strcpy(sujet, sujet_tmp);

    //Enregistrement du prédicat du syllogisme
    printf("Veuillez entrer le prédicat de la conclusion : \n");
    myfgets(predicat_tmp);

    len = strlen(predicat_tmp);
    char * predicat = (char*)malloc((len + 1) * sizeof(char));
    strcpy(predicat, predicat_tmp);

    //Enregistrement du moyen terme du syllogisme
    printf("Veuillez entrer le moyen terme : \n");
    myfgets(terme_tmp);

    len = strlen(terme_tmp);
    char * terme = (char*)malloc((len + 1) * sizeof(char));
    strcpy(terme, terme_tmp);

    //Enregistrement du type du syllogisme
    printf("Entrez le type de votre syllogisme : \n");
    while(!(type > 0 && type < 5))
    {
        scanf("%d", &type);
        clear_input_buffer();
    }

    if(type == 1)
    {
        user_syllogism[0].first_term = terme;
        user_syllogism[0].second_term = predicat;
        user_syllogism[1].first_term = sujet;
        user_syllogism[1].second_term = terme;
        user_syllogism[2].first_term = sujet;
        user_syllogism[2].second_term = predicat;
    }
    if (type == 2)
    {
        user_syllogism[0].first_term = predicat;
        user_syllogism[0].second_term = terme;
        user_syllogism[1].first_term = sujet;
        user_syllogism[1].second_term = terme;
        user_syllogism[2].first_term = sujet;
        user_syllogism[2].second_term = predicat;
    }
    if (type == 3)
    {
        user_syllogism[0].first_term = terme;
        user_syllogism[0].second_term = predicat;
        user_syllogism[1].first_term = terme;
        user_syllogism[1].second_term = sujet;
        user_syllogism[2].first_term = sujet;
        user_syllogism[2].second_term = predicat;
    }
    if (type == 4)
    {
        user_syllogism[0].first_term = predicat;
        user_syllogism[0].second_term = terme;
        user_syllogism[1].first_term = terme;
        user_syllogism[1].second_term = sujet;
        user_syllogism[2].first_term = sujet;
        user_syllogism[2].second_term = predicat;
    }
}

//Leïla
//Fonction de saisie à 8 demandes (modifie le tableau user_syllogism en parametre)
void input_simple_syllogism(T_liste uql, T_liste eql, user_proposition user_syllogism[3])
{
    bool uqList;
    T_quantifier quantifier;
    char term1_fst_prop[MAX_STR_LEN], term2_fst_prop[MAX_STR_LEN], term_scd_prop[MAX_STR_LEN];
    char s_or_p = 'a';
    int s_or_p2 = 0;
    bool f1_or_f2;

    printf("-----Module à 8 demandes-----\n");
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
    myfgets(term1_fst_prop);

    char* term1 = (char*)malloc(sizeof(char) * strlen(term1_fst_prop));
    strcpy(term1, term1_fst_prop);
    user_syllogism[0].first_term = term1;

    printf("Veuillez entrer le prédicat de la première proposition\n");
    myfgets(term2_fst_prop);

    char* term2 = (char*)malloc(sizeof(char) * strlen(term2_fst_prop));
    strcpy(term2, term2_fst_prop);
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
        clear_input_buffer();
    }

    if(s_or_p == 'o')
    {
        f1_or_f2 = false;

        printf("Veuillez choisir le sujet :\n");
        printf("[1]:%s\n", user_syllogism[0].first_term);
        printf("[2]:%s\n", user_syllogism[0].second_term);

        while((s_or_p2 != 1) && (s_or_p2 != 2))
        {
            scanf("%d", &s_or_p2);
            clear_input_buffer();
        }

        if(s_or_p2 == 1)
        {
            user_syllogism[1].first_term = user_syllogism[0].first_term;
        }
        else
        {
            user_syllogism[1].first_term = user_syllogism[0].second_term;
        }

        printf("Veuillez entrer le prédicat :\n");
        myfgets(term_scd_prop);

        char* term3 = (char*)malloc(sizeof(char) * strlen(term_scd_prop));
        strcpy(term3, term_scd_prop);
        user_syllogism[1].second_term = term3;
    }
    else
    {
        f1_or_f2 = true;

        printf("Veuillez entrer le sujet : \n");
        myfgets(term_scd_prop);

        char* term3 = (char*)malloc(sizeof(char) * strlen(term_scd_prop));
        strcpy(term3, term_scd_prop);
        user_syllogism[1].first_term = term3;

        printf("Veuillez choisir le prédicat :\n");
        printf("[1]:%s\n", user_syllogism[0].first_term);
        printf("[2]:%s\n", user_syllogism[0].second_term);

        while((s_or_p2 != 1) && (s_or_p2 != 2))
        {
            scanf("%d", &s_or_p2);
            clear_input_buffer();
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

    if(f1_or_f2)
    {
        printf("Le sujet de la conclusion est donc le sujet de la deuxième proposition.\n");
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
        printf("Le sujet de la conclusion est donc le prédicat de la deuxième proposition.\n");
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
}


//Arthur
//Demande de choisir entre le module a 7 demandes et celui a 9 demandes
//Puis lance le module choisi
void choose_input(T_liste uql, T_liste eql, user_proposition user_syllogism[3]){
    
    printf("Tapez 1 pour choisir le module pour experts\nTapez 2 pour choisir le module pour novices\nTapez 3 pour ajouter un quantificateur\n");
    int a = 0;

    while((a != 1) && (a != 2) && (a != 3))
    {
        scanf("%d", &a);
        clear_input_buffer();
    }

    if(a == 1)
    {
        printf("Module pour experts choisi\n");
        input_advanced_syllogism(uql, eql, user_syllogism);
    }else if (a == 2)
    {
        printf("Module pour novices choisi\n");
        input_simple_syllogism(uql, eql, user_syllogism);
    }
    else{
        printf("Ajout d'un quantificateur choisi\n");
        new_quantifier(&uql, &eql);
        choose_input(uql, eql, user_syllogism);
    }
}

//Leïla et Arthur
//Converti un tableau de 3 user_proposition et un tableau de 3 analysis_proposition
void convert_to_analysis(user_proposition user_syllogism[3], analysis_proposition analysis_syllogism[3])
{
    if(user_syllogism[0].first_term == user_syllogism[1].second_term)
    {
        analysis_syllogism[0].first_term = 'M';
        analysis_syllogism[0].second_term = 'P';
        analysis_syllogism[1].first_term = 'S';
        analysis_syllogism[1].second_term = 'M';
        analysis_syllogism[2].first_term = 'S';
        analysis_syllogism[2].second_term = 'P';
    }
    else if(user_syllogism[0].second_term == user_syllogism[1].second_term)
    {
        analysis_syllogism[0].first_term = 'P';
        analysis_syllogism[0].second_term = 'M';
        analysis_syllogism[1].first_term = 'S';
        analysis_syllogism[1].second_term = 'M';
        analysis_syllogism[2].first_term = 'S';
        analysis_syllogism[2].second_term = 'P';
    }
    else if(user_syllogism[0].first_term == user_syllogism[1].first_term)
    {
        analysis_syllogism[0].first_term = 'M';
        analysis_syllogism[0].second_term = 'P';
        analysis_syllogism[1].first_term = 'M';
        analysis_syllogism[1].second_term = 'S';
        analysis_syllogism[2].first_term = 'S';
        analysis_syllogism[2].second_term = 'P';
    }
    else if(user_syllogism[0].second_term == user_syllogism[1].first_term)
    {
        analysis_syllogism[0].first_term = 'P';
        analysis_syllogism[0].second_term = 'M';
        analysis_syllogism[1].first_term = 'M';
        analysis_syllogism[1].second_term = 'S';
        analysis_syllogism[2].first_term = 'S';
        analysis_syllogism[2].second_term = 'P';
    }

    analysis_syllogism[0].universal = user_syllogism[0].quantifier.universal;
    analysis_syllogism[0].affirmative = user_syllogism[0].quantifier.affirmative;
    analysis_syllogism[1].universal = user_syllogism[1].quantifier.universal;
    analysis_syllogism[1].affirmative = user_syllogism[1].quantifier.affirmative;
    analysis_syllogism[2].universal = user_syllogism[2].quantifier.universal;
    analysis_syllogism[2].affirmative = user_syllogism[2].quantifier.affirmative;

}

//Arthur
//Fonction qui permet de libérer les ressources de nos user_proposition
void free_user_syl(user_proposition p[3])
{ 
    free(p[2].first_term);
    free(p[2].second_term);

    if(p[0].first_term == p[1].second_term)
    {
        free(p[0].first_term);
    }
    else if(p[0].second_term == p[1].second_term)
    {
        free(p[0].second_term);
    }
    else if(p[0].first_term == p[1].first_term)
    {
        free(p[0].first_term);
    }
    else if(p[0].second_term == p[1].first_term)
    {
        free(p[0].second_term);
    }
}


