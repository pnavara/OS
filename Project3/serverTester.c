#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORT 8080 

void *connection_handler(void *);

int len;
char newBuffer[1024] = {0}; 

int main(int argc, char const *argv[]) { 
    int server_fd, new_socket, valread, c; 
    struct sockaddr_in address, client; 
    int opt = 1; 
    int addrlen = sizeof(address); 
  
    char *hello = "Hello from server"; 
       
    // Socket file descriptor creation
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Attatched socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Attatch socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 

    // puts("Waitin'");
    // c = sizeof(struct sockaddr_in);

    puts("Waiting for Connectionn...");
    c = sizeof(struct sockaddr_in);
        pthread_t thread_id;

    //Recieve the string from clients
    while ((new_socket = accept(server_fd, (struct sockaddr *)&client, (socklen_t*)&c)) )
    { 
        puts("Accepted");

        if( pthread_create( &thread_id , NULL ,  connection_handler , (void*) &new_socket) < 0)
        {
            perror("could not create thread");
            return 1;
        }

        puts("Handler assigned");
    } 

    if (new_socket < 0)
    {
        perror("accept failed");
        return 1;
    }
     
    return 0;

    // // reads from client
    // valread = read(new_socket, buffer, 1024); 

    // // length of string from client
    // len = strlen(buffer);
    
    // // reverses string
    // for (int i = 0; i < len; i++) {
    //     newBuffer[i] = buffer[len - 1 - i];
    // }
    // // sends string back to client
    // send(new_socket , newBuffer , strlen(newBuffer) , 0 ); 
    // printf("Reversed String sent from server\n"); 
    // return 0; 
} 

void *connection_handler(void *server_fd)
{
    //Get the socket descriptor
    int sock = *(int*)server_fd;
    int read_size;
    char *message , client_message[2000];
          
    //Receive a message from client
    while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 )
    {
        //end of string marker
		client_message[read_size] = '\0';

        //reverse string
        len = strlen(client_message);
        for (int i = 0; i < len; i++) {
        newBuffer[i] = client_message[len - 1 - i];
        }
		
		//Send the message back to client
        write(sock , newBuffer , strlen(newBuffer));
		
		//clear the message buffer
		memset(newBuffer, 0, 2000);
    }
     
    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
         
    return 0;
} 