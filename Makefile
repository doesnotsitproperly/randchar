CC := gcc
CFLAGS := -Wall -O2

default:
ifeq ($(OS), Windows_NT)
	$(CC) main.c $(CFLAGS) -o randchar.exe
else
	$(CC) main.c $(CFLAGS) -o randchar
endif

run: default
ifeq ($(OS), Windows_NT)
	.\randchar.exe
else
	./randchar
endif
