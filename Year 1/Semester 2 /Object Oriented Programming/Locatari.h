//
// Created by emato on 01.04.2024.
//

#ifndef LAB6_7_LOCATARI_H
#define LAB6_7_LOCATARI_H
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::ostream;

class Locatar{
private:
    int nr_apartament;
    string nume;
    double suprafata;
    int tip;

public:
    Locatar()=default; //permite sa cream obiecte fara sa specificam valori initiale
    Locatar(const int&, const string&, const double&, const int&); //permite sa cream obeicte cu valori initiale
    Locatar(const Locatar& l):
    nr_apartament{l.nr_apartament} , nume{l.nume}, suprafata{l.suprafata}, tip{l.tip}  {}//permite sa facme o copie unui obiect

    Locatar& operator=(const Locatar&);//declarator pentru asignare

    bool operator==(const Locatar& m) const {
        return this->get_nume() == m.get_nume() && this->get_ap()==m.get_ap();
    }

    bool operator!=(const Locatar& m) const {
        return !(*this == m);
    }

    friend std::ostream& operator<<(std::ostream& os, const Locatar& l);

    const int& get_ap() const noexcept;
    const double& get_sup() const noexcept;
    const string& get_nume() const noexcept;
    const int& get_tip() const noexcept;

    void set_nume(const string&);
};

bool cmpTip(const Locatar&l1, const  Locatar&l2);

bool cmpSuprfata(const Locatar&l1, const Locatar&l2);

bool cmpNume(const Locatar&l1, const Locatar&l2);

#endif //LAB6_7_LOCATARI_H
