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
 * ----------------------------------
 * Distrugge la tabella hash contenente gli utenti, deallocando memoria.
 *
 * Parametri:
 * tabella_utenti: la tabella da distruggere.
 *
 * Pre-condizioni:
 * - `tabella_utenti` deve essere valida o NULL.
 *
 * Post-condizioni:
 * - Tutti gli utenti nella tabella vengono distrutti.
 * - La memoria della tabella viene liberata.
 *
 * Ritorna:
 * - Nessun valore restituito (void).
 *
 * Side-effect:
 * - Dealloca memoria per la tabella e i suoi contenuti.
 */
void distruggi_tabella_utenti(TabellaUtenti tabella_utenti);

/*
 * Funzione: aggiungi_utente_in_tabella
 * ------------------------------------
 * Inserisce un nuovo utente nella tabella hash.
 *
 * Parametri:
 * tabella_utenti: la tabella dove inserire l’utente.
 * utente: il puntatore all’oggetto utente da inserire.
 *
 * Pre-condizioni:
 * - `tabella_utenti` e `utente` devono essere validi.
 *
 * Post-condizioni:
 * - L’utente è presente nella tabella.
 *
 * Ritorna:
 * - 1 in caso di successo, 0 in caso di errore.
 *
 * Side-effect:
 * - La tabella viene modificata.
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
Utente cerca_utente_in_tabella(TabellaUtenti tabella_utenti, const char *email);

/*
 * Funzione: rimuovi_utente_in_tabella
 * -----------------------------------
 * Rimuove un utente dalla tabella hash tramite la sua email.
 *
 * Parametri:
 * tabella_utenti: la tabella da cui rimuovere l’utente.
 * email: la chiave identificativa dell’utente.
 *
 * Pre-condizioni:
 * - `tabella_utenti` e `email` devono essere validi.
 *
 * Post-condizioni:
 * - L’utente viene rimosso dalla tabella.
 *
 * Ritorna:
 * - 1 in caso di successo, 0 se la rimozione fallisce.
 *
 * Side-effect:
 * - Dealloca memoria per l’utente rimosso.
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
