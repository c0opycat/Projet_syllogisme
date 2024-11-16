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


T_liste generate_list_quanti_u(T_liste l){

    l = add_quantifier(uq1, l);
    l = add_quantifier(uq2, l);
    l = add_quantifier(uq3, l);
    l = add_quantifier(uq4, l);
    l = add_quantifier(uq5, l);

    return l;
}

T_liste generate_list_quanti_e(T_liste l){

    l = add_quantifier(eq1, l);
    l = add_quantifier(eq2, l);
    l = add_quantifier(eq3, l);
    l = add_quantifier(eq4, l);

    return l;
}