PROJECT = main

all: style $(PROJECT)

style: $(PROJECT) ~/.astylerc
	astyle $(PROJECT).c

$(PROJECT): $(PROJECT).o
	gcc $(PROJECT).o -o $(PROJECT)

$(PROJECT).o: $(PROJECT).c
	gcc -c $(PROJECT).c

clean: $(PROJECT).o
	rm $(PROJECT) $(PROJECT).o
