# Compilatore e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

# Trova tutti i file .c nelle sottocartelle di src/
SRC = $(wildcard src/**/*.c) $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

# Nome dell’eseguibile
TARGET = car_sharing

# Regola principale
all: $(TARGET)

# Come costruire l'eseguibile
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Pulizia dei file oggetto e dell'eseguibile
clean:
	rm -f $(OBJ) $(TARGET)

# Per usare Bear: `bear -- make`
.PHONY: all clean
