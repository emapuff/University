//
// Created by emato on 16.03.2024.
//
#include "stdlib.h"
#include "string.h"
#include "entitate.h"


Imobil* creaza_imobil(char* tip_dat, int numar, char* strada, char* oras, float suprafata, float pret) {
    Imobil* new_imbil=(Imobil*) malloc(sizeof (Imobil));

    new_imbil->adresa = malloc(sizeof(Address));
    new_imbil->tip=(char*) malloc(40);
    new_imbil->adresa->strada=(char*) malloc(40);
    new_imbil->adresa->oras=(char*) malloc(40);
    new_imbil->pret=pret;
    new_imbil->suprafata=suprafata;
    new_imbil->adresa->numar=numar;
    strcpy(new_imbil->tip,tip_dat);
    strcpy(new_imbil->adresa->strada,strada);
    strcpy(new_imbil->adresa->oras,oras);
    return new_imbil;
}

void destroy_imobil(Imobil *imb) {
    free(imb->adresa->strada);
    free(imb->adresa->oras);
    free(imb->adresa);

    free(imb->tip);

    free(imb);
}