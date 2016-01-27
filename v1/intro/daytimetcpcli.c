/*
 * 自己测试的，服务端和客户端都使用13端口，客户端返回错误111，端口修改为1333，功能正常。还未找到原因
 * /
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define MAXLINE 512

int main(int argc, char **argv)
{
	int sockfd, n;
	char recvline[MAXLINE + 1];
	struct sockaddr_in servaddr;

	if (argc != 2)
	{
		printf("error parameter\nUsage:daytimetcpcli <address>\n");
		return 0;
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("socket error[%d]:%s\n", errno, strerror(errno));
		return 0;
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(1333);
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
	{
		printf("inet_pton error for %s\n", argv[1]);
		return 0;
	}

	if (connect(sockfd, (sockaddr*)&servaddr, sizeof(servaddr)) < 0)
	{
		printf("connect error, errno[%d]\n", errno);
		return 0;
	}

	while ((n = read(sockfd, recvline, MAXLINE)) > 0)
	{
		recvline[n] = 0; // null terminate
		if (fputs(recvline, stdout) == EOF)
		{
			printf("fputs error\n");
			return 0;
		}
	}

	if (n < 0)
	{
		printf("read error\n");
		return 0;
	}

	return 0;
}
