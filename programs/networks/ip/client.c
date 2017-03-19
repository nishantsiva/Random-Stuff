#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 3490
#define MAXSIZE 1024

void getinput(char *buffer){
	struct in_addr addr;
	char ip[INET_ADDRSTRLEN];
	int ip1,ip2,subnet,flag;
	printf("Enter 1st IP Address : ");
	flag=0;
	do{
		if(flag){
			printf("Enter valid IP : ");
		}
		scanf("%s",ip);
		flag = 1;
	}
	while(!inet_pton(AF_INET, ip, &addr));
	ip1 = addr.s_addr;
	printf("Enter 2nd IP Address : ");
	flag=0;
	do{
		if(flag){
			printf("Enter valid IP : ");
		}
		scanf("%s",ip);
		flag = 1;
	}
	while(!inet_pton(AF_INET, ip, &addr));
	ip2 = addr.s_addr;
	printf("Enter subnet mask : ");
	flag=0;
	do{
		if(flag){
			printf("Enter valid IP : ");
		}
		scanf("%s",ip);
		flag = 1;
	}
	while(!inet_pton(AF_INET, ip, &addr));
	subnet = addr.s_addr;
    sprintf(buffer,"%d %d %d",ip1,ip2,subnet);
}

void TCP(char *addr)
{
    struct sockaddr_in server_info;
    struct hostent *he;
    int socket_fd,num;
    char buffer[MAXSIZE];

    if ((he = gethostbyname(addr))==NULL) {
        fprintf(stderr, "Cannot get host name\n");
        exit(1);
    }

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0))== -1) {
        fprintf(stderr, "Socket Failure!!\n");
        exit(1);
    }

    memset(&server_info, 0, sizeof(server_info));
    server_info.sin_family = AF_INET;
    server_info.sin_port = htons(PORT);
    server_info.sin_addr = *((struct in_addr *)he->h_addr);
    if (connect(socket_fd, (struct sockaddr *)&server_info, sizeof(struct sockaddr))<0) {
        fprintf(stderr, "Connection Failure\n");
        exit(1);
    }
	getinput(buffer);
    if ((send(socket_fd,buffer, strlen(buffer),0))== -1) {
    	fprintf(stderr, "Failure Sending Message\n");
      	close(socket_fd);
      	exit(1);
    }
    else {
        printf("Client:Message being sent: %s\n",buffer);
        num = recv(socket_fd, buffer, sizeof(buffer),0);
        if ( num <= 0 )
        {
        	printf("Either Connection Closed or Error\n");
        	close(socket_fd);
        	exit(1);
        }

        buffer[num] = '\0';
        printf("Client:Message Received From Server: %s\n",buffer);
   	}
  	close(socket_fd);

}

void UDP(char *addr){
	int sockfd,n;
   	struct sockaddr_in servaddr,cliaddr;
   	char sendline[MAXSIZE];
   	char recvline[MAXSIZE];

   	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	memset(&servaddr, 0, sizeof(servaddr));
   	servaddr.sin_family = AF_INET;
   	servaddr.sin_addr.s_addr=inet_addr(addr);
   	servaddr.sin_port=htons(PORT);
	getinput(sendline);
   	sendto(sockfd,sendline,strlen(sendline),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
   	printf("Client:Message being sent: %s\n",sendline);
  	n=recvfrom(sockfd,recvline,MAXSIZE,0,NULL,NULL);
  	recvline[n]='\0';
  	printf("Client:Message Received From Server: %s\n",recvline);
   	close(sockfd);
}

int main(int argc, char *argv[]){
	int choice = -1;
	if (argc != 2) {
        fprintf(stderr, "Usage: client hostname\n");
        exit(1);
    }
	while(choice != 1 && choice != 2){
		printf("Choose the protocol\n\t1.TCP\n\t2.UDP\nChoice : ");
		scanf("%d",&choice);	
	}
	if(choice == 1){
		TCP(argv[1]);
	}
	else{
		UDP(argv[1]);
	}
	
}
