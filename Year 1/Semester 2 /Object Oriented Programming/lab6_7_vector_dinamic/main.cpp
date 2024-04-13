#include <iostream>
#include "ui.h"
#include "ValidatorLocatar.h"
#include "teste.h"
using namespace std;
/*
  ~Administrare Bloc~
  Creati o aplcatie care permite:
  - gestiunea unei liste de locatari(apartament, nume proprietari, suprafata, tip apartament)
  - adaugare, stergere, modificare si afisare locatari
  - cautare apartament
  - filtrare apartament dupa: tip apartament si suprafata
  - sortare apartamente dupa: nume proprietar, suprafata, tip apartament + suprafata
 */

void tests_and_tests()
{
    TesteLocatar tests;
    tests.run_all_testts();
}
void stard_app()
{
    Repo repo;
    LocatarValidator val;
    Service srv{repo, val};
    ConsolaLocatari ui{srv};
    ui.run();
}
int main()
{
    tests_and_tests();
    stard_app();
    return 0;
}
