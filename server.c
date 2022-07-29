#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>

#define PORT 1669
#define BUFFER 256

int server_socket = 0;
int client_socket = 0;

void sigint_handler(int signum)
{
    shutdown(server_socket, SHUT_RDWR);
    shutdown(client_socket, SHUT_RDWR);
    printf("\nserver has left.\n");
    exit(0);
}

int main()
{
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    socklen_t client_address_size = 0;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr("0.0.0.0");

    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        printf("error - bind\n change port\n");
        exit(0);
    }

    printf("waiting for client to connect...\n");
    listen(server_socket, 1);
       
    client_address_size = sizeof(client_address);
    client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_size);

    if(client_socket>=0)
        printf("client is in chat.\n");

    signal(SIGINT, sigint_handler);
    while (1)
    {
        char server_msg[BUFFER] = {0};
        char client_msg[BUFFER] = {0};
        printf("waiting for message from client... \n");
        recv(client_socket, client_msg, BUFFER, 0);
        printf("client: %s \n", client_msg);

        printf("send a message to client:\n");
        scanf("%s", server_msg);
        send(client_socket, server_msg, BUFFER, 0);
    }
    return 0;
}
