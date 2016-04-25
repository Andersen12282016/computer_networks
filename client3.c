#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char* argv[]){
	int sockfd, numbytes;
	char buf[10];
	struct sockaddr_in address;
        char ip[20];
        int port;
        printf("Input ip          :");
        scanf("%s", ip);
        printf("Input port        :");
        scanf("%d", &port);
	//TCP socket
	if ( ( sockfd = socket(AF_INET, SOCK_STREAM, 0) ) == -1 ){
		perror("socket");
		return 1;
	}

	//Initial, connect to port 2323
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = inet_addr(ip);
	bzero( &(address.sin_zero), 8 );

	//Connect to server
	if ( connect(sockfd, (struct sockaddr*)&address, sizeof(struct sockaddr)) == -1){
		perror("connect");
		return 1;
	}
        int i;
        for(i=0;i<10000;i++)
        {
             int k = i;
             int a[4];
             int j;
             for(j=3;j>=0;j--)
             {
               a[j] = k%10;
               k = k/10;
             }          
             if((a[0]-a[1])*(a[0]-a[2])*(a[0]-a[3])*(a[1]-a[2])
                           *(a[1]-a[3])*(a[2]-a[3]) != 0)
             {   
                 char t[5]; 
                 t[0] = (char)(a[0]+48);
                 t[1] = (char)(a[1]+48);
                 t[2] = (char)(a[2]+48);
                 t[3] = (char)(a[3]+48);
                 t[4] ='\0';
                 puts(t);
                 strcpy(buf,t);
                 write(sockfd, buf, sizeof(buf));
                 read(sockfd, buf, sizeof(buf));
                 puts(buf);
             }
             if (buf[0]=='4') break;
        }

	close(sockfd);
	return 0;
}
