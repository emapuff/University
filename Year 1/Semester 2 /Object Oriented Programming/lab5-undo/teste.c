#include "teste.h"

#include "service.h"

#include <assert.h>
#include <string.h>

// teste DOMAIN
void test_creeazaMedicament() {
    Medicament *m = creeazaMedicament(120, "Paracetamol", 70, 100);
    assert(strcmp(m->nume, "Paracetamol")==0);
    assert(m->cantitate==100);
    distrugeMedicament(m);
}

void test_valideazaMedicament() {
    Medicament *ex1 = creeazaMedicament(120, "Paracetamol", 70, 100);
    assert(validatorMedicament(*ex1) == 1);
    distrugeMedicament(ex1);
    Medicament *ex2 = creeazaMedicament(-130, "Aspirina", 60, -300);
    assert(validatorMedicament(*ex2) == 0);
    distrugeMedicament(ex2);
    Medicament *ex3 = creeazaMedicament(-131, "Calmotusin", 30, 100);
    assert(validatorMedicament(*ex3) == 0);
    distrugeMedicament(ex3);
    Medicament *ex4 = creeazaMedicament(131, "milka", -100, 1);
    assert(validatorMedicament(*ex4) == 0);
    distrugeMedicament(ex4);
    Medicament *ex5 = creeazaMedicament(131, "", -100, 1);
    assert(validatorMedicament(*ex5)==0);
    distrugeMedicament(ex5);
    Medicament *ex6 = creeazaMedicament(131, "milka", 100, -100);
    assert(validatorMedicament(*ex6)==0);
    distrugeMedicament(ex6);
}

// teste REPOSITORY
void test_createEmpty() {
    List* v = createEmpty();
    assert(v->lungime == 0);
    destroy(v, (destroyf) distrugeMedicament);
}

void test_add() {
    List *lista = createEmpty();
    Medicament *m = creeazaMedicament(120, "Paracetamol", 70, 100);
    assert(lista->lungime == 0);
    add(lista, m);
    assert(lista->lungime == 1);
    destroy(lista, (destroyf) distrugeMedicament);
}

void test_delete()
{
    List *lista=createEmpty();
    assert(lista->lungime==0);
    add(lista, creeazaMedicament(101, "prod", 90,90));
    add(lista, creeazaMedicament(102, "prod", 12,1234));
    add(lista, creeazaMedicament(102, "prod", 12,1234));
    TipElement elemet= delete(lista,1);
    distrugeMedicament(elemet);
    assert(lista->lungime==2);
    destroy(lista, (destroyf) distrugeMedicament);
}
void test_get() {
    List *lista = createEmpty();
    assert(lista->lungime == 0);
    add(lista, creeazaMedicament(101, "prod", 90,90));
    add(lista, creeazaMedicament(102, "prod", 12,1234));
    assert(lista->lungime == 2);
    assert(strcmp(get(lista, 0)->nume, "prod")==0);
    assert(get(lista, 0)->cantitate==90);
    destroy(lista, (destroyf) distrugeMedicament);
}

void test_size() {
    List *lista = createEmpty();
    assert(size(lista) == 0);
    add(lista, creeazaMedicament(101, "prod", 40, 90));
    add(lista, creeazaMedicament(102, "prod", 50, 1234));
    assert(size(lista) == 2);
    destroy(lista, (destroyf) distrugeMedicament);
    //assert(lista->lungime==0);
}

// teste SERVICE

void test_stergereMedicament()
{
    List *list=createEmpty();
    add(list, creeazaMedicament(101, "prod", 40, 90));
    add(list, creeazaMedicament(102, "prod", 50, 1234));
    assert(stergeMedicament(list,"ema")==0);
    assert(stergeMedicament(list,"prod")==1);
    destroy(list, (destroyf) distrugeMedicament);
}
void test_adaugaMedicament()
{
    List *list=createEmpty();
    assert(adaugaMedicament(list, 120, "Paracetamol", -70, 100)==0);
    assert(adaugaMedicament(list, 120, "Paracetamol", 70, 100)==1);
    assert(adaugaMedicament(list, 120, "Paracetamol", 70, 100)==1);
    destroy(list, (destroyf) distrugeMedicament);
}
void test_modificaMedicament() {
    List *lista = createEmpty();
    assert(adaugaMedicament(lista, 120, "Paracetamol", 70, 100)==1);
    assert(size(lista)==1);
    assert(modificaMedicament(lista, "Paracetamol", 120, "Aspirina", 19, 999)==1);
    assert(modificaMedicament(lista, "Paracetamol", 120, "Aspirina", -19, 999)==0);
    assert(modificaMedicament(lista, "Ema", 120, "Aspirina", 19, 999)==0);
    destroy(lista, (destroyf) distrugeMedicament);

}

void test_filtruMedicament() {
    List *lista = createEmpty();
    assert(adaugaMedicament(lista, 120, "Paracetamol", 70, 100));
    assert(adaugaMedicament(lista, 121, "Aspirina", 70, 100));
    assert(adaugaMedicament(lista, 122, "Calmotusin", 70, 100));
    List *lista_filtrata = filtruMedicamente(lista, 'A', 300);
    assert(size(lista_filtrata)==1);
    destroy(lista, (destroyf) distrugeMedicament);
    destroy(lista_filtrata, (destroyf) distrugeMedicament);

}

void test_sortMedicament() {
    List  *lista = createEmpty();
    Medicament *m1 = creeazaMedicament(120, "Paracetamol", 70, 100);
    Medicament *m2 = creeazaMedicament(120, "Paracetamol", 20, 10);
    assert(comparareCantitate(m1,m2)>0);
    distrugeMedicament(m1);
    distrugeMedicament(m2);
    //assert(comparareCantitate(creeazaMedicament(101, "prod", 90,90),creeazaMedicament(101, "prod", 90,70))==1);
    assert(adaugaMedicament(lista, 120, "Paracetamol", 70, 100));
    assert(adaugaMedicament(lista, 120, "Aspirina", 70, 100));
    assert(adaugaMedicament(lista, 120, "Calmotusin", 70, 100));
    assert(adaugaMedicament(lista, 120, "Algocalmin", 70, 100));
    assert(adaugaMedicament(lista, 120, "Aa", 70, 100));
    assert(adaugaMedicament(lista, 120, "B2", 70, 100));
    List *lista_sortata = sortMedicamente(lista);
    assert(size(lista_sortata)==6);
    assert(strcmp(get(lista_sortata, 0)->nume, "Aa")==0);
    assert(strcmp(get(lista_sortata, 1)->nume, "Algocalmin")==0);
    assert(strcmp(get(lista_sortata, 2)->nume, "Aspirina")==0);
    assert(get(lista_sortata, 3)->cantitate ==100);
    destroy(lista, (destroyf) distrugeMedicament);
    //assert(lista->lungime==0);
}

void testListadeliste()
{
    List * cevamedicamente = createEmpty();
    adaugaMedicament(cevamedicamente, 120, "Paracetamol", 70, 100);

    List *undolist=createEmpty();
    add(undolist, copyList(cevamedicamente));
    assert(size(undolist)==1);

    adaugaMedicament(cevamedicamente, 120, "B2", 70, 100);
    add(undolist, copyList(cevamedicamente));
    assert(size(undolist)==2);

    destroy(undolist, (destroyf) destroyListaMedicament);
    destroy(cevamedicamente, (destroyf) distrugeMedicament);

}

void test_adauga_undo()
{
    List_Manager lista=CreeazaListaMare();
    adaugaMedicament(lista.lista_Medicamente, 120, "Paracetamol", 70, 100);
    adauga_undo(&lista, lista.lista_Medicamente); //aici mai face un malloc
    assert(size(lista.lista_undo)==1);
    destroy(lista.lista_undo, (destroyf) destroyListaMedicament);
    destroy(lista.lista_Medicamente, (destroyf) distrugeMedicament);
}

void test_undo()
{
    List_Manager lista=CreeazaListaMare();
    adaugaMedicament(lista.lista_Medicamente, 120, "Paracetamol", 70, 100);
    adauga_undo(&lista, lista.lista_Medicamente); //aici mai face un malloc
    assert(size(lista.lista_undo)==1);
    adaugaMedicament(lista.lista_Medicamente, 120, "B2", 70, 100);
    undo_service(&lista);
    assert(size(lista.lista_Medicamente)==1);
    destroy(lista.lista_undo, (destroyf) destroyListaMedicament);
    destroy(lista.lista_Medicamente, (destroyf) distrugeMedicament);
}