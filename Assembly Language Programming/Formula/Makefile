TARGET = formula
CC = gcc
CFLAGS =-ansi -pedantic -Wall -m32

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = formula.o nCr.o
HEADERS = formula.h nCr.h


$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o formula $(OBJECTS)

$(TARGET).o: formula.c formula.h
	$(CC) $(CFLAGS) -c formula.c formula.h
	
nCr.o: nCr.s nCr.h
	$(CC) $(CFLAGS) -c nCr.s nCr.h
	
clean:
	-rm -f *.o
	-rm -f $(TARGET)
	-rm -f *.h.gch
