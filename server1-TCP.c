#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

int main (int argc , char *argv[])
{
/*  char s[100];
    scanf("%s", s);
    printf("%s", s);
    printf("\n");
*/
    int port;
    puts("Please give a port to the server~~");
    printf("Port Number  :");
    scanf("%d", &port);
    int clientfd, c;
    struct sockaddr_in c_addr;
    int sockfd = socket(AF_INET, SOCK_STREAM,0);
    if(sockfd == -1)
    {
        printf("Failed to create socket!");
        return 1;
    }
    puts("Socket created!");

    struct sockaddr_in dest;
    dest.sin_family = AF_INET;
    dest.sin_port = htons(port);
    dest.sin_addr.s_addr = INADDR_ANY;
    int ifb = bind(sockfd, (struct sockaddr*) &dest, sizeof(dest));
    if(ifb<0)
    {
        printf("Bind failed!");
        return 1;
    }
    puts("Finish binding!");

    listen(sockfd, 5);
    puts("Waiting for incoming connections...");
    c = sizeof(c_addr);
    clientfd = accept(sockfd, (struct sockaddr*) &c_addr, (socklen_t*)&c);
    if (clientfd < 0)
    {
        perror("Accept failed!");
        return 1;
    }
    puts("Connection accepted!!");
    
    char buf[1000] = "Hello, client!"; 
    write(clientfd, buf, sizeof(buf));
    while(buf[0]!='\0')
    {
        puts("Wait for the client...");
        read(clientfd, buf, sizeof(buf));    
        puts("The string sent from the clinet:");
        puts(buf);
        int f;
        for(f = 0; f <1000; f++)
        {
            if(buf[f]=='\0')
            break;
        }
        int i;
        int j;
        for(j = 0; j<f;j++)
        {
            buf[j] = toupper(buf[j]);
        }
        for(i = 0; i <(f/2);i++)
        {
            char t = buf[i];
            buf[i]=buf[f-1-i];
            buf[f-1-i]=t;
        }
        puts("The string after reversed:");
        puts(buf);
        puts("Send it back to the client...");
        write(clientfd, buf, sizeof(buf));
        puts("Finish sending!");
     }
    puts("All the works are done!");
    close(sockfd);
    return 0;
}

















