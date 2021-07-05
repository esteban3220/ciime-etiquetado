# change application name here (executable output name)
TARGET=main
# compiler
CC=gcc
# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN=-Wall

PTHREAD=-pthread

CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe

GTKLIB=`pkg-config --cflags --libs gtk+-3.0 ` `mariadb_config --cflags --libs`

# linker
LD=gcc
LDFLAGS=$(PTHREAD) $(GTKLIB)
OBJS= main.o

all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(GTKLIB) $(GTKLIB2) $(LDFLAGS)
 
main.o:
	$(CC) -c $(CCFLAGS) main.c $(GTKLIB) -o main.o
clean:
	rm -f *.o $(TARGET)
.PHONY: install
	./main	
run:
	./main
# Proceso de copia de los ficheros al
# directorio destino
