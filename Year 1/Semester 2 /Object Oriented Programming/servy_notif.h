//
// Created by emato on 14.04.2024.
//

#ifndef LAB6_7_SERVY_NOTIF_H
#define LAB6_7_SERVY_NOTIF_H
#include "Locatari.h"
#include "reponotify.h"
#include <string>
#include "ValidatorLocatar.h"
#include "observer.h"

class ServiNotif: public Observable{
private:
    Repo_notify &repo;
    LocatarValidator &val;

public:
    ServiNotif(Repo_notify& repo, LocatarValidator& val): repo{repo}, val{val} {};

    ServiNotif(const ServiNotif& ot)=delete;

    void golire_servi();

    void add_notif(const Locatar &l);

    void generate_random(vector<Locatar> lista);

    void export_servi(const string &file_name);

    vector <Locatar> get_everything_servi();

    bool find_obj(const Locatar&l);
};
#endif //LAB6_7_SERVY_NOTIF_H
