# Author: Ben Prishtina
# Purpose: Semester Project
# Class: COP 5611 Operating Systems Design Principles

#Set up to use the gcc Linux C++ compiler

.PHONY: all clean client_clean sharedmemserver_clean client sharedmemserver

all: parent_target client sharedmemserver

parent_target:
	@echo "Building shared memory server and client"

client:
	@echo "Entering client directory"
	$(MAKE) -C client

sharedmemserver:
	@echo "Entering sharedmemserver directory"
	$(MAKE) -C sharedmemserver

clean: client_clean sharedmemserver_clean
	@echo "Cleaning all targets"

client_clean:
	@echo "Cleaning client"
	$(MAKE) -C client clean

sharedmemserver_clean:
	@echo "Cleaning sharedmemserver"
	$(MAKE) -C sharedmemserver clean
