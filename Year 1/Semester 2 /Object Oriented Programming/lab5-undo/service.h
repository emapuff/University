//
// Created by Nicusor on 18.03.2024.
//

#ifndef LAB2_DINAMIC_SERVICE_H
#define LAB2_DINAMIC_SERVICE_H

#include "list.h"

/*
 Adauga medicamentul la lista 'v'
 param v: lista
 param cod: codul medicamentului
 param nume: numele medicamentului
 param concentratie: concentratia medicamentului
 param cantitate: cantitatea medicamentului
 return: 1 - daca s a efectuat adaugarea
         0 - daca datele au fost invalide
 */
int adaugaMedicament(List *v, int cod, char *nume, int concentratie, int cantitate);

/*
 Sterge medicamentul in functie de nume
 param v: lista
 param nume: numele medicamentului pe care il stergem
 return: 1 - daca s a sters din stoc
         0 - daca nu s a sters nimic din stoc
 */
int stergeMedicament(List *v, char *nume);

/*
 Modifica medicamentul in functie de nume
 param v: lista
 param nume: numele medicamentului de modificat
 param cod_nou: codul medicamentului nou
 param concentratie_noua: concentratia medicamentului nou
 param cantitate: cantitea medicamentului nou
 */
int modificaMedicament(List *v, char *nume, int cod_nou, char *nume_nou, int concentratie_noua, int cantitate);


typedef int(*FunctieComparare)(Medicament* m1, Medicament* m2);

int comparareNume(Medicament* m1, Medicament* m2);

int comparareCantitate(Medicament* m1, Medicament* m2);

void sort(List *v, FunctieComparare comparareNume, FunctieComparare comparareCantitate);

/*
 Sorteaza medicamentele in functie de nume si de cantitate
 param v: lista
 return: lista sortata
 */
//List sortMedicamente(List *v);

List *sortMedicamente(List *v);

/*
 * Filtreaza medicamentele cu prima litera din nume egala cu 'l' si cu cantitatea mai mica decat 'cantitate_max'
 * param v: lista
 * param l: litera dupa care se cauta medicamentul
 * param cantitate_max: cantitatea maxima de medicamente
 * return: lista filtrata
 */
List* filtruMedicamente(List *v, char l, int cantitate_max);

void adauga_undo(List_Manager *v, List* ls);

void undo_service(List_Manager *v);
#endif //LAB2_DINAMIC_SERVICE_H
