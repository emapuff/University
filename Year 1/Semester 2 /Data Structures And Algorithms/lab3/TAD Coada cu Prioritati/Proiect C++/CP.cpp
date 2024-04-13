
#include "CP.h"
#include <exception>
#include <stdio.h>
#include <stdexcept>

using namespace std;


CP::CP(Relatie r) {
	/*
	 * teta(1)
	 */
    prim= nullptr;
    rel=r;
}


void CP::adauga(TElem e, TPrioritate p) {

    /*
     * Best case: teta(1) -> adaugam fix la inceput
     * Worst case: O(n) -> adaugam la final
     * Complexitate finala: O(n), unde n este nr elementelor din coada
     */
    Element elem(e,p);
    Node * newNode=new Node(elem); //aloc spatiu pentru un nou element

    if(!prim|| rel(p, prim->data.second)) //lista este vida sau noul element are prioritate mai mare
    {
        newNode->next=prim;
        prim=newNode;
    }
    else
    {   //caut locul potrivit din lista
        Node *curent=prim;
        while(curent->next && rel(curent->next->data.second,p))
        {
            curent=curent->next;
        }
        newNode->next=curent->next;
        curent->next=newNode;
    }

}

//arunca exceptie daca coada e vida
Element CP::element() const {

	/*
	 * complexitate: teta(1)
	 */
    if(vida())
    {
       // trebuie sa aruncam o exceptie
        throw std::out_of_range("Priority queue is empty");
    }
    return prim->data;
}

Element CP::sterge() {
	 /*
	  * complexitate: teta(1)
	  */
	if(vida())
    {
        throw std::out_of_range("Priority queue is empty");
    }
    Element elem=prim->data;
    Node *aux=prim;
    prim=prim->next;
    delete aux;
    return elem;
}

bool CP::vida() const {
	/*
	 * complexitatea: teta(1)
	 */
    if(prim== nullptr)
	    return true;
    else return false;
}


CP::~CP() {
	/*
	 * complexitate: teta(n) unde n este nr de elemente din lista
	 */
    while(prim)
    {
        Node* elem=prim;
        prim=prim->next;
        delete elem;
    }
}

void CP::adauga_lista(const CP& coada) {
    /*
     * complexitate:
     * avem teta(n) din parcurgerea coadei primite in sine, apoi avem O(n) din adaugare
     * => complexitate teta(m)*O(n)=O(n*m)
     */
    Node* curent=coada.prim;
    while(curent)
    {
        adauga(curent->data.first,curent->data.second);
        curent=curent->next;
    }
};

