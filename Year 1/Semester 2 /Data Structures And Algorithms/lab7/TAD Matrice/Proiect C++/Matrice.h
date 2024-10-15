#pragma once

typedef int TElem;

#define Max_Size 300*300
#define NULL_TELEMENT 0

struct TMatrice{
    int linie,coloana;
    TElem valoare;
};

class IteratorMatrice;


class Matrice {

private:
	/* aici e reprezentarea */
    int radacina, primLiber;
    TMatrice *val;
    int  *Stanga,*Dreapta;
    int nr_linii, nr_coloane;
    int capacitate;

public:

	//constructor
	//se arunca exceptie daca nrLinii<=0 sau nrColoane<=0
	Matrice(int nrLinii, int nrColoane);

    void cauta(int i, int j, int poz, int& rez) const;

    void ActualizarePrimLiber();
	//destructor
	~Matrice(){
        delete[] Stanga;
        delete[] Dreapta;
        delete[] val;
    };

	//returnare element de pe o linie si o coloana
	//se arunca exceptie daca (i,j) nu e pozitie valida in Matrice
	//indicii se considera incepand de la 0
	TElem element(int i, int j) const;


	// returnare numar linii
	int nrLinii() const;

	// returnare numar coloane
	int nrColoane() const;


	// modificare element de pe o linie si o coloana si returnarea vechii valori
	// se arunca exceptie daca (i,j) nu e o pozitie valida in Matrice
	TElem modifica(int i, int j, TElem);

    void insert(int i, int j, TElem e, int& poz);

    IteratorMatrice iterator(int linia) const;

    void deleteElement(int poz);

};







