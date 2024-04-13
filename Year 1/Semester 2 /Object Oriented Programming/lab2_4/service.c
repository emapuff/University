//
// Created by emato on 11.03.2024.
//

#include <search.h>
#include "service.h"
#include "lista.h"


void actualizare_oferta(ListaMea* list,int indice, float new_price)
{
    /*
     * Actualizeaza pretul unui imobil
     * pre: lista de tip lista mea, indice un nr natural pana la lungime, new_price - pretul nou actualizat
     * post: -
     */
    int i;
    for(i=0;i<list->lungime;i++)
        if(i==indice)
        {
            list->lista[i]->pret=new_price;
        }
}



void ordonare_cresc(ListaMea* list) {
    /*
     * Se ordoneaza crescator lista data dupa pret si in caz de egalitate dupa tipul imobilului
     * pre: lista de tip Lista mea
     * post: -
     */
    for(int i = 0; i < list->lungime - 1; i++)
    {
        for(int j = i + 1; j < list->lungime; j++)
        {
            if(list->lista[i]->pret > list->lista[j]->pret)
            {
                Imobil* aux = list->lista[i];
                list->lista[i] = list->lista[j];
                list->lista[j] = aux;
            } else
                if (list->lista[i]->pret == list->lista[j]->pret)
                {
                    if(strcmp(list->lista[i]->tip, list->lista[j]->tip) > 0)
                    {
                        Imobil* aux = list->lista[i];
                        list->lista[i] = list->lista[j];
                        list->lista[j] = aux;
                    }
            }
        }
    }
}


void ordonare_descrescator(ListaMea* list) {
    /*
     * * Se ordoneaza descrescator lista data dupa pret si in caz de egalitate dupa tipul imobilului
     * pre: lista de tip Lista mea
     * post: -
     */
    for(int i = 0; i < list->lungime - 1; i++)
    {
        for(int j = i + 1; j < list->lungime; j++)
        {
            if(list->lista[i]->pret < list->lista[j]->pret)
            {
                Imobil* aux = list->lista[i];
                list->lista[i] = list->lista[j];
                list->lista[j] = aux;
            } else
                if (list->lista[i]->pret == list->lista[j]->pret)
            {
                if(strcmp(list->lista[i]->tip, list->lista[j]->tip) > 0)
                {
                    Imobil* aux = list->lista[i];
                    list->lista[i] = list->lista[j];
                    list->lista[j] = aux;
                }
            }
        }
    }
}

void filtrare_suprafata(ListaMea list, float suprafara, ListaMea *new_list)
{
    /*
     * Functia creeaza o lista noua cu toate imobilele care au o suprafata mai mare decat cea specificata
     * pre: list de tip Lista mea, suprafata de tip float
     * post: new_list de tip Lista mea
     */
    for(int i=0;i<list.lungime;i++)
        if(list.lista[i]->suprafata>suprafara)
            adauga_lista(new_list,list.lista[i]);


}

void filtrare_pret(ListaMea list,float pret_introdus, ListaMea *new_list)
{
    /*
     * Functia creeaza o lista noua cu toate imobilurile cu un pret mai MIC cel introdus
     */
    for(int i=0;i<list.lungime;i++)
        if(list.lista[i]->pret<=pret_introdus)
            adauga_lista(new_list,list.lista[i]);


}
void filtrare_tip(ListaMea list, char tip_cerut[], ListaMea *new_list)
{
    /*
     * Functia creeaza o lista noua cu toate imobilele care au tipul identic cu cel cerut
     * pre:
     */
    for(int i=0;i<list.lungime;i++)
        if(strcmp(list.lista[i]->tip,tip_cerut)==0)
            adauga_lista(new_list,list.lista[i]);

}

/*
int comparare_pret(const Imobil *im1,const Imobil *im2, int cresc_descresc)
{
    if(cresc_descresc==1)
    {
        if(im1->pret>im2->pret)
            return 1;
        return 0;
    }
    else
    {
        if(im1->pret>im2->pret)
            return 0;
        return 1;
    }
}



void sortulmeu(ListaMea * list, FunctieComparare comparare, int cresc_descresc) {
    int i, j;
    for (i = 0; i <list->lungime; i++) {
        for (j = i + 1; j <list->lungime; j++) {
            if (0 < comparare(list->lista[i], list->lista[j], cresc_descresc)) {
                Imobil* aux = list->lista[i];
                list->lista[i] = list->lista[j];
                list->lista[j] = aux;
            }
        }
    }
}
 */