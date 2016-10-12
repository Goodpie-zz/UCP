CC = gcc
CFLAGS = -Wall -ansi -pedantic -g
EXEC = main
TEST_EXEC = test_main
OBJ = main.o linkedlist.o csvparser.o filereader.o
TEST_OBJ = testcases.o linkedlist.o csvparser.o filereader.o

all: $(EXEC) $(TEST_EXEC)

$(EXEC):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

$(TEST_EXEC):$(TEST_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ) -o $(TEST_EXEC)

main.o: main.c main.h linkedlist.h csvparser.h filereader.h
	$(CC) $(CFLAGS) -c main.c

testcases.o: testcases.c testcases.h linkedlist.h csvparser.h filereader.h
	$(CC) $(CFLAGS) -c testcases.c

linkedlist.o: linkedlist.c linkedlist.c
	$(CC) $(CFLAGS) -c linkedlist.c

filereader.o: filereader.c filereader.h
	$(CC) $(CFLAGS) -c filereader.c

csvparser.o: csvparser.c csvparser.h filereader.h
	$(CC) $(CFLAGS) -c csvparser.c

clean:
	rm -f $(OBJ) $(TEST_OBJ)

very-clean:
	rm -f $(OBJ) $(TEST_OBJ) $(EXEC) $(TEST_EXEC)
