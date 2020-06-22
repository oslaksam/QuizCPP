PROGRAM=oslaksam
CC=g++
CFLAGS= -std=c++17 -Wall -Wpedantic -Wextra -g -lstdc++fs
SRCDIR = src

SRC = $(wildcard $(SRCDIR)/*.cpp)
HDR = $(wildcard $(SRCDIR)/*.h)

all: compile doc run

compile: $(PROGRAM)

run:
	./$(PROGRAM)

doc: $(SRC) $(HDR) Doxyfile
	mkdir doc
	doxygen

clean:
	 rm $(PROGRAM)
	 rm -rf doc


$(PROGRAM):
	$(CC) $(CFLAGS) $(SRC) $^ -o $@ -lstdc++fs
