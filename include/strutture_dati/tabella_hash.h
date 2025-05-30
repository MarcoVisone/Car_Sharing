/*
 * Autore: Russo Nello Manuel
 * Data: 09/05/2025
 */

#ifndef TABELLA_HASH_H
#define TABELLA_HASH_H

#include "modelli/byte.h"

typedef struct tabella_hash *TabellaHash;
typedef struct nodo* Nodo;

/*
 * Funzione: nuova_tabella_hash
 * ----------------------------
 *
 * crea una nuova tabella hash per la memorizzazione degli oggetti con la dimensione specificata
 *
 * Parametri:
 *    grandezza: dimensione iniziale della tabella hash
 *
 * Pre-condizioni:
 *    grandezza: deve essere maggiore di 0
 *
 * Post-condizioni:
 *    restituisce una nuova TabellaHash se l'allocazione è riuscita,
 *    altrimenti restituisce NULL
 *
 * Ritorna:
 *    un puntatore a una nuova struttura TabellaHash o NULL
 *
 * Side-effect:
 *   alloca memoria dinamicamente per la tabella hash e i suoi bucket
 */
TabellaHash nuova_tabella_hash(const unsigned int grandezza);

/*
 * Funzione: distruggi_tabella
 * ---------------------------
 *
 * libera la memoria allocata per una tabella hash, inclusi tutti gli elementi memorizzati.
 *
 * Parametri:
 *    tabella_hash: puntatore alla tabella hash da eliminare
 *    funzione_distruggi_valore: funzione da applicare ad ogni valore per liberare la memoria associata
 *
 * Pre-condizioni:
 *    tabella_hash: non deve essere NULL
 *
 * Post-condizioni:
 *    non restituisce nulla
 *
 * Side-effect:
 *    libera la memoria associata alla struttura TabellaHash e ai suoi elementi
 */
void distruggi_tabella(TabellaHash tabella_hash, void (*funzione_distruggi_valore)(void *));

/*
 * Funzione: inserisci_in_tabella
 * ------------------------------
 *
 * inserisce un elemento nella tabella hash associando una chiave a un valore
 *
 * Parametri:
 *    tabella_hash: puntatore alla tabella hash
 *    chiave: stringa costante contenente la chiave dell'elemento
 *    valore: puntatore al valore da associare alla chiave
 *
 * Pre-condizioni:
 *    tabella_hash: non deve essere NULL
 *    chiave: non deve essere NULL
 *    valore: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce 1 se l'inserimento è avvenuto con successo, 0 in caso di errore
 *
 * Ritorna:
 *    un valore di tipo Byte(1 oppure 0)
 *
 * Side-effect:
 *    modifica la tabella hash aggiungendo un nuovo elemento e ridimensiona la tabella se necessario
 */
Byte inserisci_in_tabella(TabellaHash tabella_hash, const char *chiave, void *valore);

/*
 * Funzione: cancella_dalla_tabella
 * -----------------------------------
 *
 * rimuove un oggetto dalla tabella hash utilizzando la chiave fornita
 *
 * Parametri:
 *    tabella_utenti: puntatore alla tabella hash
 *    chiave: stringa costante contenente la chiave dell'elemento da rimuovere
 *    funzione_distruggi_valore: funzione da applicare al valore per liberare la memoria associata
 *
 * Pre-condizioni:
 *    tabella_hash: non deve essere NULL
 *    chiave: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce 1 se la rimozione ha avuto successo, 0 se la chiave non è presente
 *    o se si verifica un errore
 *
 * Ritorna:
 *    un valore di tipo Byte(1 oppure 0)
 *
 * Side-effect:
 *    - modifica la tabella hash rimuovendo l'elemento associato alla chiave
 *    - libera memoria dinamicamente associata al nodo e al valore
 */
Byte cancella_dalla_tabella(const TabellaHash tabella_hash, const char *chiave, void (*funzione_distruggi_valore)(void *));

/*
 * Funzione: cerca_in_tabella
 * --------------------------
 *
 * cerca un elemento nella tabella hash tramite la chiave specificata
 *
 * Parametri:
 *    tabella_hash: puntatore alla tabella hash
 *    chiave: stringa costante contenente la chiave da cercare
 *
 * Pre-condizioni:
 *    tabella_hash: non deve essere NULL
 *    chiave: non deve essere NULL
 *
 * Post-condizioni:
 *    Se la chiave è presente, restituisce il puntatore al valore associato;
 *    altrimenti restituisce NULL
 *
 * Ritorna:
 *    un puntatore generico o NULL
 */
const void *cerca_in_tabella(TabellaHash tabella_hash, const char *chiave);

/*
 * Funzione: ottieni_vettore
 * -------------------------
 *
 * estrae tutti i valori contenuti nella tabella hash e li restituisce in un array.
 *
 * Parametri:
 *    tabella_hash: puntatore alla tabella hash
 *    dimensione: puntatore ad un intero dove verrà memorizzata la dimensione del vettore restituito
 *
 * Pre-condizioni:
 *    tabella_hash: non deve essere NULL
 *    dimensione: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce un array di puntatori ai valori presenti nella tabella hash,
 *    oppure NULL se ci sono errori o la tabella è vuota.
 *
 * Ritorna:
 *    un array di puntatori generico o NULL
 *
 * Side-effect:
 *    alloca dinamicamente memoria per il vettore risultante
 */
void **ottieni_vettore(const TabellaHash tabella_hash, unsigned int *dimensione);

#endif //TABELLA_HASH_H
