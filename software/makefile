CC=gcc
CFLAGS=-c -Wall -ggdb
LDFLAGS=-lconfig -lpthread -lpcre
SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=rotor_control


all: clean $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) $< -o $@


clean:
	rm -f $(EXECUTABLE) *.o
