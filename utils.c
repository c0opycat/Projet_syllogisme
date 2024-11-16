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

