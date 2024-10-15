#pragma once

#include <vector>
#include <utility>
#define INIT (-10008)
#define MAX 610543
using namespace std;

typedef int TCheie;
typedef int TValoare;

typedef std::pair<TCheie, TValoare> TElem;

class IteratorMD;

class MD {
    friend class IteratorMD;

private:
    int n;
    int m;
    TElem* e;
    int* urm;
    int primLiber;

    void ActualizarePrimLiber();
    int dispersue(TCheie c) const;

public:
    MD(); // Constructor
    ~MD(); // Destructor

    void adauga(TCheie c, TValoare v); // Add a key-value pair to the multimap
    bool sterge(TCheie c, TValoare v); // Remove a key-value pair from the multimap
    vector<TValoare> cauta(TCheie c) const; // Search for values associated with a key
    int dim() const; // Return the number of key-value pairs in the multimap
    bool vid() const; // Check if the multimap is empty
    IteratorMD iterator() const; // Get an iterator for the multimap
    void goleste();
};
