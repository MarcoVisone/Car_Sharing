/*
 * Autore: Marco Visone
 * Data: 06/05/2025
 */

#include "strutture_dati/coda.h"
#include <stdlib.h>

// Nodo della coda generica
typedef struct nodo {
    void *elemento;
    struct nodo *next;
} Nodo;

// Struttura della coda generica
struct coda {
    Nodo *testa;
    Nodo *coda;
};

/*
 * Funzione: crea_coda
 * -------------------
 * Crea e inizializza una nuova coda generica vuota.
 *
 * Implementazione:
 * Alloca memoria per una nuova struttura coda e imposta testa e coda a NULL.
 *
 * Parametri:
 *    nessuno
 *
 * Pre-condizioni:
 *    nessuna
 *
 * Post-condizione:
 *    La coda è inizializzata e vuota.
 *
 * Ritorna:
 *    Un puntatore alla nuova coda creata oppure NULL in caso di errore.
 *
 * Side-effect:
 *    Alloca memoria dinamica.
 */
Coda crea_coda(void) {
    Coda coda = malloc(sizeof(struct coda));
    if (!coda) return NULL;
    coda->testa = coda->coda = NULL;
    return coda;
}

/*
 * Funzione: aggiungi_in_coda
 * --------------------------
 * Inserisce un elemento generico in fondo alla coda.
 *
 * Implementazione:
 * Alloca un nuovo nodo, assegna l'elemento, aggiorna i puntatori della coda.
 *
 * Parametri:
 *    elemento: Puntatore all'elemento da inserire
 *    coda: Puntatore alla coda
 *
 * Pre-condizioni:
 *    coda deve essere valida (non NULL)
 *
 * Post-condizione:
 *    L'elemento è stato aggiunto alla fine della coda.
 *
 * Ritorna:
 *    0 se l'inserimento ha avuto successo, -1 in caso di errore.
 *
 * Side-effect:
 *    Alloca memoria dinamica per il nuovo nodo.
 */
int aggiungi_in_coda(void *elemento, Coda coda) {
    Nodo *nuovo_nodo = malloc(sizeof(Nodo));
    if (!nuovo_nodo) return -1;

    nuovo_nodo->elemento = elemento;
    nuovo_nodo->next = NULL;

    if (coda->coda) {
        coda->coda->next = nuovo_nodo;
        coda->coda = nuovo_nodo;
    } else {
        coda->testa = coda->coda = nuovo_nodo;
    }

    return 0;
}

/*
 * Funzione: rimuovi_dalla_coda
 * ----------------------------
 * Rimuove e restituisce il primo elemento della coda.
 *
 * Implementazione:
 * Estrae il nodo in testa, aggiorna i puntatori e libera la memoria del nodo.
 *
 * Parametri:
 *    coda: Puntatore alla coda da cui rimuovere l'elemento
 *
 * Pre-condizioni:
 *    coda deve essere valida (non NULL)
 *
 * Post-condizione:
 *    Il primo elemento della coda è stato rimosso
 *
 * Ritorna:
 *    Il puntatore all'elemento rimosso oppure NULL se la coda è vuota o nulla
 *
 * Side-effect:
 *    Libera memoria dinamica del nodo rimosso.
 */
void *rimuovi_dalla_coda(Coda coda) {
    if (coda == NULL || coda->testa == NULL) return NULL;

    Nodo *temp = coda->testa;
    void *elemento = temp->elemento;
    coda->testa = coda->testa->next;

    if (coda->testa == NULL) {
        coda->coda = NULL;
    }

    free(temp);
    return elemento;
}

/*
 * Funzione: coda_vuota
 * --------------------
 * Verifica se la coda è vuota.
 *
 * Implementazione:
 * Controlla se il puntatore alla testa è NULL.
 *
 * Parametri:
 *    coda: Puntatore alla coda da controllare
 *
 * Pre-condizioni:
 *    coda può essere NULL
 *
 * Post-condizione:
 *    Nessuna
 *
 * Ritorna:
 *    1 se la coda è vuota o nulla, 0 altrimenti
 *
 * Side-effect:
 *    Nessuno
 */
int coda_vuota(Coda coda) {
    if (coda == NULL) return 1;
    return coda->testa == NULL;
}

/*
 * Funzione: distruggi_coda
 * ------------------------
 * Distrugge la coda liberando tutta la memoria allocata.
 *
 * Implementazione:
 * Rimuove tutti gli elementi dalla coda, chiamando un distruttore se fornito, quindi libera la struttura.
 *
 * Parametri:
 *    coda: Puntatore alla coda da distruggere
 *    distruttore: Funzione da chiamare su ogni elemento (può essere NULL)
 *
 * Pre-condizioni:
 *    coda deve essere valida
 *
 * Post-condizione:
 *    Tutti i nodi e la struttura coda sono stati deallocati
 *
 * Ritorna:
 *    non restituisce niente
 *
 * Side-effect:
 *    Libera memoria dinamica e può avere effetti collaterali tramite la funzione distruttore
 */
void distruggi_coda(Coda coda, void (*distruttore)(void *)) {
    while (!coda_vuota(coda)) {
        void *elemento = rimuovi_dalla_coda(coda);
        if (elemento && distruttore) {
            distruttore(elemento);
        }
    }
    free(coda);
}
