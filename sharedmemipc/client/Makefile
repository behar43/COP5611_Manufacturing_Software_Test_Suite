#Set up to use the gcc Linux C compiler
CCC=gcc
DEBUG= -g
LDFLAGS= -pthread
CCFLAGS= $(DEBUG)
CFLAGS= -c -W -Wall
SOURCES=clientmsh.c
OBJECTS=$(SOURCES:.c=.o)
EXEC = clientmsh

all: $(SOURCES) $(EXEC)

$(EXEC): $(OBJECTS)
	$(CCC) $(LDFLAGS) $(CCFLAGS) *.o -o $@

.c.o:
	$(CCC) $(CCFLAGS) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o clientmsh 
