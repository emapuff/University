#include <exception>
#include "IteratorMultime.h"
#include "Multime.h"


IteratorMultime::IteratorMultime(const Multime& m) : multime(m){
	/* teta(1) */
    curent=m.prim;
}


void IteratorMultime::prim() {
	/* teta(1)*/
    curent=multime.prim;
}


void IteratorMultime::urmator() {
	/* teta(1) */
    if (!valid()) { throw std::exception(); }

    curent=multime.urm[curent];
}


TElem IteratorMultime::element() const {
	/* teta(1) */
	return multime.e[curent];
}

bool IteratorMultime::valid() const {
	/* teta(1)*/
	return curent!=-1;
}
