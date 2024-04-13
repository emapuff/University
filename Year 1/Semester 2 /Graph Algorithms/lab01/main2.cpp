#include <iostream>
#include <fstream>

using namespace std;

ifstream f("../citire.txt");
int a[101][101],n;
int d[101][101];

int main()
{
    f>>n;
    int i,j;
    while(f>>i>>j)
    {
        a[i][j]=1;
        a[j][i]=1;
        a[i][0]++;
        a[j][0]++;
    }

    cout<<"Noduri izolate: ";
    for(i=1;i<=n;i++)
    {
        bool ok=1;
        for(j=1;j<=n;j++)
            if(a[i][j]!=0){
                ok=0;
                break;
            }

        if(ok)
            cout<<i<<" ";
    }
    cout<<'\n';

    int equ=a[1][0];
    bool ok1=1;
    for(i=2;i<=n;i++)
        if(equ!=a[i][0])
        {
            ok1=0;
            break;
        }

    if(ok1)
        cout<<"Graful e regulat"<<'\n';
    else
        cout<<"Graful nu e regulat"<<'\n';


    for( i=1;i<=n;i++)
      for( j=1;j<=n;j++)
          if(i==j) d[i][j]=0;
          else
              if(a[i][j]!=0)
                  d[i][j]=1;
              else
                  d[i][j]=10000001;



    for(int k=1; k<=n; k++)
        for(i=1; i<=n; i++)
            for(j=1; j<=n; j++)
            {
                if(d[i][k]+d[k][j]<d[i][j] && d[i][k]!=0 && d[k][j]!=0)
                    d[i][j]=d[i][k]+d[k][j];
            }


    for(i=1;i<=n;i++)



    return 0;
}