#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "types.h"
#include "syllogism.h"
#include "quantifier.h"
#include "utils.h"

#define MAX_STR_LEN 100


//Getter
//Retourne le premier terme d'une user_proposition
MYPCHAR get_user_fst_term(user_proposition user_prop)
{
    return user_prop.first_term;
}

//Retourne le second terme d'une user_proposition
MYPCHAR get_user_scd_term(user_proposition user_prop)
{
    return user_prop.second_term;
}

//Retourne le quantificateur d'une user_proposition
T_quantifier get_user_quantifier(user_proposition user_prop)
{
    return user_prop.quantifier;
}

//Retourne true si la proposition est universelle
MYBOOL isU_universal(user_proposition user_prop)
{
    return get_quant_universal(get_user_quantifier(user_prop));
}

//Retourne true si la proposition est affirmative
MYBOOL isU_affirmative(user_proposition user_prop)
{
    return get_quant_affirmative(get_user_quantifier(user_prop));
}

//Retourne true si la proposition est universelle
MYBOOL isUniversal (analysis_proposition analysis_prop)
{
    return analysis_prop.universal;
}

//Retourne true si la proposition est particulière
MYBOOL isParticular (analysis_proposition analysis_prop)
{
    return !(analysis_prop.universal);
}

//Retourne true si la proposition est affirmative
MYBOOL isAffirmative (analysis_proposition analysis_prop)
{
    return analysis_prop.affirmative;
}

//Retourne true si la proposition est négative
MYBOOL isNegative (analysis_proposition analysis_prop)
{
    return !(analysis_prop.affirmative);
}

//Retourne le type (SPM) du premier terme
MYCHAR fstTerm (analysis_proposition analysis_prop)
{
    return analysis_prop.first_term;
}

//Retourne le type (SPM) du second terme
MYCHAR scdTerm (analysis_proposition analysis_prop)
{
    return analysis_prop.second_term;
}

//Retourne true si la proposition est de type A
MYBOOL isA(analysis_proposition AS)
{
    return (isUniversal(AS) && isAffirmative(AS));
}


//Retourne true si la proposition est de type E
MYBOOL isE(analysis_proposition AS)
{
    return (isUniversal(AS) && !isAffirmative(AS));
}

//Retourne true si la proposition est de type I
MYBOOL isI(analysis_proposition AS)
{
    return (!isUniversal(AS) && isAffirmative(AS));
}

//Retourne true si la proposition est de type O
MYBOOL isO(analysis_proposition AS)
{
    return (!isUniversal(AS) && !isAffirmative(AS));
}

//retourne le type de la proposition
MYCHAR get_char_type(analysis_proposition AS)
{
    if(isA(AS))
    {
        return 'A';
    }

    else if(isE(AS))
    {
        return 'E';
    }
    else if(isI(AS))
    {
        return 'I';
    }
    else
    {
        return 'O';
    }
}

//Retourne true si le sujet de la proposition est universel
MYBOOL isFstTermU(analysis_proposition AS)
{
    return (isA(AS)||isE(AS));
}

//Retourne true si le sujet de la proposition est existentiel
MYBOOL isSecTermU(analysis_proposition AS)
{
    return (isE(AS)||isO(AS));
}

//Retourne la première proposition d'un syllogisme user
user_proposition get_fst_uprop(user_syllogism us)
{
    return us.up[0];
}

//Retourne la deuxième proposition d'un syllogisme user
user_proposition get_scd_uprop(user_syllogism us)
{
    return us.up[1];
}

//Retourne la conclusion d'un syllogisme user
user_proposition get_conc_uprop(user_syllogism us)
{
    return us.up[2];
}

user_proposition get_i_uprop(user_syllogism us, MYVAL i)
{
    switch(i)
    {
        case 0: return get_fst_uprop(us);
        case 1: return get_scd_uprop(us);
        default: return get_conc_uprop(us);
    }
}

//Retourne la première proposition d'un syllogisme user
user_proposition* get_p_fst_uprop(user_syllogism* us)
{
    return &(us->up[0]);
}

//Retourne la deuxième proposition d'un syllogisme user
user_proposition* get_p_scd_uprop(user_syllogism* us)
{
    return &(us->up[1]);
}

//Retourne la conclusion d'un syllogisme user
user_proposition* get_p_conc_uprop(user_syllogism* us)
{
    return &(us->up[2]);
}

user_proposition* get_p_i_uprop(user_syllogism* us, MYVAL i)
{
    switch(i)
    {
        case 0: return get_p_fst_uprop(us);
        case 1: return get_p_scd_uprop(us);
        default: return get_p_conc_uprop(us);
    }
}

//Retourne la première proposition d'un syllogisme analysis
analysis_proposition get_fst_aprop(analysis_syllogism as)
{
    return as.ap[0];
}

//Retourne la deuxième proposition d'un syllogisme analysis
analysis_proposition get_scd_aprop(analysis_syllogism as)
{
    return as.ap[1];
}

//Retourne la conclusion d'un syllogisme analysis
analysis_proposition get_conc_aprop(analysis_syllogism as)
{
    return as.ap[2];
}

analysis_proposition get_i_aprop(analysis_syllogism as, MYVAL i)
{
    switch(i)
    {
        case 0: return get_fst_aprop(as);
        case 1: return get_scd_aprop(as);
        default: return get_conc_aprop(as);
    }
}

//Retourne la première proposition d'un syllogisme analysis
analysis_proposition* get_p_fst_aprop(analysis_syllogism* as)
{
    return &(as->ap[0]);
}

//Retourne la deuxième proposition d'un syllogisme analysis
analysis_proposition* get_p_scd_aprop(analysis_syllogism* as)
{
    return &(as->ap[1]);
}

//Retourne la conclusion d'un syllogisme analysis
analysis_proposition* get_p_conc_aprop(analysis_syllogism* as)
{
    return &(as->ap[2]);
}

analysis_proposition* get_p_i_aprop(analysis_syllogism* as, MYVAL i)
{
    switch(i)
    {
        case 0: return get_p_fst_aprop(as);
        case 1: return get_p_scd_aprop(as);
        default: return get_p_conc_aprop(as);
    }
}


//Fonction qui détermine et renvoie la figure du syllogisme
MYVAL get_user_figure(user_syllogism us)
{
    MYVAL type;
    
    if(get_user_fst_term(get_fst_uprop(us)) == get_user_scd_term(get_scd_uprop(us)))
    {
        type = 1;
    }
    else if(get_user_scd_term(get_fst_uprop(us)) == get_user_scd_term(get_scd_uprop(us)))
    {
        type = 2;
    }
    else if(get_user_fst_term(get_fst_uprop(us)) == get_user_fst_term(get_scd_uprop(us)))
    {
        type = 3;
    }
    else if(get_user_scd_term(get_fst_uprop(us)) == get_user_fst_term(get_scd_uprop(us)))
    {
        type = 4;
    }

    return type;
}      

//Fonction qui détermine et renvoie la figure du syllogisme
MYVAL get_analysis_figure(analysis_syllogism as)
{
    MYVAL type;

    if(fstTerm(get_fst_aprop(as)) == scdTerm(get_scd_aprop(as)))
    {
        type = 1;
    }
    else if(scdTerm(get_fst_aprop(as)) == scdTerm(get_scd_aprop(as)))
    {
        type = 2;
    }
    else if(fstTerm(get_fst_aprop(as)) == fstTerm(get_scd_aprop(as)))
    {
        type = 3;
    }
    else if(scdTerm(get_fst_aprop(as)) == fstTerm(get_scd_aprop(as)))
    {
        type = 4;
    }

    return type;
}


//Setter
//Setter du premier terme d'une user_proposition
void set_user_fst_term(user_proposition* user_prop, MYPCHAR term)
{
    user_prop->first_term = term;
}

//Setter du second terme d'une user_proposition
void set_user_scd_term(user_proposition* user_prop, MYPCHAR term)
{
    user_prop->second_term = term;
}

//Setter des termes d'une user_proposition
void set_user_prop(user_proposition* user_prop, MYPCHAR fst, MYPCHAR scd)
{
    set_user_fst_term(user_prop, fst);
    set_user_scd_term(user_prop, scd);
}

//Setter du premier terme d'une analysis_proposition
void set_analysis_fst_term(analysis_proposition* analysis_prop, MYCHAR term)
{
    analysis_prop->first_term = term;
}

//Setter du second terme d'une analysis_proposition
void set_analysis_scd_term(analysis_proposition* analysis_prop, MYCHAR term)
{
    analysis_prop->second_term = term;
}

//Setter des termes d'une analysis_proposition
void set_analysis_prop(analysis_proposition* analysis_prop, MYCHAR fst, MYCHAR scd)
{
    set_analysis_fst_term(analysis_prop, fst);
    set_analysis_scd_term(analysis_prop, scd);
}

//Setter du quantificateur d'une analysis_proposition
void set_analysis_prop_quantifier(analysis_proposition* analysis_prop, MYBOOL universal)
{
    analysis_prop->universal = universal;
}

//Setter du qualificateur d'une analysis_proposition
void set_analysis_prop_qualifier(analysis_proposition* analysis_prop, MYBOOL affirmative)
{
    analysis_prop->affirmative = affirmative;
}

//Arthur
//affichage d'un syllogisme d'un user_syllogism
void display_syllogism(user_syllogism us){
    for(MYVAL i = 0; i < 3; i++)
    {
        printf("%s %s %s\n", get_quant_str(get_user_quantifier(get_i_uprop(us, i))), get_user_fst_term(get_i_uprop(us, i)), get_user_scd_term(get_i_uprop(us, i)));
    }
}


//Leïla et Arthur
//Converti un tableau de 3 user_proposition et un tableau de 3 analysis_proposition
void convert_to_analysis(user_syllogism us, analysis_syllogism* as)
{
    MYVAL type = get_user_figure(us);

    if(type == 1 || type == 3)
    {
        set_analysis_prop(get_p_fst_aprop(as), 'M', 'P');
    }
    if(type == 1 || type == 2)
    {
        set_analysis_prop(get_p_scd_aprop(as), 'S', 'M');
    }
    if(type == 2 || type == 4)
    {
        set_analysis_prop(get_p_fst_aprop(as), 'P', 'M');
    }
    if(type == 3 || type == 4)
    {
        set_analysis_prop(get_p_scd_aprop(as), 'M', 'S');
    }
    
    set_analysis_prop(get_p_conc_aprop(as), 'S', 'P');

    for(int i = 0; i < 3; i++)
    {
        set_analysis_prop_quantifier(get_p_i_aprop(as, i), isU_universal(get_i_uprop(us, i)));
        set_analysis_prop_qualifier(get_p_i_aprop(as, i), isU_affirmative(get_i_uprop(us, i)));
    } 

    //TODO : A enlever
    printf("%c, %c, %d, %d\n", get_fst_aprop(*as).first_term, get_fst_aprop(*as).second_term, get_fst_aprop(*as).universal, get_fst_aprop(*as).affirmative);
    printf("%c, %c, %d, %d\n", get_scd_aprop(*as).first_term, get_scd_aprop(*as).second_term, get_scd_aprop(*as).universal, get_scd_aprop(*as).affirmative);
    printf("%c, %c, %d, %d\n", get_conc_aprop(*as).first_term, get_conc_aprop(*as).second_term, get_conc_aprop(*as).universal, get_conc_aprop(*as).affirmative);
}

//Arthur
//Fonction qui permet de libérer les ressources de nos user_proposition
void free_user_syl(user_syllogism us)
{ 
    free(us.up[2].first_term);
    free(us.up[2].second_term);

    MYVAL type = get_user_figure(us);

    if(type == 1)
    {
        free(us.up[0].first_term);
    }
    else if(type == 2)
    {
        free(us.up[0].second_term);
    }
    else if(type == 3)
    {
        free(us.up[0].first_term);
    }
    else if(type == 4)
    {
        free(us.up[0].second_term);
    }
}

// Fonction pour sauvegarder un syllogisme dans un fichier binaire
MYVAL save_syllogism(user_syllogism* us, const MYPCHAR filename) {
    FILE* file = fopen(filename, "ab"); // Mode ajout binaire
    if (!file) {
        printf("Erreur lors de l'ouverture du fichier %s\n", filename);
        return 0;
    }

    MYCHAR name[MAX_STR_LEN];
    printf("Veuillez entrer le nom du syllogisme :\n");
    scanf("%s", name);

    MYVAL len = strlen(name);
    fwrite(&len, sizeof(MYVAL), 1, file);
    fwrite(name, sizeof(MYCHAR), len, file);

    // Pour chaque proposition du syllogisme
    for (MYVAL i = 0; i < 3; i++) {
        // Sauvegarde des termes
        size_t len1 = strlen(get_user_fst_term(get_i_uprop(*us, i))) + 1; 
        size_t len2 = strlen(get_user_scd_term(get_i_uprop(*us, i))) + 1;
        size_t lenq = strlen(get_quant_str(get_user_quantifier(get_i_uprop(*us, i)))) + 1; 
        
        // Écriture des longueurs puis des données
        fwrite(&len1, sizeof(size_t), 1, file);
        fwrite(&len2, sizeof(size_t), 1, file);
        fwrite(&lenq, sizeof(size_t), 1, file);
        
        fwrite(us->up[i].first_term, sizeof(MYCHAR), len1, file);
        fwrite(us->up[i].second_term, sizeof(MYCHAR), len2, file);
        fwrite(us->up[i].quantifier.quantifier_str, sizeof(MYCHAR), lenq, file);
        
        // Sauvegarde des booléens du quantificateur
        fwrite(&us->up[i].quantifier.universal, sizeof(MYBOOL), 1, file);
        fwrite(&us->up[i].quantifier.affirmative, sizeof(MYBOOL), 1, file);
    }

    fclose(file);
    return 1;
}

MYVAL load_syllogism_pos(user_syllogism* us, const MYPCHAR filename, MYVAL position) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Erreur: Impossible d'ouvrir le fichier %s\n", filename);
        return 0;
    }

    // Sauter les syllogismes précédents
    for (MYVAL pos = 1; pos < position; pos++) {
        MYVAL name_len;
        if (fread(&name_len, sizeof(MYVAL), 1, file) != 1) {
            printf("Position invalide\n");
            fclose(file);
            return 0;
        }
        // Sauter le nom
        fseek(file, name_len, SEEK_CUR);

        // Sauter les 3 propositions
        for (MYVAL i = 0; i < 3; i++) {
            size_t len1, len2, lenq;
            if (fread(&len1, sizeof(size_t), 1, file) != 1 ||
                fread(&len2, sizeof(size_t), 1, file) != 1 ||
                fread(&lenq, sizeof(size_t), 1, file) != 1) {
                printf("Position invalide\n");
                fclose(file);
                return 0;
            }
            fseek(file, len1 + len2 + lenq + 2*sizeof(MYBOOL), SEEK_CUR);
        }
    }

    // Sauter le nom du syllogisme à charger
    MYVAL name_len;
    if (fread(&name_len, sizeof(MYVAL), 1, file) != 1) {
        printf("Position invalide\n");
        fclose(file);
        return 0;
    }
    fseek(file, name_len, SEEK_CUR);

    // Pour chaque proposition
    for (MYVAL i = 0; i < 3; i++) {
        size_t len1, len2, lenq;

        // Lecture des longueurs
        if (fread(&len1, sizeof(size_t), 1, file) != 1 ||
            fread(&len2, sizeof(size_t), 1, file) != 1 ||
            fread(&lenq, sizeof(size_t), 1, file) != 1) {
            fclose(file);
            return 0;
        }

        // Allocation mémoire
        us->up[i].first_term = (MYPCHAR)malloc(len1);
        us->up[i].second_term = (MYPCHAR)malloc(len2);
        us->up[i].quantifier.quantifier_str = (MYPCHAR)malloc(lenq);

        if (!us->up[i].first_term || !us->up[i].second_term || !us->up[i].quantifier.quantifier_str) {
            printf("Erreur d'allocation mémoire\n");
            fclose(file);
            return 0;
        }

        // Lecture des données
        if (fread(us->up[i].first_term, sizeof(MYCHAR), len1, file) != len1 ||
            fread(us->up[i].second_term, sizeof(MYCHAR), len2, file) != len2 ||
            fread(us->up[i].quantifier.quantifier_str, sizeof(MYCHAR), lenq, file) != lenq ||
            fread(&us->up[i].quantifier.universal, sizeof(MYBOOL), 1, file) != 1 ||
            fread(&us->up[i].quantifier.affirmative, sizeof(MYBOOL), 1, file) != 1) {
            
            printf("Erreur de lecture du fichier\n");
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    return 1;
}

void list_syllogisms(const MYPCHAR filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Aucun syllogisme sauvegardé\n");
        exit(EXIT_SUCCESS);
    }

    MYVAL count = 1;
    while (!feof(file)) {
        MYVAL name_len;
        
        // Lecture de la longueur du nom
        if (fread(&name_len, sizeof(MYVAL), 1, file) != 1) {
            break;  // Fin du fichier
        }

        // Lecture du nom
        MYCHAR name[MAX_STR_LEN];
        if ((int)fread(name, sizeof(MYCHAR), name_len, file) != name_len) {
            break;
        }
        name[name_len] = '\0';
        
        // Affichage
        printf("%d. %s\n", count++, name);

        // Saut des données du syllogisme
        for (MYVAL i = 0; i < 3; i++) {
            size_t len1, len2, lenq;
            fread(&len1, sizeof(size_t), 1, file);
            fread(&len2, sizeof(size_t), 1, file);
            fread(&lenq, sizeof(size_t), 1, file);
            
            // Saut des données
            fseek(file, len1 + len2 + lenq + 2*sizeof(MYBOOL), SEEK_CUR);
        }
    }

    fclose(file);
}

MYVAL count_syllogisms(const MYPCHAR filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        return 0;
    }

    MYVAL count = 0;
    while (1) {
        MYVAL name_len;
        
        // Lecture de la longueur du nom
        if (fread(&name_len, sizeof(MYVAL), 1, file) != 1) {
            break;
        }

        // Sauter le nom
        fseek(file, name_len, SEEK_CUR);

        // Sauter les données des 3 propositions
        for (MYVAL i = 0; i < 3; i++) {
            size_t len1, len2, lenq;
            if (fread(&len1, sizeof(size_t), 1, file) != 1 ||
                fread(&len2, sizeof(size_t), 1, file) != 1 ||
                fread(&lenq, sizeof(size_t), 1, file) != 1) {
                fclose(file);
                return count;
            }
            fseek(file, len1 + len2 + lenq + 2*sizeof(MYBOOL), SEEK_CUR);
        }
        count++;
    }

    fclose(file);
    return count;
}

