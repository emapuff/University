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

int v[101], k = 0;

int parser(char a[101]) {
    int numar = 0;
    int inNumar = 0;  
    for (int i = 0; i < strlen(a); i++) {
        if (a[i] != ' ') {  // e caracter
            if (isNumber(a[i]) == 1) {
                numar = numar * 10 + a[i] - '0';
                inNumar = 1;
            } else {
                printf("\033[31mEroare!! - date incorecte\n\033[0m");
                return 1;
            }
        } else if (inNumar) {  // am terminat un număr
            v[k++] = numar;
            numar = 0;
            inNumar = 0;
        }
    }
    if (inNumar) {  // ultimul număr (dacă nu s-a încheiat cu spațiu)
        v[k++] = numar;
    }
    return 0;
}

int main() {
    int c;
    char a[101];
    struct sockaddr_in server;
    c = socket(AF_INET, SOCK_STREAM, 0);
    if (c < 0) {
        printf("\033[31mEroare la crearea socketului client\033[0m \n");
        return 1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(c, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("\033[31mEroare la conectare la server\033[0m \n");
        return 1;
    }

    

    printf("Introduceti sirul de numere: \n");
    fgets(a, 101, stdin);
    a[strcspn(a, "\n")] = '\0';  // eliminăm newline-ul de la final

    if (parser(a) == 1) {
        close(c);
        return 0;
    }

	int optiune = 1;
    optiune = htons(optiune);
    send(c, &optiune, sizeof(optiune), 0);  // trimitem optiunea
    int lungime = htons(k);  // trimitem lungimea vectorului
    send(c, &lungime, sizeof(int), 0);

    for (int i = 0; i < k; i++) {
        int nr = htons(v[i]);  // convertim fiecare numar in format de rețea
        send(c, &nr, sizeof(int), 0);
    }

    int sum = 0;
    recv(c, &sum, sizeof(int), 0);
    sum = ntohs(sum);

    printf("Suma numerelor este: %d\n", sum);
    close(c);
    return 0;
}
