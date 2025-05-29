/*
 * Autore: Antonio Sicignano
 * Data: 09/05/2025
 */

#include "strutture_dati/tabella_utenti.h"
#include "strutture_dati/tabella_hash.h"
#include "modelli/utente.h"
#include <stddef.h>
#include <stdio.h>

/*
 * Funzione: crea_tabella_utenti
 * -----------------------------
 * Inizializza una nuova tabella hash per la gestione degli utenti,
 * con una dimensione specificata.
 *
 * Implementazione:
 * - Chiama la funzione `nuova_tabella_hash` passando la dimensione desiderata.
 * - Restituisce il puntatore alla nuova tabella.
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
TabellaUtenti crea_tabella_utenti(unsigned int grandezza){
    return nuova_tabella_hash(grandezza);
}

/*
 * Funzione: distruggi_utente_t
 * ----------------------------
 * Funzione di distruzione per un utente, compatibile con la tabella hash.
 *
 * Implementazione:
 * - Converte il parametro `void*` in `Utente`.
 * - Chiama la funzione `distruggi_utente` per liberare la memoria dell’utente.
 *
 * Parametri:
 * utente: puntatore generico da convertire in `Utente`.
 *
 * Pre-condizioni:
 * - `utente` deve essere un puntatore valido a un oggetto di tipo `Utente`.
 *
 * Post-condizioni:
 * - L’oggetto utente viene correttamente deallocato.
 *
 * Ritorna:
 * - Nessun valore restituito (void).
 *
 * Side-effect:
 * - Libera la memoria dell’utente.
 */
static void distruggi_utente_t(void *utente){
    Utente u = (Utente)utente;
    distruggi_utente(u);
}


/*
 * Funzione: distruggi_tabella_utenti
 * ----------------------------------
 * Distrugge la tabella hash contenente gli utenti, deallocando memoria.
 *
 * Implementazione:
 * - Verifica che la tabella non sia NULL.
 * - Chiama `distruggi_tabella`, passando `distruggi_utente_t` come funzione di distruzione.
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
void distruggi_tabella_utenti(TabellaUtenti tabella_utenti){
    if(tabella_utenti == NULL)
        return;
    distruggi_tabella(tabella_utenti, distruggi_utente_t);
}


/*
 * Funzione: aggiungi_utente_in_tabella
 * ------------------------------------
 * Inserisce un nuovo utente nella tabella hash.
 *
 * Implementazione:
 * - Verifica che la tabella non sia NULL.
 * - Ottiene la chiave (email) dell’utente tramite `ottieni_email`.
 * - Inserisce l’utente nella tabella usando `inserisci_in_tabella`.
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
Byte aggiungi_utente_in_tabella(TabellaUtenti tabella_utenti, Utente utente){
    if(tabella_utenti == NULL){
        return 0;
    }

    return inserisci_in_tabella(tabella_utenti, ottieni_email(utente), (Utente)utente);
}

/*
 * Funzione: cerca_utente_in_tabella
 * ---------------------------------
 * Cerca un utente nella tabella hash tramite la sua email.
 *
 * Implementazione:
 * - Verifica che la tabella non sia NULL.
 * - Chiama `cerca_in_tabella` con la chiave email.
 *
 * Parametri:
 * tabella_utenti: la tabella in cui cercare.
 * email: la chiave univoca dell’utente.
 *
 * Pre-condizioni:
 * - `tabella_utenti` e `email` devono essere validi.
 *
 * Post-condizioni:
 * - Nessuna modifica alla tabella.
 *
 * Ritorna:
 * - Puntatore all’utente trovato o NULL se non esiste.
 *
 * Side-effect:
 * - Nessuno.
 */
Utente cerca_utente_in_tabella(const TabellaUtenti tabella_utenti, const char *email){
    if(tabella_utenti == NULL){
        return NULL;
    }
    return (Utente)cerca_in_tabella(tabella_utenti, email);
}

/*
 * Funzione: rimuovi_utente_in_tabella
 * -----------------------------------
 * Rimuove un utente dalla tabella hash tramite la sua email.
 *
 * Implementazione:
 * - Verifica che la tabella non sia NULL.
 * - Chiama `cancella_dalla_tabella` passando anche `distruggi_utente_t`.
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
Byte rimuovi_utente_in_tabella(TabellaUtenti tabella_utenti, char *email){
    if(tabella_utenti == NULL){
        return 0;
    }
    return cancella_dalla_tabella(tabella_utenti, email, distruggi_utente_t);
}

/*
 * Funzione: carica_utenti
 * -----------------------
 * Carica una serie di utenti in una tabella hash.
 *
 * Implementazione:
 * - Verifica che la tabella, il vettore di utenti e la dimensione siano validi.
 * - Per ogni utente nel vettore, chiama `aggiungi_utente_in_tabella`.
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
void carica_utenti(TabellaUtenti tabella_utenti, Utente *utente, unsigned int dimensione){
    if(tabella_utenti == NULL || utente == NULL || !dimensione) return;

    for(unsigned int i = 0; i < dimensione; i++){
        aggiungi_utente_in_tabella(tabella_utenti, utente[i]);
    }
}
