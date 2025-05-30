/*
 * Autore: Antonio Sicignano
 * Data: 14/05/2025
 */

#ifndef HASHMAP_UTENTI_H
#define HASHMAP_UTENTI_H

#include "modelli/byte.h"

typedef struct intervallo *Intervallo;
typedef struct tabella_hash *TabellaUtenti;
typedef struct utente *Utente;

/*
 * Funzione: crea_tabella_utenti
 * -----------------------------
 * Inizializza una nuova tabella hash per la gestione degli utenti,
 * con una dimensione specificata.
 *
 * Parametri:
 *    grandezza: numero di bucket della tabella hash
 *
 * Pre-condizioni:
 *    grandezza: deve essere maggiore di 0
 *
 * Post-condizioni:
 *    crea e restituisce una tabella hash
 *
 * Ritorna:
 *    Un puntatore alla nuova tabella hash
 *
 * Side-effect:
 *    Alloca memoria per la nuova tabella
 */
TabellaUtenti crea_tabella_utenti(unsigned int grandezza);

/*
 * Funzione: distruggi_tabella_utenti
 * -----------------------------------
 *
 * libera tutta la memoria associata alla tabella dei utenti,
 * inclusi tutti i utenti memorizzati
 *
 * Implementazione:
 *    Utilizza la funzione `distruggi_tabella`, passando una funzione
 *    di distruzione specifica per gli utenti (`distruggi_utente_t`).
 *
 * Parametri:
 *    tabella_utenti: tabella hash contenente gli utenti
 *
 * Pre-condizioni:
 *    tabella_utenti: non deve essere NULL
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    tutta la memoria associata alla tabella e agli utenti viene liberata
 */
void distruggi_tabella_utenti(TabellaUtenti tabella_utenti);

/*
 * Funzione: aggiungi_utente_in_tabella
 * -------------------------------------
 *
 * inserisce un utente all'interno della tabella hash degli utenti, utilizzando l'email come chiave
 *
 * Parametri:
 *    tabella_utenti: puntatore alla tabella hash dei utenti
 *    utente: puntatore al utente da inserire
 *
 * Pre-condizioni:
 *    tabella_utenti: puntatore alla tabella hash degli utenti
 *    utente: puntatore all'utente da inserire
 *
 * Post-condizioni:
 *    restituisce 1 se l'inserimento è avvenuto con successo, 0 altrimenti
 *
 * Ritorna:
 *    un valore di tipo Byte(1 oppure 0)
 *
 * Side-effect:
 *    modifica la tabella hash aggiungendo l'utente
 */
Byte aggiungi_utente_in_tabella(TabellaUtenti tabella_utenti, Utente utente);

/*
 * Funzione: cerca_utente_in_tabella
 * -----------------------------------
 *
 * cerca un utente nella tabella hash degli utenti utilizzando l'email come chiave
 *
 * Parametri:
 *    tabella_utenti: puntatore alla tabella hash degli utenti
 *    email: stringa costante contenente l'email dell'utente da cercare
 *
 * Pre-condizioni:
 *    tabella_utenti: non deve essere NULL
 *    email: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce un puntatore all'utente se presente nella tabella,
 *    altrimenti restituisce NULL
 *
 * Ritorna:
 *    un puntatore ad un utente o NULL
 */
Utente cerca_utente_in_tabella(TabellaUtenti tabella_utenti, const char *email);

/*
 * Funzione: rimuovi_utente_in_tabella
 * ------------------------------------
 *
 * rimuove un utente dalla tabella dei utente utilizzando l'email come chiave
 *
 * Parametri:
 *    tabella_utente: puntatore alla tabella hash contenente gli utenti
 *    email: stringa contenente l'email dell'utente da rimuovere
 *
 * Pre-condizioni:
 *    tabella_utente: non deve essere NULL
 *    email: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce 1 se l'utente è stato rimosso correttamente,
 *    0 se l'email non è presente o si è verificato un errore
 *
 * Ritorna:
 *    un valore di tipo Byte(1 oppure 0)
 *
 * Side-effect:
 *    Modifica la tabella degli utenti rimuovendo l'elemento specificato
 *    e libera la memoria associata all'utente
 */
Byte rimuovi_utente_in_tabella(TabellaUtenti tabella_utenti, char *email);

/*
 * Funzione: carica_utenti
 * -----------------------
 * Carica una serie di utenti in una tabella hash.
 *
 * Parametri:
 *    tabella_utenti: puntatore alla tabella hash in cui inserire gli utenti
 *    utente: array di puntatori a utenti da caricare
 *    dimensione: numero di utenti presenti nell'array
 *
 * Pre-condizioni:
 *    tabella_utenti: non deve essere NULL
 *    utente: non deve essere NULL
 *    dimensione: deve essere maggiore di 0
 *
 * Post-condizioni:
 *    Non restituisce niente
 *
 * Side-effect:
 *    gli utenti vengono inseriti nella tabella hash. Se un utente ha un'email
 *    uguale rispetto a uno già presente, l'utente non viene inserito
 */
void carica_utenti(TabellaUtenti tabella_utenti, Utente *utente, unsigned int dimensione);

#endif // HASHMAP_UTENTI_H
