#Set up to use the gcc Linux C compiler
CCC=gcc
DEBUG= -g 
LDFLAGS= -shared -fPIC -lrt
CCFLAGS= $(DEBUG)
CFLAGS= -c -W -Wall
SOURCES=utilities.c
OBJECTS=$(SOURCES:.c=.o)
EXEC = libutilities.so

all: $(SOURCES) $(EXEC)

$(EXEC): $(OBJECTS)
	$(CCC) $(LDFLAGS) $(CCFLAGS) *.o -o $@

.c.o: 
	$(CCC) $(CCFLAGS) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o libutilities.so
