#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "liste.h"
#include "syllogism.h"

T_liste add_quantifier(const char * quantifier, T_liste ql )
{
    ajoutEnTete(ql, quantifier);
    return ql;
}

void display_quantifier(const T_liste ql)
{
    afficheListe(ql);
}

void test(){
    printf("Test");
}

int main(int argc, char const *argv[])
{
    T_liste quant_list;
    initListe(&quant_list);

    add_quantifier("Aucun", quant_list);
    add_quantifier("Tous", quant_list);

    display_quantifier(quant_list);

    return 0;
}
