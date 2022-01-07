OBJ=main.o student.o teacher.o tools_t.o principal.o tools_p.o tools_s.o tools.o
CC=gcc
BIN=manage_system
FLAG=-Wall -Werror -DDEBUG -g
STD=-std=gnu99
LIB=-lm
INCLUDE=-I.
all : $(OBJ)
	$(CC) -o $(BIN) $(OBJ) $(LIB)

main.o:main.c teacher.h principal.h student.h
	$(CC) $(STD) $(FLAG) -c main.c 
teacher.o:teacher.c teacher.h tools_t.h 
	$(CC) $(STD) $(FLAG) -c teacher.c
student.o:student.c student.h tools_s.h
	$(CC) $(STD) $(FLAG) -c student.c
principal.o:principal.c principal.h tools_p.h
	$(CC) $(STD) $(FLAG) -c principal.c
tools_t.o:tools_t.c tools_t.h tools.h
	$(CC) $(STD) $(FLAG) -c tools_t.c
tools_p.o:tools_p.c tools_p.h
	$(CC) $(STD) $(FLAG) -c tools_p.c
tools_s.o:tools_s.c tools_s.h
	$(CC) $(STD) $(FLAG) -c tools_s.c
tools.o:tools.c tools.h
	$(CC) $(STD) $(FLAG) -c tools.c
	
clean:
	rm $(BIN) $(OBJ) *~

