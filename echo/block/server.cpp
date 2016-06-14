#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cerrno>

using namespace std;

const int ECHO_PORT = 2000;
const int BUF_SIZE = 1024;

void echo_svr(int fd)
{
	char szBuf[BUF_SIZE + 1];

	while (true)
	{
		bzero(szBuf, sizeof(szBuf));
		if (0 == read(fd, szBuf, BUF_SIZE))
		{
			break;
		}
		
		cout << szBuf << endl;
		write(fd, szBuf, strlen(szBuf));
	}
}

int main(int argc, char **argv)
{
	int sock_svr = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == sock_svr)
	{
		perror("socket error");
		return errno;
	}

	struct sockaddr_in addr_svr;
	memset(&addr_svr, 0, sizeof(addr_svr));
	addr_svr.sin_family = AF_INET;
	addr_svr.sin_port = htons(ECHO_PORT);
	addr_svr.sin_addr.s_addr = INADDR_ANY;

	if (-1 == bind(sock_svr, (struct sockaddr*)&addr_svr, sizeof(addr_svr)))
	{
		perror("bind error");
		return errno;
	}

	if (-1 == listen(sock_svr, 5))
	{
		perror("listen error");
		return errno;
	}

	int sock_cli;
	struct sockaddr_in addr_cli;
	socklen_t len;
	while (true)
	{
		sock_cli = accept(sock_svr, (struct sockaddr*)&addr_cli, &len);
		if (-1 == sock_cli)
		{
			perror("accept error");
			continue;
		}
		
		cout << "Receive connect from " << inet_ntoa(addr_cli.sin_addr) << endl;
		echo_svr(sock_cli);

		close(sock_cli);
	}

	close(sock_svr);

	return 0;
}
