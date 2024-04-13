//
// Created by emato on 06.04.2024.
//

#ifndef LAB6_7_VALIDATORLOCATAR_H
#define LAB6_7_VALIDATORLOCATAR_H
#include <vector>
#include "Locatari.h"
#include <string>

using std::vector;
using std::string;
using std::ostream;

class ValidateException{
    vector<string> mesaj;
public:
    ValidateException(const  vector<string> & errors): mesaj{errors}{}
    string getErrorMessages(){
        string fullmsg;
        for(const string& e: mesaj)
        {
            fullmsg+=e+'\n';
        }
        return fullmsg;
    }

};

class LocatarValidator{
public:
    static void validate(const Locatar& l){
        vector<string> errors;
        if(l.get_nume().length()<2)
            errors.emplace_back("Numele trebuie sa aiba mai mult de 2 caractere!");
        if(l.get_ap()<0)
            errors.emplace_back("Numarul trebuie sa fie pozitiv!");
        if(l.get_sup()<0)
            errors.emplace_back("Suprafata trebuie sa fie pozitiva!");
        if(l.get_tip()<1 || l.get_tip()>3)
            errors.emplace_back("Tipul trebuie sa fie 1, 2 sau 3!");
        //eplace_back construieste direct obiectul, spre deosebire de push_back care face potentiale copii

        if(!errors.empty())
        {
            throw ValidateException(errors);
        }

    }
};
#endif //LAB6_7_VALIDATORLOCATAR_H
