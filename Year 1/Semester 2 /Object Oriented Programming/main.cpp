#include <QApplication>
#include <QPushButton>
#include <iostream>
#include "ui.h"
#include "ValidatorLocatar.h"
#include "teste.h"
#include "GUI.h"

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
    TesteLocatar::run_all_tests();
}
void stard_app()
{

}
int main(int argc, char** argv)
{
   // tests_and_tests();
   // cout<<"Tests passed"<<"\n";
    //stard_app();

    QApplication a(argc, argv);
    Repo repo;
    Repo_notify repo2;
    LocatarValidator val;
    Service srv{repo, val};
    ServiNotif srv2{repo2, val};
    LocatariGui gui{srv, srv2};

    gui.show();

    return a.exec();
}