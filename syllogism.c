#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "liste.h"
#include "syllogism.h"

#define MAX_STR_LEN 100

//Création et initialisation d'une liste
//Renvoie la liste initialisée
T_liste create_list_quantifier(){
    T_liste l;
    initListe(&l);
    return l;
}


//Arthur et Le�la
//Ajout du quantificateur quantifier à la liste ql
//Retourne la liste ql modifiée
T_liste add_quantifier(const T_quantifier quantifier, T_liste ql)
{
    //ql = ajoutEnTete(ql, quantifier);
    return ajoutEnTete(ql, quantifier);
}

//Arthur et Le�la
//Affiche la liste de quantificateurs ql
void display_quantifier(const T_liste ql)
{
    afficheListePos(ql);
}

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
//Le�la
//Demande de choisir entre quantificateurs universels et existentiels
//Renvoie true si quantificateurs universels choisi
bool choose_universal_quantifiers()
{
    bool res = false;

    int a = 0;

    printf("Tapez 1 pour ouvrir la liste des quantificateurs universels\n");
    printf("Tapez 2 pour ouvrir la liste des quantificateurs existentiels\n");

    while((a != 1) && (a != 2))
    {
        scanf("%d", &a);
        clear_input_buffer();
    }

    if(a == 1)
    {
        res = true;
    }
    return res;
}

//Le�la
//Demande de choisir un quantificateur parmi ceux contenus dans la liste ql
//Renvoie le quantificateur choisi
T_quantifier choose_quantifier(T_liste ql)
{
    const int ql_len = getNbreCell(ql);
    int choice = 0;

    afficheListePos(ql);

    while((choice < 1) || (choice > ql_len))
    {
        printf("\nVeuillez choisir un quantificateur et rentrer son numéro : \n");
        scanf("%d", &choice);
        clear_input_buffer();
    }

    T_liste tmp = ql;

    for(int i = 1; i < choice; i++)
    {
        tmp = getptrNextCell(tmp);
    }
    return *(tmp->data);
}

/*
//Arthur
//fonction de test
void pq(T_quantifier q){
    printf("%s - ", q.quantifier_str);
    if(q.affirmative){
        printf("True\n");
    }else{
        printf("False\n");
    }
}
*/



//Arthur
//affichage d'un syllogisme de 3 user_proposition
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
//modifie le tableau user_syllogism passe en parametres
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
    printf("Veuillez entrer le sujet de la conclusion : \n");
    myfgets(sujet_tmp);

    int len = strlen(sujet_tmp);
    char * sujet = (char*)malloc((len + 1) * sizeof(char));
    strcpy(sujet, sujet_tmp);

    //Enregistrement du pr�dicat du syllogisme
    printf("Veuillez entrer le prédicat de la conclusion : \n");
    myfgets(predicat_tmp);

    len = strlen(predicat_tmp);
    char * predicat = (char*)malloc((len + 1) * sizeof(char));
    strcpy(predicat, predicat_tmp);

    //Enregistrement du moyen terme du syllogisme
    printf("Veuillez entrer le moyen terme de la conclusion : \n");
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
//Fonction de saisie à 9 demandes (modifie le tableau user_syllogism en parametre)
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
    myfgets(term1_fst_prop);

    char* term1 = (char*)malloc(sizeof(char) * strlen(term1_fst_prop));
    strcpy(term1, term1_fst_prop);
    user_syllogism[0].first_term = term1;

    printf("Veuillez entrer le prédicat de la premi�re proposition\n");
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
        printf("Veuillez choisir le sujet\n");
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

        printf("Veuillez entrer le prédicat \n");
        myfgets(term_scd_prop);

        char* term3 = (char*)malloc(sizeof(char) * strlen(term_scd_prop));
        strcpy(term3, term_scd_prop);
        user_syllogism[1].second_term = term3;
    }
    else
    {
        printf("Veuillez entrer le sujet\n");
        myfgets(term_scd_prop);

        char* term3 = (char*)malloc(sizeof(char) * strlen(term_scd_prop));
        term3 = term_scd_prop;
        user_syllogism[1].first_term = term3;

        printf("Veuillez choisir le prédicat\n");
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

    printf("Le sujet est-il le sujet ou le prédicat de la deuxième propostion ?\n");
    printf("[s]:sujet  [p]:prédicat\n");

    while((s_or_p != 's') && (s_or_p != 'p'))
    {
        scanf("%c", &s_or_p);
        clear_input_buffer();
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
}


//Arthur
//Demande de choisir entre le module a 7 demandes et celui a 9 demandes
//Puis lance le module choisi
void choose_input(T_liste uql, T_liste eql, user_proposition user_syllogism[3]){
    printf("Tapez 1 pour choisire le module à 7 demandes\nTapez 2 pour choisire le module à 9 demandes\n");
    int a;
    while((a != 1) && (a != 2))
    {
        scanf("%d", &a);
        clear_input_buffer();
    }

    if(a == 1){
        printf("Module à 7 demandes choisi\n");
        input_advanced_syllogism(uql, eql, user_syllogism);
    }else{
        printf("Module à 9 demandes choisi\n");
        input_simple_syllogism(uql, eql, user_syllogism);
    }
}

//Leïla et Arthur
//Converti un tableau de 3 user_proposition et un tableau de 3 analysis_proposition
void convert_to_analysis(user_proposition user_syllogism[3], analysis_proposition analysis_syllogism[3])
{
    if(user_syllogism[0].first_term == user_syllogism[1].second_term)
    {
        printf("figure 1\n");
        analysis_syllogism[0].first_term = 'M';
        analysis_syllogism[0].second_term = 'P';
        analysis_syllogism[1].first_term = 'S';
        analysis_syllogism[1].second_term = 'M';
        analysis_syllogism[2].first_term = 'S';
        analysis_syllogism[2].second_term = 'P';
    }
    else if(user_syllogism[0].second_term == user_syllogism[1].second_term)
    {
        printf("figure 2\n");
        analysis_syllogism[0].first_term = 'P';
        analysis_syllogism[0].second_term = 'M';
        analysis_syllogism[1].first_term = 'S';
        analysis_syllogism[1].second_term = 'M';
        analysis_syllogism[2].first_term = 'S';
        analysis_syllogism[2].second_term = 'P';
    }
    else if(user_syllogism[0].first_term == user_syllogism[1].first_term)
    {
        printf("figure 3\n");
        analysis_syllogism[0].first_term = 'M';
        analysis_syllogism[0].second_term = 'P';
        analysis_syllogism[1].first_term = 'M';
        analysis_syllogism[1].second_term = 'S';
        analysis_syllogism[2].first_term = 'S';
        analysis_syllogism[2].second_term = 'P';
    }
    else if(user_syllogism[0].second_term == user_syllogism[1].first_term)
    {
        printf("figure 4\n");
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

/*

//ne fonctionne pas ???
void free_user_syl(user_proposition p[3]){
    int count = 2;
    for (int i = 0; i < count; i++)
    {
        free(p[i].first_term);
    }
}
*/

int main()
{
    T_liste quant_list1 = create_list_quantifier();
    T_liste quant_list2 = create_list_quantifier();

    T_quantifier test1 = {"Aucun", true, false};
    T_quantifier test2 = {"Tous", true, true};

    quant_list1 = add_quantifier(test1, quant_list1);
    quant_list2 = add_quantifier(test2, quant_list2);

    user_proposition user_syllogism[3];
    analysis_proposition analysis_syllogism[3];

    choose_input(quant_list2, quant_list1, user_syllogism);

    convert_to_analysis(user_syllogism, analysis_syllogism);

    display_syllogism(user_syllogism);
    display_analysis(analysis_syllogism);

    return 0;
}
