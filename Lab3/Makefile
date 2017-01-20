PROJECT = main

CFLAGS = -std=c99 -pthread -lm

all: style $(PROJECT)

$(PROJECT): $(PROJECT).o
	gcc $(CFLAGS) $(PROJECT).o -o $(PROJECT)

$(PROJECT).o: $(PROJECT).c
	gcc $(CFLAGS) -c $(PROJECT).c

clean:
	rm $(PROJECT) $(PROJECT).o
