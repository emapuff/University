//
// Created by emato on 13.04.2024.
//

#ifndef LAB6_7_REPONOTIFY_H
#define LAB6_7_REPONOTIFY_H
#include <vector>
#include "Locatari.h"
#include <fstream>
#include <string>

using std::vector;
using std::ofstream;

class Repo_notify{
private:
    vector <Locatar> lista_notif;

public:
    Repo_notify()=default;
    Repo_notify(const Repo_notify &ot)=delete;

    vector <Locatar> get_everything(){
        return lista_notif;
    }
    void golire(){
        lista_notif.clear();
    }

    void adauga_notificare(const Locatar&l)
    {
        lista_notif.push_back(l);
    }

    void export_notify(const string &file_name){
        ofstream fout(file_name+".html");
        if (fout.is_open()) {
            fout << "<html> <title> Lista notificari </title>\n<body>\n<ul>\n";
            for (auto &l: lista_notif)
                fout << "<li>" << " | Nr.Apartament: " << l.get_ap() << " | Nume" << l.get_nume() << " | Suprafata: "
                     << l.get_sup() << " | Tip:" << l.get_tip() << "</li>\n";
            fout << "</ul>\n</body>\n</html>";
            fout.close();
        }
        else{
            throw std::runtime_error("Fisierul nu poate fi deschis");
        }
    }
};
#endif //LAB6_7_REPONOTIFY_H
