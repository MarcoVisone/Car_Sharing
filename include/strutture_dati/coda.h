/*
 * Autore: Marco Visone
 * Data: 06/05/2025
 */

#ifndef CODA_H
#define CODA_H

typedef struct coda* Coda;

/*
 * Funzione: crea_coda
 * -------------------
 * Crea una nuova coda vuota.
 *
 * Parametri:
 *    Nessuno
 *
 * Pre-condizioni:
 *    Nessuna
 *
 * Post-condizione:
 *    La coda viene inizializzata e pronta per essere utilizzata
 *
 * Ritorna:
 *    Puntatore alla nuova coda
 *
 * Side-effect:
 *    Alloca memoria per la struttura dati
 */
Coda crea_coda(void);

/*
 * Funzione: distruggi_coda
 * ------------------------
 * Distrugge una coda esistente e libera tutta la memoria associata.
 *
 * Parametri:
 *    coda: Puntatore alla coda da distruggere
 *    distruttore: Funzione da applicare ad ogni elemento prima di liberarlo (può essere NULL)
 *
 * Pre-condizioni:
 *    La coda deve essere stata creata correttamente
 *
 * Post-condizione:
 *    Tutti gli elementi e la struttura della coda vengono deallocati
 *
 * Ritorna:
 *    Non restituisce niente
 *
 * Side-effect:
 *    Libera memoria e può chiamare funzioni distruttrici personalizzate
 */
void distruggi_coda(Coda coda, void (*distruttore)(void *));

/*
 * Funzione: aggiungi_in_coda
 * --------------------------
 * Aggiunge un elemento in fondo alla coda.
 *
 * Parametri:
 *    elemento: Puntatore all'elemento da inserire
 *    coda: Puntatore alla coda in cui inserire l'elemento
 *
 * Pre-condizioni:
 *    La coda deve essere stata inizializzata
 *
 * Post-condizione:
 *    L'elemento viene aggiunto in fondo alla coda
 *
 * Ritorna:
 *    0 se l'inserimento è avvenuto con successo, -1 in caso di errore
 *
 * Side-effect:
 *    Alloca memoria per un nuovo nodo
 */
int aggiungi_in_coda(void *elemento, Coda coda);

/*
 * Funzione: rimuovi_dalla_coda
 * ----------------------------
 * Rimuove l'elemento in testa alla coda e lo restituisce.
 *
 * Parametri:
 *    coda: Puntatore alla coda da cui rimuovere l'elemento
 *
 * Pre-condizioni:
 *    La coda deve essere stata inizializzata
 *
 * Post-condizione:
 *    L'elemento in testa viene rimosso dalla coda
 *
 * Ritorna:
 *    Puntatore all'elemento rimosso, o NULL se la coda è vuota o non inizializzata
 *
 * Side-effect:
 *    Libera la memoria del nodo rimosso
 */
void *rimuovi_dalla_coda(Coda coda);

/*
 * Funzione: coda_vuota
 * --------------------
 * Verifica se la coda è vuota.
 *
 * Parametri:
 *    coda: Puntatore alla coda da controllare
 *
 * Pre-condizioni:
 *    La coda deve essere stata inizializzata
 *
 * Post-condizione:
 *    Nessuna
 *
 * Ritorna:
 *    1 se la coda è vuota o NULL, 0 altrimenti
 *
 * Side-effect:
 *    Nessuno
 */
int coda_vuota(Coda coda);

#endif // CODA_H
