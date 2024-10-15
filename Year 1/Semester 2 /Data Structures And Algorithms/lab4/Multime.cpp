#include "Multime.h"
#include "IteratorMultime.h"

#include <iostream>

Multime::Multime() {
	/*
	 * Teta(CAPACITATE)
	 */
    PrimLiber=0;
    prim=-1;
    pred=new int[cp];//trebuia initializar
    urm=new int[cp];
    e=new TElem [cp];
    for(int i=0;i<CAPACITATE-1;i++){
        urm[i]=i+1;
    }
    urm[CAPACITATE-1]=-1;
}

int Multime::aloca() {
    /*
     * Complexitate Teta(1)
     * Sterge primul element din spatiu lier
     */
    int i=PrimLiber;
    PrimLiber=urm[PrimLiber];
    return i;
}
void Multime::dealoca(int i) {
    /*
     * Complexitate Teta(1)
     */
    urm[i]=PrimLiber;
    PrimLiber=i;

}
int Multime::creeazNod(TElem elem) {
    /*
     * Complexiate: Theta(1) amortizat
     */
   int i=aloca();
   if(PrimLiber==-1) redimention();
   this->e[i]=elem;
   urm[i]=-1;
   pred[i]=-1;
    return i;
}

bool Multime::adauga(TElem elem) {
	/* teta(1) amortizat de la creeazaNod*/
    if(cauta(elem))
	    return false;
    else{
        int i= creeazNod(elem);
         if (prim != -1) // Verificăm dacă mulțimea nu e goală
            pred[prim] = i; // Actualizăm predecesorul primului element cu noul element
        urm[i] = prim; // Actualizăm următorul noului element cu primul element curent
        pred[i] = -1; // Nu există un predecesor pentru primul element
        prim = i;
        return true;
    }
}

bool Multime::sterge(TElem elem) {
    /*
     * BC: teta(1) - elementul de sters e  primul
     * WC: teta(n) - elementul nu e in lista
     * AC: teta(n) elementul e pe o pozitie aleatorie
     * => Complexitate overall: O(n)
     */
    int curent = prim;
    int anterior = -1;

    while (curent != -1) {
        if (e[curent] == elem) {
            if (anterior != -1) { // Verificăm dacă elementul nu este primul din mulțime
                urm[anterior] = urm[curent]; // Actualizăm următorul elementului anterior
            } else { // Elementul de șters este primul din mulțime
                prim = urm[curent]; // Actualizăm primul element al mulțimii
            }

            if (urm[curent] != -1) { // Verificăm dacă elementul nu este ultimul din mulțime
                pred[urm[curent]] = anterior; // Actualizăm predecesorul elementului următor
            }

            dealoca(curent); // Eliberăm nodul din mulțime
            return true;
        }

        anterior = curent; // Actualizăm elementul anterior pentru următoarea iterație
        curent = urm[curent]; // Trecem la următorul element din mulțime
    }

    return false; // Elementul nu a fost găsit în mulțime
}


bool Multime::cauta(TElem elem) const {
    /*
     * BC: teta(1) - elementul cautat e primul in multime
     * WC: teta(n) - elementul nu se afla in multime
     * AC: teta(n) - elementul e undeva pe la mijloc
     * => complexitate average O(n)
     */
	int crt=prim;
    while(crt != -1){
        if(this->e[crt]==elem){
            return true;
        }
        crt=urm[crt];
    }
	return false;
}


int Multime::dim() const {
    /*
     * complexitate teta(n), unde n e lungimea multimii
     */
    int lungime = 0;
    int curent = prim;

    while (curent != -1) {
        lungime++;
        curent = urm[curent];
    }

    return lungime;
}

bool Multime::vida() const {
    /*
     * teta(1)
     */
    return (prim == -1);
}


Multime::~Multime() {
	/* teta(1) */
    delete[] e;
    delete[] urm;
    delete[] pred;

}



IteratorMultime Multime::iterator() const {
    /*
     * teta(1)
     */
	return IteratorMultime(*this);
}



void Multime::redimention() {
    /*
     * complexitatea Teta(cp) deoarece de fiecare data parcurgem toata lista
     */

    TElem * eNou = new TElem [2 * cp];
    int* urmNou = new int[2 * cp];
    int* predNou=new int[2* cp];
    //se initializeaza lista spatiului liber - toate pozitiile din vecto sunt marcate ca fiind libere
    for (int i = 0; i < cp; i++) {
        urmNou[i] = urm[i];
        predNou[i]=pred[i];
    }
    for (int i = cp; i < 2*cp - 1; i++) {
        urmNou[i] = i + 1;
    }
    urmNou[2 * cp - 1] = -1;
    for (int i = 0; i < cp ; i++)
        eNou[i] = e[i];

    PrimLiber = cp;

    //dublam capacitatea
    cp = 2 * cp;

    //eliberam vechea zona
    delete[] e;
    delete[] urm;
    delete[] pred;
    //vectorul indica spre noua zona
    e = eNou;
    urm = urmNou;
    pred=predNou;
}

int Multime::diferențaMaxMin() const {
    /*
     * Complexitate: O(n)
     * Bc: teta(1) -> cand multimea e vida
     * WC=AC -> minimul si maximul sunt pe pozitii random, dar in fiecare caz parcurgem intreaga multime
     * deci avem teta(n), n=nr de elemente din multime
     */
    if(this->vida())
        return -1;
    int minVal = e[prim];
    int maxVal = e[prim];
    int curent = urm[prim];

    while (curent != -1) {
        if (e[curent] < minVal) {
            minVal = e[curent];
        } else if (e[curent] > maxVal) {
            maxVal = e[curent];
        }
        curent = urm[curent];
    }


    int difference = maxVal - minVal;
    return difference;
}


