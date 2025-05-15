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
 * Crea una nuova tabella hash per la memorizzazione degli utenti,
 * con la dimensione specificata.
 *
 * Implementazione:
 *    La funzione chiama internamente `nuova_tabella_hash` che:
 *    - alloca dinamicamente memoria per la struttura `tabella_hash`
 *    - inizializza le sue proprietà
 *    - restituisce un puntatore alla nuova tabella hash allocata,
 *      oppure NULL se l'allocazione della memoria fallisce.
 *
 * Parametri:
 *    grandezza: numero intero che rappresenta la dimensione iniziale della tabella
 *
 * Ritorna:
 *    un nuovo oggetto TabellaUtenti allocato dinamicamente,
 *    NULL se l'allocazione fallisce
 */
TabellaUtenti crea_tabella_utenti(unsigned int grandezza){
    return nuova_tabella_hash(grandezza);
}

static void distruggi_utente_t(void *utente){
    Utente u = (Utente)utente;
    distruggi_utente(u);
}

/*
 * Funzione: distruggi_tabella_utenti
 * ----------------------------------
 * Dealloca la memoria associata alla tabella hash degli utenti,
 * liberando tutte le strutture interne.
 *
 * Implementazione:
 *    - Controlla che la tabella non sia NULL
 *    - Passa la funzione `distruggi_utente_t` come callback a `distruggi_tabella`
 *    - `distruggi_tabella` si occupa di liberare ogni nodo della tabella hash
 *      e, per ciascun utente, invoca `distruggi_utente` per deallocarne la memoria.
 *
 * Parametri:
 *    tabella_utenti: puntatore alla tabella da distruggere
 *
 * Pre-condizione:
 *    tabella_utenti non deve essere NULL
 */
void distruggi_tabella_utenti(TabellaUtenti tabella_utenti){
    if(tabella_utenti == NULL)
        return;

    distruggi_tabella(tabella_utenti, distruggi_utente_t);
}

/*
 * Funzione: aggiungi_utente_in_tabella
 * ------------------------------------
 * Inserisce un utente nella tabella hash.
 *
 * Implementazione:
 *    - Verifica che la tabella non sia NULL
 *    - Chiama `ottieni_email` per ottenere la chiave (email) dell’utente
 *    - Utilizza `inserisci_in_tabella` per inserire l’utente associato alla sua email
 *    - Restituisce 1 in caso di successo, 0 in caso di fallimento
 *
 * Parametri:
 *    tabella_utenti: puntatore alla tabella hash
 *    utente: puntatore all'utente da aggiungere
 *
 * Ritorna:
 *    Byte (1) se l'inserimento ha avuto successo,
 *    0 in caso di fallimento (es. utente già presente o errore di allocazione)
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
 * Cerca un utente nella tabella hash dato l'indirizzo email.
 *
 * Implementazione:
 *    - Verifica che la tabella non sia NULL
 *    - Chiama `cerca_in_tabella` passando l’email come chiave
 *    - Effettua il cast del risultato a `Utente`
 *
 * Parametri:
 *    tabella_utenti: puntatore alla tabella hash
 *    email: stringa contenente l'email dell'utente da cercare
 *
 * Ritorna:
 *    puntatore all'utente trovato,
 *    NULL se l'utente non è presente nella tabella
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
 * Rimuove un utente dalla tabella hash dato l'indirizzo email.
 *
 * Implementazione:
 *    - Verifica che la tabella non sia NULL
 *    - Chiama `cancella_dalla_tabella` con:
 *        - l’email come chiave
 *        - la funzione `distruggi_utente_t` per deallocare l’utente rimosso
 *    - Restituisce 1 se la rimozione è avvenuta con successo, 0 altrimenti
 *
 * Parametri:
 *    tabella_utenti: puntatore alla tabella hash
 *    email: stringa contenente l'email dell'utente da rimuovere
 *
 * Ritorna:
 *    Byte (1) se la rimozione ha avuto successo,
 *    0 se l'utente non è stato trovato o in caso di errore
 */
Byte rimuovi_utente_in_tabella(TabellaUtenti tabella_utenti, char *email){
    if(tabella_utenti == NULL){
        return 0;
    }
    return cancella_dalla_tabella(tabella_utenti, email, distruggi_utente_t);
}