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

void echo_cli(int fd)
{
	char szBuf[BUF_SIZE + 1];

	string str;
	while (cin >> str)
	{
		write(fd, str.c_str(), str.length());

		bzero(szBuf, sizeof(szBuf));
		read(fd, szBuf, BUF_SIZE);

		cout << "You say:" << szBuf << endl;
	}
}

int main(int argc, char **argv)
{
	int sock_cli = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == sock_cli)
	{
		perror("socket error");
		return errno;
	}

	struct sockaddr_in addr_svr;
	memset(&addr_svr, 0, sizeof(addr_svr));
	addr_svr.sin_family = AF_INET;
	addr_svr.sin_port = htons(ECHO_PORT);
	addr_svr.sin_addr.s_addr = INADDR_ANY;

	if (-1 == connect(sock_cli, (struct sockaddr*)&addr_svr, sizeof(addr_svr)))
	{
		perror("connect error");
	}

	echo_cli(sock_cli);

	close(sock_cli);

	return 0;
}
