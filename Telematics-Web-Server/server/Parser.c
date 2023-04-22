#include "Parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>




void isGET(struct Parser my_parser, int client_socket){
    //printf("Recibí un GET\n");

    //char* ruta = "resources/img/2017-12-19-19-22-29.jpg";
    //char* ruta = "resources/index.html";
    char buffer[262144] = {"\0"};
    char* response = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n";
    //strcpy(buffer,response);
    //strcat(buffer,response);
   // send(client_socket, response, sizeof(response), 0);
    //printf("%s", response);
    char* ruta = URI_checker(my_parser);
    char* ext = token(ruta, ".");
    //strcpy(ext,ruta);
/*
    while(ext[0] != '.'){
        ext[0] = ext[1];
    };

    printf("EXTENCIÓN-> %s", ext);
    
  */  
    
 //   FILE *response_FILE = fopen(ruta, "r");
 //   if (response_FILE == NULL){
 //       perror("HTTP /1.1 404 File/Page not found :(");
 //   }else{
  //      int index = 0;
   //     while(!feof(response_FILE)){
    //        buffer[index] = fgetc(response_FILE);
     //       index++;
      //      //printf("%c", char_leido);
       // };
   // }
    FILE* file = fopen(ruta, "r");

	if (file == NULL) {
        send(client_socket, my_parser.fail_response_404, sizeof(my_parser.fail_response_404), 0);
        close(client_socket);
	}else {
		printf("%s does exist \n", ruta);
	}

	fseek(file, 0, SEEK_END);
	long fsize = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* temp = malloc(sizeof(char) * (fsize+1));
    //strcat(temp,response);
    //printf("Headers: ");
    //printf("%s",temp);
	//char ch;
	//int i = 0;
	//while((ch = fgetc(file)) != EOF) {
//		temp[i] = ch;
//		i++;
//	}
    fread(temp,fsize,1,file);
   // printf("Leido: ");
    //printf("%s",temp);
    strcpy(buffer,response);
    strcat(buffer,temp);
    //strcat(buffer,"\r\n\r\n");
    //printf("File Size: %l",fsize+1);
    printf("buffer: ");
    printf("%s",buffer);
    //send(client_socket, buffer, sizeof(buffer), 0);   
    //send(client_socket, temp, fsize, 0);
    
	fclose(file);
   // printf("%s",buffer);

   
	
    //strcat(response, "\r\n\r\n");   
    //printf("\n");
    //char html[1028];
    //strcat(html,response);
    //strcpy(html,"<html><body>Este es un test</body></html>\n");
    //printf("%s",html);
    //char buffer2[1084] = "<html><body>Este es un test</body></html>\n";
   send(client_socket, buffer, strlen(buffer), 0);
    //fclose(response_FILE);
    modify_logger(my_parser);
  //  free(temp);

};




void isPOST(struct Parser my_parser){
    printf("Recibí un POST\n");
    modify_logger(my_parser);
};

void isHEAD(struct Parser my_parser){
    printf("Recibí un HEAD\n");
    modify_logger(my_parser);
};




char* URI_checker(struct Parser my_parser){
    for(int i = 0; i < strlen(my_parser.URI); i++ ){
        my_parser.URI[i] = my_parser.URI[i+1];
    }
    
    return my_parser.URI;

};

