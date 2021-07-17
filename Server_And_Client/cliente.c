/* Cliente; estudando programação de socket. 
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
	
	// Chamando struct 'sockaddr_in', criando 'serv_addr';
			struct sockaddr_in serv_addr;

	// Variáveis
			int sock = 0, valread;						  // var para socket
			char *hello = "Eae, aqui do cliente!!?"; // Mensagem para o servidor
			char buffer[1024] = {0};                 // buffer para o read

	// Criando socket
			sock = socket(AF_INET, SOCK_STREAM, 0);

	// Verificando se ocorreu erro
			if(sock < 0)
			{
				printf("\nErro na criação do socket\n");
			}		

	// usando a var com os atributos da struct 'sockaddr_in'		

									// Usando IPv4
	serv_addr.sin_family = 	AF_INET;
									// Usando a nossa constante 'PORTA'
	serv_addr.sin_port = 	htons(PORT);

	// Converter endereços IPv4 e IPv6 de texto para binário
			if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0){
				printf("\nEndereço inválido / Endereço não suportado\n");
				return -1;
			}

	if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
	
		printf("\nConexão Falhou \n");
		return -1;
	}

	send(sock, hello, strlen(hello), 0);
	printf("Mensagem enviada ao server\n");

	valread = read(sock, buffer, 1024);

	// Mostrando mesagem recebida na tela 
	printf("Msg recebida: %s\n",buffer);

	return 0;
}
