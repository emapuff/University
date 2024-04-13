//
// Created by emato on 16.03.2024.
//

#ifndef LAB2_4_ENTITATE_H
#define LAB2_4_ENTITATE_H
typedef struct {
    int numar;
    char *strada, *oras;
}Address;

typedef struct{
    char *tip;
    Address *adresa;
    float suprafata,pret;
}Imobil;

Imobil* creaza_imobil(char* tip_dat, int numar, char* strada, char* oras, float suprafata, float pret);
/*
     * Functia creaza un obiect de tip imobil
     * pre: tip dat char, nr strada int, strada char, oras char, suprafata si pret float
     * post: obiect de tip imobil
     */

void destroy_imobil(Imobil *imb);

#endif //LAB2_4_ENTITATE_H
