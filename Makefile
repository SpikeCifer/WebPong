create: pong.c ball.c pad.c
	cc -o pong pong.c ball.c pad.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
