# Author: Ben Prishtina
# Purpose: Semester Project
# Class: COP 5611 Operating Systems Design Principles

#Set up to use the gcc Linux C++ compiler
CCC=g++ -I../utilities
DEBUG= -g -std=c++11
LDFLAGS= -lpthread -lutilities -L../utilities 
CCFLAGS= $(DEBUG)
CFLAGS= -c -Wall
SOURCES=mainhttpd.cpp \
		httpd.cpp \
		lightwebserver.cpp \
		url.cpp \
		etss.cpp \
		ATP_ARG.cpp \
		atpPingTest.cpp \
		staticworkers.cpp \
		ATP_LOG_REC.cpp \
		atpShmTest.cpp \
		atpCanBus.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXEC = etssoftware

all: $(SOURCES) $(EXEC)

$(EXEC): $(OBJECTS)
	$(CCC) $(CCFLAGS) *.o -o $@ $(LDFLAGS)

.cpp.o:
	$(CCC) $(CCFLAGS) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o core etssoftware
