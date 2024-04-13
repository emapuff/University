#include <string.h>
#include "service.h"

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

int adaugaMedicament(List *v, int cod, char *nume, int concentratie, int cantitate){
    Medicament *m = creeazaMedicament(cod, nume, concentratie, cantitate); //aici avem un malloc
    if(validatorMedicament(*m) == 0) {
        distrugeMedicament(m);
        return 0;
    }
    for(int i = 0; i < size(v); i++) {
        if(strcmp(get(v, i)->nume, m->nume) == 0) {
            modificaMedicament(v, nume, cod, nume, concentratie, cantitate);
            distrugeMedicament(m);
            return 1;
        }
    }
    add(v, m);
    return 1;
}

/*
 Sterge medicamentul in functie de nume
 param v: lista
 param nume: numele medicamentului pe care il stergem
 return: 1 - daca s a sters din stoc
         0 - daca nu s a sters nimic din stoc
 */

int stergeMedicament(List *v, char *nume){
    int poz;
    for(int i = 0; i < size(v); i++){
        if(strcmp(get(v, i)->nume, nume) == 0){
            poz = i;
            Medicament *m = delete(v, poz);
            distrugeMedicament(m);
            return 1;
        }
    }
    return 0;
}

/*
 Modifica medicamentul in functie de nume
 param v: lista
 param nume: numele medicamentului de modificat
 param cod_nou: codul medicamentului nou
 param concentratie_noua: concentratia medicamentului nou
 */

int modificaMedicament(List *v, char *nume, int cod_nou, char *nume_nou, int concentratie_noua, int cantitate){
    Medicament *m = creeazaMedicament(cod_nou, nume_nou, concentratie_noua, cantitate);
    if(validatorMedicament(*m) == 0) {
        distrugeMedicament(m);
        return 0;
    }
    int sters = stergeMedicament(v, nume);
    if(sters == 0){
        distrugeMedicament(m);
        return 0;
    } else {
        adaugaMedicament(v, cod_nou, nume_nou, concentratie_noua, cantitate);
        distrugeMedicament(m);
    }
    return 1;
}

int comparareNume(Medicament* m1, Medicament* m2){
    return strcmp(m1->nume, m2->nume);
}

int comparareCantitate(Medicament* m1, Medicament* m2){
    return m1->cantitate > m2->cantitate;
}

/*
 Sorteaza medicamentele in functie de nume si de cantitate
 param v: lista
 return: lista sortata
 */
void sort(List *v, FunctieComparare comparareNume, FunctieComparare comparareCantitate){
    List listaSortata = *v;
    Medicament *temp;
    for(int i = 0; i < size(&listaSortata)-1; i++) {
        for(int j = i+1; j < size(&listaSortata); j++) {
            if(comparareNume(listaSortata.elemente[i], listaSortata.elemente[j])>0) {
                temp = listaSortata.elemente[i];
                listaSortata.elemente[i] = listaSortata.elemente[j];
                listaSortata.elemente[j] = temp;
            }
//            else if(comparareNume(listaSortata.elemente[i], listaSortata.elemente[j])==0) {
//                if(comparareCantitate(listaSortata.elemente[i], listaSortata.elemente[j])) {
//                    temp = listaSortata.elemente[i];
//                    listaSortata.elemente[i] = listaSortata.elemente[j];
//                    listaSortata.elemente[j] = temp;
//                }
//            }
        }
    }
}

List* sortMedicamente(List *v){
    List* listaSortata = v;
    sort(listaSortata, comparareNume, comparareCantitate);
    return listaSortata;
}

/*
 * Filtreaza medicamentele cu prima litera din nume egala cu 'l' si cu cantitatea mai mica decat 'cantitate_max'
 * param v: lista
 * param l: litera dupa care se cauta medicamentul
 * param cantitate_max: cantitatea maxima de medicamente
 * return: lista filtrata
 */
List* filtruMedicamente(List *v, char l, int cantitate_max) {
    List *listaFiltrata = createEmpty();
    for (int i = 0; i < size(v); i++) {
        Medicament *m = get(v, i);
        if (m->nume[0] == l && m->cantitate < cantitate_max) {
            add(listaFiltrata, creeazaMedicament(m->cod, m->nume, m->concentratie, m->cantitate));
        }
    }
    return listaFiltrata;
}
/*
 * Adauga undo
 * param v: Structura de lista cu cele doua
 * param ls: lista adaugata
 */
void adauga_undo(List_Manager *v, List* ls)
{
    add(v->lista_undo, copyList(ls));
}

/*
 * Realizeaza partea de undo
 * param v: structura de lista cu cele doua
 */
void undo_service(List_Manager *v)
{
    List *element= delete(v->lista_undo,v->lista_undo->lungime-1);
    destroy(v->lista_Medicamente, (destroyf) distrugeMedicament);
    v->lista_Medicamente=element;

}