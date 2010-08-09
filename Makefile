#
# Makefile for Nanbox
#
# (C) Copyright 2009 Andy Wardley.  All rights reserved.
#

# directories
SOURCE_DIR   = .
INCLUDE_DIR  = .

# targets
NB_TEST     = nbtest
NB_TARGETS  = $(NB_TEST)
NB_OBJECTS  = \
	value.o \
        tap.o

# executables
CC         = gcc
LD         = ld
AR         = ar
RM         = rm
TOUCH      = touch

# file extensions
SOURCE_EXT = .c
OBJECT_EXT = .o

# extra options
CCDEFS     = -DDEBUG -DDEBUG_LEVEL=15
CCOPTS     = -Wall -g -O

# commands
CCCMD      = $(CC) $(CCOPTS) $(DEFS) $(INCLUDE_DIRS)

# primary dependency
all: $(NB_TARGETS)

clean:
	rm $(NB_TARGETS) $(NB_OBJECTS)

# test program
$(NB_TEST): $(NB_OBJECTS) $(NB_TEST)$(OBJECT_EXT)
	## building test program
	$(CCCMD) -o $(NB_TEST) \
	$(NB_OBJECTS) \
	$(NB_TEST)$(OBJECT_EXT) 

# general 

.c.o:
	$(CCCMD) -c $(SOURCE_DIR)/$< 

value.o : $(SOURCE_DIR)/value.c
nbtest.o : $(SOURCE_DIR)/nbtest.c

