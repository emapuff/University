#include <stdio.h>
#include <stdlib.h>
#include "service.h"
#include "teste.h"
#include "validator.h"
#include "lista.h"

void print_meniu()
{
    printf("Meniu\n");
    printf("1.Adaugare imobil\n");
    printf("2.Actualizare oferta\n");
    printf("3.Stergere oferta\n");
    printf("4.Vizualizare oferta ordonate dupa pret si tip dat\n"); //aici trebuie crescator si descrescator
    printf("5.Vizualizare oferta dupa criteriu\n");
    printf("6. Printati lista\n");
    printf("7.Exit\n");
    printf("Introduceti nr optiunii:");
}

void printare_lista(ListaMea *list)
{
    if(list->lungime==0)
        printf("\nOOPS: nu exista elemente in lista!\n");
    else
        for(int i=0;i<list->lungime;i++)
        {
            printf("%d. Tip: %s Suprafata: %.2f Pret: %.2f Adresa: str. %s, nr. %d, %s \n", i, list->lista[i]->tip,list->lista[i]->suprafata,list->lista[i]->pret,list->lista[i]->adresa->strada,list->lista[i]->adresa->numar,list->lista[i]->adresa->oras );
        }
}
int printare_erori(int errors[10])
{
    int ok=1;
    if(errors[0]) printf("\nERROR: tip invalid de imobil\n"),ok=0;
    if(errors[1]) printf("\n ERROR: nr adresei nu poate fi negativ \n"),ok=0;
    if(errors[2]) printf("\n ERROR: suprafata nu poate fi negaiva!\n"),ok=0;
    if(errors[3]) printf("\n ERROR pretul nu poate fi negativ"),ok=0;
    return ok;
}

void optiune_1(ListaMea *list)
{
    char tip_nou[20],strada_nou[20],oras_nou[20];
    float suprafata_noua, pret_nou;
    int numar_nou,errors[10]={0};
    printf("tipul imobilului: \n");
    scanf(" %s",tip_nou);
    printf("suprafata: \n");
    scanf(" %f",&suprafata_noua);
    printf("pretul: \n");
    scanf(" %f",&pret_nou);
    printf("numarul adresei: \n");
    scanf(" %d",&numar_nou);
    printf("strada adresei: \n");
    scanf(" %s",strada_nou);
    printf("orasul adresei: \n");
    scanf(" %s",oras_nou);
    Imobil *new_imobil= creaza_imobil(tip_nou,numar_nou,strada_nou,oras_nou,suprafata_noua,pret_nou);
    validare_imobil_nou(new_imobil,errors);
    int ok= printare_erori(errors);
    if(ok)
    {
        adauga_lista(list,new_imobil);
    }
}

void option_2(ListaMea *list)
{
    /*
     * Actualizarea pretului unui imobil, partea de ui
     * pre: list de tip ListaMea
     * post: -
     */
    float new_price;
    int indice;
    printare_lista(list);
    printf("Introduceti pretul nou: \n");
    scanf("%f",&new_price);
    printf("Introduceti indicele imobilului de actualizat: \n");
    scanf("%d",&indice);
    if(indice<0 || indice >= list->lungime)
        printf("ERROR: indice invalid!");
    else
    {
        actualizare_oferta(list, indice, new_price);
    }

}

void optiune_3(ListaMea *list)
{
    /*
     * Stergerea unei oferte, partea de UI
     */
    int indice;
    printare_lista(list);
    printf("Introduceti indicele imobilului de sters: \n");
    scanf("%d",&indice);
    if(indice<0 || indice >= list->lungime)
        printf("ERROR: indice invalid!");
    else
    {
        stergere_oferta(list, indice);
    }

}

void option_4(ListaMea *list)
{
    /*
     * Vizualizare oferte ordonate dupa pret si in caz de egalitate dupa tip
     */
    char c;
    printf("Introduceti d pentru descrescator si c pentru crescator \n");
    scanf("%c",&c);
     if(c!='c'&&c!='d') printf("\nERROR: optiune invalida!\n");
     else
        {
            if (c=='c') ordonare_cresc(list);
            else ordonare_descrescator(list);
            printare_lista(list);
        }


}

void option_5(ListaMea *list)
{
    /*
     * Vizualizare oferta dupa criteriu tip, suprafata sau pret
     */
    char c;
    printf("Introduceti t pentru tip, s pentru suprafata si p pentru pret\n");
    scanf("%c",&c);
    if(c!='p'&&c!='s'&&c!='t')
    {
        printf("\nERROR: cerinta invalida\n");
    }
    else
    {
        if(c=='t') //afisam imobilurile de un anumit tip
        {
            char tip_dat[50];
            printf("Introduceti tipul solicitat: \n");
            scanf("%s", tip_dat);
            if(strcmp("teren",tip_dat)!=0&&strcmp("casa",tip_dat)!=0&&strcmp("apartament",tip_dat)!=0)
            {
                printf("\nERROR: tip invalid\n");
            }
            else
            {
                ListaMea new_list;
                filtrare_tip(*list,tip_dat,&new_list);
                printare_lista(&new_list);
                destroy(&new_list);

            }
        }

        else if(c=='s') //afisam imobilurile cu suprafata mai mare decat cea introdus
        {
            float suprafata_noua;
            printf("Introduceti valoarea minima pe care trebuie sa o aiba un imobil: \n");
            scanf("%f",&suprafata_noua);
            if(suprafata_noua<0)
            {
                printf("\nERROR: Suprafata nu poate fi negativa!\n");
            }
            else
            {
                ListaMea new_list;
                filtrare_suprafata(*list,suprafata_noua,&new_list);
                printare_lista(&new_list);
                destroy(&new_list);
            }
        }

        else //afisam imobilurile cu un pret mai mic sau egal cu valoarea introdusa de la tastatura
        {
            float pret_nou;
            printf("Introduceti pretul maxim pe care il poate avea un imobil: \n ");
            scanf("%f", &pret_nou);
            if(pret_nou<0)
            {
                printf("\n ERROR: pretul nu poate fi negativ \n");
            }
            else
            {
                ListaMea new_list;
                filtrare_pret(*list,pret_nou,&new_list);
                printare_lista(&new_list);
                destroy(&new_list);
            }
        }
    }
}

void rulare_meniu()
{
    ListaMea list=creaza_vid();
    int ok=1;
    char option[10], *end;
    long option_number;
    while(ok)
    {
        print_meniu();

        scanf("%s",option);
        option_number = strtol(option,&end,10);
        //if(validare_optiune((char)option)-'0')
        {
            if(option_number==7) ok=0;
            else if(option_number==6) printare_lista(&list);
            else if(option_number==1) optiune_1(&list);
            else if(option_number==2) option_2(&list);
            else if(option_number==3) optiune_3(&list);
            else if(option_number==4) option_4(&list);
            else option_5(&list);
        }
//       else
//        {
//            printf("\nERROR: optiune invalida!\n");
//        }
    }
    destroy(&list);
}

int main() {
    run_all_test();
    rulare_meniu();
    return 0;
}
