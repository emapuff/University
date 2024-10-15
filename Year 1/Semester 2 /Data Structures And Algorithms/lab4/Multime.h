#pragma once
#define CAPACITATE 4
#define NULL_TELEM -1
typedef int TElem;

class IteratorMultime;



class Multime {
	friend class IteratorMultime;

    private:
		int cp=CAPACITATE;
        TElem *e;
        int *urm;
        int *pred;
        int prim;
        int PrimLiber;
        int aloca();
        void dealoca(int i);
        int creeazNod(TElem elem);

    public:
 		//constructorul implicit
		Multime();

         void redimention();

		//adauga un element in multime
		//returneaza adevarat daca elementul a fost adaugat (nu exista deja in multime)
		bool adauga(TElem e);

		//sterge un element din multime
		//returneaza adevarat daca elementul a existat si a fost sters
		bool sterge(TElem e);

		//verifica daca un element se afla in multime
		bool cauta(TElem elem) const;


		//intoarce numarul de elemente din multime;
		int dim() const;

		//verifica daca multimea e vida;
		bool vida() const;

		//returneaza un iterator pe multime
		IteratorMultime iterator() const;

        int diferențaMaxMin() const;

    // destructorul multimii
		~Multime();
};




