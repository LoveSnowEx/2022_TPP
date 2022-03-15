CC=g++
OBJDIR:=$(shell [ -d obj ] || mkdir obj && echo "obj")
CFLAGS=-Wall -Wextra -std=c++17
LDFLAGS=-lm

TARGETS=main
main_OBJ=vec.o maze.o robot.o main.o

.PHONY: all

all: CFLAGS:=$(CFLAGS) -O2
all: $(TARGETS)

debug: CFLAGS:=$(CFLAGS) -g -DDEBUG -fsanitize=leak -fsanitize=undefined
debug: LDFLAGS:=$(LDFLAGS) -fsanitize=address -lubsan -lasan
debug: $(TARGETS)

dev: CFLAGS:=$(CFLAGS) -g -DDEBUG
dev: LDFLAGS:=$(LDFLAGS)
dev: $(TARGETS)


.SECONDEXPANSION:
$(TARGETS): $$(patsubst %, $(OBJDIR)/%, $$($$@_OBJ))
	$(CC) $(filter %.o, $^) -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(TARGETS) obj
