#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char* argv[]){
	int sockfd, numbytes;
	char buf[1000000];
	struct sockaddr_in address;
        struct stat filestat;
	FILE *fp;
        char filename[100];
        char ip[20];
        int port;
        printf("Input ip          :");
        scanf("%s", ip);
        printf("Input port        :");
        scanf("%d", &port);
        printf("Input file name   :");
        scanf("%s", filename);
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

	//Connect to file
	if ( lstat(filename, &filestat) < 0){
                return 1;
        }
        printf("The file size is %lun", filestat.st_size);

        fp = fopen(filename, "rb");

	//Connect to server
	if ( connect(sockfd, (struct sockaddr*)&address, sizeof(struct sockaddr)) == -1){
		perror("connect");
		return 1;
	}


        write(sockfd, filename, sizeof(filename));

//Sending file

        while(!feof(fp)){
                numbytes = fread(buf, sizeof(char), sizeof(buf), fp);
                printf("fread %d bytes, ", numbytes);
                numbytes = write(sockfd, buf, numbytes);
                printf("Sending %d bytesn",numbytes);
        }


	fclose(fp);
	close(sockfd);
	return 0;
}
