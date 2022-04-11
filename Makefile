SRC = \
	  main.c \
	  builtins.c

OBJ = ${SRC:.c=.o}

#INCS = -I. -I/usr/include

CFLAGS = -Wall ${INCS}

all: main

main: ${OBJ}
	cc -o $@ ${OBJ} ${LIBS}

.c.o:
	${CC} -c ${CFLAGS} $<

clean:
	rm -f main ${OBJ}
