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
 *    Nessuno.
 *
 * Pre-condizioni:
 *    Nessuna.
 *
 * Post-condizioni:
 *    Viene restituito un valore NULL, che rappresenta una lista vuota.
 *
 * Ritorna:
 *    un valore NULL
 *
 * Side-effect:
 *    Nessuno.
 */
Nodo crea_lista();

/*
 * Funzione: distruggi_nodo
 * ------------------------
 * Libera la memoria occupata da un nodo, distruggendo anche l'item se indicato.
 *
 * Parametri:
 *    nodo: il nodo da distruggere.
 *    funzione_distruggi_item: puntatore a funzione che distrugge il contenuto `item`.
 *
 * Pre-condizioni:
 *    nodo: non deve essere NULL
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    Il nodo viene deallocato.
 *    Se la funzione è fornita, viene chiamata sull'item.
 */
void distruggi_nodo(Nodo nodo, void (*funzione_distruggi_item)(void *));

/*
 * Funzione: aggiungi_nodo
 * -----------------------
 * Aggiunge un nuovo nodo in testa alla lista, contenente l'item fornito.
 *
 * Parametri:
 *    item: puntatore all'oggetto da inserire nel nodo.
 *    nodo: nodo a cui collegare il nuovo nodo in testa.
 *
 * Pre-condizioni:
 *    item: non deve essere NULL
 *    nodo: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce la lista con un nuovo nodo, in caso di errore restituisce la lista iniziale
 *
 * Ritorna:
 *    una lista
 *
 * Side-effect:
 *    Alloca memoria dinamica per il nuovo nodo.
 */
Nodo aggiungi_nodo(Item item, Nodo nodo);

/*
 * Funzione: ottieni_item
 * ----------------------
 * Restituisce il contenuto `item` di un nodo.
 *
 * Parametri:
 *    nodo: nodo da cui ottenere l'item.
 *
 * Pre-condizioni:
 *    nodo: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce il contenuto di un nodo
 *
 * Ritorna:
 *    un item
 */
Item ottieni_item(Nodo nodo);

/*
 * Funzione: ottieni_prossimo
 * --------------------------
 * Restituisce il puntatore al nodo successivo nella lista.
 *
 * Parametri:
 *    nodo: nodo da cui ottenere il successivo.
 *
 * Pre-condizioni:
 *    nodo: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce il puntatore al nodo successivo nella lista, in caso di errore restituisce NULL
 *
 * Ritorna:
 *    un puntatore ad un nodo o NULL
 */
Nodo ottieni_prossimo(Nodo nodo);

/*
 * Funzione: imposta_prossimo
 * --------------------------
 * Imposta il nodo successivo per un nodo corrente.
 *
 * Parametri:
 *    nodo: nodo da modificare.
 *    prossimo: nodo da impostare come successivo.
 *
 * Pre-condizioni:
 *    nodo: non deve essere NULL
 *    prossimo: non deve essere NULL
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    Il campo `next` del nodo viene aggiornato con il nuovo valore.
 */
void imposta_prossimo(Nodo nodo, Nodo prossimo);

/*
 * Funzione: inverti_lista
 * ----------------------
 * Inverte l'ordine degli elementi di una lista collegata singolarmente.
 *
 * Parametri:
 *    nodo: puntatore al primo nodo della lista originale.
 *
 * Pre-condizioni:
 *    nodo: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce la lista invertita
 *
 * Ritorna:
 *    una lista
 *
 * Side-effect:
 *    La lista è invertita modificando i puntatori `next` di ciascun nodo.
 */
Nodo inverti_lista(Nodo nodo);

/*
 * Funzione: lista_vuota
 * ---------------------
 * Verifica se una lista (rappresentata da un nodo) è vuota.
 *
 * Parametri:
 *    lista: puntatore al nodo iniziale della lista.
 *
 * Pre-condizioni:
 *    Nessuna.
 *
 * Post-condizioni:
 *    restituisce 1 se la lista è vuota, altrimenti 0
 *
 * Ritorna:
 *    un valore di tipo Byte(0 o 1)
 */
Byte lista_vuota(Nodo lista);

#endif // LISTA_H
