#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdbool.h>
#define PORT 8080

int server_fd, opt=1;
struct sockaddr_in address;
int counter = 0;

void handle_client(){
	if(listen(server_fd, 5)<0){
		perror("Failure while listening");
		exit(EXIT_FAILURE);
	}
	int new_socket, addr_len = sizeof(address);
	if((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addr_len))<0){
		perror("Failure accepting connection");
		exit(EXIT_FAILURE);
	}
	int client_no = counter++;
	printf("New connection found! Client %d joined in\n", client_no);
	pid_t pid = fork();
	char msg[200], rcv_msg[200];
	if(pid>0){
		handle_client();
	}else if(pid==0){
		pid_t pid1 = fork();
		if(pid1>0){
			while(1){
				memset(msg, 0, sizeof(msg));
				gets(msg);
				send(new_socket, msg, strlen(msg), 0);
			}
		}else if(pid1==0){
			while(1){
				memset(rcv_msg, 0, sizeof(rcv_msg));
				int read_val = read(new_socket, rcv_msg, 200);
				printf("Message from client %d: %s\n", client_no, rcv_msg);
			}
		}
	}else{
		perror("Failure creating processes");
		exit(EXIT_FAILURE);
	}
}


int main(){
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(server_fd < 0){
		perror("Socket could not be created");
		exit(EXIT_FAILURE);
	}
	if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
		perror("Socket option failure");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
	if(bind(server_fd, (struct sockaddr*)&address, (socklen_t)sizeof(address))<0){
		perror("Binding error");
		exit(EXIT_FAILURE);
	}
	printf("Server online! Waiting for connections...\n");
	handle_client();
	return 0;
}
