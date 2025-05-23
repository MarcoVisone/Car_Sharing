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
 * Nessuno.
 *
 * Pre-condizioni:
 * Nessuna.
 *
 * Post-condizioni:
 * - Una nuova struttura Coda viene allocata e i suoi puntatori interni
 * (testa e coda) sono impostati a NULL, indicando una coda vuota.
 *
 * Side-effect:
 * - Alloca memoria dinamica per la struttura della coda.
 *
 * Ritorna:
 * Un puntatore di tipo `Coda` alla coda appena creata, o **NULL** in caso di fallimento
 * dell'allocazione di memoria.
 */
Coda crea_coda(void);

/*
 * Funzione: distruggi_coda
 * -----------------------
 * Distrugge una coda esistente, liberando tutta la memoria associata ai suoi nodi
 * e alla struttura della coda stessa.
 *
 * Parametri:
 * coda: puntatore alla coda da distruggere.
 * distruttore: puntatore a una funzione di callback (`void (*distruttore)(void *)`)
 * che verrà applicata a ogni elemento della coda prima che il nodo venga
 * liberato. Può essere **NULL** se gli elementi non richiedono deallocazione specifica.
 *
 * Pre-condizioni:
 * - `coda` deve essere un puntatore valido a una coda precedentemente creata con `crea_coda` o **NULL**.
 *
 * Post-condizioni:
 * - Tutta la memoria allocata per la coda (nodi ed elementi, se `distruttore` è fornito)
 * viene rilasciata.
 * - La coda diventa inutilizzabile dopo questa chiamata.
 *
 * Side-effect:
 * - Libera la memoria dinamica occupata dai nodi della coda.
 * - Se `distruttore` è fornito, applica questa funzione a ciascun elemento prima di liberare il nodo.
 *
 * Ritorna:
 * Questa funzione non restituisce alcun valore.
 */
void distruggi_coda(Coda coda, void (*distruttore)(void *));

/*
 * Funzione: aggiungi_in_coda
 * --------------------------
 * Aggiunge un elemento alla fine della coda.
 *
 * Parametri:
 * elemento: puntatore generico all'elemento da inserire nella coda.
 * coda: puntatore alla coda in cui inserire l'elemento.
 *
 * Pre-condizioni:
 * - `coda` deve essere un puntatore valido a una coda precedentemente creata con `crea_coda`.
 * - `elemento` può essere **NULL**.
 *
 * Post-condizioni:
 * - L'elemento viene aggiunto correttamente alla fine della coda.
 * - La dimensione della coda aumenta di uno.
 *
 * Side-effect:
 * - Alloca un nuovo nodo in memoria dinamica per contenere l'elemento.
 * - Modifica i puntatori interni della coda (`coda->coda` e possibilmente `coda->testa`).
 *
 * Ritorna:
 * **0** se l'inserimento è avvenuto con successo, **-1** in caso di errore (es. fallimento dell'allocazione di memoria per il nuovo nodo).
 */
int aggiungi_in_coda(void *elemento, Coda coda);

/*
 * Funzione: rimuovi_dalla_coda
 * ----------------------------
 * Rimuove e restituisce l'elemento che si trova in testa alla coda (il primo elemento aggiunto).
 *
 * Parametri:
 * coda: puntatore alla coda da cui rimuovere l'elemento.
 *
 * Pre-condizioni:
 * - `coda` deve essere un puntatore valido a una coda precedentemente creata con `crea_coda`.
 *
 * Post-condizioni:
 * - L'elemento in testa alla coda viene rimosso.
 * - La coda viene modificata, con il suo nuovo elemento in testa che era il secondo elemento prima della rimozione.
 * - Se la coda diventa vuota, i puntatori `testa` e `coda` della struttura vengono impostati a **NULL**.
 *
 * Side-effect:
 * - Libera la memoria dinamica occupata dal nodo rimosso dalla testa della coda.
 *
 * Ritorna:
 * Un puntatore generico (`void *`) all'elemento rimosso, o **NULL** se la coda è vuota o il puntatore `coda` non è valido.
 */
void *rimuovi_dalla_coda(Coda coda);

/*
 * Funzione: coda_vuota
 * --------------------
 * Verifica se la coda è vuota.
 *
 * Parametri:
 * coda: puntatore alla coda da controllare.
 *
 * Pre-condizioni:
 * - `coda` deve essere un puntatore valido a una coda precedentemente creata con `crea_coda` o **NULL**.
 *
 * Post-condizioni:
 * Nessuna. La funzione non modifica lo stato della coda.
 *
 * Side-effect:
 * Nessuno.
 *
 * Ritorna:
 * **1** (vero) se la coda è vuota (o se `coda` è **NULL**), **0** (falso) altrimenti.
 */
int coda_vuota(Coda coda);

#endif // CODA_H
