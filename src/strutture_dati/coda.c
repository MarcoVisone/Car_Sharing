/*
 * Autore: Marco Visone
 * Data: 06/05/2025
 */

#include "strutture_dati/coda.h"
#include <stdlib.h> // Per malloc e free

/*
 * Struttura interna che rappresenta un nodo della coda.
 * Ogni nodo contiene un puntatore generico all'elemento memorizzato e
 * un puntatore al nodo successivo nella coda.
 */
typedef struct nodo {
    void *elemento;
    struct nodo *next;
} Nodo;

struct coda {
    Nodo *testa;
    Nodo *coda;
};

/*
 * Funzione: crea_coda
 * -------------------
 * Crea e inizializza una nuova coda vuota.
 *
 * Implementazione:
 *    Viene allocata dinamicamente una nuova struttura di tipo `struct coda` usando `malloc`.
 *    Se l'allocazione ha successo (il puntatore restituito non è NULL), i puntatori
 *    `testa` e `coda` della nuova struttura vengono inizializzati a NULL. In caso di
 *    fallimento dell'allocazione di memoria, la funzione restituisce NULL.
 *
 * Parametri:
 *    Nessuno.
 *
 * Pre-condizioni:
 *    Nessuna.
 *
 * Post-condizioni:
 *    - Una nuova struttura Coda viene allocata e i suoi puntatori interni
 *    (testa e coda) sono impostati a NULL, indicando una coda vuota.
 *
 * Ritorna:
 *    Un puntatore di tipo `Coda` o NULL
 *
 * Side-effect:
 *    - Alloca memoria dinamica per la struttura della coda.
 *
 */
Coda crea_coda(void) {
    Coda coda = malloc(sizeof(struct coda));
    if (!coda) return NULL; // Verifica l'allocazione
    coda->testa = coda->coda = NULL; // Inizializza la coda come vuota
    return coda;
}

/*
 * Funzione: distruggi_coda
 * ------------------------
 * Distrugge una coda esistente, liberando tutta la memoria associata ai suoi nodi
 * e alla struttura della coda stessa.
 *
 * Implementazione:
 *    La funzione itera sulla coda finché non è vuota, rimuovendo gli elementi uno per uno
 *    usando la funzione `rimuovi_dalla_coda`. Per ogni `elemento` rimosso (il contenuto
 *    del nodo), se `elemento` non è NULL e se è stata fornita una funzione `distruttore`,
 *    quest'ultima viene invocata per liberare la memoria specifica dell'elemento stesso.
 *    Questo è cruciale per la gestione di tipi di dati complessi. Al termine dell'iterazione,
 *    quando tutti i nodi sono stati rimossi e deallocati, viene liberata la memoria della
 *    struttura `Coda` stessa.
 *
 * Parametri:
 *    coda: puntatore alla coda da distruggere.
 *    distruttore: puntatore a una funzione di callback (`void (*distruttore)(void *)`)
 *    che verrà applicata a ogni elemento della coda prima che il nodo venga
 *    liberato. Può essere NULL se gli elementi non richiedono deallocazione specifica.
 *
 * Pre-condizioni:
 *    - `coda` deve essere un puntatore valido a una coda precedentemente creata con `crea_coda` o NULL.
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    - Tutta la memoria allocata per la coda (nodi ed elementi, se `distruttore` è fornito)
 *    viene rilasciata.
 *    - La coda diventa inutilizzabile dopo questa chiamata.
 *    - Se `distruttore` è fornito, applica questa funzione a ciascun elemento prima di liberare il nodo.
 */
void distruggi_coda(Coda coda, void (*distruttore)(void *)) {
    // Non è necessario controllare se coda è NULL qui, la funzione rimuovi_dalla_coda e coda_vuota lo fanno
    while (!coda_vuota(coda)) {
        void *elemento = rimuovi_dalla_coda(coda);
        if (elemento && distruttore) { // Se c'è un elemento e un distruttore, chiama il distruttore
            distruttore(elemento);
        }
    }
    free(coda); // Libera la struttura della coda
}

/*
 * Funzione: aggiungi_in_coda
 * --------------------------
 * Aggiunge un elemento alla fine della coda.
 *
 * Implementazione:
 *    Viene allocato dinamicamente un nuovo nodo di tipo `Nodo` usando `malloc`.
 *    Se l'allocazione fallisce, la funzione restituisce -1.
 *    Il campo `elemento` del nuovo nodo viene impostato al puntatore `elemento`
 *    passato come parametro, e il puntatore `next` del nuovo nodo viene impostato a NULL
 *    perché sarà l'ultimo nodo della coda.
 *    Se la coda è attualmente vuota (`coda->coda` è NULL), il nuovo nodo diventa
 *    sia la testa che la coda della lista. Altrimenti, il nodo precedente in coda
 *    (`coda->coda`) punta al nuovo nodo, e il puntatore `coda->coda` viene aggiornato
 *    per puntare al nuovo nodo.
 *
 * Parametri:
 *    elemento: puntatore generico all'elemento da inserire nella coda.
 *    coda: puntatore alla coda in cui inserire l'elemento.
 *
 * Pre-condizioni:
 *    coda: non deve essere NULL
 *    elemento: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce 0 se l'elemento viene aggiunto correttamente, altrimenti -1
 *
 * Ritorna:
 *    un valore intero(0 o -1)
 *
 * Side-effect:
 *    - Alloca un nuovo nodo nella memoria dinamica.
 *    - Modifica i puntatori interni della coda (`coda->coda` e possibilmente `coda->testa`).
 */
int aggiungi_in_coda(void *elemento, Coda coda) {
    if (coda == NULL) return -1; // La coda deve essere valida

    Nodo *nuovo_nodo = malloc(sizeof(Nodo));
    if (!nuovo_nodo) return -1; // Fallimento allocazione nodo

    nuovo_nodo->elemento = elemento;
    nuovo_nodo->next = NULL;

    if (coda->coda) { // Se la coda non è vuota
        coda->coda->next = nuovo_nodo; // Il vecchio ultimo nodo punta al nuovo
        coda->coda = nuovo_nodo; // Il nuovo nodo diventa l'ultimo
    } else { // Se la coda è vuota
        coda->testa = coda->coda = nuovo_nodo; // Il nuovo nodo è sia testa che coda
    }

    return 0;
}

/*
 * Funzione: rimuovi_dalla_coda
 * ----------------------------
 * Rimuove e restituisce l'elemento che si trova in testa alla coda (il primo elemento aggiunto).
 *
 * Implementazione:
 *    La funzione esegue una verifica iniziale per assicurarsi che il puntatore `coda` non sia NULL
 *    e che la coda non sia vuota (`coda->testa` non sia NULL). In caso contrario, restituisce NULL.
 *    Se la coda contiene elementi, un puntatore temporaneo (`temp`) viene salvato per il nodo in testa.
 *    L'elemento contenuto in questo nodo viene estratto e conservato. Il puntatore `coda->testa`
 *    viene aggiornato per puntare al nodo successivo, rimuovendo di fatto il primo nodo dalla lista.
 *    Se, dopo la rimozione, la coda diventa vuota (`coda->testa` è NULL), anche `coda->coda`
 *    viene impostato a NULL per mantenere la coerenza. Infine, la memoria del nodo `temp` viene
 *    liberata e l'elemento estratto viene restituito al chiamante.
 *
 * Parametri:
 *    coda: puntatore alla coda da cui rimuovere l'elemento.
 *
 * Pre-condizioni:
 *    coda: non deve essere NULL
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    - L'elemento in testa alla coda viene rimosso.
 *    - La coda viene modificata, con il suo nuovo elemento in testa che era il secondo elemento prima della rimozione.
 *    - Se la coda diventa vuota, i puntatori `testa` e `coda` della struttura vengono impostati a NULL.
 *    - Libera la memoria dinamica occupata dal nodo rimosso dalla testa della coda.
 */
void *rimuovi_dalla_coda(Coda coda) {
    if (coda == NULL || coda->testa == NULL) return NULL; // Coda non valida o vuota

    Nodo *temp = coda->testa; // Salva il nodo da rimuovere
    void *elemento = temp->elemento; // Estrai l'elemento

    coda->testa = coda->testa->next; // Aggiorna la testa al nodo successivo

    if (coda->testa == NULL) { // Se la coda è diventata vuota
        coda->coda = NULL; // Aggiorna anche la coda
    }

    free(temp); // Libera la memoria del nodo rimosso
    return elemento;
}

/*
 * Funzione: coda_vuota
 * --------------------
 * Verifica se la coda è vuota.
 *
 * Implementazione:
 *    La funzione prima controlla se il puntatore `coda` stesso è NULL. Se lo è,
 *    la coda viene considerata non inizializzata o non valida, e la funzione restituisce 1 (vuota).
 *    Altrimenti, la funzione verifica se il puntatore `coda->testa` è NULL. Se `coda->testa`
 *    è NULL, significa che non ci sono nodi nella coda, e quindi la coda è vuota;
 *    in questo caso, restituisce 1. Se `coda->testa` non è NULL, significa
 *    che la coda contiene almeno un elemento, e la funzione restituisce 0 (non vuota).
 *
 * Parametri:
 *    coda: puntatore alla coda da controllare.
 *
 * Pre-condizioni:
 *    coda: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce 1 se la coda è vuota o è NULL, altrimenti 0
 *
 * Ritorna:
 *    un valore intero(0 o 1)
 */
int coda_vuota(Coda coda) {
    if (coda == NULL) return 1; // Una coda NULL è considerata vuota/non valida
    return coda->testa == NULL; // La coda è vuota se la testa è NULL
}
