//
// Created by emato on 07.04.2024.
//

#ifndef LAB6_7_UI_H
#define LAB6_7_UI_H
#include "ServiceLocatari.h"

class ConsolaLocatari{
private:
    Service& srv;
public:
    ConsolaLocatari(Service& srv): srv{ srv }{};
    ConsolaLocatari(const ConsolaLocatari& ot)=delete;

    void printare_meniu();
    void ui_add();
    void ui_delete();
    void ui_modify();
    void ui_filter();
    void ui_sort();
    void printList(VectorDinamic<Locatar> totilocatarii);
    void run();

};
#endif //LAB6_7_UI_H
