//
// Created by emato on 01.04.2024.
//

#ifndef LAB6_7_REPOLOCATARI_H
#define LAB6_7_REPOLOCATARI_H
#include <exception>
#include <string>
#include <ostream>
#include <utility>
#include <vector>
#include <random>
#include "Locatari.h"
#include "map"


using std::string;
using std::ostream;
using std::vector;
using std::map;


class RepoException{
private:
    string errorMsg;
public:
    explicit RepoException(string errorMsg) :errorMsg{std::move( errorMsg )} {};
    string getErrorMessage() {
        return this->errorMsg;
    }
    friend ostream& operator<<(ostream& stream, const RepoException& exception) {
        return stream << exception.errorMsg;
    }
};



class AbsRepo{
public:
    virtual void addLocatar(const Locatar& l)=0;

    virtual const Locatar& findLocatar(const string& nume, int nr)=0;

    virtual bool is_in(const Locatar&l)=0;

    virtual void modify_Locatar(const Locatar&l,const string& new_name)=0;

    virtual const vector<Locatar>& getall()=0;

    virtual void deleteLocatar(int pozition)=0;

    virtual const Locatar& findNr(const int nr)=0;

    virtual int get_position(const Locatar&l)=0;

    virtual const Locatar& position_find(int positon)=0;

    virtual int findNrbyObject(const Locatar&L)=0;

};
class Repo: public AbsRepo{
    private:
        vector<Locatar> lista;
    public:
        Repo()=default;

        Repo(const Repo& ot)=delete; //nu lasam sa facem copie de repository

        void addLocatar(const Locatar& l) override;


        Locatar & findLocatar(const string& nume, int nr)override;

        bool is_in(const Locatar&l)override;

        void modify_Locatar(const Locatar&l, const string& new_name)override;

        const vector<Locatar>& getall() override;

        void deleteLocatar(int pozition) override;

        const Locatar& findNr(const int nr) override;

        int get_position(const Locatar&l) override;

        int findNrbyObject(const Locatar&L) override;

        const Locatar& position_find(int positon) override;
};

class RepoDictionary: public AbsRepo{
private:
    std::map<int,Locatar> dictionar_locatari;
    double probabilitate;

    void random() const;

public:
    RepoDictionary()=default;

    explicit RepoDictionary(double chance);

    RepoDictionary(const RepoDictionary&ot)=delete;
    void addLocatar(const Locatar& l) override;

    void deleteLocatar(int pozition) override;

};
#endif //LAB6_7_REPOLOCATARI_H
