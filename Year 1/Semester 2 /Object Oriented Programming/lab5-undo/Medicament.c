#include "Medicament.h"
#include <string.h>
#include <stdlib.h>

/*
 * Creeaza o entitate de tipul Medicament
 * param cod: codul entitatii (int)
 * param nume: numele entitatii (char)
 * param concentratie: concentratia entitatii (int)
 * param cantitate: cantitatea (int)
 * return: Medicament
 *
 * #pragma warning(disable: 4996) - daca sunt
 * probleme la strcpy_s(am avut probleme cu el in VS)
 */
Medicament* creeazaMedicament(int cod, char *nume, int concentratie, int cantitate){
    Medicament * m= malloc(sizeof (Medicament));

    m->cod = cod;
    int nrC  = (int) strlen(nume)+1;
    m->nume = malloc(nrC * sizeof(char));
    strcpy(m->nume, nume);
    m->concentratie = concentratie;
    m->cantitate = cantitate;

    return m;
}

/*
 Valideaza o entitate de tipul Medicament
 param: m (struct)
 return: 1 - daca entitatea este valida
         0 - daca entitatea nu este valida
 */
int validatorMedicament(Medicament m){
    if(m.cod < 0)
        return 0;
    if(strlen(m.nume) == 0)
        return 0;
    if(m.concentratie < 0)
        return 0;
    if(m.cantitate < 0)
        return 0;
    return 1;
}

/*
 Sterge elementele entitatii de tip Medicament
 param: m (struct)
 */
void distrugeMedicament(Medicament *m){

    free(m->nume);
    free(m);
}

Medicament* copiazaMedicament(Medicament* m) {
    return creeazaMedicament(m->cod, m->nume, m->concentratie, m->cantitate);
}