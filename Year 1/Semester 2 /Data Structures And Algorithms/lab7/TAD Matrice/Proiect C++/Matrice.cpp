#include "Matrice.h"

#include <exception>
#include <Iterator.h>
using namespace std;

Matrice::Matrice(int nrLinii, int nrColoane) {
    /*
     * theta(capacitate)
     */
    if (nrLinii <= 0 || nrColoane <= 0) {
        throw std::exception();
    }
    nr_linii = nrLinii;
    nr_coloane = nrColoane;
    capacitate = Max_Size;
    radacina = -1;
    primLiber = 0;
    val = new TMatrice[capacitate];
    Stanga = new TElem[capacitate];
    Dreapta = new TElem[capacitate];
    for (int i = 0; i < capacitate; ++i) {
        Stanga[i] = Dreapta[i] = -1;
        val[i].valoare = NULL_TELEMENT;
    }
}


int Matrice::nrLinii() const {
    /*
     * theta(1)
     */
    return nr_linii;
}


int Matrice::nrColoane() const {
    /*
     * theta(1)
     */
    return nr_coloane;
}

TElem Matrice::element(int i, int j) const {
    /*
     * BC: theta(1)
     * WC: theta(log h)
     * => O(log h)
     */
    if (i < 0 || j < 0 || i >= nr_linii || j >= nr_coloane) {
        throw std::exception();
    }
    int rez = -1;
    if (radacina != -1) {
        cauta(i, j, radacina, rez); //O(logh)
    }
    if(rez == -1)
        return NULL_TELEMENT;
    else
        return val[rez].valoare;
}


TElem Matrice::modifica(int i, int j, TElem e) {
    /*
     * BC: theta(1)
     * WC: O(n) + 0(log h) + O(log h) = O(n)
     * AC: O(log h)
     * => O(log h)
     */
    if (i < 0 || j < 0 || i >= nr_linii || j >= nr_coloane) {
        throw std::exception();
    }
    int rez = -1;
    TElem anterior = NULL_TELEMENT;
    if (radacina != -1) {
        cauta(i, j, radacina, rez); //O(log h)
        if (rez == -1) {
            insert(i, j, e, radacina); //O(log h)
        } else {
            if(e==NULL_TELEMENT){   //trebuie sa sterg
                deleteElement(rez);
                ActualizarePrimLiber();
            }
            else{
                anterior = val[rez].valoare;
                val[rez].valoare = e;
            }
        }
    } else {
            radacina = primLiber;
            val[primLiber].linie = i;
            val[primLiber].coloana = j;
            val[primLiber].valoare = e;
            ActualizarePrimLiber(); //O(1)

    }
    return anterior;
}


void Matrice::insert(int i, int j, TElem e, int& poz) {
    /*
     * BC: theta(1)
     * WC: theta(log h ) h - inaltimea arborelui
     * AC: theta( log h)
     * => O(logh)
     */
    if (poz == -1) {
        poz = primLiber;
        val[primLiber].linie = i;
        val[primLiber].coloana = j;
        val[primLiber].valoare = e;
        ActualizarePrimLiber();
    } else {
        if (i < val[poz].linie || (i == val[poz].linie && j < val[poz].coloana)) {
            insert(i, j, e, Stanga[poz]);
        } else {
            insert(i, j, e, Dreapta[poz]);
        }
    }
}


void Matrice::cauta(int i, int j, int poz, int& rez) const {
    /*
     * BC: theta(1)
     * WC: theta(log h ) h - inaltimea arborelui
     * AC: theta( log h)
     * => O(logh)
     */
    if (poz == -1) {
        return;
    }
    if (val[poz].linie == i && val[poz].coloana == j) {
        rez = poz;
    } else if (i < val[poz].linie || (i == val[poz].linie && j < val[poz].coloana)) {
        cauta(i, j, Stanga[poz], rez);
    } else {
        cauta(i, j, Dreapta[poz], rez);
    }
}


void Matrice::ActualizarePrimLiber() {
    /*
     * BC: theta(1)
     * WC: theta(capacitate)
     * AC: theta(1)
     */
    int i = primLiber + 1;
    while (i < capacitate && val[i].valoare != NULL_TELEMENT) {
        ++i;
    }
    primLiber = (i < capacitate) ? i : -1;
}

IteratorMatrice Matrice::iterator(int linia) const {
    return IteratorMatrice(*this, linia);
}

void Matrice::deleteElement(int poz) {
    /*
     * BC: theta(1)
     * WC: O(log h) // trebuie sa parcurgem tot
     * => AC: O(log h)
     */
    if (Stanga[poz] == -1 && Dreapta[poz] == -1) { //nod frunza
        val[poz].valoare = NULL_TELEMENT;
        poz = -1;
    } else if (Stanga[poz] == -1 || Dreapta[poz] == -1) { //un nod cu un sigur succesor
        int child = (Stanga[poz] != -1) ? Stanga[poz] : Dreapta[poz];
        val[poz] = val[child];
        Stanga[poz] = Stanga[child];
        Dreapta[poz] = Dreapta[child];
        poz = child;
    } else {
        int succParent = poz; //nod cu mai multi succesori
        int succ = Dreapta[poz];
        while (Stanga[succ] != -1) {
            succParent = succ;
            succ = Stanga[succ];
        }

        val[poz] = val[succ];

        if (succParent != poz) {
            Stanga[succParent] = Dreapta[succ];
        } else {
            Dreapta[succParent] = Dreapta[succ];
        }
        poz = succ;
    }
}




