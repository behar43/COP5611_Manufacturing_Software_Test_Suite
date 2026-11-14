# Author: Ben Prishtina
# Purpose: Semester Project
# Class: COP 5611 Operating Systems Design Principles

#Set up to use the gcc Linux C++ compiler

.PHONY: all clean etssoftware sharedmemipc utilities etssoftware_clean sharedmemipc_clean utilities_clean

all: parent_target utilities etssoftware sharedmemipc

parent_target:
	@echo "Building ALL software and libraries for COP 5611 Semester Project"

utilities:
	@echo "Entering the utilities directory library"
	$(MAKE) -C utilities

etssoftware:
	@echo "Entering client directory"
	$(MAKE) -C etssoftware

sharedmemipc:
	@echo "Entering sharedmemipc directory"
	$(MAKE) -C sharedmemipc

clean: etssoftware_clean sharedmemipc_clean utilities_clean
	@echo "Cleaning all targets"

etssoftware_clean:
	@echo "Cleaning etssoftware"
	$(MAKE) -C etssoftware clean

sharedmemipc_clean:
	@echo "Cleaning sharedmemipc directory"
	$(MAKE) -C sharedmemipc clean

utilities_clean:
	@echo "Cleaning the utilities directory library"
	$(MAKE) -C utilities clean

