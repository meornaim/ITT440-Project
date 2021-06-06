
// Client  program to demonstrate Socket Programming
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 4096// Local Host Port

int main(int argc, char const *argv[])
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};

    // Creating a new socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Connect
    if(inet_pton(AF_INET, "192.168.56.109", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid IP Address/ Address Not Supported  \n");
        return -1;
    }
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    send(sock , hello , strlen(hello) , 0 );
    printf("\nHello message sent\n"); // Recv/Send
    valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );
    return 0;
}



