/*
 * Autore: Antonio Sicignano
 * Data: 09/05/2025
 */

#include "strutture_dati/tabella_utenti.h"
#include "strutture_dati/tabella_hash.h"
#include "modelli/utente.h"
#include <stddef.h>

/*
 * Funzione: crea_tabella_utenti
 * -----------------------------
 *
 * crea una nuova tabella hash per la memorizzazione degli utenti,
 * con la dimensione specificata
 *
 * Implementazione:
 *    Chiama la funzione `nuova_tabella_hash` passando la grandezza.
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
TabellaUtenti crea_tabella_utenti(unsigned int grandezza){
    return nuova_tabella_hash(grandezza);
}

/*
 * Funzione: distruggi_utente_t
 * ----------------------------
 *
 * converte un puntatore generico in un oggetto Utente e lo distrugge
 *
 * Implementazione:
 *    Effettua il cast del puntatore void* a Utente e chiama la funzione `distruggi_utente`.
 *
 * Parametri:
 *    utente: puntatore generico a un oggetto Utente da liberare
 *
 * Pre-condizione:
 *    il puntatore deve riferirsi a un oggetto Utente valido
 *
 * Post-condizione:
 *    l'oggetto Utente puntato viene distrutto e la memoria liberata
 *
 * Side-effect:
 *    deallocazione della memoria associata all'Utente
 */
static void distruggi_utente_t(void *utente){
    Utente u = (Utente)utente;
    distruggi_utente(u);
}


/*
 * Funzione: distruggi_tabella_utenti
 * ----------------------------------
 *
 * dealloca la memoria associata alla tabella hash degli utenti,
 * liberando tutte le strutture interne
 *
 * Implementazione:
 *    Controlla se la tabella è NULL e, in tal caso, termina subito.
 *    Altrimenti procede alla distruzione della tabella e delle sue risorse.
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
void distruggi_tabella_utenti(TabellaUtenti tabella_utenti){
    if(tabella_utenti == NULL)
        return;
    distruggi_tabella(tabella_utenti, distruggi_utente_t);
}


/*
 * Funzione: aggiungi_utente_in_tabella
 * ------------------------------------
 *
 * inserisce un utente nella tabella hash
 *
 * Implementazione:
 * 	  Controlla se la tabella è NULL e restituisce 0 in tal caso.
 * 	  Altrimenti inserisce l'utente nella tabella usando la sua email come chiave.
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
Byte aggiungi_utente_in_tabella(TabellaUtenti tabella_utenti, Utente utente){
    if(tabella_utenti == NULL){
        return 0;
    }

    return inserisci_in_tabella(tabella_utenti, ottieni_email(utente), (Utente)utente);
}


/*
 * Funzione: cerca_utente_in_tabella
 * ---------------------------------
 *
 * cerca un utente nella tabella hash dato l'indirizzo email
 *
 *
 * Implementazione:
 *   Controlla se la tabella è NULL e restituisce NULL in tal caso.
 *   Altrimenti cerca l'utente nella tabella usando l'email come chiave.
 *
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
Utente cerca_utente_in_tabella(TabellaUtenti tabella_utenti, char *email){
    if(tabella_utenti == NULL){
        return NULL;
    }
    return (Utente)cerca_in_tabella(tabella_utenti, email);
}


/*
 * Funzione: rimuovi_utente_in_tabella
 * -----------------------------------
 *
 * rimuove un utente dalla tabella hash dato l'indirizzo email
 *
 * Implementazione:
 *    Controlla se la tabella è NULL e restituisce 0 in tal caso.
 *    Altrimenti rimuove l'utente dalla tabella usando l'email come chiave,
 *    chiamando anche la funzione `distruggi_utente_t` per liberare la memoria.
 *
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
void carica_utenti(TabellaUtenti tabella_utenti, Utente *utente, unsigned int dimensione){
    if(tabella_utenti == NULL || utente == NULL || !dimensione) return;

    for(unsigned int i = 0; i < dimensione; i++){
        aggiungi_utente_in_tabella(tabella_utenti, utente[i]);
    }
}
