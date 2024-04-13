//
// Created by emato on 07.04.2024.
//

#include "teste.h"
#include "RepoLocatari.h"
#include "Locatari.h"
#include "ServiceLocatari.h"
#include "ValidatorLocatar.h"
#include <cassert>

void TesteLocatar::run_all_testts() {
    this->run_teste_repo();
    this->run_teste_adaugare();
}

void TesteLocatar::run_teste_repo() {
    Repo repotest;
    assert(repotest.getall().size()==0);
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

}

void TesteLocatar::run_teste_adaugare() {
    Repo repo;
    LocatarValidator val;
    Service srv{repo, val};
    srv.addServi(12,"Oti", 469.5, 2);
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
        srv.addServi(12,"Oti", 469.5, 2);
    }
    catch (RepoException&)
    {
        assert(true);
    }

    assert(srv.deleteServi(-1)== false);
    assert(srv.deleteServi(1)==true);
    assert(srv.deleteServi(100)== false);

}
