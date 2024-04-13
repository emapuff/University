//
// Created by emato on 11.03.2024.
//
#pragma once
#ifndef LAB2_4_SERVICE_H
#define LAB2_4_SERVICE_H
#include <stdio.h>
#include <string.h>
#include "lista.h"
typedef int(*Functiecomparare)(const void*, const void*);

int comparare_tip(const void* a, const void* b);
int comparare_pret(const void* a, const void* b);


void sortul_meu(ListaMea * list, int criteriu, Functiecomparare comparare);

void actualizare_oferta(ListaMea* list,int indice, float new_price);
/*
     * Actualizeaza pretul unui imobil
     * pre: lista de tip lista mea, indice un nr natural pana la lungime, new_price - pretul nou actualizat
     * post: -
     */


void ordonare_cresc(ListaMea* list);
/*
     * Se ordoneaza crescator lista data dupa pret si in caz de egalitate dupa tipul imobilului
     * pre: lista de tip Lista mea
     * post: -
     */
void ordonare_descrescator(ListaMea* list);
/*
    * * Se ordoneaza descrescator lista data dupa pret si in caz de egalitate dupa tipul imobilului
    * pre: lista de tip Lista mea
    * post: -
    */

void filtrare_suprafata(ListaMea list, float suprafara, ListaMea *new_list);

void filtrare_tip(ListaMea list, char tip_cerut[], ListaMea *new_list);

void filtrare_pret(ListaMea list,float pret_introdus, ListaMea *new_list);



typedef int(*FunctieComparare)(Imobil *im1, Imobil *im2, int cresc_descresc);

//int comparare_pret(const Imobil *im1,const Imobil *im2, int cresc_descresc);

void sortulmeu(ListaMea * list, FunctieComparare cmpF, int cresc_descresc);
#endif //LAB2_4_SERVICE_H

