/*
 * gcc -o udpSvr ./udpSvr.c
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
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
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

	getchar();

	char buf[1500];
	int iCount = 0;
	while(1)
	{
		memset(buf, 0, 1024);
		int iRet = recv(fd, buf, 1500, 0);
		iCount++;
		// printf("recv data len [%d]\n", iRet);
		printf("Recv package count[%d]\t", iCount);
		printf("recv content [%s]\n", buf);
	}
	close(fd);

	return 0;
}
