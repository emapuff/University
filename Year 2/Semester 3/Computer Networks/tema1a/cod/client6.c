/*
Un client trimite unui server un sir de caractere si un caracter. 
Serverul va returna clientului toate pozitiile pe care caracterul primit se regaseste in sir.
*/
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    printf("CERINTA: aparitiile unui caracter in sir \n");
    int c;
    char a[101];
    struct sockaddr_in server;

    // Crearea socketului client
    c = socket(AF_INET, SOCK_STREAM, 0);
    if (c < 0) {
        printf("Eroare la crearea socketului client \n");
        return 1;
    }

    // Configurarea adresei serverului
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Conectarea la server
    if (connect(c, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Eroare la conectare la server \n");
        return 1;
    }

    // Introducerea șirului de caractere
    printf("Introduceti sirul de caractere: \n");
    fgets(a, 101, stdin);
    a[strcspn(a, "\n")] = '\0';  

    int optiune = 6;
    optiune = htons(optiune);
    send(c, &optiune, sizeof(optiune), 0);  
   
    int lungime = strlen(a);
    int lungime_network = htons(lungime); 
    send(c, &lungime_network, sizeof(lungime_network), 0); 
    send(c, a, lungime, 0); 

    // Introducerea caracterului de căutat
    char caracter;
    printf("Introduceti caracterul: \n");
    scanf(" %c", &caracter); 
    send(c, &caracter, sizeof(caracter), 0);

   
    int len = 0, v[101];
    recv(c, &len, sizeof(len), 0); // Primim numărul de poziții
    len = ntohs(len);

    // Primirea vectorului de poziții
    recv(c, v, len * sizeof(int), 0);

    for (int i = 0; i < len; i++) {
        v[i] = ntohs(v[i]); 
    }
    printf("Pozitii gasite: %d\n",len);
    
    printf("Pozitiile aparitiilor sunt: \n");
    for (int i = 0; i < len; i++) {
        printf("%d\n", v[i]);
    }

    close(c); // Închidem conexiunea
    return 0;
}

