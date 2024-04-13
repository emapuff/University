//
// Created by emato on 01.04.2024.
//

#include "RepoLocatari.h"

using std::exception;

void Repo::addLocatar(const Locatar &l) {
    if(is_in(l))
        throw RepoException("Locatarul deja exista!!");
    this->lista.push_back(l);
}

void Repo::deleteLocatar(int position) {
    if(position<0 || position> this->lista.size())
        throw RepoException("Pozitie invalida!");
    this->lista.erase(this->lista.begin()+position-1); //indexarea incepe de la 0
}

const Locatar& Repo::findLocatar(const string& nume, int nr) {
    for(const auto&locatar_in_vector: this->lista)
        if(locatar_in_vector.get_nume()==nume&&locatar_in_vector.get_ap()==nr)
            return locatar_in_vector;
    throw RepoException("Locatarul cu datele introduse nu exista");
}

bool Repo::is_in(const Locatar &l) {
    for( auto &locatar_in_vector: this->lista)
        if(locatar_in_vector==l) //aveam nevoide de operatie de egalitate
            return true;
    return false;
}

void Repo::modify_Locatar(const Locatar &l, const string& new_name) {
    for( auto &locatar_in_vector: this->lista)
        if(locatar_in_vector==l)
           locatar_in_vector.set_nume(new_name);
}

const vector<Locatar> &Repo::getall() {
    return this->lista;
}
