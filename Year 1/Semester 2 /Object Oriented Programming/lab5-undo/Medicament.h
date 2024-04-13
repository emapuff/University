#ifndef LAB2_DINAMIC_MEDICAMENT_H
#define LAB2_DINAMIC_MEDICAMENT_H

typedef struct {
    int cod;
    char* nume;
    int concentratie;
    int cantitate;
}Medicament;

/*
 * Creeaza o entitate de tipul Medicament
 * param cod: codul entitatii (int)
 * param nume: numele entitatii (char)
 * param concentratie: concentratia entitatii (int)
 * param cantitate: cantitatea (int)
 * return: Medicament
 */
Medicament* creeazaMedicament(int cod, char *nume, int concentratie, int cantitate);

/*
 Valideaza o entitate de tipul Medicament
 param: m (struct)
 return: 1 - daca entitatea este valida
         0 - daca entitatea nu este valida
 */
int validatorMedicament(Medicament m);

/*
 Sterge elementele entitatii de tip Medicament
 param: m (struct)
 */
void distrugeMedicament(Medicament *m);

Medicament* copiazaMedicament(Medicament* m);

#endif //LAB2_DINAMIC_MEDICAMENT_H
