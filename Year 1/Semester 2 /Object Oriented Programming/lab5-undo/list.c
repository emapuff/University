#pragma once
#include <stdlib.h>

#include "list.h"
/*
 * Creeaza o lista goala
 * return: lista
 */
List* createEmpty() {
    List* v= malloc(sizeof (List));
    v->capacitate = 2;
    v->lungime = 0;
    v->elemente = malloc(sizeof(TipElement) * v->capacitate);
    return v;
}

/*
 * creeaza manager ul de liste
 * return: structura de lista
 */
List_Manager CreeazaListaMare()
{
    List_Manager v;
    v.lista_Medicamente=createEmpty();
    v.lista_undo=createEmpty();
    return v;
}

/*
 * distrugerea unei liste cu elemente de tip medicament
 * param l: lista care trebuie eliberata
 */
void destroyListaMedicament(List *l)
{
    destroy(l, (destroyf) distrugeMedicament);
}

/*
 * Distruge o lista
 */
void destroy(List* v, destroyf distrugere) {
    for(int i = 0; i < v->lungime; i++){
        TipElement element = v->elemente[i];
        distrugere(element);
    }
    free(v->elemente);
    free(v);
}

/*
 * Adauga in lista v elementul el
 * param v: lista
 * param el: elementul ce se introduce in lista
 */
void add(List *v, TipElement el) {
    if(v->lungime == v->capacitate){
        int Capacitate_noua = v->capacitate * 2;
        TipElement* elementeNoi = malloc(sizeof(TipElement) * Capacitate_noua);
        for(int i = 0; i<v->lungime; i++) {
            elementeNoi[i] = v->elemente[i];
        }
        free(v->elemente);
        v->elemente = elementeNoi;
        v->capacitate = Capacitate_noua;
    }
    v->elemente[v->lungime] = el;
    v->lungime++;

}

/*
 * Sterge elementul de pe pozitia 'poz' din lista 'v'
 * param v: lista din care se sterge
 * param poz: pozitia elementului ce se sterge (int)
 * return: elementul ce s-a sters
 */
TipElement delete(List *v, int poz) {
    TipElement el = v->elemente[poz];
    for(int i = poz; i<v->lungime-1; i++) {
        v->elemente[i] = v->elemente[i+1];
    }
    v->lungime--;
    return el;
}

/*
 * Returneaza elementul de pe pozitia 'poz'
 * param v: lista
 * param poz: pozitia elementului ce se returneaza
 * return: Elementul de pe pozitia 'poz'
 */
Medicament* get(List *v, int poz) {
    return v->elemente[poz];
}

/*
 * Returneaza lungimea listei 'v'
 * param v: lista
 * return: lungimea listei 'v'
 */
int size(List *v) {
    return v->lungime;
}

List* copyList(List* l) {
    List* copie_l = createEmpty();
    for (int i = 0; i < l->lungime; i++)
        add(copie_l, copiazaMedicament(l->elemente[i]));

    return copie_l;
}