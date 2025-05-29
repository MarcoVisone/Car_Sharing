/*
 * Autore: Antonio Sicignano
 * Data: 09/05/2025
 */

#ifndef LISTA_H
#define LISTA_H

#include "modelli/byte.h"

typedef struct nodo *Nodo;
typedef void *Item;

/*
 * Funzione: crea_lista
 * --------------------
 * Crea e restituisce una lista vuota (inizialmente NULL).
 *
 * Parametri:
 * - Nessuno.
 *
 * Pre-condizioni:
 * - Nessuna.
 *
 * Post-condizioni:
 * - Viene restituito un valore NULL, che rappresenta una lista vuota.
 *
 * Ritorna:
 * - NULL, che rappresenta una lista vuota.
 *
 * Side-effect:
 * - Nessuno.
 */
Nodo crea_lista();

/*
 * Funzione: distruggi_nodo
 * ------------------------
 * Libera la memoria occupata da un nodo, distruggendo anche l'item se indicato.
 *
 * Parametri:
 * nodo: il nodo da distruggere.
 * funzione_distruggi_item: puntatore a funzione che distrugge il contenuto `item`.
 *
 * Pre-condizioni:
 * - `funzione_distruggi_item` può essere NULL.
 *
 * Post-condizioni:
 * - Il nodo viene deallocato.
 * - Se la funzione è fornita, viene chiamata sull'item.
 *
 * Ritorna:
 * - void
 *
 * Side-effect:
 * - Libera memoria associata al nodo.
 * - Potenzialmente libera anche la memoria dell'item.
 */
void distruggi_nodo(Nodo nodo, void (*funzione_distruggi_item)(void *));

/*
 * Funzione: aggiungi_nodo
 * -----------------------
 * Aggiunge un nuovo nodo in testa alla lista, contenente l'item fornito.
 *
 * Parametri:
 * item: puntatore all'oggetto da inserire nel nodo.
 * nodo: nodo a cui collegare il nuovo nodo in testa.
 *
 * Pre-condizioni:
 * - `item` deve essere valido (non NULL, se richiesto dalla logica dell'app).
 *
 * Post-condizioni:
 * - Un nuovo nodo viene allocato e aggiunto in testa alla lista.
 *
 * Ritorna:
 * - Il nuovo nodo creato (non NULL).
 *
 * Side-effect:
 * - Alloca memoria dinamica per il nuovo nodo.
 */
Nodo aggiungi_nodo(Item item, Nodo nodo);

/*
 * Funzione: ottieni_item
 * ----------------------
 * Restituisce il contenuto `item` di un nodo.
 *
 * Parametri:
 * nodo: nodo da cui ottenere l'item.
 *
 * Pre-condizioni:
 * - `nodo` può essere NULL.
 *
 * Post-condizioni:
 * - Nessuna modifica allo stato del nodo.
 *
 * Ritorna:
 * - Puntatore all'item, oppure NULL se `nodo` è NULL.
 *
 * Side-effect:
 * - Nessuno.
 */
Item ottieni_item(Nodo nodo);

/*
 * Funzione: ottieni_prossimo
 * --------------------------
 * Restituisce il puntatore al nodo successivo nella lista.
 *
 * Parametri:
 * nodo: nodo da cui ottenere il successivo.
 *
 * Pre-condizioni:
 * - `nodo` può essere NULL.
 *
 * Post-condizioni:
 * - Nessuna modifica allo stato del nodo.
 *
 * Ritorna:
 * - Puntatore al nodo successivo, oppure NULL se `nodo` è NULL.
 *
 * Side-effect:
 * - Nessuno.
 */
Nodo ottieni_prossimo(Nodo nodo);

/*
 * Funzione: imposta_prossimo
 * --------------------------
 * Imposta il nodo successivo per un nodo corrente.
 *
 * Parametri:
 * nodo: nodo da modificare.
 * prossimo: nodo da impostare come successivo.
 *
 * Pre-condizioni:
 * - `nodo` può essere NULL.
 *
 * Post-condizioni:
 * - Il campo `next` del nodo viene aggiornato con il nuovo valore.
 *
 * Ritorna:
 * - void
 *
 * Side-effect:
 * - Modifica il campo `next` della struttura `nodo`.
 */
void imposta_prossimo(Nodo nodo, Nodo prossimo);

/*
 * Funzione: inverti_lista
 * ----------------------
 * Inverte l'ordine degli elementi di una lista collegata singolarmente.
 *
 * Parametri:
 * nodo: puntatore al primo nodo della lista originale.
 *
 * Pre-condizioni:
 * - `nodo` è il puntatore al primo elemento di una lista collegata o NULL.
 *
 * Post-condizioni:
 * - La lista è invertita modificando i puntatori `next` di ciascun nodo.
 *
 * Ritorna:
 * - Il puntatore al nuovo primo nodo della lista invertita (precedentemente l'ultimo nodo).
 *
 * Side-effect:
 * - Modifica i puntatori `next` dei nodi nella lista originale.
 */
Nodo inverti_lista(Nodo nodo);

/*
 * Funzione: lista_vuota
 * ---------------------
 * Verifica se una lista (rappresentata da un nodo) è vuota.
 *
 * Parametri:
 * lista: puntatore al nodo iniziale della lista.
 *
 * Pre-condizioni:
 * - Nessuna.
 *
 * Post-condizioni:
 * - Nessuna modifica alla lista.
 *
 * Ritorna:
 * - 1 se la lista è vuota (lista == NULL), 0 altrimenti.
 *
 * Side-effect:
 * - Nessuno.
 */
Byte lista_vuota(Nodo lista);

#endif // LISTA_H
