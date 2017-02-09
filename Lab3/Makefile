PROJECT = main

CFLAGS = -std=c99 -pthread -lm
CC = colorgcc

all: $(PROJECT)

$(PROJECT): $(PROJECT).o
	$(CC) $(CFLAGS) $(PROJECT).o -o $(PROJECT)

$(PROJECT).o: $(PROJECT).c
	$(CC) $(CFLAGS) -c $(PROJECT).c

clean:
	rm $(PROJECT) $(PROJECT).o
