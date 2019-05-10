#include <iostream>
#include "GramReg.h"

using namespace std;

int main() {

    GramReg G("intrare.txt");
    //G.showMatrice();
    G.verificareCuvant("");
    G.verificareCuvant("aaa");
    G.verificareCuvant("ab");


    return 0;
}