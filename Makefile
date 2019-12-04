# Define variable CC to be the compiler we want to use
CC = g++

# Define CFLAGS for the flags we will want to use with clang
CFLAGS = -g -Wall -std=c++17

# Define targets

TARGETS = server client

# If no arguments are passed to make, it will attempt the '' target
default: $(TARGETS)

# This runs the all targets (including 'clean') when 'make all' is run
all: $(TARGETS)

# $^ = names of all dependant files, deduped and with spaces
# $< = name of first item in dependencies list
# $@ = complete name of the target

server: networking/server.cpp
	$(CC) $(CFLAGS) -pthread $^ -o $@

client: networking/client.cpp model/user.cpp
	$(CC) $(CFLAGS) $^ -o $@
