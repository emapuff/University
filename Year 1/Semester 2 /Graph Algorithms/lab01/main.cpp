#include <iostream>
#include <fstream>

using namespace std;

ifstream f("../citire.txt");

void printare(int m[101][101],int n)
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
            cout<<m[i][j]<<" ";
        cout<<'\n';
    }
}

int main()
{
    int n, i,j, matrice_adiacenta[101][101]={0},lista_adiacenta[101][101]={0},matrice_incidenta[101][101]={0};
    int poz=0;
    int m=0;
    f>>n;

    while(f>>i>>j)
    {
        m++;
        matrice_adiacenta[i][j]=1;
        matrice_adiacenta[j][i]=1;

        lista_adiacenta[i][0]++;
        lista_adiacenta[j][0]++;
        lista_adiacenta[i][lista_adiacenta[i][0]]=j;
        lista_adiacenta[j][lista_adiacenta[j][0]]=i;

        poz++;
        matrice_incidenta[i][poz]=1;
        matrice_incidenta[j][poz]=1;

    }

    cout<<"Matrice adiacenta: "<<'\n';
    printare(matrice_adiacenta,n);
    cout<<"\n"<<"Lista adiacenta: "<<"\n";

    for(i=1;i<=n;i++)
    {
        cout<<i<<": ";
        for(j=1;j<=n;j++)
            if(lista_adiacenta[i][j]!=0)
                cout<<lista_adiacenta[i][j]<<" ";
            else
                break;


        cout<<'\n';
    }

    cout<<"Matrice incidenta: "<<'\n';
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
            cout<<matrice_incidenta[i][j]<<" ";
        cout<<'\n';
    }

    return 0;
}