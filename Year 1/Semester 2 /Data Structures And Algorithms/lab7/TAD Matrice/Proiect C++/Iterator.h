//
// Created by emato on 30.05.2024.
//

#ifndef LAB7_ITERATOR_H
#define LAB7_ITERATOR_H
#include "Matrice.h"
class IteratorMatrice{
    friend class Matrice;
private:
    int linie;
    int index;
    const Matrice &m;
public:
    IteratorMatrice(const Matrice&m, int linie): m(m), linie(linie), index(0) {};

    void first();

    void next();

    bool valid() const;

    TElem getCurent() const;
};
#endif //LAB7_ITERATOR_H
