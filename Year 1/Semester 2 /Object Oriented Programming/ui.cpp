//
// Created by emato on 07.04.2024.
//

#include "ui.h"
#include <iostream>

using namespace std;

void ConsolaLocatari::ui_add() {
    cout<<"-----Adaugare-----"<<'\n';
    string nume;
    int ap, tip;
    double suprafata;
    cout<<"Numele locatarului este: "<<'\n';
    getline(cin>>ws, nume);
    cout<<"Apartamentul este: "<<'\n';
    cin>>ap;
    cout<<"Tipul este: "<<'\n';
    cin>>tip;
    cout<<"Suprafata este: "<<'\n';
    cin>>suprafata;

    try{
        srv.addServi(ap,nume,suprafata,tip);
    }
    catch (RepoException& re){
        cout<<re;
    }
    catch (ValidateException& ve){
        cout<<"EROARE: Locatarul nu este valid!"<<'\n';
        cout<<ve.getErrorMessages();
    }
}

void ConsolaLocatari::printare_meniu() {
    cout<<"-----Meniu-----"<<'\n';
    cout<<"1.Adauga locatari"<<"\n";
    cout<<"2.Stergere locatar"<<'\n';
    cout<<"3.Modifica numele unui locatar"<<'\n';
    cout<<"4.Filtrare"<<'\n';
    cout<<"5.Sortare"<<'\n';
    cout<<"6.Afisare toti locatarii"<<'\n';
    cout<<"7 .Lista notificari---"<<'\n';
    cout<<"9. Map"<<'\n';
    cout<<"8. Exit"<<'\n'<<'\n';
}

void ConsolaLocatari::ui_delete() {
    cout<<"-----Stergere-----"<<'\n';
    int position;
    bool ok;
    ConsolaLocatari::printList(srv.getAllServi());
    cout<<"Introduceti pozitia Locatarului de sters: "<<'\n';
    cin>>position;
    ok=srv.deleteServi(position);
    if(!ok)
        cout<<"Stergerea nu a putut fi efectuata!";
    else
        cout<<"Stergere efectuata cu succes!";

}

void ConsolaLocatari::ui_modify() {
    cout<<"-----Modificare-----"<<'\n';
    string new_name, old_name;
    int ap;
    ConsolaLocatari::printList(srv.getAllServi());
    cout<<"Introduceti numele locatarului de modificat: "<<'\n';
    getline(cin>>ws,old_name);
    cout<<"Introduceti apartamentul locatarului de modificat: "<<'\n';
    cin>>ap;
    cout<<"Introduceti numele nou: "<<'\n';
    getline(cin>>ws, new_name);
    srv.modifyServi(old_name,ap,new_name);

}

void ConsolaLocatari::ui_filter() {
    cout<<"-----Filtrare-----"<<'\n';
    cout<<"Criteriul de filtrare este tip/suprafata"<<'\n';
    string criteriu;
    cin>>criteriu;

    if(criteriu=="tip")
    {
        cout<<"Tipul poate sa fie 1,2 sau 3 camere"<<'\n';
        int tip;
        cin>>tip;
        printList(srv.filtrareTip(tip));
    }
    else if(criteriu=="suprafata")
    {
        cout<<"Introduceti suprafata minima pe care doriti sa o aiba un apartament: "<<'\n';
        double suprafata;
        cin>>suprafata;
        printList(srv.filtrareSuprafata(suprafata));
    }
    else
        cout<<"Criteriul introdus este invalid... "<<'\n';
}

void ConsolaLocatari::ui_sort() {
    cout<<"-----Sortare------"<<'\n';
    cout<<"Criteriul de sortare este nume, suprafata sau tip"<<'\n';
    string criteriu;
    cin>>criteriu;
    if(criteriu=="nume")
        srv.sortByName();
    else if(criteriu=="suprafata")
        srv.sortBySuprafata();
    else if(criteriu=="tip")
        srv.sortByTip();
    else
        cout<<"Criteriul introdus e invalid... "<<'\n';
}

void ConsolaLocatari::printList(const vector<Locatar> &totilocatarii) {
    if(totilocatarii.empty())
        cout<<"Nu exista locatari!"<<'\n';
    else
    {
        int contor=1;
        for(const auto& l: totilocatarii)
        {
            cout<<contor++<<"."<<" | Nr.Apartament: "<<l.get_ap()<<" | Nume: "<<l.get_nume()<<" | Suprafata: "<<l.get_sup()<<" | Tip:"<<l.get_tip()<<'\n';
        }
    }
}

void ConsolaLocatari::run() {
    int running=1;
    int comanda;
    while(running)
    {
        printare_meniu();
        cout<<"Optiunea este: ";
        cin>>comanda;
        switch (comanda) {
            case 1:
                ui_add();
                break;
            case 2:
                ui_delete();
                break;
            case 3:
                ui_modify();
                break;
            case 4:
                ui_filter();
                break;
            case 5:
                ui_sort();
                break;
            case 6:
                printList(srv.getAllServi());
                break;
            case 8:
                running=0;
                break;
            case 7:
                notify_list_menu();
                break;
            case 9:
                map_ceva();
                break;
            default:
                break;

        }
    }
}

void ConsolaLocatari::notify_list_menu() {
    bool runin=true;
    int comanda;
    while(runin)
    {
        print_menu_notification();
        cout<<"Optiunea este: ";
        cin>>comanda;

        switch (comanda) {
            case 1:
                delete_list();
                break;
            case 2:
                add_notification();
                break;
            case 3:
                generate_random_notification();
                break;
            case 4:
                export_notification();
                break;
            case 5:
                runin=false;
                break;
            default:
                break;
        }
    }
}

void ConsolaLocatari::delete_list() {
    this->srv2.golire_servi();
}

void ConsolaLocatari::add_notification() {
    ConsolaLocatari::printList(this->srv.getAllServi());
    cout<<"Introduceti nr apartamentului: \n";
    int nr;
    cin>>nr;
    Locatar l=this->srv.find_locatar(nr);
    this->srv2.add_notif(l);
}

void ConsolaLocatari::generate_random_notification() {
    this->srv2.generate_random(this->srv.getAllServi());
}

void ConsolaLocatari::export_notification() {
    cout<<"| Exportare | "<<"\n";
    string nume_fisier;
    cout<<"Introduceti numele fiserului: "<<'\n';
    getline(cin>>ws, nume_fisier);
    this->srv2.export_servi(nume_fisier);
}

void ConsolaLocatari::print_menu_notification() {
    cout<<"| Lista Notificari |"<<'\n'<<'\n';
    cout<<"1. Goleste lista "<<"\n"<<"2. Adauga in lista\n"<<"3. Genereaza lista"<<'\n'<<"4. Exporta"<<'\n'<<"5. Back to default menu";
}

void ConsolaLocatari::map_ceva() {

}

