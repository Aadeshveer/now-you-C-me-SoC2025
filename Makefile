CC = g++
CFLAGS = -g

all: main

main: lexer
	$(CC) $(CFLAGS) -o file_lexer.exe ./src/main.cpp ./obj/lexer.o

lexer: object
	$(CC) -c ./src/lexer.h ./src/lexer.cpp
	mv lexer.o ./obj

object:
	mkdir -p obj

clean:
	rm -r ./obj
	rm file_lexer.exe
	rm ./src/lexer.h.gch