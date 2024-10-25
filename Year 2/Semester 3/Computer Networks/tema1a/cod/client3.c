#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>

/*
Un client trimite unui server un sir de caractere. 
Serverul va returna clientului acest sir oglindit (caracterele sirului in ordine inversa).

*/

int main() {
	printf("CERINTA: sir oglindit \n");
    int c;
    char a[101],final[101];
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

    

    printf("Introduceti sirul de numere: \n");
    fgets(a, 101, stdin);
    a[strcspn(a, "\n")] = '\0';  // eliminăm newline-ul de la final


	int optiune = 3;
    optiune = htons(optiune);
    send(c, &optiune, sizeof(optiune), 0);  // trimitem optiunea
	int lungime = strlen(a);
    lungime = htons(lungime);  // trimitem lungimea vectorului
    send(c, &lungime, sizeof(int), 0);

    send(c,a,lungime,0);

    recv(c,final,sizeof(final),0);
    printf("am primit final");
    //final=ntohs(final);
    printf("Sirul nou este: %s\n",final);
    close(c);
    return 0;
}
