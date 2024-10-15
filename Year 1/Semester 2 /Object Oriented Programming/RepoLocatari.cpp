//
// Created by emato on 01.04.2024.
//

#include "RepoLocatari.h"
#include <algorithm>
#include <map>

using std::exception;
using std::map;

void Repo::addLocatar(const Locatar &l) {
    /*
     * Adauga un locatar in lista
     */
    if (is_in(l))
        throw RepoException("Locatarul deja exista!!");
    this->lista.push_back(l);
}

void Repo::deleteLocatar(int position) {
    /*
     * sterge um locatar din lista dipa numarul apartamentului
     */
    auto it = std::find_if(lista.begin(), lista.end(), [&](const Locatar& l) {
        return l.get_ap() == position;
    });

    if (it != lista.end()) {
        lista.erase(it); // Erase the element if found
    } else {
        throw RepoException("Nu exista apartament cu nr indicat");
    }
}


Locatar & Repo::findLocatar(const string &nume, int nr) {
    auto it = std::find_if(this->lista.begin(), this->lista.end(), [&](const Locatar &locatar_in_vector) {
        return locatar_in_vector.get_nume() == nume && locatar_in_vector.get_ap() == nr;
    });

    if (it != this->lista.end()) {
        return *it;
    } else {
        throw RepoException("Locatarul cu datele introduse nu exista");
    }
}

bool Repo::is_in(const Locatar &l) {
    bool exists = std::find(this->lista.begin(), this->lista.end(), l) != this->lista.end();
    return exists;
}

void Repo::modify_Locatar(const Locatar &l, const string &new_name) {
    auto it = std::find_if(this->lista.begin(), this->lista.end(), [&](const Locatar &locatar_in_vector) {
        return locatar_in_vector == l;
    });

    if (it != lista.end()) {
        it->set_nume(new_name); // Return a reference to the found Locatar
    } else {
        throw RepoException("Nu exista locatarul indicat");
    }
}


const vector<Locatar> &Repo::getall() {
    return this->lista;
}

const Locatar &Repo::findNr(const int nr) {
    auto it = std::find_if(this->lista.begin(), this->lista.end(), [&](const Locatar &locatar_in_vector) {
        return locatar_in_vector.get_ap() == nr;
    });

    if (it != this->lista.end())
        return *it;
    else
        throw std::runtime_error("Locatar not found!");
}

int Repo::get_position(const Locatar &l) {
    int contor = 1;
    for (const auto &locatar: this->lista) {
        if (l == locatar)
            return contor;
        contor++;
    }
}

const Locatar &Repo::position_find(int positon) {
    int contor = 1, ok = 0;
    for (const auto &L: getall()) {
        if (contor == positon) {
            ok = 1;
            return L;
        }
        contor++;

    }
    throw RepoException("Nu exista pozitia indicata!\n");
}

int Repo::findNrbyObject(const Locatar &L) {
    return L.get_ap();
}

RepoDictionary::RepoDictionary(double chance) {
    probabilitate = chance;
    dictionar_locatari.clear();
}

void RepoDictionary::addLocatar(const Locatar &l) {
    random();
    dictionar_locatari.insert(std::make_pair(dictionar_locatari.size(), l));
}


void RepoDictionary::deleteLocatar(int pozition) {
    random();
    dictionar_locatari.erase(pozition);
}


void RepoDictionary::random() const {
    auto prb = int(probabilitate * 10);
    int nr = rand() % 10 + 1;
    if (nr <= prb) {
        return;
    }
    throw RepoException("Eroare detectata\n");
}
