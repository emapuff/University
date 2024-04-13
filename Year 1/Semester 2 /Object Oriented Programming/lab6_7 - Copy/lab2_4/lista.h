//
// Created by emato on 15.03.2024.
//

#ifndef LAB2_4_LISTA_H
#define LAB2_4_LISTA_H
#include "entitate.h"


typedef struct {
    Imobil **lista;
    int lungime;
    int capacitate;
}ListaMea;

ListaMea creaza_vid();

void resize_vector(ListaMea* list, ListaMea *new_list);

void adauga_lista(ListaMea* list,Imobil* imb);
/*
     * Adauga un imobil nou in lista
     * pre: Lista de tip lista mea, imobil
     * post: -
     */

void destroy(ListaMea* list);


void stergere_oferta(ListaMea* list, int indice);
/*
     * Sterge un element de pe indice dat
     * pre: lista de tip lista mea, indice de tip natural, cuprins intre 1 si lungimea listei
     * post: -
     */

#endif //LAB2_4_LISTA_H
