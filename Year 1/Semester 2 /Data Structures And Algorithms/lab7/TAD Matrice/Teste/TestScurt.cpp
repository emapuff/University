#include "TestScurt.h"
#include <assert.h>
#include "Matrice.h"
#include <iostream>
#include "Iterator.h"

using namespace std;

void testAll() { //apelam fiecare functie sa vedem daca exista
	Matrice m(4,4);
	assert(m.nrLinii() == 4);
	assert(m.nrColoane() == 4);
	//adaug niste elemente
	m.modifica(1,1,5);
	assert(m.element(1,1) == 5);
	m.modifica(1,1,6);
	assert(m.element(1,2) == NULL_TELEMENT);

    Matrice mtest(4,4);
    assert(mtest.nrLinii() == 4);
    assert(mtest.nrColoane() == 4);
    //adaug elemente
    mtest.modifica(1,0,1);
    mtest.modifica(1,2,2);
    IteratorMatrice i{mtest,1};
    assert(i.valid()==1);
    assert(i.getCurent() == 1);
    i.next();
    i.next();
    i.next();
    i.next();
    i.next();
    assert(i.valid()==0);

}
