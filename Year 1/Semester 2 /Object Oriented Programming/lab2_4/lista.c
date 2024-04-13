//
// Created by emato on 15.03.2024.
//
#include "stdlib.h"
#include "lista.h"
#include "entitate.h"

ListaMea creaza_vid() {
    ListaMea list;
    list.capacitate = 2;
    list.lista = malloc(sizeof(Imobil) * list.capacitate);
    list.lungime = 0;
    return list;
}

void resize_vector(ListaMea* list, ListaMea* new_list)
{
    /*
     * Functia mareste dimensiunile vectorului dinamic daca spatiul alocat se ocupa
     * pre: lista de tip lista mea
    */
    list->capacitate*=2;
    Imobil ** noi = malloc(sizeof(Imobil*) * list->capacitate);

    for(int i=0;i<list->lungime;i++)
        noi[i]=list->lista[i];

    free(list->lista);
    list->lista = noi;


}


void destroy(ListaMea* list)
{
    /*
     * Functia distruge vectorul dinamic si ii curata memoria
     */
    int i;
    for(i=0;i<list->lungime;i++)
    {
        destroy_imobil(list->lista[i]);
    }
    free(list->lista);
    list->lungime=0;
    //free(list);
}


void adauga_lista(ListaMea* list, Imobil* imb) {
    /*
     * Adauga un imobil nou in lista
     * pre: Lista de tip lista mea, imobil
     * post: -
     */
    if (list->lungime < list->capacitate) {
        list->lista[list->lungime] = imb;
        list->lungime = list->lungime + 1;

    }
    else
    {
        ListaMea newList = creaza_vid();
        resize_vector(list, &newList);
    }
}

void stergere_oferta(ListaMea* list, int indice)
{
    /*
     * Sterge un element de pe indice dat
     * pre: lista de tip lista mea, indice de tip natural, cuprins intre 0 si lungimea listei-1
     * post: -
     */
    destroy_imobil(list->lista[indice]);

    for(int i=indice; i<list->lungime;i++)
    {
        list->lista[i]=list->lista[i+1];
    }
    list->lungime--;

}
