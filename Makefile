# Compilatore e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude

# Trova tutti i file .c nelle sottocartelle di src/
SRC = $(wildcard src/**/*.c) $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

# Nome dell’eseguibile
TARGET = car_sharing

# Comando di rimozione compatibile cross-platform
ifeq ($(OS),Windows_NT)
    RM = cmd /C del /Q /F
else
    RM = rm -f
endif

# Regola principale
all: $(TARGET)

# Come costruire l'eseguibile
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Pulizia dei file oggetto e dell'eseguibile
clean:
	-$(RM) $(OBJ) $(TARGET)

# Per usare Bear: bear -- make
.PHONY: all clean
