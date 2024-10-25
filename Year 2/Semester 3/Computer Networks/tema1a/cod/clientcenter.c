#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int isNumber(char c){
    if( strchr("1234567890",c)!=NULL)
        return 1;
    return 0;
}

int main() {
    char option[10001];
    
    while (1) {
        printf("\033[36m\n------Meniu--------\n");
		 printf("0. exit\n");
		  printf("1. suma numerelor \n");
		   printf("2. nr de caractere spatii dintr-un sir\n");
		    printf("3. sirul oglindit\n");
			 printf("4. interclasarea a doua siruri ordonate\n");
			  printf("5. divizorii unui numar\n");
			   printf("6. pozitiile unui caracter in alt sir\n");
			    printf("7. subsirul de lungime data, de pe o poz data \033[0m\n");
				printf("\033[35mInroduceti nr optiunii dorite: \033[0m");
        scanf("%s", option); 

		if(!isNumber(option[0])){
			printf("\033[31mEROARE: Optiune incorecta \033[0m");
			goto jump_here;
		}
        // Dacă utilizatorul introduce 0, ieșim din buclă
        if (option[0] == '0') {
            printf("Iesire din program...\n");
            break;
        }

        // Construim un șir pentru numele programului
        char program[10];
        snprintf(program, sizeof(program), "./client%c", option[0]);

        pid_t pid = fork();
        if (pid < 0) {
            perror("\033[31mEroare la fork \033[0m");
            return 1;
        }

        if (pid == 0) {
            // Procesul copil execută programul
            execlp(program, program, (char *)NULL);

            // Dacă execuția eșuează, afișăm un mesaj de eroare
            perror("\033[31mEroare la execlp \033[0m");
            exit(1);
        } else {
            // Procesul părinte așteaptă copilul să termine
            wait(0);
        }
		jump_here:
    }

    return 0;
}
