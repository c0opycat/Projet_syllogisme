#include "syllogism.h"


//universal quantifier
T_quantifier uq1 = {"Aucun", true, false};
T_quantifier uq2 = {"Tous les", true, true};
T_quantifier uq3 = {"N'importe quel", true, true};
T_quantifier uq4 = {"Chaque", true, true};
T_quantifier uq5 = {"Nul", true, false};

//existential quantifier
T_quantifier eq1 = {"Certains", false, true};
T_quantifier eq2 = {"Il existe", false, true};
T_quantifier eq3 = {"Il n'y a pas", false, false};
T_quantifier eq4 = {"Quelques", false, true};

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