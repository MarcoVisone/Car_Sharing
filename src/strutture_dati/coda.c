#include "strutture_dati/coda.h"
#include <stdlib.h>

// Nodo della coda generica
typedef struct nodo {
    void *elemento;        // Puntatore generico al dato
    struct nodo *next;     // Puntatore al nodo successivo
} Nodo;

// Struttura della coda generica
struct coda {
    Nodo *testa;   // Puntatore al primo elemento
    Nodo *coda;    // Puntatore all'ultimo elemento
};

// Crea una nuova coda vuota
Coda crea_coda(void) {
    Coda coda = malloc(sizeof(Coda));
    if (!coda) return NULL;
    coda->testa = coda->coda = NULL;
    return coda;
}

// Aggiungi un elemento alla coda
int aggiungi_in_coda(void *elemento, Coda coda) {
    Nodo *nuovo_nodo = malloc(sizeof(Nodo));
    if (!nuovo_nodo) return -1;

    nuovo_nodo->elemento = elemento;
    nuovo_nodo->next = NULL;

    if (coda->coda) {
        coda->coda->next = nuovo_nodo;  // Aggiungi in fondo alla coda
        coda->coda = nuovo_nodo;        // Aggiorna l'ultimo elemento
    } else {
        coda->testa = coda->coda = nuovo_nodo;  // Prima aggiunta, coda vuota
    }

    return 0;
}

// Rimuovi un elemento dalla coda e restituiscilo
void *rimuovi_dalla_coda(Coda coda) {
    if (coda == NULL) return NULL;

    Nodo *temp = coda->testa;
    void *elemento = temp->elemento;
    coda->testa = coda->testa->next;

    if (coda->testa == NULL) {
        coda->coda = NULL;  // La coda è ora vuota
    }

    free(temp);
    return elemento;
}

// Verifica se la coda è vuota
int coda_vuota(Coda coda) {
    if(coda == NULL) return 1;
    return coda->testa == NULL;
}

// Distruggi la coda e libera la memoria
void distruggi_coda(Coda coda, void (*distruttore)(void *)) {
    while (!coda_vuota(coda)) {
        void *elemento = rimuovi_dalla_coda(coda);
        if (elemento && distruttore) {
            distruttore(elemento);  // Se esiste una funzione distruttore, la chiamiamo
        }
    }
    free(coda);
}
