#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
int main(){
	int sockfd, new_fd, numbytes, sin_size;
	char buf[10];
	struct sockaddr_in my_addr;
	struct sockaddr_in their_addr;
        int port;
        printf("Input port  :");
        scanf("%d", &port);
        int a[4];
        int guess[4];
        srand(time(NULL));
        a[0]=(rand()%10);
        a[1]=a[0];
        a[2]=a[0];
        a[3]=a[0];
        while(a[1]==a[0])
        {
            a[1]=(rand()%10);
        }
        while((a[2]==a[0])||(a[2]==a[1]))
        {
            a[2]=(rand()%10);
        }
        while((a[3]==a[0])||(a[3]==a[1])||(a[3]==a[2]))
        {
            a[3]=(rand()%10);
        }
        printf("%d",a[0]);
        printf("%d",a[1]);
        printf("%d",a[2]);
        printf("%d",a[3]);
        printf("\n");
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

        char t[5];
      while(t[0]!='4'){
                read(new_fd, buf, sizeof(buf));
                guess[0] = (int)(buf[0]) -48;
                guess[1] = (int)(buf[1]) -48;
                guess[2] = (int)(buf[2]) -48;
                guess[3] = (int)(buf[3]) -48;
                puts(buf);
                int i;
                int j;
                int ans[2] = {0,0};
                for(i = 0; i<4; i++)
                {
                    for(j = 0 ; j<4; j++)
                    {
                        if(guess[i]==a[j])
                        {
                            if(i==j) ans[0]+=1;
                            else
                              ans[1]+=1;
                        }
                    }
                }
                t[0] = (char)(ans[0]+48);
                t[1] = 'A';
                t[2] = (char)(ans[1]+48);  
                t[3] = 'B';
                t[4] = '\0';
                write(new_fd, t, sizeof(t));
                puts(t);
                if (t[0]=='4') break;
              }
        printf("\n");
	close(new_fd);
	close(sockfd);
	return 0;
}
