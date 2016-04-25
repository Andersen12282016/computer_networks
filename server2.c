#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

int main(){
	int sockfd, new_fd, numbytes, sin_size;
	char buf[1000000];
	struct sockaddr_in my_addr;
	struct sockaddr_in their_addr;

	FILE *fp;
        int port;
        printf("Input port  :");
        scanf("%d", &port);


	//TCP socket
	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){
		perror("socket");
		return 1;
	}
        
	//Initail, bind to port
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(port);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	bzero( &(my_addr.sin_zero), 8 );
        
	//binding
	if ( bind(sockfd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr)) == -1 ){
		perror("bind");
		return 1;
	}

	//Start listening
	if ( listen(sockfd, 10) == -1 ){
		perror("listen");
		return 1;
	}

	//Connect
	if ( (new_fd = accept(sockfd, (struct sockaddr*)&their_addr, &sin_size)) == -1 ){
		perror("accept");
		return 1;
	}

        //Open file
        char filename[100];
        read(new_fd, filename, sizeof(filename));
        printf("Received file name  :");
        puts(filename);
        int i;
        for(i=0;i<100;i++ )
        {
            if(filename[i]=='.')
            {
                break;
            }
        }
        char temp[10];
        strcpy(temp, (filename+i));
        strcpy((filename+i), "-b00901026");
        strcpy((filename+i+10), temp);
        printf("New file name       :");
        puts(filename);
        
        if ( (fp = fopen(filename, "wb")) == NULL){
                perror("fopen");
                return 1;
        }

        //Receive file from server
      while(1){
                numbytes = read(new_fd, buf, sizeof(buf));
                printf("read %d bytes, ", numbytes);
                if(numbytes == 0){
                        break;
                }
                numbytes = fwrite(buf, sizeof(char), numbytes, fp);
                printf("fwrite %d bytesn", numbytes);
        }



        printf("\n");
	close(new_fd);
	close(sockfd);
	return 0;
}
