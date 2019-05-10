//
// Created by dobre on 10-May-19.
//

#include "GramReg.h"


GramReg::GramReg(const string &fisier) {

    ifstream fin(fisier);
    fin >> nr_litere >> nr_linii >> nr_stari;
    fin >> stare_min >> stare_in >> lit_alf >> lambda;

    /*  matricea aloca dinamic linii in functie de numarul de stare, coloane = nr de linii + o coloana unde se afla starea finala
     * si fiecarui element matrice[linie][coloana] un vector care are nr_litere + 1(lambda) elemente
     *  se initializeaza fiecare element al matricei cu 0
     */

    matrice = new int **[nr_stari];
    for (int i = 0; i < nr_stari; i++) {
        matrice[i] = new int *[nr_stari + 1];
        for (int j = 0; j < nr_stari + 1; j++) {
            matrice[i][j] = new int[nr_litere + 1];
        }
    }

    for (int i = 0; i < nr_stari; i++) {
        for (int j = 0; j < nr_stari + 1; j++) {

            for (int k = 0; k < nr_litere + 1; k++) {
                matrice[i][j][k] = 0;

            }
        }
    }

    /*  sir_temp = sir in care se citeste ficare linie cu stari
     *  sir_dummy = un sir care este citit inainte de liniile cu stari pentru ca nu era citita inainte o linie cu stari
     */
    char sir_temp[50], sir_dummy[10];

    fin.getline(sir_dummy, 10); // se citeste din fisier dummy_sir
    for (int i = 0; i < nr_linii; i++) {

        //sunt citite pe rand liniiile cu stari

        fin.getline(sir_temp, 50);
        int size_sir = strlen(sir_temp);
        int x;
        if (sir_temp[0] == stare_in) { //daca prima litera de pe linie este starea initiala atunci coordonata pentru linie ia valoarea 0
            x = 0;
        } else {
            x = sir_temp[0] - stare_min + 1; //altfel se face scaderea intre litera starii, cea mai mica litera de stare si se adauga 1 (ex: 'A' - 'A' + 1 = 1, pentru ca S = 0)
        }

        for (int j = 2; j < size_sir; j++) {

            /*  se pleaca de la 2 deoarece primul caracter al sirului este deja verificat mai sus
             * iar al doilea caracter este '-' mereu
             *  se verifica daca caracterul de pe linie este litera mica din alfabet, si daca da,
             * atunci se verifica daca caracterul urmator este o stare si daca da, coordonata respectiva
             * din matrice ia valoarea 1
             */

            int y, z; //y = coordonata coloanei, z = coordonata literei daca starea de pe linie se duce in starea de pe coloana cu litera respectiva

            if ((sir_temp[j] >= lit_alf) && (sir_temp[i] <= (lit_alf + nr_litere - 1))) {
                z = sir_temp[j] - lit_alf + 1; // z ia valoarea diferentei dintre litera mica a sirului si cea mai mica litera a alfabetului + 1 (ex: 'a' - 'a' + 1 = 1)
                if (sir_temp[j + 1] == stare_in) { //daca litera mare de pe sir este starea initiala atunci coordonata ia valoarea
                    y = 0;
                } else if ((sir_temp[j + 1] >= stare_min) && (sir_temp[j + 1] <= stare_min + nr_stari - 2)) {//altfel se face diferenta intre litere
                    y = sir_temp[j + 1] - stare_min + 1;
                } else {
                    y = nr_stari;//altfel daca litera mica nu este urmata de o stare, inseamna ca se poate iesi din cuvant cu ea si se pune ca stare finala
                }

            } else if (sir_temp[j] == lambda) { //daca cumva caracterul verificat este lambda, atunci automat este pus in starea finala
                y = nr_stari;
                z = 0;
            }
            matrice[x][y][z] = 1;
        }

        strcpy(sir_temp, "");//se reintializeaza sirul pentru citirea liniilor
    }

    fin.close();
}

void GramReg::showMatrice() {
    cout << endl;
    for (int i = 0; i < nr_stari; i++) {
        for (int j = 0; j < nr_stari + 1; j++) {
            cout << "[";
            for (int k = 0; k < nr_litere + 1; k++) {
                if (k == nr_litere) {
                    cout << matrice[i][j][k];
                } else {
                    cout << matrice[i][j][k] << ",";
                }
            }
            cout << "] ";
        }
        cout << endl;
    }
}

void GramReg::verificareCuvant(const char cuv[]) {

    int x = 0; //se incepe de la starea initiala
    int lungime = strlen(cuv);
    bool cuvAdevarat = false; //pornim de la premisa ca cuvantul este fals pentru a incerca sa demonstram ca este adevarat

    if ((lungime == 0) && (matrice[x][nr_stari][0] == 1)) {
        cuvAdevarat = true; //daca cuvantul este vid si din starea initiala se poate iesi cu lambda atunci cuvantul apartine limbajului
    }
    for (int i = 0; i < lungime; i++) {
        int temp = cuv[i] - lit_alf + 1; //temp = diferenta dintre litera cuvantului si cea mai mica litera din alfabet, la care se adauga 1
        if (i == lungime - 1) {
            if (matrice[x][nr_stari][temp] == 1) {//daca se ajunge la ultima litera si se poate iesi cu ea atunci cuvantul este adevarat
                cuvAdevarat = true;
                break;
            } else { //alfel continua sa schimbe starea si daca din starea in care se schimba se poate iesi cu lambda atunci cuvantul este adevarat
                for (int j = 0; j < nr_stari; j++) {
                    if (matrice[x][j][temp] == 1) {
                        if (matrice[j][nr_stari][0] == 1) {
                            cuvAdevarat = true;
                            break;
                        }
                    }
                }
            }
        } else { //daca nu este ultima litera atunci se parcuge pe linie fiecare coloana si se cauta o stare in care se poate schimba linia cu litera respectiva
            for (int k = 0; k < nr_stari; k++) {
                if ((k == nr_stari - 1) && (matrice[x][k][temp] != 1)) {
                    break;
                }
                if (matrice[x][k][temp] == 1) {
                    x = k;
                }
            }
        }

    }


    if (cuvAdevarat) {
        if (!strcmp(cuv, "")) {
            cout << "Cuvantul vid apartine alfabetului.";
        } else { cout << "Cuvantul " << '\"' << cuv << '\"' << " apartine alfabetului."; }
        cout << endl;
    } else {
        if (!strcmp(cuv, "")) {
            cout << "Cuvantul vid nu apartine alfabetului.";
        } else { cout << "Cuvantul " << '\"' << cuv << '\"' << " nu apartine alfabetului."; }

        cout << endl;

    }
}
