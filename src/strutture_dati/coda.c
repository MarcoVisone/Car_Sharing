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
 * Crea una nuova coda vuota.
 *
 * Implementazione:
 *    Viene allocata dinamicamente una nuova struttura di tipo `struct coda`.
 *    Se l'allocazione ha successo, i puntatori `testa` e `coda` vengono
 *    inizializzati a NULL, indicando che la coda è vuota. Se l'allocazione
 *    fallisce, la funzione restituisce NULL.
 *
 * Parametri:
 *    Nessuno
 *
 * Pre-condizioni:
 *    Nessuna
 *
 * Post-condizione:
 *    La coda viene inizializzata e pronta per essere utilizzata.
 *
 * Side-effect:
 *    Alloca memoria per la struttura dati della coda.
 *
 * Ritorna:
 *    Puntatore alla nuova coda.
 */
Coda crea_coda(void) {
    Coda coda = malloc(sizeof(struct coda));
    if (!coda) return NULL;
    coda->testa = coda->coda = NULL;
    return coda;
}

/*
 * Funzione: distruggi_coda
 * ------------------------
 * Distrugge una coda esistente e libera tutta la memoria associata.
 *
 * Implementazione:
 *    Si itera la coda rimuovendo gli elementi uno per uno tramite la funzione
 *    `rimuovi_dalla_coda`. Per ogni elemento rimosso, se è stato fornito un
 *    distruttore, viene chiamato per liberare l’elemento dentro il nodo.
 *    Al termine, viene liberata la memoria della struttura della coda stessa.
 *
 * Parametri:
 *    coda: puntatore alla coda da distruggere.
 *    distruttore: funzione da applicare ad ogni elemento prima di liberarlo (può essere NULL).
 *
 * Pre-condizioni:
 *    La coda deve essere stata creata correttamente.
 *
 * Post-condizione:
 *    Tutta la memoria allocata per la coda viene rilasciata.
 *
 * Side-effect:
 *    Libera la memoria occupata dai nodi e, se fornito, applica la funzione distruttore
 *    ad ogni elemento della coda.
 *
 * Ritorna:
 *    Non restituisce niente.
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

/*
 * Funzione: aggiungi_in_coda
 * --------------------------
 * Aggiunge un elemento in fondo alla coda.
 *
 * Implementazione:
 *    Viene allocato in memoria un nuovo nodo. Se l'allocazione fallisce,
 *    la funzione restituisce -1. Il campo `elemento` del nodo viene
 *    inizializzato con il valore passato come parametro, mentre il puntatore
 *    `next` viene impostato a NULL. Se la coda è vuota (testa è NULL),
 *    il nuovo nodo diventa sia la testa che la coda. Altrimenti, viene
 *    collegato come nuovo ultimo nodo della coda.
 *
 * Parametri:
 *    elemento: puntatore all'elemento da inserire.
 *    coda: puntatore alla coda in cui inserire l'elemento.
 *
 * Pre-condizioni:
 *    La coda deve essere stata inizializzata.
 *
 * Post-condizione:
 *    L'elemento viene aggiunto alla fine della coda.
 *
 * Side-effect:
 *    Alloca un nuovo nodo nella memoria dinamica.
 *
 * Ritorna:
 *    0 se l'inserimento è avvenuto con successo, -1 in caso di errore.
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
 * Rimuove l'elemento in testa alla coda e lo restituisce.
 *
 * Implementazione:
 *    La funzione verifica se la coda è NULL o vuota: in tal caso restituisce NULL.
 *    Altrimenti, salva un puntatore temporaneo al nodo in testa, estrae l'elemento
 *    contenuto, aggiorna il puntatore `testa` al nodo successivo e, se la coda
 *    diventa vuota, imposta anche `coda` a NULL. Infine libera la memoria del nodo
 *    rimosso e restituisce l'elemento estratto.
 *
 * Parametri:
 *    coda: puntatore alla coda da cui rimuovere l'elemento.
 *
 * Pre-condizioni:
 *    La coda deve essere stata inizializzata.
 *
 * Post-condizione:
 *    La coda viene modificata con un elemento in meno in testa.
 *
 * Side-effect:
 *    Libera la memoria occupata dal nodo rimosso.
 *
 * Ritorna:
 *    Puntatore all'elemento rimosso, oppure NULL se la coda è vuota o non inizializzata.
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
 *    La funzione controlla se il puntatore alla coda è NULL. In tal caso,
 *    considera la coda come vuota e restituisce 1. Altrimenti, verifica
 *    se il campo `testa` è NULL, segno che la coda non contiene nodi.
 *
 * Parametri:
 *    coda: puntatore alla coda da controllare.
 *
 * Pre-condizioni:
 *    La coda deve essere stata inizializzata.
 *
 * Post-condizione:
 *    Nessuna.
 *
 * Ritorna:
 *    1 se la coda è vuota o NULL, 0 altrimenti.
 */
int coda_vuota(Coda coda) {
    if (coda == NULL) return 1;
    return coda->testa == NULL;
}
