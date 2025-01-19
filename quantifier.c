#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "utils.h"
#include "quantifier.h"
#include "liste.h"


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

//Arthur
//Prend en parametre une liste de quantificateurs et un booleen(true si il s'agit de la liste de quantificateurs universels, false sinon)
//Renvoie la meme liste contenant les quantificateurs déclarés plus tot
/*
//Fonction pour initialiser le fichier de sauvegarde avec les quantificateurs de base

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


T_liste init_list_quanti(T_liste l, bool isUniversal)
{
    char * filenameqlu = "QuantSave/quantifierUniversal.bin";
    char * filenameqle = "QuantSave/quantifierExistential.bin";
    
    if(isUniversal)
    {
        l = ajouterEtSauvegarder(l , &uq1, filenameqlu);
        l = ajouterEtSauvegarder(l , &uq2, filenameqlu);
        l = ajouterEtSauvegarder(l , &uq3, filenameqlu);
        l = ajouterEtSauvegarder(l , &uq4, filenameqlu);
        l = ajouterEtSauvegarder(l , &uq5, filenameqlu);

        return l;
    }
    else
    {
        l = ajouterEtSauvegarder(l , &eq1, filenameqle);
        l = ajouterEtSauvegarder(l , &eq2, filenameqle);
        l = ajouterEtSauvegarder(l , &eq3, filenameqle);
        l = ajouterEtSauvegarder(l , &eq4, filenameqle);

        return l;
    }
    
}
*/

void sauvegarderQuantificateur(FILE* file, T_quantifier* quant) {
    // Sauvegarder la longueur de la chaîne pour la lire correctement plus tard
    size_t len = strlen(quant->quantifier_str) + 1;
    fwrite(&len, sizeof(size_t), 1, file);
    fwrite(quant->quantifier_str, sizeof(char), len, file);
    fwrite(&quant->universal, sizeof(bool), 1, file);
    fwrite(&quant->affirmative, sizeof(bool), 1, file);
}

T_liste ajouterEtSauvegarder(T_liste liste, T_quantifier* quant, const MYPCHAR filename) {
    // Ajouter à la liste en mémoire
    liste = ajouterEnFin(liste, quant);

    // Sauvegarder dans le fichier
    FILE* file = fopen(filename, "ab");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier pour sauvegarde");
        return liste;
    }
    sauvegarderQuantificateur(file, quant);
    fclose(file);

    return liste;
}

T_quantifier* lireQuantificateur(FILE* file) {
    size_t len;
    if (fread(&len, sizeof(size_t), 1, file) != 1) return NULL;

    T_quantifier* quant = (T_quantifier*)malloc(sizeof(T_quantifier));
    if (!quant) {
        perror("Erreur d'allocation mémoire pour un quantificateur");
        exit(EXIT_FAILURE);
    }
    quant->quantifier_str = (char*)malloc(len);
    if (!quant->quantifier_str) {
        perror("Erreur d'allocation mémoire pour la chaîne de quantificateur");
        exit(EXIT_FAILURE);
    }

    fread(quant->quantifier_str, sizeof(char), len, file);
    fread(&quant->universal, sizeof(bool), 1, file);
    fread(&quant->affirmative, sizeof(bool), 1, file);

    return quant;
}

T_liste initialiserListeDepuisFichier(const MYPCHAR filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Fichier introuvable ou inaccessible, initialisation d'une liste vide");
        return NULL; // Fichier introuvable, liste vide
    }

    T_liste liste = NULL;
    T_quantifier* quant;
    while ((quant = lireQuantificateur(file)) != NULL) {
        liste = ajouterEnFin(liste, quant);
    }

    fclose(file);
    return liste;
}

//Leïla
//Ajout d'un quantificateur par saisie utilisateur
void new_quantifier(T_liste *qlu, T_liste *qle)
{

    MYPCHAR filenameqlu = "QuantSave/quantifierUniversal.bin";
    MYPCHAR filenameqle = "QuantSave/quantifierExistential.bin";

    T_quantifier toAdd;
    MYCHAR tmp[50];
    MYCHAR toBool = 'a';


    printf("Veuillez rentrer le quantificateur\n");

    scanf("%s", tmp);
    clear_input_buffer();

    toAdd.quantifier_str = (MYPCHAR)malloc(sizeof(MYCHAR) * strlen(tmp));
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
        *qlu = ajouterEtSauvegarder(*qlu, &toAdd, filenameqlu);
        display_quantifier(*qlu);
    }
    else
    {
        toAdd.universal = false;
        *qle = ajouterEtSauvegarder(*qle, &toAdd, filenameqle);
        display_quantifier(*qle);
    }
}

//Arthur et Leïla
//Affiche la liste de quantificateurs ql
void display_quantifier(const T_liste ql)
{
    afficheListePos(ql);
}



//Leïla
//Demande de choisir entre quantificateurs universels et existentiels
//Renvoie true si quantificateurs universels choisi
MYBOOL choose_universal_quantifiers()
{
    MYBOOL res = false;

    MYVAL a = 0;

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
    const MYVAL ql_len = getNbreCell(ql);
    MYVAL choice = 0;

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

//Fonction qui modifie le quantificateur passé en paramètre avec la saisie utilisateur
void set_quantifier(T_quantifier* q, T_liste uql, T_liste eql)
{
    T_quantifier quantifier;
    quantifier = choose_universal_quantifiers() ? choose_quantifier(uql) : choose_quantifier(eql);
    
    *q = quantifier;
}