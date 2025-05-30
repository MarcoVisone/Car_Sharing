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
 * grandezza: numero di bucket della tabella hash.
 *
 * Pre-condizioni:
 * - `grandezza` deve essere maggiore di 0.
 *
 * Post-condizioni:
 * - La tabella hash viene creata e pronta per essere utilizzata.
 *
 * Ritorna:
 * - Un puntatore alla nuova tabella hash.
 *
 * Side-effect:
 * - Alloca memoria per la nuova tabella.
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
 *    di distruzione specifica per i utenti (`distruggi_utente_t`).
 *
 * Parametri:
 *    tabella_utenti: tabella hash contenente i utenti
 *
 * Pre-condizioni:
 *    tabella_utenti: non deve essere NULL
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    tutta la memoria associata alla tabella e ai utenti viene liberata
 */
void distruggi_tabella_utenti(TabellaUtenti tabella_utenti);

/*
 * Funzione: aggiungi_utente_in_tabella
 * -------------------------------------
 *
 * inserisce un utente all'interno della tabella hash dei utenti, utilizzando la targa come chiave
 *
 * Parametri:
 *    tabella_utenti: puntatore alla tabella hash dei utenti
 *    utente: puntatore al utente da inserire
 *
 * Pre-condizioni:
 *    tabella_utenti: non deve essere NULL
 *    utente: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce 1 se l'inserimento è avvenuto con successo, 0 altrimenti
 *
 * Ritorna:
 *    un valore di tipo Byte(1 oppure 0)
 *
 * Side-effect:
 *    modifica la tabella hash aggiungendo il utente
 */
Byte aggiungi_utente_in_tabella(TabellaUtenti tabella_utenti, Utente utente);

/*
 * Funzione: cerca_utente_in_tabella
 * -----------------------------------
 *
 * cerca un utente nella tabella hash dei utenti utilizzando la targa come chiave
 *
 * Parametri:
 *    tabella_utenti: puntatore alla tabella hash dei utenti
 *    targa: stringa costante contenente la targa del utente da cercare
 *
 * Pre-condizioni:
 *    tabella_utenti: non deve essere NULL
 *    targa: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce un puntatore al utente se presente nella tabella,
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
 * rimuove un utente dalla tabella dei utente utilizzando la targa come chiave
 *
 * Parametri:
 *    tabella_utente: puntatore alla tabella hash contenente i utente
 *    targa: stringa contenente la targa del utente da rimuovere
 *
 * Pre-condizioni:
 *    tabella_utente: non deve essere NULL
 *    targa: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce 1 se il utente è stato rimosso correttamente,
 *    0 se la targa non è presente o si è verificato un errore
 *
 * Ritorna:
 *    un valore di tipo Byte(1 oppure 0)
 *
 * Side-effect:
 *    Modifica la tabella dei utente rimuovendo l'elemento specificato
 *    e libera la memoria associata al utente
 */
Byte rimuovi_utente_in_tabella(TabellaUtenti tabella_utenti, char *email);

/*
 * Funzione: carica_utenti
 * -----------------------
 * Carica una serie di utenti in una tabella hash.
 *
 * Parametri:
 * tabella_utenti: la tabella in cui caricare gli utenti.
 * utente: array di puntatori a oggetti `Utente`.
 * dimensione: numero di elementi nell’array.
 *
 * Pre-condizioni:
 * - `tabella_utenti`, `utente` devono essere validi e `dimensione > 0`.
 *
 * Post-condizioni:
 * - Tutti gli utenti validi vengono inseriti nella tabella.
 *
 * Ritorna:
 * - Nessun valore restituito (void).
 *
 * Side-effect:
 * - La tabella viene modificata e aggiornata con nuovi utenti.
 */
void carica_utenti(TabellaUtenti tabella_utenti, Utente *utente, unsigned int dimensione);

#endif // HASHMAP_UTENTI_H
