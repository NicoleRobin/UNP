include ../Make.defines

PROGS = tcpserv01 tcpcli01 tcpserv02

all:${PROGS}

tcpserv01:tcpserv01.c
	${CC} ${FLAG} -o $@ $< -lunp

tcpcli01:tcpcli01.c
	${CC} ${FLAG} -o $@ $< -lunp

tcpserv02:tcpserv02.o sigchldwait.o
	${CC} ${FLAG} -o $@ tcpserv02.o sigchldwait.o -lunp

%.o:%.c
	${CC} ${FLAG} -o $@ -c $<

.PHONY:clean
clean:
	rm -rf ${PROGS}
