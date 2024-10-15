//
// Created by emato on 07.04.2024.
//

#include "teste.h"
#include "RepoLocatari.h"
#include "Locatari.h"
#include "ServiceLocatari.h"
#include "ValidatorLocatar.h"
#include <cassert>
#include <map>
#include "reponotify.h"
#include "servy_notif.h"

using std::map;


void TesteLocatar::run_all_tests() {
   // TesteLocatar::run_teste_repo();
    //TesteLocatar::run_teste_adaugare();
    TesteLocatar::run_test_service();
}

void TesteLocatar::run_teste_repo() {
    Repo repotest;
    assert(repotest.getall().empty());
    Locatar l(23, "Pikachu", 900.1,2);
    repotest.addLocatar(l);
    assert(repotest.getall().size()==1);
    Locatar l1(17,"Ema",1405,2);
    repotest.addLocatar(l1);
    repotest.deleteLocatar(1);
    assert(repotest.getall().size()==1);
    Locatar cautat=repotest.findLocatar("Ema",17);
    assert(cautat.get_nume()=="Ema");
    assert(repotest.is_in(cautat));

    Repo_notify notif;
    notif.adauga_notificare(l1);
    notif.adauga_notificare(l);
    assert(notif.get_everything().size()==2);

    notif.golire();
    assert(notif.get_everything().empty());

    notif.export_notify("teste");
}

void TesteLocatar::run_teste_adaugare() {
    Repo repo;
    LocatarValidator val;
    Service srv{repo, val};
    srv.addServi(12,"Adi", 469.5, 2);
    srv.addServi(17,"Ema", 600.5, 2);
    srv.addServi(13,"Ema", 1600.5, 3);
    srv.addServi(1,"Alexandra", 134.5, 1);
    srv.addServi(7,"Andrei", 60.5, 1);

    try{
        srv.addServi(-2,"",-1,7);
    }
    catch (ValidateException&){
        assert(true);
    }

    try{
        srv.addServi(12,"Adi", 469.5, 2);
    }
    catch (RepoException&)
    {
        assert(true);
    }

    assert(srv.deleteServi(-1)== false);
    assert(srv.deleteServi(1)==true);
    assert(srv.deleteServi(100)== false);

}

void TesteLocatar::run_test_service() {
    Repo repoTest;
    LocatarValidator val;
    Service srv{repoTest, val};
    srv.addServi(12,"Adi", 469.5, 2);
    srv.addServi(17,"Ema", 600.5, 2);
    srv.addServi(13,"Ema", 1600.5, 3);
    srv.addServi(1,"Alexandra", 134.5, 1);
    srv.addServi(7,"Andrei", 60.5, 1);
    assert(repoTest.getall().size() == 5);

    srv.addServi(5,"Maria",37749.22,2);
    srv.fa_undo();  //test undo add
    assert(repoTest.getall().size() == 5);

    srv.deleteServi(5);
    assert(repoTest.getall().size() == 4);
    srv.fa_undo(); //test undo stergere
    assert(repoTest.getall().size() == 5);
    srv.deleteServi(5);


    srv.modifyServi("Adi",12,"Adrian");
    Locatar l(12,"Adrian", 469.5, 2);
    assert((Locatar) repoTest.findLocatar("Adrian", 12) == l);
    srv.fa_undo();
    Locatar l1(12,"Adi",469.5,2);
    assert((Locatar)repoTest.findLocatar("Adi", 12) == l1);

    auto lista_sortata=srv.sortByName();
    assert(lista_sortata[0].get_nume()=="Adi");

    auto lista_sortat1=srv.sortByTip();
    assert(lista_sortat1[0].get_tip()==3);

    auto lista_sortat3=srv.sortBySuprafata();
    assert(lista_sortat3[0].get_sup()==1600.5);

    auto lista_tip=srv.filtrareTip(1);
    assert(lista_tip.size()==1);

    auto lista_tip1=srv.filtrareSuprafata(1000);
    assert(lista_tip1.size()==1);


    Repo_notify repon;
    ServiNotif srv2{repon,val};

    srv2.add_notif(Locatar(12,"Adi", 469.5, 2));
    srv2.add_notif(Locatar(17,"Ema", 600.5, 2));
    assert(srv2.get_everything_servi().size()==2);

    srv2.golire_servi();
    assert(srv2.get_everything_servi().empty());

    srv2.generate_random(srv.getAllServi());

    assert(!srv2.get_everything_servi().empty());


    map<int,int> result=srv.make_map();

    assert((result[2])==2);
    assert((result[3])==1);
    assert((result[1])==1);
//supraincarcarea operatorilor

}
