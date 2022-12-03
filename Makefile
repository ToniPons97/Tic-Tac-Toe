CC=gcc
TARGET=tic-tac-toe

all:
	$(CC) tic-tac-toe.c -o $(TARGET) -lncurses -Wall
clean:
	rm $(TARGET)