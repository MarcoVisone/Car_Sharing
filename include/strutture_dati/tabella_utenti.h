/*
 * Autore: Antonio Sicignano
 * Data: 14/05/2025
 */

#ifndef HASHMAP_UTENTI_H
#define HASHMAP_UTENTI_H
#include "modelli/byte.h"

// Rinominata TabellaHash in TabellaUtenti
typedef struct intervallo *Intervallo;
typedef struct tabella_hash *TabellaUtenti;
typedef struct utente *Utente;

TabellaUtenti crea_tabella_utenti(unsigned int grandezza);

void distruggi_tabella_utenti(TabellaUtenti tabella_utenti);

Byte aggiungi_utente_in_tabella(TabellaUtenti tabella_utenti, Utente utente);

Utente cerca_utente_in_tabella(TabellaUtenti tabella_utenti, char *email);

Byte rimuovi_utente_in_tabella(TabellaUtenti tabella_utenti, char *email);

#endif //HASHMAP_UTENTI_H
