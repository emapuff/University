#include <fstream>
#include <vector>
#include <queue>
#include <bitset>
#include <cmath>
#include <iostream>
#define INF 1000
using namespace std;

ifstream fin("citire.in");

const int Max = 5e4 + 1;
const int Inf = 1 << 30;

int n, m; //n=nr de noduri, m=nr de muchii

float a[100][100];
float costuri[100];
int vizitat[100];

int cord[101][101];
void read()
{
    int x, y;
    int xc,yc;
    float z;
    fin >> n >> m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
             a[i][j]=a[j][i]=INF;

    for(int i=1;i<=n;i++) //parcurgem coordonatele
    {
        fin>>xc>>yc;
        cord[i][1]=xc;
        cord[i][2]=yc;
    }

    for(int i=1;i<=n;i++)
        cout<<cord[i][1]<<" "<<cord[i][2]<<'\n';

    for (int i = 1; i <= m; ++i)
    {
        fin >> x >> y ; //exista muchie intre x si y, trebuie sa calculam distanta
        z= sqrt((cord[x][1]-cord[y][1])*(cord[x][1]-cord[y][1])+(cord[x][2]-cord[y][2])*(cord[x][2]-cord[y][2]));
        cout<<z<<'\n';
        a[x][y]=z;
        a[y][x]=z;
    }
}

void Bellman_Ford(int nod) {
    int x;
    for (int i = 1; i <= n; i++)
        costuri[i] = INF, vizitat[i] = 0;

    costuri[nod] = 0;
    vizitat[nod] = 1;
    std::queue<int> c;

    c.push(nod);
    while (!c.empty()) {
        x = c.front();
        cout<<x<<'\n';
        for (int i = 1; i <= n; i++)
            if (a[x][i] < INF  && costuri[i] > costuri[x] + a[x][i]) {
                costuri[i] = costuri[x] + a[x][i];
                c.push(i);
                vizitat[i] = 1;
            }
        c.pop();
        vizitat[x] = 0;
    }


}

int main()
{
    read();
    int start,finish;
    cout<<"Introduceti numarul de inceput de la tastatura: ";
    cin>>start;
    cout<<"Introduceti nr de final de la tastratura: ";
    cin>>finish;
    Bellman_Ford(start);
    cout<<"Cel mai mic drum dintre nodul "<<start<<" si nodul "<<finish<<"este : "<<costuri[finish];

    return 0;
}
