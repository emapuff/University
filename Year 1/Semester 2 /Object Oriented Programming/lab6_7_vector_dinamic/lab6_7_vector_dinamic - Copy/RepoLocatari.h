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
#include "Locatari.h"
#include "vector_dinamic.h"
using std::string;
using std::ostream;
using std::vector;

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


class Repo{
    private:
        VectorDinamic<Locatar> lista;
    public:
        Repo()=default;

        Repo(const Repo& ot)=delete; //nu lasam sa facem copie de repository

        void addLocatar(const Locatar& l);


        const Locatar& findLocatar(const string& nume, int nr);

        bool is_in(const Locatar&l);

        void modify_Locatar(const Locatar&l,const string& new_name);

        VectorDinamic<Locatar> getall();

    void deleteLocatar(int pozition);
};
#endif //LAB6_7_REPOLOCATARI_H
