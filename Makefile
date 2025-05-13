# Compilatore e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude

# OS Detection
OS := $(shell uname -s)
ifeq ($(OS),Windows_NT)
    RM = del /Q
    DETECTED_OS = Windows
    PATHSEP = \\
else
    RM = rm -f
    DETECTED_OS := $(OS)
    PATHSEP = /
endif

# Trova tutti i file .c nelle sottocartelle di src/ (funziona su Unix e WSL)
SRC := $(shell find src -name '*.c')
OBJ := $(patsubst %.c,%.o,$(SRC))

# Nome dell’eseguibile
TARGET = car_sharing

# Regola principale
all: $(TARGET)

# Come costruire l'eseguibile
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Pulizia dei file oggetto e dell'eseguibile
clean:
	$(RM) $(OBJ) $(TARGET)

# Per usare Bear: `bear -- make`
.PHONY: all clean
