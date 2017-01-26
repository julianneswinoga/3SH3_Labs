PROJECT = main

all: $(PROJECT)

$(PROJECT): $(PROJECT).o
	gcc $(PROJECT).o -o $(PROJECT)

$(PROJECT).o: $(PROJECT).c
	gcc -c $(PROJECT).c -std=c99 -Wall

clean: $(PROJECT).o
	rm $(PROJECT) $(PROJECT).o
