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
char* choose_quantifier(T_liste ql)
{
    // int ql_len =;
    // T_liste tmp = ql;
    // for(int i = 0; i < pos; i++)
    // {
    //     tmp = getptrNextCell(tmp);
    // }
    return NULL;
}

void input_simple_syllogism(T_liste uql, T_liste eql)
{
    bool uqList = choose_universal_quantifiers();

    T_liste qList;

    if(uqList)
    {
        qList = uql;
    }
    else
    {
        qList = eql;
    }
}

int main()
{
    T_liste quant_list;
    initListe(&quant_list);

    T_quantifier test1 = {"Aucun", false};
    T_quantifier test2 = {"Tous", true};

    quant_list = add_quantifier(test1, quant_list);
    quant_list = add_quantifier(test2, quant_list);

    display_quantifier(quant_list);

    return 0;
}
