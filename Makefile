CC = gcc
CFLAGS = -Wall -ansi -pedantic
CFLAGS_DEBUG = $(CFLAGS) -g
OBJ = main.o LinkedList.o
EXEC = main
DEBUG_EXEC = main_debug

all: $(EXEC) $(DEBUG_EXEC)

$(EXEC):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

$(DEBUG_EXEC):$(OBJ)
	$(CC) $(CFLAGS_DEBUG) $(OBJ) -o $(DEBUG_EXEC)
	
main.o: main.c main.h LinkedList.h
	$(CC) $(CFLAGS) -c main.c
	
LinkedList.o: LinkedList.c LinkedList.h
	$(CC) $(CFLAGS) -c LinkedList.c
	
clean:
	rm -f $(OBJ)
	
very-clean:
	rm -f $(OBJ) $(EXEC)
