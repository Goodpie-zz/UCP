CC = gcc
CFLAGS = -Wall -ansi -pedantic -g
EXEC = main
OBJ = main.o linkedlist.o csvparser.o filereader.o headerinfo.o insertionsort.o

$(EXEC):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

main.o: main.c linkedlist.h csvparser.h filereader.h headerinfo.h boolean.h insertionsort.h
	$(CC) $(CFLAGS) -c main.c

linkedlist.o: linkedlist.c linkedlist.c
	$(CC) $(CFLAGS) -c linkedlist.c

filereader.o: filereader.c filereader.h boolean.h
	$(CC) $(CFLAGS) -c filereader.c

csvparser.o: csvparser.c csvparser.h filereader.h headerinfo.h boolean.h
	$(CC) $(CFLAGS) -c csvparser.c

headerinfo.o: headerinfo.c headerinfo.h linkedlist.h boolean.h
	$(CC) $(CFLAGS) -c headerinfo.c

insertionsort.o: insertionsort.c insertionsort.h linkedlist.h
	$(CC) $(CFLAGS) -c insertionsort.c

clean:
	rm -f $(OBJ)

very-clean:
	rm -f $(OBJ) $(EXEC)
