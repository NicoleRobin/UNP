/*
 * gcc -o tcpSvr ./tcpSvr.c
 */
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

const int PORT = 8080;

int main(int argc, char **argv)
{
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1)
	{
		perror("socket");
		return errno;
	}

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(PORT);

	if (-1 == bind(fd, (struct sockaddr*)&addr, sizeof(addr)))
	{
		perror("bind");
		return errno;
	}

	if (-1 == listen(fd, 5))
	{
		perror("listen");
		return errno;
	}

	struct sockaddr_in cli_addr;
	socklen_t len = sizeof(cli_addr);
	int client = accept(fd, (struct sockaddr*)&cli_addr, &len);
	if (client == -1)
	{
		perror("accept");
		return errno;
	}
	
	printf("accept an client\n");

	char buf[1024];
	while(1)
	{
		memset(buf, 0, 1024);
		//int iRet = recv(client, buf, 10, 0);
		int iRet = 0;
		printf("recv data len [%d]\n", iRet);
		printf("recv content [%s]\n", buf);
		sleep(2);
	}
	close(fd);

	return 0;
}
