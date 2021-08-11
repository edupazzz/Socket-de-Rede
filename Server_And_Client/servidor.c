#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080

int main(int argc, char const *argv[])
{
	// Struct sockaddr_in: struct básica para todas as syscalls
	// e funções que lidam com endereço de internet
		struct sockaddr_in address;

/*Variáveis */
	int server_fd, new_socket, valread;
	int opt = 1; // Usar de opção para func: setsockopt
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	char *hello = "Mensagem aqui, do servidor!";
/*Fim Viariáveis */

	// Construindo socket
		server_fd = socket(AF_INET, SOCK_STREAM, 0);

	// Verificando se deu algum erro
		if(server_fd == 0)
		{
			perror("Falha no Socket"); // printa msg de erro do sys
			exit(EXIT_FAILURE); 			// termina o processo
		}

		

	// Forçando o socket a se conectar a porta 8080
	// com a função "setsockopt", que serve para
	// ver e atribuir opções personalizadas no socket
		int sock_opcoes = setsockopt(server_fd, SOL_SOCKET,
											  SO_REUSEADDR | SO_REUSEPORT
											  , &opt, sizeof(opt));
	// Verificando se deu algum erro
		if(sock_opcoes < 0){
	
			perror("setsockopt");
			exit(EXIT_FAILURE);
		}

/* Usando vars da struct sockaddr_in */

	// AF_INET: tipos de endereços com quem o socket vai se comunicar
		address.sin_family = AF_INET;

		// INADDR_ANY: liga o socket a todas as interfaces disponíveis
		address.sin_addr.s_addr = INADDR_ANY; 
		
		// htons: funcão usada para converter a ordem dos bytes do host para big-endian, para transmiti-los na rede
		address.sin_port = htons( PORT );  
		
	
	// Atribuindo um nome ao socket (veja o "man bind")
		int myBind = bind(server_fd, (struct sockaddr *)&address,
												sizeof(address));

	// Verficado se há erros											
		if(myBind < 0){
	
			perror("Atribuição Falhou");
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

	// Criando um novo socket conectado usando a syscall accept
	// (veja o man 2 accept)
		new_socket = accept(server_fd, (struct sockaddr *)&address,
									  (socklen_t*)&addrlen);

	// Verificando se há erros
	if(new_socket< 0){
									
		perror("accept");
		exit(EXIT_FAILURE);
	}

	// Usando variável "valread", para receber a func "read"
	// que vai ler o "buffer"
	valread = read(new_socket, buffer, sizeof(buffer));

	// Mostrando mensagem recebida na tela
	printf("\nMsg Recebida: %s\n",buffer);

	// Enviando mensagem ao Cliente com "send",
	// que serve para enviar uma mensagem à um socket
	send(new_socket, hello, strlen(hello), 0);
	printf("\nMensagem enviada ao Cliente\n");

	return 0;
}
