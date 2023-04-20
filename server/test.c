#include "Server.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>


char* response = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n";
char buffer_response[262144] = {"\0"};
char client_request[1048];
char* temp_response;
char* body_response;
struct Token{

    char* method;
    char* URI;
    char* version; 
    char* mime;
    int pclient_socket;
    char* request_line;
    int sizeofrequest;
    //char* body_response; //Por alguna razon desconocida, crear esta variable crea un error de segmentacion siempre.
};

void* HTTP_handler(void* args){
    struct Token *my_token = (struct Token *)args;
   // temp_response = malloc((*my_token).sizeofrequest + 1);
 //   memcpy(temp_response,(*my_token).request_line,(*my_token).sizeofrequest);
 //   printf("TEMP RESPONSE ANTES: %s\n",temp_response);
    (*my_token).method = strtok((*my_token).request_line, " ");
    (*my_token).URI = strtok(NULL, " ");
    (*my_token).version = strtok(NULL, " ");
     
    //(*my_token).request_body = strtok(NULL, " ");
  //  printf("version: %s",(*my_token).version);
  //  if(strcmp((*my_token).version, "HTTP/1.1") == 0 ){
  //    perror("HTTP/1.1 400 Bad request -> Version\n");
  //  }else{
  //    printf("La versión fue verificada\n");
  //  }

    
    for(int i = 0; i < strlen((*my_token).URI); i++ ){
        (*my_token).URI[i] = (*my_token).URI[i+1];
    }
    (*my_token).mime = strchr((*my_token).URI, '.');
    
    printf("RUTA ->%s\n", (*my_token).URI);
    printf("MIME ->%s\n", (*my_token).mime);

        if((*my_token).mime == NULL){
            (*my_token).mime = "undefined";
        }
        if (strcmp((*my_token).mime, ".html") == 0 || strcmp((*my_token).mime, ".htm") == 0){
            response = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".css") == 0){
            response = "HTTP/1.1 200 OK\r\nContent-type: text/css\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".csv") == 0){
            response = "HTTP/1.1 200 OK\r\nContent-type: text/csv\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".ics") == 0){
            response = "HTTP/1.1 200 OK\r\nContent-type: text/calendar\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".jpg") == 0){
            response = "HTTP/1.1 200 OK\r\nContent-type: image/jpg\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".png") == 0){
            response = "HTTP/1.1 200 OK\r\nContent-type: image/png\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".jpeg") == 0){
            response = "HTTP/1.1 200 OK\r\nContent-type: image/jpeg\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".gif") == 0){
            response = "HTTP/1.1 200 OK\r\nContent-type: image/gif\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".ico") == 0){
            response = "HTTP/1.1 200 OK\r\nContent-type: image/x-icon\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".tif") == 0 || strcmp((*my_token).mime, ".tiff") == 0 ){
            response = "HTTP/1.1 200 OK\r\nContent-type: image/tiff\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".webp") == 0 ){
            response = "HTTP/1.1 200 OK\r\nContent-type: image/webp\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".svg") == 0 ){
            response = "HTTP/1.1 200 OK\r\nContent-type: image/svg+xml\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".aac") == 0){
            response = "HTTP/1.1 200 OK\r\nContent-type: audio/aac\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".abw") == 0){
            response = "HTTP/1.1 200 OK\r\nContent-type: application/x-abiword\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".arc") == 0){
            response = "HTTP/1.1 200 OK\r\nContent-type: application/octet-stream\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".avi") == 0){
            response = "HTTP/1.1 200 OK\r\nContent-type: video/x-msvideo\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".azw") == 0){
            response = "HTTP/1.1 200 OK\r\nContent-type: application/vnd.amazon.ebook\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".bin") == 0){
            response = "HTTP/1.1 200 OK\r\nContent-type: application/octet-stream\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".bz") == 0){
            response = "HTTP/1.1 200 OK\r\nContent-type: application/x-bzip\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".bz2") == 0){
            response = "HTTP/1.1 200 OK\r\nContent-type: application/x-bzip2\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".csh") == 0){
            response = "HTTP/1.1 200 OK\r\nContent-type: application/x-csh\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".doc") == 0){
            response = "HTTP/1.1 200 OK\r\nContent-type: application/msword\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".epub") == 0){
            response = "HTTP/1.1 200 OK\r\nContent-type: application/epub+zip\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".jar") == 0){
            response = "HTTP/1.1 200 OK\r\nContent-type: application/java-archive\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".js") == 0){
            response = "HTTP/1.1 200 OK\r\nContent-type: application/javascript\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".json") == 0){
            response = "HTTP/1.1 200 OK\r\nContent-type: application/json\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".mid") == 0 || strcmp((*my_token).mime, ".midi") == 0  ){
            response = "HTTP/1.1 200 OK\r\nContent-type: audio/midi\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".mpeg ") == 0 ){
            response = "HTTP/1.1 200 OK\r\nContent-type: video/mpeg\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".mpkg") == 0 ){
            response = "HTTP/1.1 200 OK\r\nContent-type: application/vnd.apple.installer+xml\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".odp") == 0 ){
            response = "HTTP/1.1 200 OK\r\nContent-type: application/vnd.oasis.opendocument.presentation\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".ods") == 0 ){
            response = "HTTP/1.1 200 OK\r\nContent-type: application/vnd.oasis.opendocument.spreadsheet\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".odt") == 0 ){
            response = "HTTP/1.1 200 OK\r\nContent-type: application/vnd.oasis.opendocument.text\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".oga") == 0 ){
            response = "HTTP/1.1 200 OK\r\nContent-type: audio/ogg\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".ogv") == 0 ){
            response = "HTTP/1.1 200 OK\r\nContent-type: video/ogg\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".ogx") == 0 ){
            response = "HTTP/1.1 200 OK\r\nContent-type: application/ogg\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".pdf") == 0 ){
            response = "HTTP/1.1 200 OK\r\nContent-type: application/pdf\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".ppt") == 0 ){
            response = "HTTP/1.1 200 OK\r\nContent-type: application/vnd.ms-powerpoint\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".rar") == 0 ){
            response = "HTTP/1.1 200 OK\r\nContent-type: application/x-rar-compressed\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".rtf") == 0 ){
            response = "HTTP/1.1 200 OK\r\nContent-type: application/rtf\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".sh") == 0 ){
            response = "HTTP/1.1 200 OK\r\nContent-type: application/x-sh\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".swf") == 0 ){
            response = "HTTP/1.1 200 OK\r\nContent-type: application/x-shockwave-flash\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".tar") == 0 ){
            response = "HTTP/1.1 200 OK\r\nContent-type: application/x-tar\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".ttf") == 0 ){
            response = "HTTP/1.1 200 OK\r\nContent-type: font/ttf\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".vsd") == 0 ){
            response = "HTTP/1.1 200 OK\r\nContent-type: application/vnd.visio\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".wav") == 0 ){
            response = "HTTP/1.1 200 OK\r\nContent-type: audio/x-wav\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".weba") == 0 ){
            response = "HTTP/1.1 200 OK\r\nContent-type: audio/webm\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".webm") == 0 ){
            response = "HTTP/1.1 200 OK\r\nContent-type: video/webm\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".woff") == 0 ){
            response = "HTTP/1.1 200 OK\r\nContent-type: font/woff\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".woff2") == 0 ){
            response = "HTTP/1.1 200 OK\r\nContent-type: font/woff2\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".xhtml") == 0 ){
            response = "HTTP/1.1 200 OK\r\nContent-type: application/xhtml+xml\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".xls") == 0 ){
            response = "HTTP/1.1 200 OK\r\nContent-type: application/vnd.ms-excel\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".xml") == 0 ){
            response = "HTTP/1.1 200 OK\r\nContent-type: application/xml\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".xul") == 0 ){
            response = "HTTP/1.1 200 OK\r\nContent-type: application/vnd.mozilla.xul+xml\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".zip") == 0 ){
            response = "HTTP/1.1 200 OK\r\nContent-type: application/zip\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".3gp") == 0 ){
            response = "HTTP/1.1 200 OK\r\nContent-type: video/3gpp \r\n\r\n";
        }else if (strcmp((*my_token).mime, ".3g2 ") == 0 ){
            response = "HTTP/1.1 200 OK\r\nContent-type: video/3gpp2\r\n\r\n";
        }else if (strcmp((*my_token).mime, ".7z") == 0 ){
            response = "HTTP/1.1 200 OK\r\nContent-type: application/x-7z-compressed\r\n\r\n";
        }

    
    if (strcmp((*my_token).method, "GET") == 0){
        printf("Recibí un GET\n");
    //    printf("TEMP RESPONSE DESPUES: %s\n",temp_response);
        FILE* file = fopen((*my_token).URI, "r");

	    if (file == NULL) {
            file = fopen("resources/error404.html", "r");
     //       perror("HTTP/1.1 404 File Not found :(");
	    }else {
		    printf("%s does exist \n", (*my_token).URI);
	}

	fseek(file, 0, SEEK_END);
	long fsize = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* temp = malloc(sizeof(char) * (fsize+1));
    fread(temp,fsize,1,file);
    strcpy(buffer_response,response);
   // strcat(buffer_response,temp);
    printf("buffer: ");
    printf("%s",buffer_response);
    
	fclose(file);
    if(send((*my_token).pclient_socket, buffer_response, strlen(buffer_response), 0) == -1){
        perror("no se envio\n");
    }
    if(send((*my_token).pclient_socket, temp, fsize, 0) == -1){
        perror("no se envio\n");
    }
    //free(temp);
    //flag = 1;
    


    }else if (strcmp((*my_token).method, "POST") == 0){
        printf("Recibí un POST\n");
     //   char* content_type = strstr(temp_response, "Content-Type:");
    //    content_type = strtok(content_type,"\n");
     //   content_type += 13;
        printf("Ruta mandada: %s\n",(*my_token).URI);
     //   printf("Content Type: %s\n", content_type);
        response = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n";
       // strcpy(response,temp2);
        
        
    //    char* body;
    //    content_type = strstr(content_type, "\r\n\r\n");
    //    content_type += 2; //BODY de la request      
       // while(temp_response != NULL){
     //  printf("Body: %s\n",content_type);
      //  temp_response = strtok(NULL, "\n\n");
      //  }
    FILE* file = fopen("resources/error404.html", "r");

	fseek(file, 0, SEEK_END);
	long fsize = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* temp = malloc(sizeof(char) * (fsize+1));
    fread(temp,fsize,1,file);
    
    printf("Sent response: %s\n",response);
    send((*my_token).pclient_socket, response , sizeof(response), 0);
    printf("Sent file: %s\n",temp);
    send((*my_token).pclient_socket,temp,sizeof(temp),0);

    }else if(strcmp((*my_token).method, "HEAD") == 0){
        printf("Recibí un HEAD\n");
    }else{
        perror("HTTP/1.1 400 Bad request -> Method");
    }
    close((*my_token).pclient_socket);
   // free(temp_response);
   
    
}   
    


void launch(struct Server *my_server){


   //char* server_msg = "Trying INADDR_ANY...\nConnected to Telematis Web Server.";
   

   while(1){
      printf("\n====== WAITING FOR CONNECTION ========\n");
      int address_len = sizeof(my_server->address);

      //Before to create a new socket, we need to accept the server socket.
      //Hold the client server -> When you accept the connection, what you get back is the client socket.
      int client_socket = accept(my_server->socket, (struct sockaddr *)&my_server->address, (socklen_t *)&address_len );

      //Now we have a client that we can send data to:
     // send(client_socket, server_msg, strlen(server_msg), 0);
      //write(client_socket, server_msg, strlen(server_msg));

      read(client_socket, client_request, sizeof(client_request));
      //recv(client_socket, &client_request, sizeof(client_request), 0); 
      //printf("%s",client_request);
      
      pthread_t hilo_htpp;
      struct Token my_token;
      strcpy(my_token.request_line,client_request);
      my_token.sizeofrequest = sizeof(client_request);
      my_token.pclient_socket = client_socket;
      pthread_create(&hilo_htpp,NULL,HTTP_handler,(void *)&my_token);
      //HTTP_handler(my_token, client_request, client_socket);
      
   //while(1){
     //  if(flag == 1){
       //     break;
      //  }
   // }
      

      //close(client_socket);
      


   
   };
      

};


int main(int argc, char* argv[]) {

   struct Server my_server = server_contructor(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY, 10 , launch);
   my_server.launch(&my_server);
   
   return 0;
}