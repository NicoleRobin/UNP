CC = gcc
INCDIR = ../include
LIBDIR = ../lib
FLAG = -I${INCDIR} -L${LIBDIR} ${DEBUGFLAG}

all:daytimetcpcli daytimetcpsrv daytimetcpcli1 daytimetcpsrv1 daytimetcpcli2 daytimetcpsrv2 byteorder daytimetcpsrv3 

daytimetcpcli:daytimetcpcli.c
	${CC} -o $@ $< ${FLAG} -lunp

daytimetcpsrv:daytimetcpsrv.c
	${CC} -o $@ $< ${FLAG} -lunp

daytimetcpcli1:daytimetcpcli1.c
	${CC} -o $@ $< ${FLAG} -lunp

daytimetcpsrv1:daytimetcpsrv1.c
	${CC} -o $@ $< ${FLAG} -lunp

daytimetcpcli2:daytimetcpcli2.c
	${CC} -o $@ $< ${FLAG} -lunp

daytimetcpsrv2:daytimetcpsrv2.c
	${CC} -o $@ $< ${FLAG} -lunp

byteorder:byteorder.c
	${CC} -o $@ $< ${FLAG} -lunp

daytimetcpsrv3:daytimetcpsrv3.c
	${CC} -o $@ $< ${FLAG} -lunp

.PHONY:clean
clean:
	rm -rf daytimetcpcli daytimetcpsrv daytimetcpcli1 daytimetcpsrv1 daytimetcpcli2 daytimetcpsrv2 byteorder daytimetcpsrv3
