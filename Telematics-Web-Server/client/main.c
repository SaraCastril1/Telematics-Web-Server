#include "Cliente.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

    char buff_tx[BUFSIZ]; 
    char buff_rx[BUFSIZ];


int main(){

    int socket_client;
   struct Client my_client = client_contructor(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY);

    //now we can use the  parameters of the address to create the sockets for the server
   socket_client = socket(my_client.domain, my_client.service, my_client.protocol);

   //SOCKET socket(int af, int type, int protocol) -> Creates a socket communication with the network 

   if ( (connect(socket_client, (struct sockaddr*)&my_client.address, sizeof(my_client.address))) < 0){
    perror("Failed to connect to the remote socket...");

   };




   while(1){
   fgets(buff_tx, sizeof(buff_tx), stdin);
   write(socket_client, buff_tx, sizeof(buff_tx));
   //recv(socket_client,buff_rx, sizeof(BUFSIZ), 0);
   read(socket_client, buff_rx, sizeof(buff_rx));
   printf("%s", buff_rx);
   }
        
   
    
   return 0;
}