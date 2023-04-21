#include "Server.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/stat.h>


char response[BUFSIZ];
//char buffer_response[262144] = {"\0"};
char client_request[1048];
char* temp_response;
char* body_response;
int mistake = 0;
int flag = 0; //esta flag es para activar y ejecutar correctamente el ACTION de un html


struct Token{

    char* method;
    char* URI;
    char* version; 
    char* headers;
    char* body;
    char* mime;


};


void HTTP_handler(struct Token my_token,char* request_line, int client_socket){
   // printf("request_line dentro de la funcion, antes del malloc: %s\n",request_line);
  //  temp_response = malloc(sizeof(request_line)*100);
   // printf("size of request_line: %i\n",sizeof(request_line));
   // memcpy(temp_response, request_line,sizeof(request_line));
 //   printf("Temp response dentro de la funcion, despues del memcpy: %s\n",temp_response);
    my_token.method = strtok(request_line, " ");
    my_token.URI = strtok(NULL, " ");
    my_token.version = strtok(NULL, " "); 

    /*if (strcmp(my_token.method, "POST") == 0){

        while()
        //printf("TEMP-> %s", temp_response)
        //temp_response = malloc(sizeofrequest + 1);
       my_token.headers = strtok(NULL, " ");
       printf("\nESTE ES EL HEADER -> %s", my_token.headers);

    }*/



    //Geneal Headers
    char header_date[30]; 
    char last_modified[30] = "Last-Modified: ";


    //Body Headers
    char content_length[30];
    char* content_type;
    char content_location[30] = "Content-Location: "; // -> Para POST

    //Response headers
    //server
 
  

    my_token.URI++;
    if(strlen(my_token.URI)==0){
    my_token.URI = "resources/index.html";    
    printf("URI: %s\n",my_token.URI);
    }
    my_token.mime = strchr(my_token.URI, '.');

    //printf("RUTA ->%s\n", my_token.URI);
    //printf("MIME ->%s\n", my_token.mime);


    //--------------------------------- HEADER Content_type --------------------------------------     
    if(my_token.mime == NULL){
            my_token.mime = "undefined";
        }
    else if (strcmp(my_token.mime, ".html") == 0 || strcmp(my_token.mime, ".htm") == 0){
        //response = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n";
        content_type = "Content-type: text/html\r\n\r\n";
    }else if (strcmp(my_token.mime, ".css") == 0){
        //response = "HTTP/1.1 200 OK\r\nContent-type: text/css\r\n\r\n";
        content_type ="Content-type: text/css\r\n\r\n";
    }else if (strcmp(my_token.mime, ".csv") == 0){
        //response = "HTTP/1.1 200 OK\r\nContent-type: text/csv\r\n\r\n";
        content_type = "Content-type: text/csv\r\n\r\n";
    }else if (strcmp(my_token.mime, ".ics") == 0){
        //response = "HTTP/1.1 200 OK\r\nContent-type: text/calendar\r\n\r\n";
        content_type ="Content-type: text/calendar\r\n\r\n";
    }else if (strcmp(my_token.mime, ".jpg") == 0){
        //response = "HTTP/1.1 200 OK\r\nContent-type: image/jpg\r\n\r\n";
        content_type ="Content-type: image/jpg\r\n\r\n";
    }else if (strcmp(my_token.mime, ".png") == 0){
        //response = "HTTP/1.1 200 OK\r\nContent-type: image/png\r\n\r\n";
        content_type ="Content-type: image/png\r\n\r\n";
    }else if (strcmp(my_token.mime, ".jpeg") == 0){
        //response = "HTTP/1.1 200 OK\r\nContent-type: image/jpeg\r\n\r\n";
        content_type = "Content-type: image/jpeg\r\n\r\n";
    }else if (strcmp(my_token.mime, ".gif") == 0){
        //response = "HTTP/1.1 200 OK\r\nContent-type: image/gif\r\n\r\n";
        content_type ="Content-type: image/gif\r\n\r\n";
    }else if (strcmp(my_token.mime, ".ico") == 0){
        //response = "HTTP/1.1 200 OK\r\nContent-type: image/x-icon\r\n\r\n";
        content_type = "Content-type: image/x-icon\r\n\r\n";
    }else if (strcmp(my_token.mime, ".tif") == 0 || strcmp(my_token.mime, ".tiff") == 0 ){
        //response = "HTTP/1.1 200 OK\r\nContent-type: image/tiff\r\n\r\n";
        content_type = "Content-type: image/tiff\r\n\r\n";
    }else if (strcmp(my_token.mime, ".webp") == 0 ){
        //response = "HTTP/1.1 200 OK\r\nContent-type: image/webp\r\n\r\n";
        content_type = "Content-type: image/webp\r\n\r\n";
    }else if (strcmp(my_token.mime, ".svg") == 0 ){
        //response = "HTTP/1.1 200 OK\r\nContent-type: image/svg+xml\r\n\r\n";
        content_type = "Content-type: image/svg+xml\r\n\r\n";
    }
    else if (strcmp(my_token.mime, ".7z") == 0 ){
        //response = "HTTP/1.1 200 OK\r\nContent-type: application/x-7z-compressed\r\n\r\n";
        content_type = "Content-type: application/x-7z-compressed\r\n\r\n";
    }
    
    /* else if (strcmp(my_token.mime, ".aac") == 0){
        //response = "HTTP/1.1 200 OK\r\nContent-type: audio/aac\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".abw") == 0){
        //response = "HTTP/1.1 200 OK\r\nContent-type: application/x-abiword\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".arc") == 0){
        //response = "HTTP/1.1 200 OK\r\nContent-type: application/octet-stream\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".avi") == 0){
        //response = "HTTP/1.1 200 OK\r\nContent-type: video/x-msvideo\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".azw") == 0){
        //response = "HTTP/1.1 200 OK\r\nContent-type: application/vnd.amazon.ebook\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".bin") == 0){
        //response = "HTTP/1.1 200 OK\r\nContent-type: application/octet-stream\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".bz") == 0){
        //response = "HTTP/1.1 200 OK\r\nContent-type: application/x-bzip\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".bz2") == 0){
        //response = "HTTP/1.1 200 OK\r\nContent-type: application/x-bzip2\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".csh") == 0){
        //response = "HTTP/1.1 200 OK\r\nContent-type: application/x-csh\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".doc") == 0){
        //response = "HTTP/1.1 200 OK\r\nContent-type: application/msword\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".epub") == 0){
        //response = "HTTP/1.1 200 OK\r\nContent-type: application/epub+zip\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".jar") == 0){
        //response = "HTTP/1.1 200 OK\r\nContent-type: application/java-archive\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".js") == 0){
        //response = "HTTP/1.1 200 OK\r\nContent-type: application/javascript\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".json") == 0){
        //response = "HTTP/1.1 200 OK\r\nContent-type: application/json\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".mid") == 0 || strcmp(my_token.mime, ".midi") == 0  ){
        //response = "HTTP/1.1 200 OK\r\nContent-type: audio/midi\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".mpeg ") == 0 ){
        //response = "HTTP/1.1 200 OK\r\nContent-type: video/mpeg\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".mpkg") == 0 ){
        //response = "HTTP/1.1 200 OK\r\nContent-type: application/vnd.apple.installer+xml\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".odp") == 0 ){
        //response = "HTTP/1.1 200 OK\r\nContent-type: application/vnd.oasis.opendocument.presentation\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".ods") == 0 ){
        //response = "HTTP/1.1 200 OK\r\nContent-type: application/vnd.oasis.opendocument.spreadsheet\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".odt") == 0 ){
        //response = "HTTP/1.1 200 OK\r\nContent-type: application/vnd.oasis.opendocument.text\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".oga") == 0 ){
        //response = "HTTP/1.1 200 OK\r\nContent-type: audio/ogg\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".ogv") == 0 ){
        //response = "HTTP/1.1 200 OK\r\nContent-type: video/ogg\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".ogx") == 0 ){
        //response = "HTTP/1.1 200 OK\r\nContent-type: application/ogg\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".pdf") == 0 ){
        //response = "HTTP/1.1 200 OK\r\nContent-type: application/pdf\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".ppt") == 0 ){
        //response = "HTTP/1.1 200 OK\r\nContent-type: application/vnd.ms-powerpoint\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".rar") == 0 ){
        //response = "HTTP/1.1 200 OK\r\nContent-type: application/x-rar-compressed\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".rtf") == 0 ){
        //response = "HTTP/1.1 200 OK\r\nContent-type: application/rtf\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".sh") == 0 ){
        //response = "HTTP/1.1 200 OK\r\nContent-type: application/x-sh\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".swf") == 0 ){
        //response = "HTTP/1.1 200 OK\r\nContent-type: application/x-shockwave-flash\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".tar") == 0 ){
        //response = "HTTP/1.1 200 OK\r\nContent-type: application/x-tar\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".ttf") == 0 ){
        //response = "HTTP/1.1 200 OK\r\nContent-type: font/ttf\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".vsd") == 0 ){
        //response = "HTTP/1.1 200 OK\r\nContent-type: application/vnd.visio\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".wav") == 0 ){
        //response = "HTTP/1.1 200 OK\r\nContent-type: audio/x-wav\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".weba") == 0 ){
        //response = "HTTP/1.1 200 OK\r\nContent-type: audio/webm\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".webm") == 0 ){
        //response = "HTTP/1.1 200 OK\r\nContent-type: video/webm\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".woff") == 0 ){
        //response = "HTTP/1.1 200 OK\r\nContent-type: font/woff\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".woff2") == 0 ){
        //response = "HTTP/1.1 200 OK\r\nContent-type: font/woff2\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".xhtml") == 0 ){
        //response = "HTTP/1.1 200 OK\r\nContent-type: application/xhtml+xml\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".xls") == 0 ){
        //response = "HTTP/1.1 200 OK\r\nContent-type: application/vnd.ms-excel\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".xml") == 0 ){
        //response = "HTTP/1.1 200 OK\r\nContent-type: application/xml\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".xul") == 0 ){
        //response = "HTTP/1.1 200 OK\r\nContent-type: application/vnd.mozilla.xul+xml\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".zip") == 0 ){
        //response = "HTTP/1.1 200 OK\r\nContent-type: application/zip\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".3gp") == 0 ){
        //response = "HTTP/1.1 200 OK\r\nContent-type: video/3gpp \r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".3g2 ") == 0 ){
        //response = "HTTP/1.1 200 OK\r\nContent-type: video/3gpp2\r\n\r\n";
        content_type =
    }else if (strcmp(my_token.mime, ".7z") == 0 ){
        //response = "HTTP/1.1 200 OK\r\nContent-type: application/x-7z-compressed\r\n\r\n";
        content_type =
    }
    
    */


    //--------------------------------- HEADER DATE --------------------------------------        
    time_t my_date = time(NULL);

    char* today;
    char* month;

    struct tm date = *localtime(&my_date);

    if (date.tm_wday == 1){
        today = "Lun";
    }else if (date.tm_wday == 2){
        today = "Tue";
    }else if (date.tm_wday == 3){
        today = "Wed";
    }else if (date.tm_wday == 4){
        today = "Thu";
    }else if (date.tm_wday == 5){
        today = "Fri";
    }else if (date.tm_wday == 6){
        today = "Sat";
    }else if (date.tm_wday == 7){
        today = "Sun";
    };



    if (date.tm_mon+1 == 1){
        month = "Jan";
    }else if (date.tm_mon+1 == 2){
        month = "Feb";
    }else if (date.tm_mon+1 == 3){
        month = "Mar";
    }else if (date.tm_mon+1 == 4){
        month = "Apr";
    }else if (date.tm_mon+1 == 5){
        month = "May";
    }else if (date.tm_mon+1 == 6){
        month = "Jun";
    }else if (date.tm_mon+1 == 7){
        month = "Jul";
    }else if (date.tm_mon+1 == 8){
        month = "Aug";
    }else if (date.tm_mon+1 == 9){
        month = "Sep";
    }else if (date.tm_mon+1 == 10){
        month = "Oct";
    }else if (date.tm_mon+1 == 11){
        month = "Nov";
    }else if (date.tm_mon+1 == 12){
        month = "Dec";
    };

    
        
    sprintf(header_date, "Date: %s, %d %s %d %d:%d:%d GMT\n", today, date.tm_mday, month, date.tm_year+1900, date.tm_hour, date.tm_min, date.tm_sec);

    //printf("%s",header_date);
    //strcat(response, header_date);



    // ------------------------------ Header Last_modified --------------------------
  /*  
    struct stat st;
    int result = stat(my_token.URI, &st);
    if (result != 0) {
        perror("stat");
    }

    time_t modified_time = st.st_mtime;
    struct tm* time_info = localtime(&modified_time);
    char time_str[30];
    //strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time_info);
    strftime(time_str, sizeof(time_str), "%d %m %Y %H:%M:%S", time_info);

    //printf("Last modified time of %s: %s\n", my_token.URI, time_str);
    strcat(last_modified, time_str);
    strcat(last_modified, " GMT\n");
  

*/

// ---------------------------------------- GET --------------------------------------------------------

    if (strcmp(my_token.method, "GET" ) == 0 ||strcmp(my_token.method, "HEAD") == 0){
        //printf("Recibí un GET\n");
        FILE* file = fopen(my_token.URI, "r");

        if (file == NULL) {
            file = fopen("resources/error404.html", "r");
            mistake = 1;
    //       perror("HTTP/1.1 404 File Not found :(");
        //}else {
            //printf("%s does exist \n", my_token.URI);
        }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);


    // ----------------------- HEADER content_length ------------------------------
    sprintf(content_length, "Content-Length: %ld\n", fsize);
    //printf("%s", content_length);
    // --------------------------------------------------------------------------


    char* temp = malloc(sizeof(char) * (fsize+1));
    fread(temp,fsize,1,file);

    // ------------------------------------ RESPONSE-----------------------------------------
    strcat(response, "HTTP/1.1 200 OK\n");
    strcat(response, header_date);
    strcat(response, "Server: TWS\n");
    //strcat(response, last_modified);
    strcat(response, content_length);
    //strcat(response, content_location);
    //strcat(response, my_token.URI);
    //strcat(response, "\n"); 
    strcat(response, content_type);
    
    

    //strcpy(buffer_response,response);
    //strcat(buffer_response,temp);
    
    
    fclose(file);
    send(client_socket, response, strlen(response), 0);
    if(strcmp(my_token.method, "GET") == 0){
    send(client_socket, temp, fsize, 0);
    }
    
    free(temp);
    memcpy(response, "", sizeof(""));

 //------------------------POST---------------------------------------------------------------   
    }else if (strcmp(my_token.method, "POST") == 0){
      //  printf("Temp response: %s\n", temp_response);
        if(strstr(temp_response,"Content-Type: application/x-www-form-urlencoded") != NULL){
        printf("Content-type: Aplicacion, aceptado\n");
    //    printf("URI: %s\n",my_token.URI);
        temp_response = strstr(temp_response,"\r\n\r\n");
        char* body = temp_response;
        body += 2;
        body = strtok(body,"&");
        while(body != NULL){
            printf("Key + value: %s\n",body);
            body = strtok(NULL,"&");
        }
        //Ejemplo de una "action" dentro del HTML
        if(strcmp(my_token.URI, "register") == 0){
            flag = 1;
            FILE* file = fopen("resources/register.html", "r");
            fseek(file, 0, SEEK_END);
            long fsize = ftell(file);
            fseek(file, 0, SEEK_SET);
            char* temp = malloc(sizeof(char) * (fsize+1));
            fread(temp,fsize,1,file);
            strcat(response, "HTTP/1.1 200 OK\r\n\r\n");
            send(client_socket, response, strlen(response), 0);
            send(client_socket, temp, fsize, 0);

        }    

        }else if(strstr(temp_response,"Content-Type: text/plain") != NULL){
            printf("temp response: %s\n",temp_response);
            printf("Content-type: Texto plano, aceptado\n");
       //     printf("URI: %s\n",my_token.URI);
            temp_response = strstr(temp_response,"\r\n\r\n");
            char* body_text = temp_response;
            body_text += 2;
            printf("Body: %s\n",body_text);
        }
        strcat(response, "HTTP/1.1 200 OK\n");
        strcat(response, content_type);
       // printf("response: %s\n",response);
        if(flag == 0){
        send(client_socket, response, strlen(response), 0);
        }
        flag = 0;
        memcpy(response, "", sizeof(""));
        memcpy(temp_response, "", sizeof(""));
        //printf("%s\n", my_token.method);
        //printf("%s\n", my_token.URI);
        //printf("%s\n", my_token.mime);
        //printf("%s\n", my_token.headers);


      //  content_type = strstr(temp_response, "Content-Type:");
      //  content_type = strtok(content_type,"\n");
      //  content_type += 14;
        //printf("Ruta mandada: %s\n",my_token.URI);
       // printf("Content Type: %s\n", content_type); 
        
       // strcpy(response, "HTTP/1.1 200 OK\r\n\r\n");
      //  printf("Sent response: %s\n",response);
       // send(client_socket,response,sizeof(response),0);
    //    char* body;
        //content_type = strtok(content_type, "\r\n\r\n");
        //content_type += 2; //BODY de la request      
       // while(temp_response != NULL){
    //   printf("Body: %s\n",content_type);
      //  temp_response = strtok(NULL, "\n\n");
      //  }



/*
        FILE* file = fopen(my_token.URI, "r");

        if (file == NULL) {
            send(client_socket, "HTTP/1.1 400 Bad Request\n", 26, 0);
            mistake = 2;
        }else {
            send(client_socket, "HTTP/1.1 201 OK\n", 17, 0);
        }
*/
   // 
    }//else if(strcmp(my_token.method, "HEAD") == 0){
       // printf("Recibí un HEAD\n");
      // }
       else{
        perror("HTTP/1.1 400 Bad request -> Method");
    }


    //------------ LOGGER ------------------------


    FILE *logger_FILE = fopen("logger.txt", "a+");
    if (logger_FILE == NULL){
        perror("No se pudo modificar el logger");
    }else{
        fputs(header_date, logger_FILE);
        if (mistake == 0){
            fputs(" INFO: ", logger_FILE);
            fputs(my_token.method, logger_FILE);
            fputs(" requested on ", logger_FILE);
            fputs(my_token.URI, logger_FILE);
            fputs("---> Succesfully atended\n", logger_FILE);
        }else if(mistake == 1){
            fputs(" ERROR: ", logger_FILE);
            fputs(my_token.method, logger_FILE);
            fputs(" requested on ", logger_FILE);
            fputs(my_token.URI, logger_FILE);
            fputs("---> File not found\n", logger_FILE);

        }else if(mistake == 2){
            fputs(" ERROR: ", logger_FILE);
            fputs(my_token.method, logger_FILE);
            fputs(" requested on ", logger_FILE);
            fputs(my_token.URI, logger_FILE);
            fputs("---> Bad Request\n", logger_FILE);

        }
        


    }
    fclose(logger_FILE);

    //free(temp_response);

    
};   
    


void launch(struct Server *my_server){


   //char* server_msg = "Trying INADDR_ANY...\nConnected to Telematis Web Server.";
   temp_response = malloc(sizeof(client_request)+100);

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
      
      memcpy(temp_response,client_request,sizeof(client_request));
      //recv(client_socket, &client_request, sizeof(client_request), 0); 
     // printf("%s\n",client_request);
    //  printf("Size of client_request: %i\n",strlen(client_request));
      struct Token my_token;
      HTTP_handler(my_token, client_request, client_socket);
      
      
      

      close(client_socket);
      


   
   };
      

};


int main(int argc, char* argv[]) {

   struct Server my_server = server_contructor(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY, 10 , launch);
   my_server.launch(&my_server);
   
   return 0;
}
