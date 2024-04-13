#include "IteratorColectie.h"
#include "Colectie.h"


IteratorColectie::IteratorColectie(const Colectie& c): col(c) {
    /*
     * BC: O(1)
     * WC = AC : O(n), n = capacitatea colectiei
     * => complexitatea O(n)
     */
    this->prim();
}

void IteratorColectie::prim() {
	/*
	 * BC: O(1), nu se executa while ul
	 * WC = AC: parcurgem tot sirul => O(n), n - capacitatea
	 * => complexitate O(n)
	 * */
    index=-1;
    frecventa=0;
    while(frecventa==0 && index < col.capacity)
    {
        index++;
        frecventa=col.e[index];
    }
}


void IteratorColectie::urmator() {
    /*
     * Bc: O(1), nu e valid sau indexul e mai mare ca si capacitatea
     * WC=Ac: O(n), indexul creste pana la capacitate
     * => complexitatea O(n)
     */
	frecventa--;
    if(!valid())
    {
        if(index<col.capacity-1)
        {
            index++;
            while(index < col.capacity && col.e[index]==0)
                index++;

            if(index < col.capacity) frecventa=col.e[index];
            else frecventa=0;
        }
    }
}


bool IteratorColectie::valid() const {
    /*
     * complexitate teta(1)
     */
    if(col.vida()) return false;
    if(index>=col.capacity) return false;
    if(index < col.capacity && frecventa> 0) return true;
	return false;
}



TElem IteratorColectie::element() const {
    /*
     * complexitate teta(1)
     */
	if(valid()) return index+col.remap;
	return -1;
}
