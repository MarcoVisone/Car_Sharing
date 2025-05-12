/*
 * Autore: Russo Nello Manuel
 * Data: 09/05/2025
 */

#ifndef TABELLA_HASH_H
#define TABELLA_HASH_H

#include "modelli/byte.h"

typedef struct tabella_hash *TabellaHash;
typedef struct nodo* Nodo;

TabellaHash nuova_tabella_hash(unsigned int grandezza);

void distruggi_tabella(TabellaHash tabella_hash, void (*funzione_distruggi_valore)(void *));

Byte inserisci_in_tabella(TabellaHash tabella_hash, char *chiave, void *valore);

Byte cancella_dalla_tabella(TabellaHash tabella_hash, char *chiave, void (*funzione_distruggi_valore)(void *));

void *cerca_in_tabella(TabellaHash tabella_hash, char *chiave);

#endif //TABELLA_HASH_H
