/*
 * gcc -o udpCli ./udpCli.c
 */
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
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
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(PORT);

	// get send buffer size
	int iWBufSize;
	socklen_t optLen = sizeof(iWBufSize);
	getsockopt(fd, SOL_SOCKET, SO_SNDBUF, &iWBufSize, &optLen);
	printf("Write buffer size = %d\n", iWBufSize);

	int iRBufSize;
	optLen = sizeof(iRBufSize);
	getsockopt(fd, SOL_SOCKET, SO_RCVBUF, &iRBufSize, &optLen);
	printf("Read buffer size = %d\n", iRBufSize);

	char buf[1500] = "hello world!";
	int iCount = 0;
	while (1)
	{
		sprintf(buf, "%d", iCount);
		int iRet = sendto(fd, buf, 1500, 0, (struct sockaddr*)&addr, sizeof(addr));
		if (iRet == -1)
		{
			perror("sendto");
			break;
		}
		else
		{
			// printf("Send data len [%d]\n", iRet);
			iCount++;
		}
		if (iCount % 100 == 0)
		{
			printf("Send package count %d\n", iCount);
			sleep(1);
		}
	}
	printf("Send package count %d\n", iCount);
	close(fd);

	return 0;
}
