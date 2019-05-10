//
// Created by dobre on 10-May-19.
//

#ifndef LFA_TEMA_2_EX_4_GRAMREG_H
#define LFA_TEMA_2_EX_4_GRAMREG_H

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <new>

using namespace std;

/* nr_litere = nr de litere din alfabet
     * nr_linii = nr de linii care au stari (ex: S-aA/a)
     * nr_stari = nr de stari
     * stare_min = starea cu litera cea mai mica; (A)
     * stare_in = litera starii initiale
     * lit_alf = cea mai mica litera a alfabetului
     * lambda = caracterul pus pentru lambda
     */


class GramReg {
private:
    int ***matrice; //matrice tridimensionala pentru a reprezenta trecerea dintr-o stare in alta cu o anumita litera
    int nr_litere, nr_linii, nr_stari;
    char stare_in, lit_alf, lambda, stare_min;

public:
    GramReg(const string &fisier); // constructor care primeste ca parametru numele fisierului din care se vor citi datele
    void showMatrice(); //functie de afisare a matricei, pentru testare
    void verificareCuvant(const char cuv[]); //functie care primeste un cuvant ca parametru si il verifica daca apartine Gramaticii Regulate
    ~GramReg() = default;

};


#endif //LFA_TEMA_2_EX_4_GRAMREG_H
