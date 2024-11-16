#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "quantifier.h"
#include "liste.h"

//universal quantifier
T_quantifier uq1 = {"Aucun", true, false};
T_quantifier uq2 = {"Tout(e)", true, true};
T_quantifier uq3 = {"N'importe quel(le)", true, true};
T_quantifier uq4 = {"Chaque", true, true};
T_quantifier uq5 = {"Nul", true, false};

//existential quantifier
T_quantifier eq1 = {"Certains", false, true};
T_quantifier eq2 = {"Il existe", false, true};
T_quantifier eq3 = {"Il n'y a pas", false, false};
T_quantifier eq4 = {"Quelques", false, true};

//Création et initialisation d'une liste
//Renvoie la liste initialisée
T_liste create_list_quantifier(){
    T_liste l;
    initListe(&l);
    return l;
}

//Arthur et Leïla
//Ajout du quantificateur quantifier à la liste ql
//Retourne la liste ql modifiée
T_liste add_quantifier(const T_quantifier quantifier, T_liste ql)
{
    
    return ajoutEnTete(ql, quantifier);
}

//Leïla
//Ajout d'un quantificateur par saisie utilisateur
void new_quantifier(T_liste *qlu, T_liste *qle)
{
    T_quantifier toAdd;
    char tmp[50];
    char toBool = 'a';


    printf("Veuillez rentrer le quantificateur\n");

    scanf("%s", tmp);
    clear_input_buffer();

    toAdd.quantifier_str = (char*)malloc(sizeof(char) * strlen(tmp));
    strcpy(toAdd.quantifier_str, tmp);

        
    printf("Le quantificateur est-il affirmatif ?\n [o]:oui [n]:non \n");

    while(toBool != 'o' && toBool != 'n')
    {
        scanf("%c", &toBool);
        clear_input_buffer();
    }

    if(toBool == 'o')
    {
        toAdd.affirmative = true;
    }
    else
    {
        toAdd.affirmative = false;
    }

    //Pour rentrer dans la 2e boucle while
    toBool = 'a';

    printf("Le quantificateur est-il universel ?\n [o]:oui [n]:non \n");
    
    while(toBool != 'o' && toBool != 'n')
    {
        scanf("%c", &toBool);
        clear_input_buffer();
    }

    if(toBool == 'o')
    {
        toAdd.universal = true;
        *qlu = add_quantifier(toAdd, *qlu);
    }
    else
    {
        toAdd.universal = false;
        *qle = add_quantifier(toAdd, *qle);
    }
}

//Arthur et Leïla
//Affiche la liste de quantificateurs ql
void display_quantifier(const T_liste ql)
{
    afficheListePos(ql);
}

//Arthur
//Fonction qui prend une liste en parametre ainsi qu'un booleen et qui remplit celle-ci des quantificateur déclarés plus tôt avant de renvoyer cette meme liste remplit
T_liste init_list_quanti(T_liste l, bool isUniversal)
{
    if(isUniversal)
    {
        l = add_quantifier(uq1, l);
        l = add_quantifier(uq2, l);
        l = add_quantifier(uq3, l);
        l = add_quantifier(uq4, l);
        l = add_quantifier(uq5, l);

        return l;
    }
    else
    {
        l = add_quantifier(eq1, l);
        l = add_quantifier(eq2, l);
        l = add_quantifier(eq3, l);
        l = add_quantifier(eq4, l);

        return l;
    }
    
}

//Leïla
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

//Leïla
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