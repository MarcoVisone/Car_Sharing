# Compilatore e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude

# Trova tutti i file .c nelle sottocartelle di src/
SRC = $(wildcard src/**/*.c) $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

# Nome dell’eseguibile
TARGET = car_sharing

# Compatibilità con Windows/Linux/macOS per il comando clean
ifdef OS
    RM = del /Q /F
    FixPath = $(subst /,\,$1)
    TARGET = car_sharing.exe
else
    ifeq ($(shell uname), Linux)
        RM = rm -f
        FixPath = $1
    endif
endif

# Regola principale
all: $(TARGET)

# Come costruire l'eseguibile
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Pulizia
clean:
	-$(RM) $(call FixPath,$(OBJ)) $(call FixPath,$(TARGET))

# Per usare Bear: bear -- make
.PHONY: all clean
