//
// Created by emato on 22.04.2024.
//

#ifndef LAB6_7_FILEREPO_H
#define LAB6_7_FILEREPO_H
#include "RepoLocatari.h"

class FileRepository: public AbsRepo{
private:
    string fileName;
public:
    void loadRepo();
    void saveRepo();
    void emptyFile();
    void setPath(const string& name){
        this->fileName=name;
    }
    explicit FileRepository(const string& name);
    ~FileRepository();
};
#endif //LAB6_7_FILEREPO_H
