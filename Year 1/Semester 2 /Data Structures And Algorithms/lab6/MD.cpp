#include "MD.h"
#include "IteratorMD.h"
#include <cstdlib> // For abs function
#include <iostream>


void MD::ActualizarePrimLiber() {
    /*
     * BC: theta(1)
     * WC: O(m), parcurgem toata tabela
     * AC: tehta(1) - dispersie uniforma
     */
    primLiber++;
    while (primLiber < m && e[primLiber].first != INIT)
        primLiber++;
}

int MD::dispersue(TCheie c) const {
    /*
     * theta(1)
     */
    return abs(c) % m;
}

MD::MD() {
    /*
     * theta(m)
     */
    m = MAX;
    n = 0;
    e = new TElem[m];
    urm = new int[m];
    primLiber = 0;
    for (int i = 0; i < m; i++) {
        e[i] = TElem(INIT, INIT);
        urm[i] = -1;
    }
}

MD::~MD() {
    /*
     * theta(1)
     */
    delete[] e;
    delete[] urm;
}

void MD::adauga(TCheie c, TValoare v) {
    /*
     * BC: theta(1)
     * WC: O(m) - cand avem o coliziune
     * Ac: theta(1) pentru o dispersie buna
     */
    int i = dispersue(c), j=-1;
    n++; //eventual rehash and resize
    if (e[i].first == INIT) {
        e[i].first = c;
        e[i].second = v;
        if (i == primLiber) {
            ActualizarePrimLiber();
        }
    }
    else {
       while(i!=-1){
           j=i;
           i=urm[i];
       }
       e[primLiber].first=c;
       e[primLiber].second=v;
       urm[j]=primLiber;
       ActualizarePrimLiber();
    }
}


bool MD::sterge(TCheie c, TValoare v) {
    /*
     * wc: o(N)
     * bc: theta(1)
     * ac:theta(1)
     */
    int i= dispersue(c);
    int p, pp, j=-1;
    bool gata;
    for (int k = 0; k < m && j == -1; k++)
        if (urm[k] == i)
            j = k;
    while (i != -1 && !(e[i].first == c && e[i].second == v)) {
        j = i;
        i = urm[i];
    }
    if (i == -1)
        return false;
    else {
        gata = false;
        do {
            p = urm[i];
            pp = i;
            while (p != -1 && dispersue(e[p].first) != i)
            {
                pp = p;
                p = urm[p];
            }
            if (p == -1)
                gata = true;
            else {
                e[i] = e[p];
                i = p;
                j = pp;
            }
        } while (!gata);
        if (j != -1) {
            urm[j] = urm[i];
        }
        e[i].first = INIT;
        e[i].second = INIT;
        urm[i] = -1;
        if (primLiber > i)
            primLiber = i;
        n--;
        return true;
    }
}

vector<TValoare> MD::cauta(TCheie c) const {
    /*
     * bc:theta(1)
     * wc:o(m)
     * ac: o(m)
     */
    int poz = dispersue(c);
    vector<TValoare> v;
    while (poz != -1) {
        if (e[poz].first == c) {
            v.push_back(e[poz].second);
        }
        poz = urm[poz];
    }
    return v;
}

int MD::dim() const {
    /*
     * theta(1)
     */
    return n;
}

bool MD::vid() const {
    /*
     * theta(1)
     */
    return n == 0;
}

IteratorMD MD::iterator() const {
    /*theta(1)*/
    return IteratorMD(*this);
}

void MD::goleste() {
    if(dim()!=0)
    {
        IteratorMD im= this->iterator();
        im.prim();
        while(im.valid()){
            bool ok=sterge(im.element().first,im.element().second);
            if (!ok) {
                throw std::runtime_error("eroare la stergere!");
            }
            im.urmator();
        }

    }
}
