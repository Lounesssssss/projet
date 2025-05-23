# Variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -Iinclude
LDFLAGS = -lSDL2 -lSDL2main

# Détection de l'OS
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
    CFLAGS += `sdl2-config --cflags`
    LDFLAGS = `sdl2-config --libs`
endif
ifeq ($(UNAME_S), Darwin)
    CFLAGS += `sdl2-config --cflags`
    LDFLAGS = `sdl2-config --libs`
endif

# Windows avec MSYS2
ifeq ($(OS), Windows_NT)
    CFLAGS += -IC:/msys64/mingw64/include/SDL2
    LDFLAGS = -LC:/msys64/mingw64/lib -lSDL2main -lSDL2
    TARGET = bin/labyrinthe.exe
else
    TARGET = bin/labyrinthe
endif

# Sources
SRCDIR = src
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=build/%.o)

# Règles
all: directories $(TARGET)

directories:
	mkdir -p bin build

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

build/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build bin

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run directories