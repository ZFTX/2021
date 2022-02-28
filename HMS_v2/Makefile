CC=g++
FLAG=-Wall -Werror
OBJ=main.o hotel.o tools.o
BIN=HMS

all:$(OBJ)
	$(CC) $(OBJ) -o $(BIN) && ./$(BIN) hotel_room.txt

%.o:%.cpp
	$(CC) -c $(FLAG) $< -o $@

clean:
	rm -rf *~ *.h.gch
	rm -rf $(OBJ) $(BIN)
