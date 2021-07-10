/* Clente: estudando programação de socket. 
 * @eduardopazzz cyberundead */

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

// Constante com a porta a ser usada:
#define PORT 8080

// MAIN func
int main(int argc, char const *argv[])
{
	int sock = 0, valread;	
	// Chamando struct 'sockaddr_in', criando 'serv_addr';
	struct sockaddr_in serv_addr;

	char *hello = "Eaee, daqui, do cliente!!?";
	char buffer[1024] = {0};

	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\nErro na criação do socket\n");
	}

	// usando a var com os atributos da struct 'sockaddr_in'		

									// Usando IPv4
	serv_addr.sin_family = 	AF_INET;
									// Usando a nossa constante 'PORTA'
	serv_addr.sin_port = 	htons(PORT);

	// Converter endereços IPv4 e IPv6 de texto para binário
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)	 {
		printf("\nEndereço inválido / Endereço não suportado\n");
		return -1;
	}

	if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
	
		printf("\nConexão Falhou \n");
		return -1;
	}

	send(sock, hello, strlen(hello), 0);
	printf("Hello mensagem enviada\n");

	valread = read(sock, buffer, 1024);

	printf("%s\n",buffer);

	return 0;
}
