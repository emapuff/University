//
// Created by emato on 22.04.2024.
//

#ifndef LAB6_7_UNDO_H
#define LAB6_7_UNDO_H
#include <utility>

#include "Locatari.h"
#include "RepoLocatari.h"

class ActiuneUndo{
public:
    virtual void doUndo()=0; //destructor virtual, nu asiguram ca se apeleaza desctructorul corect in polimorfisrm
    virtual ~ActiuneUndo()=default;
};

class UndoAdauga: public ActiuneUndo{
    Locatar locatar_adaugat;
    AbsRepo& repopoly;
public:
    UndoAdauga(const Locatar& locatar, AbsRepo& repopoly): repopoly{repopoly}, locatar_adaugat(locatar){};
    void doUndo() override{
        repopoly.deleteLocatar(repopoly.findNrbyObject(locatar_adaugat));
    }
};

class UndoSterge: public ActiuneUndo{
    Locatar to_readd;
    AbsRepo& repopoly;
public:
    UndoSterge(AbsRepo& repopoly, const Locatar& locatar): repopoly{repopoly}, to_readd{locatar}{};
    void doUndo() override{
        repopoly.addLocatar(to_readd);
    }
};

class UndoModifica:public ActiuneUndo{
    Locatar locatar_adaugat;
    AbsRepo &repopoly;
    string vechiul_nume;
public:
    UndoModifica(const Locatar&locatar, AbsRepo&repopoly, string  vechiul_nume): repopoly{repopoly}, locatar_adaugat{locatar}, vechiul_nume{std::move(vechiul_nume)}{};
    void doUndo() override{
        repopoly.modify_Locatar(locatar_adaugat,vechiul_nume);
    }
};
#endif //LAB6_7_UNDO_H
