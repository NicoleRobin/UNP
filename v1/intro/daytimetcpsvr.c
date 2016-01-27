#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <time.h>

#define MAXLINE 512

int main(int argc, char **argv)
{
	int listenfd, connfd;
	struct sockaddr_in servaddr;
	char szBuff[MAXLINE];
	time_t ticks;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(1333); // daytime server

	bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	listen(listenfd, 5);

	for (; ;)
	{
		connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);

		ticks = time(NULL);
		snprintf(szBuff, sizeof(szBuff), "%.24s\r\n", ctime(&ticks));
		write(connfd, szBuff, strlen(szBuff));
		
		close(connfd);
	}

	return 0;
}
