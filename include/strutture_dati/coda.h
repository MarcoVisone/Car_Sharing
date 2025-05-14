#ifndef CODA_H
#define CODA_H

// Definizione della coda generica
typedef struct coda* Coda;

// Funzioni per la gestione della coda generica
Coda crea_coda(void);     // Crea una nuova coda

void distruggi_coda(Coda coda, void (*distruttore)(void *)); // Distruggi la coda

int aggiungi_in_coda(void *elemento, Coda coda); // Aggiungi un elemento alla coda

void *rimuovi_dalla_coda(Coda coda);            // Rimuovi un elemento dalla coda

int coda_vuota(Coda coda);                      // Verifica se la coda è vuota

#endif // CODA_GENERICA_H
