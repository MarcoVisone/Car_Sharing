# Compilatore e flags
CC = gcc
CFLAGS = -Wall -Wextra -I../include

# Directory dei sorgenti
SRC_DIR = ../src
MOD_DIR = $(SRC_DIR)/modelli
SD_DIR  = $(SRC_DIR)/strutture_dati
UT_DIR  = $(SRC_DIR)/utils

# File sorgenti da compilare (escludendo main.c)
SRC = \
    $(MOD_DIR)/data.c \
    $(MOD_DIR)/intervallo.c \
    $(MOD_DIR)/prenotazione.c \
    $(MOD_DIR)/utente.c \
    $(MOD_DIR)/veicolo.c \
    $(SD_DIR)/coda.c \
    $(SD_DIR)/lista.c \
    $(SD_DIR)/lista_prenotazione.c \
    $(SD_DIR)/prenotazioni.c \
    $(SD_DIR)/tabella_hash.c \
    $(SD_DIR)/tabella_utenti.c \
    $(SD_DIR)/tabella_veicoli.c \
    $(UT_DIR)/gestore_file.c \
    $(UT_DIR)/md5.c \
    $(UT_DIR)/utils.c \
    test.c

# Nome dell'eseguibile
TARGET = test

# Regola principale
all: $(TARGET)

# Regola di compilazione
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Pulizia dei file oggetto e binari
clean:
	rm -f $(TARGET)

.PHONY: all clean run
