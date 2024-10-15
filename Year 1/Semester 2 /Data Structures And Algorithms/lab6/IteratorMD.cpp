#include "IteratorMD.h"
#include "MD.h"

using namespace std;

IteratorMD::IteratorMD(const MD& _md): md(_md) {
	/* O(m) */
    curent=0;
    while (curent < md.m && md.e[curent].first == INIT) {
        curent++;
    }
}

TElem IteratorMD::element() const{
	/* theta(1) */
    return md.e[curent];
}

bool IteratorMD::valid() const {
    /*
     * theta(1)
     */
    return curent < md.m;
}

void IteratorMD::urmator() {
    //O(m)
    if(valid()) {
        curent++;
        while (curent < md.m && md.e[curent].first == INIT) {
            curent++;
        }
    }

}
void IteratorMD::prim() {
	// O(m)
    curent = 0;
    while (curent < md.m && md.e[curent].first == INIT) {
        curent++;
    }
}

