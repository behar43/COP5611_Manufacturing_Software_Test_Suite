#Set up to use the gcc Linux C compiler
CCC=gcc
DEBUG= -g
LDFLAGS= -pthread -lrt
CCFLAGS= $(DEBUG)
CFLAGS= -c -W -Wall
SOURCES=servermsh.c
OBJECTS=$(SOURCES:.c=.o)
EXEC = servermsh

all: $(SOURCES) $(EXEC)

$(EXEC): $(OBJECTS)
	$(CCC) $(LDFLAGS) $(CCFLAGS) *.o -o $@

.c.o:
	$(CCC) $(CCFLAGS) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o servermsh 
