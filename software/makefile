CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.c dac.c gs232-interface.c microchip_mcp4901.c pseudoterminal.c gpio.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=rotor_control


all: clean $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@


clean:
	rm -f $(EXECUTABLE) *.o
