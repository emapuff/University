//
// Created by emato on 30.05.2024.
//

#include <exception>
#include "Iterator.h"

//theta(1)
void IteratorMatrice::first() {
    index=0;
}


//theta(1)
void IteratorMatrice::next() {
    if(!valid())
        throw std::exception();
    index++;
}


//theta(1)
bool IteratorMatrice::valid() const {
    return index>=0&&index<=m.nrColoane();
}

//O(log h)
TElem IteratorMatrice::getCurent() const {
    if(!valid())
        throw std::exception();
    return m.element(linie,index);
}
