#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>

#define PORT 1669
#define BUFFER 256


void sigint_handler(int signum){
    printf("\nclient has left.\n");
    exit(0);
}

int main(){   
    int server_socket = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in server_address;    
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr("192.168.43.102");

    connect(server_socket,(struct sockaddr*)&server_address,sizeof(server_address));
    
    signal(SIGINT,sigint_handler);
    while (1)
    {      
        char server_msg[BUFFER] ={0};
        char client_msg[BUFFER] = {0};
        printf("send a message to server: \n");
        scanf("%s", client_msg);
        send(server_socket,client_msg,BUFFER,0);  

        printf("waiting for message from server... \n");
        recv(server_socket,server_msg,BUFFER,0);
        printf("server: %s \n", server_msg);             
    }
    return 0;
}