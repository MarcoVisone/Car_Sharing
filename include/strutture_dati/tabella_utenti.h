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
 *
 * crea una nuova tabella hash per la memorizzazione degli utenti,
 * con la dimensione specificata
 *
 * Parametri:
 *    grandezza: dimensione iniziale della tabella
 *
 * Pre-condizione:
 *    nessuna
 *
 * Post-condizione:
 *    viene restituito un nuovo oggetto TabellaUtenti allocato dinamicamente
 *    oppure NULL se l'allocazione fallisce
 *
 * Side-effect:
 *    allocazione dinamica di memoria
 */
TabellaUtenti crea_tabella_utenti(unsigned int grandezza);

/*
 * Funzione: distruggi_tabella_utenti
 * ----------------------------------
 *
 * dealloca la memoria associata alla tabella hash degli utenti,
 * liberando tutte le strutture interne
 *
 * Parametri:
 *    tabella_utenti: puntatore alla tabella da distruggere
 *
 * Pre-condizione:
 *    tabella_utenti non deve essere NULL
 *
 * Post-condizione:
 *    la memoria occupata dalla tabella e dalle strutture interne è liberata
 *
 * Side-effect:
 *    deallocazione dinamica di memoria
 */
void distruggi_tabella_utenti(TabellaUtenti tabella_utenti);

/*
 * Funzione: aggiungi_utente_in_tabella
 * ------------------------------------
 *
 * inserisce un utente nella tabella hash
 *
 * Parametri:
 *    tabella_utenti: puntatore alla tabella hash
 *    utente: puntatore all'utente da aggiungere
 *
 * Pre-condizione:
 *    tabella_utenti e utente non devono essere NULL
 *
 * Post-condizione:
 *    ritorna Byte (1) se l'inserimento ha avuto successo,
 *    0 in caso di fallimento (es. utente già presente o errore di allocazione)
 *
 * Side-effect:
 *    modifica la tabella hash aggiungendo un nuovo utente
 */
Byte aggiungi_utente_in_tabella(TabellaUtenti tabella_utenti, Utente utente);

/*
 * Funzione: cerca_utente_in_tabella
 * ---------------------------------
 *
 * cerca un utente nella tabella hash dato l'indirizzo email
 *
 * Parametri:
 *    tabella_utenti: puntatore alla tabella hash
 *    email: stringa contenente l'email dell'utente da cercare
 *
 * Pre-condizione:
 *    tabella_utenti e email non devono essere NULL
 *
 * Post-condizione:
 *    ritorna il puntatore all'utente trovato,
 *    NULL se l'utente non è presente nella tabella
 *
 * Side-effect:
 *    nessuno
 */
Utente cerca_utente_in_tabella(TabellaUtenti tabella_utenti, char *email);

/*
 * Funzione: rimuovi_utente_in_tabella
 * -----------------------------------
 *
 * rimuove un utente dalla tabella hash dato l'indirizzo email
 *
 * Parametri:
 *    tabella_utenti: puntatore alla tabella hash
 *    email: stringa contenente l'email dell'utente da rimuovere
 *
 * Pre-condizione:
 *    tabella_utenti e email non devono essere NULL
 *
 * Post-condizione:
 *    ritorna Byte (1) se la rimozione ha avuto successo,
 *    0 se l'utente non è stato trovato o in caso di errore
 *
 * Side-effect:
 *    modifica la tabella hash rimuovendo l'utente specificato
 */
Byte rimuovi_utente_in_tabella(TabellaUtenti tabella_utenti, char *email);

/*
 * Funzione: carica_utenti
 * ------------------------
 *
 * carica un insieme di utenti in una tabella hash
 *
 * Parametri:
 *    tabella_utenti: puntatore alla tabella hash in cui inserire i utenti
 *    utente: array di puntatori a utenti da caricare
 *    dimensione: numero di utenti presenti nell'array
 *
 * Pre-condizioni:
 *    - tabella_utenti: non deve essere NULL
 *    - utente: non deve essere NULL
 *    - dimensione: deve essere maggiore di 0
 *
 * Post-condizioni:
 *    Non restituisce niente
 *
 * Side-effect:
 *    Gli utenti vengono inseriti nella tabella hash. Se un utente ha un'email
 *    uguale rispetto a uno già presente, l'utente non viene inserito
 */
void carica_utenti(TabellaUtenti tabella_utenti, Utente *utente, unsigned int dimensione);

#endif // HASHMAP_UTENTI_H