#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(int argc , char *argv[])
{
    char ip[20];
    int port;
    int sock;
    struct sockaddr_in server;
    char message[1000];
    char server_reply[2000];
    puts("Please input the ip and port of the server~~");
    printf("IP address  :");
    scanf("%s", ip);
    printf("Port Number :");
    scanf("%d", &port);
    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
        return 1;
    }
    puts("Socket created");
     
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
 
    
    if(connect(sock , (struct sockaddr *)&server , sizeof(server))<0)
    {
        printf("fail to connect!");
    } 
    puts("Connected");
    
    read(sock, server_reply, sizeof(server_reply));
    puts(server_reply);
    int time = 100;
    while(time)
    {
        puts("Please type a sentence,");
        puts("and the server will send it back reversed!");
        printf("Input  :");
        scanf(" %[^\n]", message);
        puts("Send it to the server...");
        write(sock, message, sizeof(message));
        puts("Wait for the server reply...");
        read(sock, server_reply, sizeof(server_reply));
        printf("Result :");
        puts(server_reply);
        time--;
    }
    puts("All works are done!");
    close(sock);
    return 0;
}
