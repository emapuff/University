   #include <sys/types.h>
   #include <sys/socket.h>
   #include <stdio.h>
   #include <netinet/in.h>
   #include <netinet/ip.h>
   #include <string.h>
   #include <unistd.h>
   
   
   void problema4(int c){
	   /*
	   Un client trimite unui server doua siruri de caractere ordonate. 
	   Serverul va interclasa cele doua siruri si va returna clientului sirul rezultat interclasat.
	   */
       printf("\nAvem conectat clientul 4 cu interclasarea a doua siruri\n");
	   int lenA, lenB;
       char a[101],b[101],final[202];
	   recv(c,&lenA,sizeof(lenA), MSG_WAITALL);
       lenA=ntohs(lenA);
       recv(c,a,lenA,MSG_WAITALL);
       a[sizeof(a) - 1] = '\0';
       printf("am primit a: %s\n",a);
 
       recv(c,&lenB,sizeof(lenB),MSG_WAITALL);
       lenB=ntohs(lenB);
       recv(c,b,lenB,MSG_WAITALL);
       printf("am primit b: %s\n", b);
       b[sizeof(b) - 1] = '\0';
 
              //-------ALGORITM--------------------
       int i=0, j=0, k=0;
 
       while(i<lenA && j<lenB){
            if(a[i] == b[j]){
                  final[k++] = a[i];
                  final[k++] = a[i];
                  i++, j++;
            }
            else{
                  if(a[i] < b[j] ){
                        final[k++] = a[i];
                        i++;
                  }
                  else {
                        final[k++] = b[j];
                        j++;
                  }
               }
        }
 
        while (i < lenA) {
                final[k++] = a[i++];
        }
 
        while (j < lenB) {
                final[k++] = b[j++];
        }
 
              //-------------------------------------
 
        printf("am terminat algoritmul\n");
        final[k] = '\0';

        send(c, final, k, 0);
        printf("am trimis sirul final \n");
	   
   }
   
   void problema1(int c){
	   
	   int k, v[101];
	   recv(c,&k,sizeof(k), MSG_WAITALL);
	   k = ntohs(k);
	   recv(c,v, k * sizeof(int),MSG_WAITALL);
	   for(int i=0;i<k;i++)
		   v[i] = ntohs(v[i]);
	   
	   int sum = 0 ;
	   for(int i=0;i<k;i++)
		   sum += v[i];
	   
	   sum = htons(sum);
	   send(c,&sum,sizeof(sum),0);
	   
   }
  
   void problema2(int c){
	   int lenA;
       char a[101];
	   recv(c,&lenA,sizeof(lenA), MSG_WAITALL);
       lenA=ntohs(lenA);
       recv(c,a,lenA,MSG_WAITALL);
       a[sizeof(a) - 1] = '\0';
	   
	   int nr =0; 
	   for(int i=0;i< lenA;i++)
		   if(a[i] == ' ') nr++;
	   
	   nr = htons(nr);
	   send(c, &nr, sizeof(nr), 0);
	   
   }
  
  void problema3(int c){
	    int lenA;
       char a[101],final[202];
	   recv(c,&lenA,sizeof(lenA), MSG_WAITALL);
       lenA=ntohs(lenA);
       recv(c,a,lenA,MSG_WAITALL);
       a[sizeof(a) - 1] = '\0';
	   
	   for(int i=0;i<lenA;i++)
		   final[i] = a [lenA-i-1];
	   
	   final[lenA]=0;
	   send(c, final,lenA,0);
  }
  
 void problema5(int c) {
    int v[101], k = 0;
    int nr;
    recv(c, &nr, sizeof(nr), MSG_WAITALL);
    nr = ntohs(nr);
    for (int d = 1; d <= nr; d++)
        if (nr % d == 0)
            v[k++] = d;

    // Trimiterea numărului de divizori
    int k_net = htons(k); 
    send(c, &k_net, sizeof(k_net), 0);


    for (int i = 0; i < k; i++)
        v[i] = htons(v[i]);

    send(c, v, k * sizeof(int), 0); 
}

void problema6(int c) {
    int lenA;
    char a[101], cautat;

   
    recv(c, &lenA, sizeof(lenA), MSG_WAITALL);
    lenA = ntohs(lenA);

    recv(c, a, lenA, MSG_WAITALL);
    a[lenA] = '\0'; 

   
    recv(c, &cautat, sizeof(cautat), MSG_WAITALL);
    int v[101], k = 0;

    for (int i = 0; i < lenA; i++) {
        if (a[i] == cautat) {
            v[k++] = i; 
        }
    }

    int k_net = htons(k);
    send(c, &k_net, sizeof(k_net), 0);

    
    for (int i = 0; i < k; i++) {
        v[i] = htons(v[i]);
    }
    send(c, v, k * sizeof(int), 0); 
}

void problema7(int c) {
    int lenA;
    char a[101];
    int i, j;

    recv(c, &lenA, sizeof(lenA), MSG_WAITALL);
    lenA = ntohs(lenA);
	printf("%d\n",lenA);
	
    recv(c, a, lenA, MSG_WAITALL);
    a[lenA] = '\0'; 
	
   recv(c, &i, sizeof(i), MSG_WAITALL);
    i = ntohs(i);
	
    recv(c, &j, sizeof(j), MSG_WAITALL);
    j = ntohs(j);
	

    char v[101];
    int k = 0;

    for (int ii = i; ii < i + j && ii < lenA; ii++) {
        v[k++] = a[ii];
    }
    v[k] = '\0';  

    int k_net = htons(k);
    send(c, &k_net, sizeof(k_net), 0);
    send(c, v, k, 0);  
}

  int main(){
  
          int s;
          struct sockaddr_in server, client;
          int c;
          socklen_t l;
          s = socket(AF_INET, SOCK_STREAM,0);
          if(s<0){
              printf("\033[31mEroare la crearea socketului\033[0m\n" );
              return 1;
          }
 
          memset(&server,0,sizeof(server));
          server.sin_port=htons(1234);
          server.sin_family=AF_INET;
          server.sin_addr.s_addr=INADDR_ANY;
 
          if(bind(s,(struct sockaddr *) &server, sizeof(server))<0){
                  printf("\033[31mEroare la bind \033[0m\n");
                 return 1;
          }
 
          listen(s,5);
          l = sizeof(client);
          memset(&client,0,sizeof(client));
          printf("\033[33mBun venit in server-ul Empuff\033[0m\n");
          while(1){
              int optiune;
              c = accept(s, (struct sockaddr *)&client, &l);
              printf("\033[35mS-a conectat un client \033[0m\n");
			  recv(c,&optiune,sizeof(optiune),MSG_WAITALL);
			  optiune=ntohs(optiune);
			  switch(optiune){
				  case 1: printf("optiunea1: suma numerelor din sir\n");
						  problema1(c);
						  break;
				  case 2: printf("optiunea2: nr de spatii intr-un sir de caractre\n");
				          problema2(c);
						  break;
				  case 3: printf("optiunea3: sir oglindit");
						  problema3(c);
						  break;
				  case 4: 
						printf("optiunea 4 selectata: interclasarea a doua siruri\n");
						problema4(c);
						break;
				  case 5:
						printf("optiunea 5: divizorii unui numar");
						problema5(c);
						break;
				  case 6: 
				        printf("optiunea 6: pozitiile unde gasim un caracter dat");
						problema6(c);
						break;
				 case 7: 
						printf("optiunea 7: subsirul unui sir");
						problema7(c);
						break;
				  default: 
						break;
				  
			  }
              close(c);
 
          }
          return 0;
 }
