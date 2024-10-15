//
// Created by emato on 22.04.2024.
//

#include "FileRepo.h"
#include "fstream"

using std::ifstream;
using std::ofstream;


FileRepository::FileRepository(const string &name) {
    this->fileName=name;
    loadRepo();
}


void FileRepository::loadRepo() {
    ifstream file(fileName);
    Locatar locatar_fisier{};
    Locatar lg{};
    while(file >> reinterpret_cast<bool &>(locatar_fisier))
    {
        if(lg!= locatar_fisier)
            addLocatar(locatar_fisier);
        lg=locatar_fisier;
    }
}

void FileRepository::saveRepo() {
    ofstream ofile(fileName);
    if(!ofile.is_open())
        throw RepoException("File does not exist\n");

    for(const auto & l:this->getall())
    {
        ofile << l;
    }
    ofile.close();
}

void FileRepository::emptyFile() {
    ofstream oflie(fileName);
    oflie<<"";
    oflie.close();
}

FileRepository::~FileRepository()=default;

