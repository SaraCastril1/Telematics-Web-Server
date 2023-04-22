#include "Cliente.h"
#include <stdio.h>
#include <stdlib.h>

struct Client client_contructor(int domain, int service, int protocol, int port, unsigned long interf){

    struct Client client;

    client.domain = domain;
    client.service = service;
    client.protocol = protocol;
    client.port = port;
    client.interf = interf;

    client.address.sin_family = domain;
    client.address.sin_port = htons(port); //It converts our integer port into bytes that are going to refer a network port
    client.address.sin_addr.s_addr = htonl(interf); // The real   Client address that we are going to be connecting to...
                                                   // When sending INADD_ANY We are using any address that is running in our local machine 




   return client;   
};