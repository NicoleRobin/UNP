CC = gcc
INCDIR = ../include
LIBDIR = ../lib
FLAG = -I${INCDIR} -L${LIBDIR} ${DEBUGFLAG}

all:daytimetcpcli daytimetcpsrv daytimetcpcli1 daytimetcpsrv1

daytimetcpcli:daytimetcpcli.c
	${CC} -o $@ $< ${FLAG} -lunp

daytimetcpsrv:daytimetcpsrv.c
	${CC} -o $@ $< ${FLAG} -lunp

daytimetcpcli1:daytimetcpcli1.c
	${CC} -o $@ $< ${FLAG} -lunp

daytimetcpsrv1:daytimetcpsrv1.c
	${CC} -o $@ $< ${FLAG} -lunp

.PHONY:clean
clean:
	rm -rf daytimetcpcli daytimetcpsrv daytimetcpcli1 daytimetcpsrv1
