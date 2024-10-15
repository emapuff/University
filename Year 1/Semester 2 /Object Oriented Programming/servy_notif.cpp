//
// Created by emato on 14.04.2024.
//
#include <random>
#include <algorithm>
#include "servy_notif.h"
#include <chrono>

using std::mt19937;

void ServiNotif::golire_servi() {
    this->repo.golire();
}

void ServiNotif::add_notif(const Locatar &l) {
    /*
     * functia adauga un locatar in lista de notificari
     * pre: l - locatarul de adaugat
     * post: -
     */
    this->repo.adauga_notificare(l);
    notify();
}


void ServiNotif::export_servi(const string &file_name) {
    /*
     * functia exporteaza lista cu elemente
     * pre: string - numele fisierului unde exportam
     * post: -
     */
    this->repo.export_notify(file_name);
}

void ServiNotif::generate_random(vector<Locatar> lista) {
    /*
     * functia genereaza un nr random de locatari care vor fi adaugti
     * pre: lista din care generam
     * post:-
     */
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    mt19937 gen(seed);

    // Generate a random number of elements to select between 1 and lista.size()
    std::uniform_int_distribution<int> dist(1, static_cast <int> (lista.size()));
    int nr = dist(gen);

    shuffle(lista.begin(), lista.end(), gen);

    vector<Locatar> randomSelection(lista.begin(), lista.begin() + nr);


    for (const auto& locatar : randomSelection) {
        if(!find_obj(locatar))
             this->repo.adauga_notificare(locatar);
    }
    notify();
}

vector<Locatar> ServiNotif::get_everything_servi() {
    /*
     * functia returneaza lista de notificari
     */
    return this->repo.get_everything();
}

bool ServiNotif::find_obj(const Locatar &l) {
    vector <Locatar> caut=this->get_everything_servi();
    for(const auto&locatar: caut){
        if(l==locatar)
            return true;
    }
    return false;
}

