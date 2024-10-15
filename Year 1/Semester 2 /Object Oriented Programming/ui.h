//
// Created by emato on 07.04.2024.
//

#ifndef LAB6_7_UI_H
#define LAB6_7_UI_H
#include "ServiceLocatari.h"
#include "servy_notif.h"
class ConsolaLocatari{
private:
    Service& srv;
    ServiNotif& srv2;
public:
    ConsolaLocatari(Service& srv, ServiNotif& srv2): srv{ srv }, srv2{srv2}{};
    ConsolaLocatari(const ConsolaLocatari& ot)=delete;

    static void printare_meniu();
    void ui_add();
    void ui_delete();
    void ui_modify();
    void ui_filter();
    void ui_sort();
    static void printList(const vector<Locatar>& totilocatarii);
    void run();
    void notify_list_menu();
    void delete_list();
    void add_notification();
    void generate_random_notification();
    void export_notification();
    static void print_menu_notification();
    void map_ceva();

};
#endif //LAB6_7_UI_H
