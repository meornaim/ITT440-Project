//Server program to demonstrate Socket Programming
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define SERVER_PORT 4096 //Local Host Port (ss -tulw)

int main(int argc, char const *argv[])
{
    int server_fd, new_socket;
    long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    
    // HTTP protocol implement
    // Send a response 
    char *hello = "HTTP/1.1 200 OK\nContent-Type:text/plain \n\nHave A Nice Day Everyone"; 
    // Creating a new socket 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    // (AF_INET = Internet Socket)
    // (SOCK_STREAM = TCP Stream Socket )
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }
    
    // Set Up Address 
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( SERVER_PORT );//Server Port Im Lisenting On
    
    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    
    // Listen And Bind  
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("In bind"); // Accept 
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 10) < 0)
    {
        perror("In listen"); // Accept 
        exit(EXIT_FAILURE);
    }

    //Implement Loop  
    while(1)
    {
        printf("\n-------- Waiting for new connectionto be bind ---------\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");  //Send 
            exit(EXIT_FAILURE);
        }
        
        char buffer[30000] = {0};
        valread = read( new_socket , buffer, 30000);
        printf("%s\n",buffer );
        write(new_socket , hello , strlen(hello));
        printf("\n-----------------Message Sent-----------------"); // Recv 
        close(new_socket);//Close Socket
    }
    return 0;
}
