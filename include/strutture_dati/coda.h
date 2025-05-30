/*
 * Autore: Marco Visone
 * Data: 06/05/2025
 */

#ifndef CODA_H
#define CODA_H

/*
 * Tipo opaco per la gestione di una coda generica.
 */
typedef struct coda* Coda;

/*
 * Funzione: crea_coda
 * -------------------
 * Crea e inizializza una nuova coda vuota.
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
Coda crea_coda(void);

/*
 * Funzione: distruggi_coda
 * -----------------------
 * Distrugge una coda esistente, liberando tutta la memoria associata ai suoi nodi
 * e alla struttura della coda stessa.
 *
 * Parametri:
 *    coda: puntatore alla coda da distruggere.
 *    distruttore: puntatore a una funzione di callback (`void (*distruttore)(void *)`)
 *    che verrà applicata a ogni elemento della coda prima che il nodo venga
 *    liberato. Può essere **NULL** se gli elementi non richiedono deallocazione specifica.
 *
 * Pre-condizioni:
 *    - `coda` deve essere un puntatore valido a una coda precedentemente creata con `crea_coda` o **NULL**.
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
void distruggi_coda(Coda coda, void (*distruttore)(void *));

/*
 * Funzione: aggiungi_in_coda
 * --------------------------
 * Aggiunge un elemento alla fine della coda.
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
int aggiungi_in_coda(void *elemento, Coda coda);

/*
 * Funzione: rimuovi_dalla_coda
 * ----------------------------
 * Rimuove e restituisce l'elemento che si trova in testa alla coda (il primo elemento aggiunto).
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
void *rimuovi_dalla_coda(Coda coda);

/*
 * Funzione: coda_vuota
 * --------------------
 * Verifica se la coda è vuota.
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
int coda_vuota(Coda coda);

#endif // CODA_H
