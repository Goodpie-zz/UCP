CC = gcc
CFLAGS = -Wall -ansi -pedantic
OBJ = main.o LinkedList.o
EXEC = main

$(EXEC):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)
	
main.o: main.c main.h LinkedList.h
	$(CC) $(CFLAGS) -c main.c
	
LinkedList.o: LinkedList.c LinkedList.h
	$(CC) $(CFLAGS) -c LinkedList.c
	
clean:
	rm -f $(OBJ)
	
very-clean:
	rm -f $(OBJ) $(EXEC)