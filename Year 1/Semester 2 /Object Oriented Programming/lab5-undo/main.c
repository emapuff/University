#include <stdio.h>
#include "service.h"
#include "teste.h"

void testAll() {
    // test domain
    test_creeazaMedicament();
     test_valideazaMedicament();

// // test list
     test_createEmpty();
     test_add();
     test_get();
    test_size();
    test_delete();

  // test service
    test_stergereMedicament();
    test_adaugaMedicament();
    test_modificaMedicament();
    test_filtruMedicament();
    test_sortMedicament();
    testListadeliste();
    test_adauga_undo();
    test_undo();
}

//Functia UI de adaugare
void uiAdauga(List_Manager * v) {
    char nume[30];
    int cod, concentratie, cantitate;
    printf("Cod: ");
    scanf("%d", &cod);
    printf("Nume: ");
    scanf("%s", nume);
    printf("Concentratie: ");
    scanf("%d", &concentratie);
    printf("Cantitate: ");
    scanf("%d", &cantitate);
    adauga_undo(v,v->lista_Medicamente);
    int succes = adaugaMedicament(v->lista_Medicamente, cod, nume, concentratie, cantitate);
    if (succes)
        printf("Medicament adaugat cu succes!\n");
    else
        printf("Medicamentul nu este valid!\n");
}

// Functia ui de modificare
void uiModifica(List_Manager * v) {
    char nume[30], nume_nou[30];
    int cantitate, cod_nou, concentratie_noua;
    printf("De modificat\n");
    printf("Nume: ");
    scanf("%s30", nume);
    printf("Codul nou: ");
    scanf("%d", &cod_nou);
    printf("Nume nou: ");
    scanf("%s30", nume_nou);
    printf("Concentratie noua: ");
    scanf("%d", &concentratie_noua);
    printf("Cantitate: ");
    scanf("%d", &cantitate);
    adauga_undo(v,v->lista_Medicamente);
    int succes = modificaMedicament(v->lista_Medicamente, nume, cod_nou, nume_nou, concentratie_noua, cantitate);

    if (succes)
        printf("Modificarea s-a efectuat cu succes!\n");
    else
        printf("Modificarea nu s-a efectuat! Date invalide!\n");
}

// Functia ui de stergere
void uiSterge(List_Manager * v) {
    char nume[30];
    printf("Numele medicamentului de sters: ");
    scanf("%s", nume);
    adauga_undo(v,v->lista_Medicamente);
    int succes = stergeMedicament(v->lista_Medicamente, nume);

    if (succes)
        printf("Medicament sters cu succes!\n");
    else
        printf("Nu exista medicament de acest fel!\n");
}

// Functia Ui de afisare a stocului
void uiStoc(List* v) {
    if (v->lungime == 0)
        printf("Nu este nimic in stoc!\n");
    else {
        printf("STOC: \n");
        for (int i = 0; i < size(v); i++) {
            Medicament  *m = get(v, i);
            printf("Cod: %d | Nume: %s | Concentratie: %d | Cantitate: %d\n", m->cod, m->nume, m->concentratie, m->cantitate);
        }
    }
}

// Functia ui de sortare
void uiSortare(List* v) {
    List *listaSortata = sortMedicamente(v);
    uiStoc(listaSortata);
}

// Functia ui de filtrare
void uiFiltru(List* v) {
    char l;
    int cantitate_max;
    printf("Prima litera: ");
    scanf(" %c", &l);
    printf("Cantitatea maxima: ");
    scanf("%d", &cantitate_max);
    List* listaFiltrata = filtruMedicamente(v, l, cantitate_max);
    uiStoc(listaFiltrata);
}

void uiUndo(List_Manager *v)
{
    if(v->lista_undo->lungime==0)
    {
        printf("Nothing to Undo!\n");
    }
    else
    {
        undo_service(v);
    }
}
void MeniuUI() {
    printf(" -- MENIU --\n");
    printf("1. Adaugare Medicament(daca exista deja in stoc se actualizeaza cantitatea)\n");
    printf("2. Modificare Medicament\n");
    printf("3. Stergere Medicament\n");
    printf("4. Afisare Stoc\n");
    printf("5. Vizualizare medicamente ordonate dupa nume si cantitate\n");
    printf("6. Vizualizare medicamente filtrate dupa un criteriu\n");
    printf("7. UNDO\n");
    printf("0. Iesire din program\n");
    printf("--\t--\t--\n");
}

void run_console() {
    List_Manager lista=CreeazaListaMare();
    int ok = 1, option;
    while (ok) {
       MeniuUI();
        printf("Optiune: ");
        scanf("%d", &option);
        switch (option) {
            case 1:
                printf("Adaugare medicament \n");
                uiAdauga(&lista);
                break;
            case 2:
               printf("Modificare medicament\n");
                uiModifica(&lista);
                break;
            case 3:
                printf("Stergere medicamente\n");
                uiSterge(&lista);
                break;
            case 4:
                uiStoc(lista.lista_Medicamente);
                break;
            case 5:
                printf("Vizualizare medicamente ordonate dupa nume si cantitate\n");
                uiSortare(lista.lista_Medicamente);
                break;
            case 6:
                printf("Vizualizare medicamente filtrate dupa un criteriu\n");
                uiFiltru(lista.lista_Medicamente);
                break;
            case 7:
                uiUndo(&lista);
                break;
            case 0:
                printf("Iesire din program.\n");
                ok = 0;
                destroy(lista.lista_Medicamente, (destroyf) distrugeMedicament);
                destroy(lista.lista_undo, (destroyf) destroyListaMedicament);
                break;
            default:
                printf("Optiunea nu este valida!\n");
                break;
        }
    }
}

int main() {
    testAll();
   // run_console();

    return 0;
}
