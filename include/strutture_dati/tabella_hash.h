/*
* Autore: Russo Nello Manuel
 * Data: 09/05/2025
 */

#ifndef TABELLA_HASH_H
#define TABELLA_HASH_H

#include "strutture_dati/lista.h"
#include "modelli/byte.h"

typedef struct tabella_hash *TabellaHash;

TabellaHash nuova_tabella_hash(int grandezza);

Byte inserisci_in_tabella(TabellaHash tabella_hash, char *chiave, void *valore);

Byte cancella_dalla_tabella(TabellaHash tabella_hash, char *chiave);
#endif //TABELLA_HASH_H