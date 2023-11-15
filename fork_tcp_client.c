#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#define PORT 8080

struct sockaddr_in serv_addr;
int sock;

int main(){
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock<0){
		perror("Failure creating socket");
		exit(EXIT_FAILURE);
	}
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr.s_addr)<=0){
		perror("Invalid address\n");
		exit(EXIT_FAILURE);
	}
	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))<0){
		perror("Connection failed\n");
		exit(EXIT_FAILURE);
	}
	pid_t pid = fork();
	char msg[200], rcv_msg[200];
	if(pid>0){
		while(1){
			memset(msg, 0, sizeof(msg));
			gets(msg);
			send(sock, msg, strlen(msg), 0);
		}
	}else if(pid==0){
		while(1){
			memset(rcv_msg, 0, sizeof(rcv_msg));
			int read_val = read(sock, rcv_msg, 200);
			printf("Message from server: %s\n", rcv_msg);
		}
	}else{
		perror("Error creating processes");
		exit(EXIT_FAILURE);
	}
	return 0;
}
