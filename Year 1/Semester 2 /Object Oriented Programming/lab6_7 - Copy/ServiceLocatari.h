//
// Created by emato on 06.04.2024.
//

#ifndef LAB6_7_SERVICELOCATARI_H
#define LAB6_7_SERVICELOCATARI_H
#include "RepoLocatari.h"
#include <vector>
#include "Locatari.h"
#include "ValidatorLocatar.h"
#include <functional>
#include <string>

using std::vector;
using std::function;
using std::string;

class Service{
private:
    Repo& repo;
    LocatarValidator& val;
    vector<Locatar> filter(function<bool(const Locatar&)> fct);
    vector<Locatar> generalSort(bool(*maiMicF)(const Locatar&, const Locatar&));

public:
    Service(Repo& repo, LocatarValidator& val): repo{repo}, val{val} {};
    Service(const Service& ot)=delete;

    void addServi(const int&, const string&, const double&, const int&);

    bool deleteServi(const int& position);

    void modifyServi(const string &nume_vechi,const int&ap, const string &nume_nou);

    [[nodiscard]] const vector<Locatar>& getAllServi() const noexcept{
        return this->repo.getall();
    }

    vector <Locatar> filtrareTip(const int& tip);

    vector<Locatar> filtrareSuprafata(const double& suprafata);

    vector <Locatar> sortByName();

    vector <Locatar> sortBySuprafata();

    vector <Locatar> sortByTip();

};
#endif //LAB6_7_SERVICELOCATARI_H
