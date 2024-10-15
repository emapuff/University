//
// Created by emato on 06.04.2024.
//

#include "ServiceLocatari.h"
#include <functional>
#include <algorithm>
#include <utility>
#include <map>

using std::sort;
using std::map;


//vector<Locatar> Service::generalSort(bool (*maiMicF)(const Locatar &, const Locatar &)) {
//    vector<Locatar> v{repo.getall()};
//    for (size_t i = 0; i < v.size(); i++) {
//        for (size_t j = i + 1; j < v.size(); j++) {
//            if (!maiMicF(v[i], v[j])) {
//                //interschimbam
//                std::swap(v[i], v[j]);
//            }
//        }
//    }
//    return v;
//}

void Service::addServi(const int &ap, const string &nume, const double &supr, const int &tip) {
    Locatar l1{ap,nume,supr,tip};
    LocatarValidator::validate(l1);
    repo.addLocatar(l1);
    undo_list.push_back(new UndoAdauga(l1,repo));
}

bool Service::deleteServi(const int &position) {
    try{
        cout<<"ceva1"<<'\n';
        Locatar l=repo.findNr(position);
        cout<<"ceva2"<<'\n';
        repo.deleteLocatar(position);
        cout<<"ceva3"<<'\n';
        undo_list.push_back(new UndoSterge(repo,l));
        return true;
    } catch( const RepoException&e){
        return false;
    }
    catch(std::exception e){
        vector <string> erori;
        erori.push_back("Locatar negasit!");
        throw ValidateException(erori); //trebuia suprascris what
    }
}

void Service::modifyServi(const string &nume_vechi,const int&ap, const string &nume_nou) {
    Locatar& l1=repo.findLocatar(nume_vechi,ap);
    repo.modify_Locatar(l1,nume_nou);
    undo_list.push_back(new UndoModifica(l1,repo,nume_vechi));
}

vector<Locatar> Service::filter(function<bool(const Locatar&)> fct) {
    vector<Locatar> filteredvector;
    //back_iterator -> iteratie care insereaza la finalul listei
    //move(obj) -> cast the object
    //copy_if(first, last, result, pred) -> iterates from first to last, copying the objects that satisfy the pred binary function in result (all are pointers except pred)
    std::copy_if(repo.getall().begin(), repo.getall().end(), std::back_inserter(filteredvector), std::move(fct));
    return filteredvector;
}

vector<Locatar> Service::filtrareTip(const int &tip) {
   return filter([tip](const Locatar&l){
       return l.get_tip()==tip;
   });
}

vector<Locatar> Service::filtrareSuprafata(const double &suprafata) {
    return filter([suprafata](const Locatar&l){
        return l.get_sup()>=suprafata;
    });
}

vector<Locatar> Service::sortByName() {
   auto sortedCopy=repo.getall();
   sort(sortedCopy.begin(),sortedCopy.end(), cmpNume);
   return sortedCopy;
}

vector<Locatar> Service::sortBySuprafata() {
    auto sortedCopy=repo.getall();
    sort(sortedCopy.begin(),sortedCopy.end(), cmpSuprfata);
    return sortedCopy;
}

vector<Locatar> Service::sortByTip() {
    /*
     * returneaza o lista cu locatarii salvati
     * pre: -
     * post: lista cu elemente sortate
     */
    auto sortedCopy=repo.getall();
    sort(sortedCopy.begin(),sortedCopy.end(), cmpTip);
    return sortedCopy;
}

const Locatar& Service::find_locatar(const int &nr) {
    /*
     * functia returneaza un locatar care sta la nr introdus
     * pre: int nr
     * post: locatar care sta la nr introdus
     */
    return this->repo.findNr(nr);
}

map<int, int> Service::make_map() {
    /*
     * functia construieste un map cu cate apartamente sunt de cata tipuri
     * pre: -
     * post: map < int (tip), int (contor)>
     */
    map<int,int> new_map;
    for( auto &l : this->repo.getall())
    {
        auto it=new_map.find(l.get_tip());
        if(it!=new_map.end())
            it->second++;
        else
            new_map.insert({l.get_tip(),1});
    }

    return new_map;
}

void Service::fa_undo()
{
    if(undo_list.empty())
        throw RepoException("Nu se poate efectua undo!\n");
    undo_list.back()->doUndo();
    undo_list.pop_back();
}

const Locatar &Service::findObjectbyNrServi(int position) {
    return repo.findNr(position);
}


