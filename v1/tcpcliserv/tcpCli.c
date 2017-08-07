/*
 * gcc -o tcpCli ./tcpCli.c
 */
#include <unistd.h>
#include <fcntl.h>
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
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1)
	{
		perror("socket");
		return errno;
	}

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("45.76.168.153");
	addr.sin_port = htons(PORT);

	if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
	{
		perror("connect");
		return errno;
	}

	fcntl(fd, F_SETFL, O_NONBLOCK);

	// get send buffer size
	int iWBufSize;
	socklen_t optLen = sizeof(iWBufSize);
	getsockopt(fd, SOL_SOCKET, SO_SNDBUF, &iWBufSize, &optLen);
	printf("Write buffer size = %d\n", iWBufSize);

	int iRBufSize;
	optLen = sizeof(iRBufSize);
	getsockopt(fd, SOL_SOCKET, SO_RCVBUF, &iRBufSize, &optLen);
	printf("Read buffer size = %d\n", iRBufSize);

	char buf[65536] = "hello world!";
	while (1)
	{
		int iRet = send(fd, buf, 65536, 0); 
		if (iRet == -1)
		{
			perror("send");
		}
		else
		{
			printf("Send data len [%d]\n", iRet);
			printf("Send content [%s]\n", buf);
		}
		sleep(2);
	}
	close(fd);

	return 0;
}
