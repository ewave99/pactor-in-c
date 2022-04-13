SRC = \
	  main.c \
	  compile.c \
	  stack.c

OBJ = ${SRC:.c=.o}

#INCS = -I. -I/usr/include

CFLAGS = -Wall ${INCS}

all: pactor

pactor: ${OBJ}
	cc -o $@ ${OBJ} ${LIBS}

.c.o:
	${CC} -c ${CFLAGS} $<

clean:
	rm -f pactor ${OBJ}
