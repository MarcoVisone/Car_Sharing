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
 * Crea una nuova lista vuota, rappresentata da un puntatore Nodo.
 *
 * Ritorna:
 *    un Nodo che rappresenta la lista vuota (NULL o nodo sentinella)
 */
Nodo crea_lista();

/*
 * Funzione: distruggi_nodo
 * ------------------------
 * Dealloca la memoria del nodo passato come parametro,
 * e chiama la funzione di distruzione per l'item contenuto nel nodo.
 *
 * Parametri:
 *    nodo: puntatore al nodo da distruggere
 *    funzione_distruggi_item: funzione callback per liberare la memoria
 *                            associata all'item contenuto nel nodo
 *
 * Pre-condizioni:
 *    nodo non deve essere NULL
 *    funzione_distruggi_item deve essere valida (non NULL)
 *
 * Post-condizione:
 *    la memoria del nodo e dell'item è liberata
 */
void distruggi_nodo(Nodo nodo, void (*funzione_distruggi_item)(void *));

/*
 * Funzione: aggiungi_nodo
 * -----------------------
 * Inserisce un nuovo nodo contenente l'item in testa alla lista.
 *
 * Parametri:
 *    item: puntatore all'elemento da inserire nella lista
 *    nodo: puntatore al nodo testa della lista esistente
 *
 * Ritorna:
 *    il nuovo nodo testa della lista con l'item aggiunto
 */
Nodo aggiungi_nodo(Item item, Nodo nodo);

/*
 * Funzione: ottieni_item
 * ----------------------
 * Restituisce l'item contenuto nel nodo.
 *
 * Parametri:
 *    nodo: puntatore al nodo da cui estrarre l'item
 *
 * Pre-condizione:
 *    nodo non deve essere NULL
 *
 * Ritorna:
 *    il puntatore all'item contenuto nel nodo
 */
Item ottieni_item(Nodo nodo);

/*
 * Funzione: ottieni_prossimo
 * --------------------------
 * Restituisce il puntatore al nodo successivo della lista.
 *
 * Parametri:
 *    nodo: puntatore al nodo corrente
 *
 * Pre-condizione:
 *    nodo non deve essere NULL
 *
 * Ritorna:
 *    il puntatore al nodo successivo, oppure NULL se non c'è un nodo successivo
 */
Nodo ottieni_prossimo(Nodo nodo);

/*
 * Funzione: imposta_prossimo
 * --------------------------
 * Imposta il puntatore al nodo successivo per il nodo corrente.
 *
 * Parametri:
 *    nodo: puntatore al nodo corrente
 *    prossimo: puntatore al nodo da impostare come successivo
 *
 * Pre-condizione:
 *    nodo non deve essere NULL
 *
 * Post-condizione:
 *    il campo "prossimo" del nodo è modificato
 */
void imposta_prossimo(Nodo nodo, Nodo prossimo);

/*
 * Funzione: lista_vuota
 * ---------------------
 * Verifica se la lista è vuota.
 *
 * Parametri:
 *    lista: puntatore alla lista (nodo testa)
 *
 * Ritorna:
 *    1 (Byte) se la lista è vuota (NULL),
 *    0 (Byte) altrimenti
 */
Byte lista_vuota(Nodo lista);

#endif // LISTA_H