#include <iostream>
#include <fstream>
#include <queue>

using namespace std;
ifstream f("graf.txt");
ifstream f4("graf4.txt");
ifstream f2("graf2.txt");

void citire_muchii(int l[100][100], int &n)
{
    f>>n;
    int i,j;
    while(f>>i>>j)
    {
        l[i][j]=1;
    }
}

void moore(int l[100][100],int lungime[100], int n, int nod)
{
    int i,x,y;
    for(i=1;i<=n;i++)
    {
        lungime[i]=10000;
    }
    lungime[nod]=0;
    queue<int>coada;
    coada.push(nod);
    while(!coada.empty())
    {
        x=coada.front();
        for(i=1;i<=n;i++)
            if(l[x][i]==1 && lungime[i]>lungime[x]+1)
            {
                lungime[i]=lungime[x]+1;
                coada.push(i);
            }
        coada.pop();
    }

}

void cerinta_1()
{
    int l[100][100],n,lungime[100], nod;
    citire_muchii(l,n);
    cout<<"Introduceti nodul de unde sa se porneasca: ";
    cin>> nod;
    moore(l,lungime,n,nod);
    for(int i=1;i<=n;i++)
        if(lungime[i]==10000)
        {
            cout<<"Nu exista lant intre nodul "<<i<<" si "<<nod<<'\n';
        }
        else
        {
            cout<<"Lungimea celui mai scurt lant e de la "<<nod<< " la "<<i<<" este de "<< lungime[i]<<'\n';
        }
}

void citire_neordonat(int l[100][100],int &n)
{
    int i,j;
    f4>>n;
    while(f4>>i>>j)
    {
        l[i][j]=1;
        l[j][i]=1;
    }
}
void bfs(int nod, int l[100][100],int n)
{
    int viz[100]={0},x;
    queue<int>coada;
    coada.push(nod);
    viz[nod]=1;
    while(!coada.empty())
    {
        x=coada.front();
        for(int i=1;i<=n;i++)
            if(l[x][i]==1 && viz[i]==0)
            {
                viz[i]=viz[x]+1;
                coada.push(i);
            }
        coada.pop();
    }
    for(int i=1;i<=n;i++)
    {
        if(viz[i]!=0&&i!=nod)
        {
            cout<<i<<"de distanta: "<<viz[i]-1<<'\n';
        }
    }
}

void cerinta_4()
{
    int n,l[100][100];
    for(int i=1;i<100;i++)
        for(int j=1;j<100;j++)
            l[i][j]=l[j][i]=0;

    citire_neordonat(l,n);
    int nod;
    cout<<"Introduceti nodul de unde sa se porneasca: ";
    cin>>nod;
    bfs(nod,l,n);
}

void cerinta_2()
{
    int i,j,inchidere[100][100]={0},n,x,y,frecventa,lista[100][100],lungime[100];
    f2>>n;
    while(f2>>x>>y)
    {
        lista[x][y]=1;
        frecventa=lista[x][1];
        lista[x][frecventa+1]=y;
    }

    for(int i=1;i<=n;i++) {
        moore(lista, lungime, n, i);
        for (j = 1; j <= n; j++)
            if (lungime[j] != 10000 && lungime[j] != 0) {
                inchidere[i][j] = 1;
            }
    }
    cout<<"\nInchiderea tranzitiva a grafului dat este:\n";
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            cout<<inchidere[i][j]<<" ";
        }
        cout<<"\n";
    }
}

int main() {
    int i;
    cout<<"Introduceti nr cerintei: ";
    cin>>i;
    if(i==1)
        cerinta_1(); //moore
    else if (i==2)
        cerinta_2(); //inchidere tranzitiva
    else
        cerinta_4();
    return 0;
}
