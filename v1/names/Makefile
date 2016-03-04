include ../Make.defines

PROGS=hostent

all:${PROGS}

hostent:hostent.c
	${CC} -o $@ $< ${FLAG} -lunp

.PHONY:clean
clean:
	rm -rf ${PROGS}
