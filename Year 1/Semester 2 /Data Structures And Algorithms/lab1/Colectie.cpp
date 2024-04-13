#include "Colectie.h"
#include "IteratorColectie.h"
#include <exception>
#include <iostream>

using namespace std;

void Colectie::redim(TElem elem) {
    /*
     * Best case: nu intra in nicin if si atunci avem teta(1)
     * Worst case: intra pe unul dintre cazuri si se mareste capacitatea O(n), n=capacitatea vectorului de frecventa
     * Average case: identic cu worst case
     * => complexitate O(n)
     */
    if(elem< this->remap) //trebuie sa remapam
    {
        this->capacity=this->pozitive-elem+1;
        TElem *nou=new TElem [this->capacity];
        int index=0;

        for(int j=0;j<this->capacity;j++) //aloc spatiu nou
            if( j< this->capacity - this->pozitive +this->remap-1)
                nou[j]=0;
            else  //copiez elementele vechi pe pozitiile noi
            {
                nou[j]=this->e[j - this->remap + elem];
                index++;
            }

            this->remap=elem;
            delete [] this->e;
            this->e=nou;
    }

    if(elem>this->pozitive) //trebuie sa redimensionam vectorul
    {
        this->capacity = elem - this->remap + 1;
        TElem *nou = new TElem[this->capacity];
        // Copy existing elements to new array
        for (int j = 0; j < this->capacity; j++)
            if (j <= this->pozitive + (-1) * this->remap)
                nou[j] = this->e[j];
            else
                nou[j] = 0;
        this->pozitive = elem;
        delete[] this->e;
        this->e = nou;
    }
}


Colectie::Colectie() {
    this->capacity=10;
    e = new TElem [100];
    this->pozitive=9;
    this->n=0;
    this->remap=0;
    for(int i=0;i<this->capacity; i++) this->e[i]=0;
}


void Colectie::adauga(TElem elem) {
    /*
     * Best case: cand apelam functia redim aceasta are complexitate teta(1) => complexitatea totala va fi O(1)
     * Worst case = Average case: functia redim are complexitatea O(n) => complexitatea va fi O(n)
     * => complexitatea va fi O(n)
     */
   this->redim(elem);
   this->e[elem-remap]++;
   this->n++;
}


bool Colectie::sterge(TElem elem) {
    /*
     * BC= WC = AC complexitate teta(1)
     */
	if(cauta(elem)) //daca il gasim, il stergem
    {
      this->e[elem-remap]--;
      this->n--;
      return true;
    }
	return false;
}


bool Colectie::cauta(TElem elem) const {
    /*
     * BC= WC = AC complexitate teta(1)
     */
    if(vida()) return false;
    if(elem>this->pozitive || elem < this->remap) return false; //elementul nu apartine intervalului
    if(this->e[elem-remap]==0) return false; //nu am nicio aparitie a elementului
    return true;
}

int Colectie::nrAparitii(TElem elem) const {
    /*
     * BC= WC = AC complexitate teta(1)
     */
    if(cauta(elem))
        return this->e[elem-remap];
	return 0;
}


int Colectie::dim() const {
    /*
     * BC= WC = AC complexitate teta(1)
     */
	return this->n;
}


bool Colectie::vida() const {
    /*
     * BC= WC = AC Complexitate teta(1)
     */
	if (this->n==0) return true;
    return false;
}

IteratorColectie Colectie::iterator() const {
    /*
     * complexitatea teta(1)
     */
	return  IteratorColectie(*this);
}


Colectie::~Colectie() {
    /*
     *  BC= WC = AC Complexitate teta(1)
     */
	delete[] e;
}

int Colectie::stergereNrAparitii(TElem elem) {
    /*
     * BC= WC = AC => teta(1)
     * sterge toate aparitiile unui element si returneaza nr de elemente eliminate
     */
    int numar= nrAparitii(elem);
    if(numar!=0)
    {
        int i=0;
        for(i=0; i<numar; i++)
            sterge(elem);
        return numar;
    }
    else return 0;


}

