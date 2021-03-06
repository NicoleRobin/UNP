#include "unp.h"

int main(void)
{
	int listenfd, connfd;
	pid_t childid;
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);
	Bind(listenfd, (SA*)&servaddr, sizeof(servaddr));
	Listen(listenfd, LISTENQ);
	for (; ; )
	{
		clilen = sizeof(cliaddr);
		connfd = Accept(listenfd, (SA*)&cliaddr, &clilen);
		if ((childid = Fork()) == 0)
		{ // child process
			Close(listenfd); // close listenfd
			str_echo(connfd); // protcess the request
			exit(0);
		}
		Close(connfd); // parent closes connected socket
	}
}
