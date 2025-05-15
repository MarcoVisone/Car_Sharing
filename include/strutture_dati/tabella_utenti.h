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
 * Crea una nuova tabella hash per la memorizzazione degli utenti,
 * con la dimensione specificata.
 *
 * Parametri:
 *    grandezza: numero intero che rappresenta la dimensione iniziale della tabella
 *
 * Ritorna:
 *    un nuovo oggetto TabellaUtenti allocato dinamicamente,
 *    NULL se l'allocazione fallisce
 */
TabellaUtenti crea_tabella_utenti(unsigned int grandezza);

/*
 * Funzione: distruggi_tabella_utenti
 * ----------------------------------
 * Dealloca la memoria associata alla tabella hash degli utenti,
 * liberando tutte le strutture interne.
 *
 * Parametri:
 *    tabella_utenti: puntatore alla tabella da distruggere
 *
 * Pre-condizione:
 *    tabella_utenti non deve essere NULL
 */
void distruggi_tabella_utenti(TabellaUtenti tabella_utenti);

/*
 * Funzione: aggiungi_utente_in_tabella
 * ------------------------------------
 * Inserisce un utente nella tabella hash.
 *
 * Parametri:
 *    tabella_utenti: puntatore alla tabella hash
 *    utente: puntatore all'utente da aggiungere
 *
 * Ritorna:
 *    Byte (1) se l'inserimento ha avuto successo,
 *    0 in caso di fallimento (es. utente già presente o errore di allocazione)
 */
Byte aggiungi_utente_in_tabella(TabellaUtenti tabella_utenti, Utente utente);

/*
 * Funzione: cerca_utente_in_tabella
 * ---------------------------------
 * Cerca un utente nella tabella hash dato l'indirizzo email.
 *
 * Parametri:
 *    tabella_utenti: puntatore alla tabella hash
 *    email: stringa contenente l'email dell'utente da cercare
 *
 * Ritorna:
 *    puntatore all'utente trovato,
 *    NULL se l'utente non è presente nella tabella
 */
Utente cerca_utente_in_tabella(TabellaUtenti tabella_utenti, char *email);

/*
 * Funzione: rimuovi_utente_in_tabella
 * -----------------------------------
 * Rimuove un utente dalla tabella hash dato l'indirizzo email.
 *
 * Parametri:
 *    tabella_utenti: puntatore alla tabella hash
 *    email: stringa contenente l'email dell'utente da rimuovere
 *
 * Ritorna:
 *    Byte (1) se la rimozione ha avuto successo,
 *    0 se l'utente non è stato trovato o in caso di errore
 */
Byte rimuovi_utente_in_tabella(TabellaUtenti tabella_utenti, char *email);

#endif // HASHMAP_UTENTI_H
