#ifndef Cliente_h
#define Cliente_h

#include <sys/socket.h>
#include <netinet/in.h>



   struct Client{
      int domain;   
      int service;
      int protocol;
      int port;
      unsigned long interf;

      struct sockaddr_in address;


   };

   struct Client client_contructor(int domain, int service, int protocol, int port, unsigned long interf);   

#endif 