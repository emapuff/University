   #include <string.h>
   #include <sys/types.h>
   #include <sys/socket.h>
   #include <netinet/in.h>
   #include <netinet/ip.h>
   #include <stdio.h>
   #include <arpa/inet.h>
   #include <unistd.h>
  
  int main(){
          int c;
          char a[101], b[101],final[202];
          struct sockaddr_in server;
          c = socket(AF_INET,SOCK_STREAM,0);
          if(c<0){
                  printf("Eroare la crearea socketului client \n");
                  return 1;
          }
 
          memset(&server,0,sizeof(server));
          server.sin_port=htons(1234);
          server.sin_family = AF_INET;
          server.sin_addr.s_addr=inet_addr("127.0.0.1");
 
          if(connect(c, (struct sockaddr *) &server, sizeof(server))<0){
                  printf("eroare la conectare la server \n");
                  return 1;
          }
		 
		  int optiune=4;
		  optiune = htons(optiune);
		  send(c,&optiune,sizeof(optiune),0); //trimit optiunea
          printf("Introduceti primul sir de max 100 caractere: \n");
          scanf("%s",a);
		  printf("Introduceti al doilea sir de maxim 100 caractere: \n");
          scanf("%s",b);
        //a=htons(a);
          //b=htons(b);
          int lenA = strlen(a);
          int lenB = strlen(b);
          lenA=htons(lenA);
          lenB=htons(lenB);
          send(c,&lenA,sizeof(int),0);
          send(c,a,sizeof(char)*strlen(a),0);
          printf("am trimis a\n");
          send(c,&lenB, sizeof(int),0);
          send(c,b,sizeof(char)*strlen(b),0);
          printf("am trimis b\n");
          recv(c,final,sizeof(final),0);
          printf("am primit final");
          //final=ntohs(final);
          printf("Sirul nou este: %s\n",final);
          close(c);
          return 0;
  }