/*
 * gcc -o udpCli_01 ./udpCli_01.c
 */
// 测试包的大小大于UDP数据包最大时出现什么情况
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

const int PORT = 8080;
#define BUF_LEN 2000

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
	addr.sin_addr.s_addr = inet_addr("45.76.168.153");
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

	char buf[BUF_LEN] = "";
	for (int i = 0; i < BUF_LEN - 1; ++i)
	{
		buf[i] = 'a';
	}

	int iCount = 0;
	while (1)
	{
		int iRet = sendto(fd, buf, BUF_LEN, 0, (struct sockaddr*)&addr, sizeof(addr));
		if (iRet == -1)
		{
			perror("sendto");
			break;
		}
		else
		{
			printf("send data %d \n", iRet);
			break;
		}

		scanf("%d", &iCount);
	}
	printf("Send package count %d\n", iCount);
	close(fd);

	return 0;
}
