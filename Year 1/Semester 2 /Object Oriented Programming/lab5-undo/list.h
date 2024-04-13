#ifndef LAB2_DINAMIC_LIST_H
#define LAB2_DINAMIC_LIST_H

#include "Medicament.h"

typedef void* TipElement;

typedef void (*destroyf)(TipElement);

typedef struct {
    TipElement* elemente;
    int lungime;
    int capacitate;
}List;

typedef struct{
    List* lista_Medicamente;
    List* lista_undo;
}List_Manager;

/*
 * Creeaza o lista goala
 * return: lista
 */
List* createEmpty();

List_Manager CreeazaListaMare();

void destroyListaMedicament(List *l);
/*
 * Distruge o lista
 */
void destroy(List* v, destroyf distrugere);

/*
 * Adauga in lista v elementul el
 * param v: lista
 * param el: elementul ce se introduce in lista
 */
void add(List *v, TipElement el);

/*
 * Sterge elementul de pe pozitia 'poz' din lista 'v'
 * param v: lista din care se sterge
 * param poz: pozitia elementului ce se sterge (int)
 * return: elementul ce s-a sters
 */
TipElement delete(List *v, int poz);

/*
 * Returneaza elementul de pe pozitia 'poz'
 * param v: lista
 * param poz: pozitia elementului ce se returneaza
 * return: Elementul de pe pozitia 'poz'
 */
Medicament * get(List *v, int poz);

/*
 * Returneaza lungimea listei 'v'
 * param v: lista
 * return: lungimea listei 'v'
 */
int size(List *v);

List* copyList(List* l);
#endif //LAB2_DINAMIC_LIST_H
