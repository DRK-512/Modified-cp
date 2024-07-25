CC = gcc
CFLAGS = -Iinclude -Wall -g

all: modcp

modcp: 
	${CC} ${CFLAGS} src/main.c src/functions.c -o modcp

clean: 
	rm modcp

