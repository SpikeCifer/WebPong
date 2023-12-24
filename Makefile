CC=cc
CLFAGS=-I
DEPS=ball.h pad.h
LIBS=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

build: pong.o ball.o pad.o
	$(CC) -o pong pong.o ball.o pad.o $(LIBS)
