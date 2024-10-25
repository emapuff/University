/*
Un client trimite unui server un sir de caractere si doua numere (fie acestea s, i, l). 
Serverul va returna clientului subsirul de lungime l a lui s care incepe la pozitia i.
*/
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>

int isNumber(char c){
    if( strchr("1234567890",c)!=NULL)
        return 1;
    return 0;
}

int main() {
    printf("CERINTA: subsirul unui sir dat \n");
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

    
    if (connect(c, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Eroare la conectare la server \n");
        return 1;
    }


    printf("Introduceti sirul de caractere: \n");
    fgets(a, 101, stdin);
    a[strcspn(a, "\n")] = '\0'; 

    int optiune = 7;
    optiune = htons(optiune);
    send(c, &optiune, sizeof(optiune), 0);  
   
    int lungime = strlen(a);
    int lungime_network = htons(lungime); 
    send(c, &lungime_network, sizeof(lungime_network), 0); 

   
    send(c, a, lungime, 0); 

    int i, j;
    printf("Introduceti prima pozitie: \n");
	
    if (scanf("%d", &i) != 1) {  
        printf("\033[31mEROARE: date invalide\n\033[0m");
        goto jump_here;
    }
	i = htons(i);
    send(c, &i, sizeof(i), 0);

    
    printf("Introduceti lungimea subșirului: \033[0m\n");
    if (scanf("%d", &j) != 1) {  
        printf("\033[31mEROARE: date invalide\n");
        goto jump_here;
    }
	j=htons(j);
    send(c, &j, sizeof(j), 0); 


    int len = 0;
    char v[101];
    recv(c, &len, sizeof(len), 0); // Primim lungimea subșirului
    len = ntohs(len);

	printf("Lungimea este: %d\n",len);
    // Primirea subșirului
    recv(c, v, len, 0); // Primim subșirul de la server


    printf("Subsirul este: %s\n", v);

	jump_here:
    close(c); 
    return 0;
}

