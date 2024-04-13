//
// Created by emato on 17.03.2024.
//

#include "validator.h"
#include "entitate.h"
#include "string.h"

int validare_optiune(char c)
{
    if(strchr("1234567",c)==NULL)
        return 0;
    return 1;
}

void validare_imobil_nou(Imobil *imb, int errors[10])
{
    //tipul poate fi doar teren, casa, apartament
    if (strcmp("teren", imb->tip) != 0 && strcmp("casa", imb->tip) != 0 && strcmp("apartament", imb->tip) != 0) {
        errors[0] = 1;
    }
    if(imb->adresa->numar<0) errors[1]=1;
    if(imb->suprafata<0) errors[2]=1;
    if(imb->pret<0) errors[3]=1;

}

