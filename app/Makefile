APP_NAME=app
CC=gcc
CFLAGS=-Wall -Wextra
LIBS=-lSDL2 -lpthread
SRC=main.c engine.c device.c

all:
	$(CC) $(CFLAGS) $(SRC) $(LIBS) -o $(APP_NAME)
clean:
	rm -rf $(APP_NAME)
