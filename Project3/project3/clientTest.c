#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 8080 
   
// Based off of socket api sample from geeksforgeeks.com
int main(int argc, char const *argv[]) { 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char *string = "This is the client string"; 
    char buffer[1024] = {0};
    int len;

    // socket creation n error check
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    // sin.family is the first member of serv_addr
    // code for address family, always AF_INET
                                // indicates internet domain
    serv_addr.sin_family = AF_INET; 

    // Storing port number into sin_port
    serv_addr.sin_port = htons(PORT); // htons() converts host byte order of port# 
                                    // to network byte order repr.
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 

    // establish connection to server n error check
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    // sends over string message through socket
    send(sock , string , strlen(string) , 0 ); 
    
    printf("String sent to server from Client\n"); 
    // reads message sent
    valread = read( sock , buffer, 1024); 
    
    // shows original and reversed
    printf("The original string is: %s\n", string); 
    printf("The reversed string is: %s\n", buffer); 
    return 0; 
} 