CFLAGS = -c -Wall
CC = gcc
LIBS = -lm
OBJ = scanner.o reader.o charcode.o token.o error.o parser.o debug.o symtab.o  main.o
TARGET = symtab


all: $(TARGET)

debug: CFLAGS += -g
debug: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIBS) -Wl,--subsystem,console

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	-del /Q *.o 2>NUL
	-del /Q $(TARGET).exe 2>NUL

clean-linux:
	rm -f *.o *~ $(TARGET)
