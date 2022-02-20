CC=gcc
CFLAGS=-c -Wall -Werror -Wextra
BUILD_PATH=../build

SOURCES=ds.c graph.c input.c main.c rpn.c
OBJECTS=$(SOURCES:.c=.o)

all: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BUILD_PATH)/graph -lm

ds.o: ds.c
	$(CC) $(CFLAGS) ds.c

graph.o: graph.c
	$(CC) $(CFLAGS) graph.c

input.o: input.c
	$(CC) $(CFLAGS) input.c

main.o: main.c
	$(CC) $(CFLAGS) main.c

rpn.o: rpn.c
	$(CC) $(CFLAGS) rpn.c

run: all
	$(BUILD_PATH)/graph

rebuild: clean all

clean:
	rm -rf *.o $(BUILD_PATH)/graph