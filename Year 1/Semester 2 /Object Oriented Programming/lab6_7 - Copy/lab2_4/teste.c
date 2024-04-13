//
// Created by emato on 11.03.2024.
//

#include "teste.h"
#include "service.h"
#include <assert.h>

void test_stergere_oferta()
{
    ListaMea listatest=creaza_vid();
    Imobil *new_imobil= creaza_imobil("teren",13,"Primaverii","Cluj-Napoca",2000,3455.5);
    adauga_lista(&listatest,new_imobil);
    stergere_oferta(&listatest,0);
    assert(listatest.lungime==0);
    new_imobil= creaza_imobil("teren",13,"Primaverii","Cluj-Napoca",2000,3455.5);
    adauga_lista(&listatest,new_imobil);
    stergere_oferta(&listatest,0);
    assert(listatest.lungime==0);
    destroy(&listatest);
}

void test_actualizare_oferta()
{
    ListaMea listatest=creaza_vid();
    Imobil *new_imobil= creaza_imobil("teren",13,"Primaverii","Cluj-Napoca",2000,3455.5);
    adauga_lista(&listatest,new_imobil);
    float a=800.8;
    actualizare_oferta(&listatest,0,a);
    assert(listatest.lista[0]->pret==a);
    destroy(&listatest);
}

void test_adauga_lista()
{
    ListaMea listatest=creaza_vid();
    assert(listatest.lungime==0);
    Imobil *new_imobil = creaza_imobil("teren",13,"Primaverii","Cluj-Napoca",2000,3455.5);
    adauga_lista(&listatest,new_imobil);
    assert(listatest.lungime==1);
    destroy(&listatest);
}

void test_ordoanre_crescator()
{
    ListaMea listatest=creaza_vid();
    assert(listatest.lungime==0);
    Imobil *new_imobil1= creaza_imobil("teren",13,"Primaverii","Cluj-Napoca",2000,3455.5);
    adauga_lista(&listatest,new_imobil1);
    //destroy_imobil(&new_imobil1);
    Imobil *new_imobil2=creaza_imobil("teren",12,"brancusi","Cluj-Napoca",2000,400);
    adauga_lista(&listatest,new_imobil2);
    //destroy_imobil(&new_imobil2);
    Imobil *new_imobil3= creaza_imobil("casa",13,"Primaverii","Cluj-Napoca",2000,3455.5);
    adauga_lista(&listatest,new_imobil3);
    ordonare_cresc(&listatest);
    assert(listatest.lista[0]->pret==400);
    destroy(&listatest);
}

void test_ordonare_descrescator()
{
    ListaMea listatest=creaza_vid();
    assert(listatest.lungime==0);
    Imobil *new_imobil= creaza_imobil("teren",13,"Primaverii","Cluj-Napoca",2000,3455.5);
    adauga_lista(&listatest,new_imobil);
    Imobil *new_imobil1=creaza_imobil("teren",12,"brancusi","Cluj-Napoca",2000,400);
    adauga_lista(&listatest,new_imobil1);
    Imobil *new_imobil2= creaza_imobil("casa",13,"Primaverii","Cluj-Napoca",2000,3455.5);
    adauga_lista(&listatest,new_imobil2);
    ordonare_descrescator(&listatest);
    assert(strcmp(listatest.lista[0]->tip,"teren")==0);
    destroy(&listatest);
}

void test_filtrare_suprafata()
{

}

void run_all_test()
{
    test_adauga_lista();
    test_actualizare_oferta();
    test_stergere_oferta();
    test_ordoanre_crescator();
    test_ordonare_descrescator();
}

/*
List resize(List list){

    List newList;
    newList.capacity=2*list.capacity;
    newList.length=list.length;
    newList.materii = malloc(newList.capacity * sizeof(Materie));
    for(int i=0;i<list.length;i++) {
        newList.materii[i] = list.materii[i];
    }
    free(list.materii);

    return newList;

}*/