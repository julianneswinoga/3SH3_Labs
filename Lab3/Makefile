PROJECT = main

CFLAGS = -std=c99 -pthread -lm

all: style $(PROJECT)

style: $(PROJECT).c ~/.astylerc
	astyle $(PROJECT).c

$(PROJECT): $(PROJECT).o
	gcc $(CFLAGS) $(PROJECT).o -o $(PROJECT)

$(PROJECT).o: $(PROJECT).c
	gcc $(CFLAGS) -c $(PROJECT).c

clean:
	rm $(PROJECT) $(PROJECT).o
