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
 * Funzione: crea_tabella_Utenti
 * -----------------------------
 * Inizializza una nuova tabella hash per la gestione degli utenti,
 * con una dimensione specificata.
 *
 * Implementazione:
 *    - Chiama la funzione `nuova_tabella_hash` passando la dimensione desiderata.
 *    - Restituisce il puntatore alla nuova tabella.
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
TabellaUtenti crea_tabella_utenti(unsigned int grandezza){
    return nuova_tabella_hash(grandezza);
}

/*
 * Funzione: distruggi_utente_t
 * -----------------------------
 *
 * funzione di supporto che effettua il cast del puntatore generico void *
 * a un oggetto di tipo Utente, permettendo l'utilizzo della funzione distruggi_utente
 *
 * Parametri:
 *    utente: puntatore generico a un utente
 *
 * Pre-condizioni:
 *    utente: non deve essere NULL
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    la memoria associata all'utente viene liberata
 */
static void distruggi_utente_t(void *utente){
    Utente u = (Utente)utente;
    distruggi_utente(u);
}

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
void distruggi_tabella_utenti(TabellaUtenti tabella_utenti){
    if(tabella_utenti == NULL)
        return;
    distruggi_tabella(tabella_utenti, distruggi_utente_t);
}

/*
 * Funzione: aggiungi_utente_in_tabella
 * -------------------------------------
 *
 * inserisce un utente all'interno della tabella hash degli utenti, utilizzando l'email come chiave
 *
 * Implementazione:
 *    chiama la funzione inserisci_in_tabella utilizzando l'email dell'utente come chiave
 *    e il puntatore all'utente come valore.
 *
 * Parametri:
 *    tabella_utenti: puntatore alla tabella hash degli utenti
 *    utente: puntatore all'utente da inserire
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
 *    modifica la tabella hash aggiungendo l'utente
 */
Byte aggiungi_utente_in_tabella(TabellaUtenti tabella_utenti, Utente utente){
    if(tabella_utenti == NULL){
        return 0;
    }

    return inserisci_in_tabella(tabella_utenti, ottieni_email(utente), (Utente)utente);
}

/*
 * Funzione: cerca_utente_in_tabella
 * -----------------------------------
 *
 * cerca un utente nella tabella hash degli utenti utilizzando l'email come chiave
 *
 * Implementazione:
 *    utilizza la funzione cerca_in_tabella passando l'email come chiave,
 *    e restituisce il puntatore all'utente trovato se esiste
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
Utente cerca_utente_in_tabella(const TabellaUtenti tabella_utenti, const char *email){
    if(tabella_utenti == NULL){
        return NULL;
    }
    return (Utente)cerca_in_tabella(tabella_utenti, email);
}

/*
 * Funzione: rimuovi_utente_in_tabella
 * ------------------------------------
 *
 * rimuove un utente dalla tabella dei utente utilizzando l'email come chiave
 *
 * Implementazione:
 *    richiama la funzione cancella_dalla_tabella passando l'email come chiave
 *    e la funzione distruggi_utente_t per liberare la memoria dell'utente
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
Byte rimuovi_utente_in_tabella(TabellaUtenti tabella_utenti, char *email){
    if(tabella_utenti == NULL){
        return 0;
    }
    return cancella_dalla_tabella(tabella_utenti, email, distruggi_utente_t);
}

/*
 * Funzione: carica_utenti
 * ------------------------
 *
 * carica un insieme di utenti in una tabella hash
 *
 * Implementazione:
 *    itera sull'array di utenti fornito e li inserisce uno a uno nella tabella
 *    usando la funzione aggiungi_utente_in_tabella.
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
void carica_utenti(TabellaUtenti tabella_utenti, Utente *utente, unsigned int dimensione){
    if(tabella_utenti == NULL || utente == NULL || !dimensione) return;

    for(unsigned int i = 0; i < dimensione; i++){
        aggiungi_utente_in_tabella(tabella_utenti, utente[i]);
    }
}
