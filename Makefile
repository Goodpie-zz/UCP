CC = gcc
CFLAGS = -Wall -ansi -pedantic -g
EXEC = main
OBJ = main.o linkedlist.o csvparser.o filereader.o

$(EXEC):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

main.o: main.c main.h linkedlist.h csvparser.h filereader.h
	$(CC) $(CFLAGS) -c main.c

linkedlist.o: linkedlist.c linkedlist.c
	$(CC) $(CFLAGS) -c linkedlist.c

filereader.o: filereader.c filereader.h
	$(CC) $(CFLAGS) -c filereader.c

csvparser.o: csvparser.c csvparser.h filereader.h
	$(CC) $(CFLAGS) -c csvparser.c

clean:
	rm -f $(OBJ)

very-clean:
	rm -f $(OBJ) $(EXEC)
