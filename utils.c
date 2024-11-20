#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

//Fonction de récupération de la chaîne de caractère saisie par l'utilisateur
//Retourne la chaîne de caractère lue
char* read_str()
{
    char term_tmp[MAX_STR_LEN];
    
    myfgets(term_tmp);
    int len = strlen(term_tmp);
    
    char * term = (char*)malloc((len + 1) * sizeof(char));
    strcpy(term, term_tmp);

    return term;
}

//Fonction de récupération du caractère saisi par l'utilisateur
//Retourne le caractère lu
char read_char()
{
    char res;

    scanf("%c", &res);
    clear_input_buffer();

    return res;
}

//Fonction de récupération de l'entier saisi par l'utilisateur
//Retourne l'entier lu
int read_int()
{
    int res;

    scanf("%d", &res);
    clear_input_buffer();

    return res;
}
