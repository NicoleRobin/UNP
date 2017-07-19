/*
 * gcc -o udpSvr_01 ./udpSvr_01.c
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
#define BUF_LEN 1024*1024

int main(int argc, char **argv)
{
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd == -1)
	{
		perror("socket");
		return errno;
	}

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	// addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_addr.s_addr = inet_addr("192.168.1.114");
	addr.sin_port = htons(PORT);

	if (-1 == bind(fd, (struct sockaddr*)&addr, sizeof(addr)))
	{
		perror("bind");
		return errno;
	}

	char buf[BUF_LEN];

	while(1)
	{
		memset(buf, 0, BUF_LEN);
		int iRet = recv(fd, buf, BUF_LEN, 0);
		printf("recv data len [%d]\n", iRet);
	}
	close(fd);

	return 0;
}
