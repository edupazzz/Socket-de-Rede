/* JUST A EXAMPLE !CODE =D \o/
 *
 * Studing Network with C language in Linux system
 * @Eduardo Paz-cyberundead 
 *
 * source: https://www.geeksforgeeks.org/socket-programming-cc/
 * setsockopt: https://pubs.opengroup.org/onlinepubs/009695399/functions/setsockopt.html
 * 
 * comments in my mother tongue: PT-BR
 */
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>
/* Criação do Socket */ /* man 2 socket */
    //int sockfd = socket(dominio, tipo, protocolo);
		int sockfd = socket(AF_INET, SOCKS_DGRAM, 0);

/*
		-> sockfd: socket descriptor (um "nome" único usado para 
												referenciar o socket,
							              ), um inteiro 
												(como um identificador de
												 arquivos)

		-> dominio: inteiro, domínio de comunicação e.g, 
						AF_INET(IPv4), AF_INET6(IPv6)

		-> tipo: tipo de comunicação (TCP/IP, UDP)
					SOCKS_STREAM: TCP
					SOCKS_DGRAM: UDP

		-> protocolo: valor para o Internet Protocol(IP),
						  o qual é 0. ( 0 é o mesmo número
						  				    que aparece no campo
											 do protocolo no 
											 cabeçalho de um
											 pacote.
											 Veja no terminal:
											 'man protocols'
											 tbm o arquivo 'protocols'
				    						 /etc/protocols)
END*/


/* Opicional: 
 * Usando Função 'setsockopt' setsockopt - definindo as opções 
   do socket: */        /* Ver também: man setsockopt | man 7 socket */
  	   int setsockopt(int sockfd, int level, int optname, const void *optval
							socklen_t, optlen);

		// int 6 == TCP (veja /etc/protocols)
		setsockopt(server_fd, SOL_SOCKET,
 28       SO_REUSEADDR | SO_REUSEPORT, &opt,
 29       sizeof(opt));  

/* Isso ajuda na manipulação de opções para o socket referido 
 * pelo file descriptor 'sockfd'.
 * Ajuda na reutilização de endereço e porta
 * evita erros como "address already in use"
END*/


/* Bind-"Ligação" */ /* man bind */
		int bind(int sockfd, const struct sockaddr *addr,
				socklen_t addrlen);

/* Após a criação do socket, a função 'bind' liga o socket
 * ao endereço e ao número da porta especificado em 'addr'.
 * Em nosso exemplo, vinculamos o servidor ao localhost,
 * por isso usamos INADDR_ANY para especificar o endereço IP.
 END*/


/* Listen-"Escutar" */ /* man listen */
		int listen(int sockfd, int backlog);
		
/* Colocamos o socket do servidor em modo passivo, 
 * onde esperamos a conexão do cliente para 
 * estabelecer a conexção.
 *
 * O 'backlog' define o comprimento máximo para o
 * qual a fila de conexões pendentes para o socket
 * (nosso 'sockfd') pode crescer.
 * Se uma solicitação de conexão chegar quando a 
 * fila estiver cheia, o cliente pode receber um 
 * erro com a indicação ECONNREFUSED 
 END*/


/* Accept - "Aceitar" */ /* man accept */
		int new_socket = accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);	

/* Ele extrai a primeira solicitação de conexão na fila 
 * de conexões pendentes para o socket de escuta, ('sockfd'), 
 * cria um novo socket conectado e retorna um novo 
 * descritor de arquivo (file-descriptor) referindo-se 
 * a esse socket. 
 *
 * Nesse ponto, a conexão é estabelecida entre o cliente 
 * e o servidor e eles estão prontos para transferir dados.
 * END*/



/*--------STAGES DO CLIENTE--------*/


/* Connect - "conectar" Inicia a conexão a um socket *//* man connect*/

		int connect(int sockfd, const struct sockaddr *addr,
						socklen_t addrlen);

/* A chamada de sistema 'connect()', conecta o socket 
 * referido pelo descritor de arquivo (file-descriptor)
 * sockfd ao endereço especificado por addr. 
 * O endereço e a porta do servidor são especificados em addr. 
 END*/
