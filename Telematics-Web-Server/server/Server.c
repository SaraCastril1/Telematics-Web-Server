#include "Server.h"
#include <stdio.h>
#include <stdlib.h>

struct Server server_contructor(int domain, int service, int protocol, int port, unsigned long interf, int backlog, void (*launch)(struct Server *server)){

   struct Server server;
   server.domain = domain;
   server.service = service;
   server.protocol = protocol;
   server.port = port;
   server.backlog = backlog;
   server.interf = interf;

   server.address.sin_family = domain;
   server.address.sin_port = htons(port); //It converts our integer port into bytes that are going to refer a network port
   server.address.sin_addr.s_addr = htonl(interf); // The real server address that we are going to be connecting to...
                                                   // When sending INADD_ANY We are using any address that is running in our local machine 


   //now we can use the  parameters of the address to create the sockets for the server
   server.socket = socket(domain, service, protocol);

   //SOCKET socket(int af, int type, int protocol) -> Creates a socket communication with the network 


   if (server.socket == 0){
      perror("Failed to connect the socket...\n");
      exit(1);
   };


   //Once we create the socket it is necesary to bind(vincularlo) it to the network -> connect()   
   if ( (bind(server.socket, (struct sockaddr*)&server.address, sizeof(server.address))) < 0 ){
      perror("Failed to bind socket...\n");
      exit(1);
   };

   
   if ( (listen(server.socket, server.backlog)) < 0){
      perror("Failed to start listening...\n");
      exit(1);
   }

   server.launch=launch;


   return server;   
};