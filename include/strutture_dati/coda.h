/*
 * Autore: Marco Visone
 * Data: 06/05/2025
 */

#ifndef CODA_H
#define CODA_H

typedef struct coda* Coda;

/*
 * Funzione: crea_coda
 *
 * Crea una nuova coda vuota.
 *
 * Parametri:
 *   Nessuno
 *
 * Pre-condizione:
 *   Nessuna
 *
 * Post-condizione:
 *   La coda viene inizializzata e pronta per essere utilizzata.
 *
 * Ritorna:
 *   Puntatore alla nuova coda.
 */
Coda crea_coda(void);

/*
 * Funzione: distruggi_coda
 *
 * Distrugge una coda esistente e libera tutta la memoria associata.
 *
 * Parametri:
 *   coda: puntatore alla coda da distruggere.
 *   distruttore: funzione da applicare ad ogni elemento prima di liberarlo (può essere NULL).
 *
 * Pre-condizione:
 *   La coda deve essere stata creata correttamente.
 *
 * Post-condizione:
 *   Tutta la memoria allocata per la coda viene rilasciata.
 *
 * Side-effect:
 *   Libera la memoria occupata dai nodi e, se fornito, applica la funzione distruttore
 *   ad ogni elemento della coda.
 */
void distruggi_coda(Coda coda, void (*distruttore)(void *));

/*
 * Funzione: aggiungi_in_coda
 *
 * Aggiunge un elemento in fondo alla coda.
 *
 * Parametri:
 *   elemento: puntatore all'elemento da inserire.
 *   coda: puntatore alla coda in cui inserire l'elemento.
 *
 * Pre-condizione:
 *   La coda deve essere stata inizializzata.
 *
 * Post-condizione:
 *   L'elemento viene aggiunto alla fine della coda.
 *
 * Ritorna:
 *   0 se l'inserimento è avvenuto con successo, -1 in caso di errore.
 */
int aggiungi_in_coda(void *elemento, Coda coda);

/*
 * Funzione: rimuovi_dalla_coda
 *
 * Rimuove l'elemento in testa alla coda e lo restituisce.
 *
 * Parametri:
 *   coda: puntatore alla coda da cui rimuovere l'elemento.
 *
 * Pre-condizione:
 *   La coda deve essere stata inizializzata.
 *
 * Post-condizione:
 *   La coda viene modificata con un elemento in meno in testa.
 *
 * Side-effect:
 *   Libera la memoria occupata dal nodo rimosso.
 *
 * Ritorna:
 *   Puntatore all'elemento rimosso, oppure NULL se la coda è vuota o non inizializzata.
 */
void *rimuovi_dalla_coda(Coda coda);

/*
 * Funzione: coda_vuota
 *
 * Verifica se la coda è vuota.
 *
 * Parametri:
 *   coda: puntatore alla coda da controllare.
 *
 * Pre-condizione:
 *   La coda deve essere stata inizializzata.
 *
 * Post-condizione:
 *   Nessuna.
 *
 * Ritorna:
 *   1 se la coda è vuota o NULL, 0 altrimenti.
 */
int coda_vuota(Coda coda);

#endif // CODA_H
