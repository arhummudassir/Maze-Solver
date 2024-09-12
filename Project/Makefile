
CFLAGS = -Wno-implicit-function-declaration

all: project

project: memory.o ant.o interpreter.o main.o
	@echo "Linking and producing application"
	gcc $(CFLAGS) memory.o ant.o interpreter.o main.o -o project

main.o: main.c
	@echo "Compiling main file"
	gcc $(CFLAGS) -c main.c

ant.o: ant.c
	@echo "Compiling ant file"
	gcc $(CFLAGS) -c ant.c

memory.o: memory.c
	@echo "Compiling memory file"
	gcc $(CFLAGS) -c memory.c

inter.o: interpreter.c
	@echo "Compiling interpreter file"
	gcc $(CFLAGS) -c interpreter.c

clean : 
	@echo "Cleaning everything but the source files"
	rm main.o memory.o ant.o interpreter.o