//
// Created by emato on 06.04.2024.
//

#include "ServiceLocatari.h"
#include <functional>
#include <algorithm>

using std::sort;

vector<Locatar> Service::generalSort(bool (*maiMicF)(const Locatar &, const Locatar &)) {
    vector<Locatar> v{repo.getall()};
    for (size_t i = 0; i < v.size(); i++) {
        for (size_t j = i + 1; j < v.size(); j++) {
            if (!maiMicF(v[i], v[j])) {
                //interschimbam
                std::swap(v[i], v[j]);
            }
        }
    }
    return v;
}

void Service::addServi(const int &ap, const string &nume, const double &supr, const int &tip) {
    Locatar l1{ap,nume,supr,tip};
    val.validate(l1);
    repo.addLocatar(l1);
}

bool Service::deleteServi(const int &position) {
    if(position<0 || position>repo.getall().size())
        return false; //nu putem sterge
    repo.deleteLocatar(position);
    return true;
}

void Service::modifyServi(const string &nume_vechi,const int&ap, const string &nume_nou) {
    Locatar l1=repo.findLocatar(nume_vechi,ap);
    repo.modify_Locatar(l1,nume_nou);
}

vector<Locatar> Service::filter(function<bool(const Locatar &)> fct) {
    vector <Locatar> filteredvector;
    for(const auto& l:repo.getall())
    {
        if(fct(l))
            filteredvector.push_back(l);
    }
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
    auto sortedCopy=repo.getall();
    sort(sortedCopy.begin(),sortedCopy.end(), cmpTip);
    return sortedCopy;
}


