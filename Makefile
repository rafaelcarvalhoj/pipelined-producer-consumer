CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pthread
TARGET = main

SOURCES = $(shell find src -type f -name '*.c')
HEADERS = $(shell find src -type f -name '*.h')

ZIPFILE = prog.zip

.PHONY: build run clean

build: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -Isrc $(SOURCES) -o $@

run: build
	./$(TARGET)

clean:
	rm $(TARGET) $(ZIPFILE)


zip:
	zip $(ZIPFILE) -r . -x ".git/*"
