//
// Created by emato on 01.04.2024.
//

#include "Locatari.h"

Locatar::Locatar(const int &_nr_apartament, const string & _nume, const double &_suprafata, const int &_tip):
    nr_apartament{ _nr_apartament},
    nume {_nume},
    suprafata {_suprafata},
    tip {_tip}{}



Locatar &Locatar::operator=(const Locatar &another_one) {
    this->nr_apartament=another_one.nr_apartament;
    this->suprafata=another_one.suprafata;
    this->nume=another_one.nume;
    this->tip=another_one.tip;
    return *this;
    //Locatar l(1,"ceva",45.4,1);
}

const int &Locatar::get_ap() const noexcept {
    return this->nr_apartament;
}

const double &Locatar::get_sup() const noexcept {
    return this->suprafata;
}

const string &Locatar::get_nume() const noexcept {
    return this->nume;
}

const int &Locatar::get_tip() const noexcept {
    return this->tip;
}

void Locatar::set_nume(const string &_new_name) {
    this->nume=_new_name;
}

bool cmpTip(const Locatar&l1, const  Locatar&l2){
    return l1.get_tip()>l2.get_tip();
}

bool cmpSuprfata(const Locatar&l1, const Locatar&l2)
{
    return l1.get_sup()>l2.get_sup();
}

bool cmpNume(const Locatar&l1, const Locatar&l2){
    return l1.get_nume()<l2.get_nume();
}



