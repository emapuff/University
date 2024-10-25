#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>

/*
Un client trimite unui server un numar. 
serverul returneaza lista divizorilor. 

*/
int isNumber(char c){
    if( strchr("1234567890",c)!=NULL)
        return 1;
    return 0;
}

int main() {
	printf("CERINTA: sirul divizorilor numarului\n");
    int c;
    int v[101];
    struct sockaddr_in server;
    c = socket(AF_INET, SOCK_STREAM, 0);
    if (c < 0) {
        printf("Eroare la crearea socketului client \n");
        return 1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(c, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Eroare la conectare la server \n");
        return 1;
    }

    

    printf("Introduceti un numar: \n");
    int nr;
	if(scanf("%d",&nr)!=1)
	{
		printf("\033[31mEROARE: date invalide\033[0m");
		goto jumphere;
	}
	
	int optiune = 5;
    optiune = htons(optiune);
    send(c, &optiune, sizeof(optiune), 0);  // trimitem optiunea
	
	nr = htons(nr);
    send(c, &nr, sizeof(int), 0);

 

    int len = 0;
    recv(c, &len, sizeof(int), 0); //lungimea sirului
    len = ntohs(len);
    recv(c, v, len * sizeof(int), 0); 

	
	for(int i=0;i<len;i++)
		v[i] = ntohs(v[i]);
	
    printf("Divizorii sunt: \n");
	
	for(int i=0;i<len;i++)
		printf("%d\n",v[i]);
	
	jumphere:
    close(c);
    return 0;
}
