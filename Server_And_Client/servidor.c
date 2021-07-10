#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080

int main(int argc, char const *argv[])
{
	int server_fd, new_socket, valread;
	// Struct sockaddr_in: struct básica para todas as syscalls
	// e funções que lidam com endereço de internet
		struct sockaddr_in address;

	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	char *hello = "Mensagem aqui, do servidor!";

	// Construindo socket
		server_fd = socket(AF_INET, SOCK_STREAM,0);

	// Verificando se deu algum erro
		if(server_fd == 0)
		{
			perror("Falha no Socket"); // printa msg de erro do sys
			exit(EXIT_FAILURE); 			// termina o processo
		}

		

	// Forçando o socket a se conectar a porta 8080
	// com a função "setsockopt", que serve para
	// ver e atribuir opções personalizadas no socket
		if(setsockopt(server_fd, SOL_SOCKET, 
	   	SO_REUSEADDR | SO_REUSEPORT, &opt, 
			sizeof(opt))){
	
			perror("setsockopt");
			exit(EXIT_FAILURE);
		}

	/* Usando vars da struct sockaddr_in */

	// AF_INET: tipos de endereços com quem o socket vai se comunicar
		address.sin_family = AF_INET;

		// INADDR_ANY: liga o socket a todas as interfaces disponíveis
		address.sin_addr.s_addr = INADDR_ANY; 
		
		// htons: funcão usada para converter a ordem dos bytes do host para big-endian, para transmti-los na rede
		address.sin_port = htons( PORT );  
		
	
	// Forçando o socket a se conectar a porta 8080
	
	// Fazendo a ligação
		int myBind = bind(server_fd, (struct sockaddr *)&address,
												sizeof(address));
	// Verficado se há erros											
		if(myBind < 0){
	
			perror("a ligação falhou");
			exit(EXIT_FAILURE);
		}
	
	
	// Colocando o servidor para ouvir no socket
		// All hail, the Listener! :v
		int listener = listen(server_fd, 3);
	// Verificando se há erros 
		if(listener < 0){
		
			perror("listen");
			exit(EXIT_FAILURE);
		}


	if((new_socket = accept(server_fd, (struct sockaddr *)&address,
									(socklen_t*)&addrlen)) < 0){
									
		perror("accept");
		exit(EXIT_FAILURE);
	}
	valread = read(new_socket, buffer, 1024);
	printf("%s\n",buffer);
	send(new_socket, hello, strlen(hello), 0);
	printf("Mensagem de Alooou enviada kkk\n");

	return 0;
}
