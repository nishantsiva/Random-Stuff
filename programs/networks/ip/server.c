#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 3490
#define BACKLOG 10
#define MAXSIZE 1024

void evaluate(char *buffer){
	int i,j,l,temp,iter,values[5];
	char c;
	iter = 0;
    temp = 0;
    l = 0;
    do{
    	c = buffer[iter];
        if(c>='0' && c<='9'){
    		temp = temp*10 + (c - '0');
    		continue;
    	}
    	values[l++] = temp;
    	temp = 0;
    }while(buffer[iter++] != '\0');
    if((values[0]&values[2]) == (values[1]&values[2]))
		sprintf(buffer,"Same Network.");
	else
		sprintf(buffer,"Different Network.");
}

void TCP()
{
    struct sockaddr_in server;
    struct sockaddr_in dest;
    int status,socket_fd, client_fd,num;
    socklen_t size;

    char buffer[MAXSIZE];
    char *buff;
    int yes =1;

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0))== -1) {
        fprintf(stderr, "Socket failure!!\n");
        exit(1);
    }

    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        fprintf(stderr, "Set Socket failed\n");
        exit(1);
    }
    memset(&server, 0, sizeof(server));
    memset(&dest,0,sizeof(dest));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY; 
    if ((bind(socket_fd, (struct sockaddr *)&server, sizeof(struct sockaddr )))== -1)    {
        fprintf(stderr, "Binding Failure\n");
        exit(1);
    }

    if ((listen(socket_fd, BACKLOG))== -1){
        fprintf(stderr, "Listening Failure\n");
        exit(1);
    }

    while(1) {

        size = sizeof(struct sockaddr_in);

        if ((client_fd = accept(socket_fd, (struct sockaddr *)&dest, &size))==-1 ) {
            perror("accept");
            exit(1);
        }
        printf("Server got connection from client %s\n", inet_ntoa(dest.sin_addr));

        while(1) {

                if ((num = recv(client_fd, buffer, MAXSIZE,0))== -1) {
                        perror("recv");
                        exit(1);
                }
                else if (num == 0) {
                        printf("Connection closed\n");
                        break;
                }
                buffer[num] = '\0';
                printf("Server:Msg Received %s\n", buffer);
                evaluate(buffer);
                if ((send(client_fd,buffer, strlen(buffer),0))== -1) 
                {
                     fprintf(stderr, "Failure Sending Message\n");
                     close(client_fd);
                     break;
                }

                printf("Server:Msg being sent: %s\nNumber of bytes sent: %d\n",buffer, (int)strlen(buffer));

        } 
        close(client_fd);
    }

    close(socket_fd);
}
void UDP(){
	int sockfd,n;
   	struct sockaddr_in servaddr,cliaddr;
   	socklen_t len;
   	char mesg[MAXSIZE];

   	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	memset(&servaddr, 0, sizeof(servaddr));
   	servaddr.sin_family = AF_INET;
   	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
   	servaddr.sin_port=htons(PORT);
   	bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

   	while(1){
	  	len = sizeof(cliaddr);
	  	n = recvfrom(sockfd,mesg,MAXSIZE,0,(struct sockaddr *)&cliaddr,&len);
	  	printf("\nServer got connection from client %s\n", inet_ntoa(cliaddr.sin_addr));
	  	
	  	mesg[n] = '\0';
	  	printf("Server:Msg Received: %s\n",mesg);
	  	evaluate(mesg);
	  	sendto(sockfd,mesg,n,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
	  	printf("Server:Msg being sent: %s\nNumber of bytes sent: %d\n\n",mesg, (int)strlen(mesg));
   	}
}

int main(){
	int choice = -1;
	while(choice != 1 && choice != 2){
		printf("Choose the protocol\n\t1.TCP\n\t2.UDP\nChoice : ");
		scanf("%d",&choice);	
	}
	if(choice == 1){
		TCP();
	}
	else{
		UDP();
	}
	
}
