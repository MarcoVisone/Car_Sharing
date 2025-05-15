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
 * Pre-condizione:
 *    nessuna
 *
 * Post-condizione:
 *    ritorna un nodo che rappresenta la lista vuota (NULL o nodo sentinella)
 *
 * Ritorna:
 *    Nodo nuovo nodo lista vuota
 *
 * Side-effect:
 *    nessuno
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
 * Pre-condizione:
 *    nodo non deve essere NULL
 *    funzione_distruggi_item deve essere valida (non NULL)
 *
 * Post-condizione:
 *    la memoria del nodo e dell'item è liberata
 *
 * Side-effect:
 *    deallocazione dinamica di memoria
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
 * Pre-condizione:
 *    nodo e item possono essere NULL (lista vuota o elemento nullo)
 *
 * Post-condizione:
 *    ritorna il nuovo nodo testa della lista con l'item aggiunto
 *
 * Ritorna:
 *    Nodo nuovo nodo testa della lista
 *
 * Side-effect:
 *    modifica la struttura della lista aggiungendo un nuovo nodo
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
 *    puntatore all'item contenuto nel nodo
 *
 * Side-effect:
 *    nessuno
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
 *    puntatore al nodo successivo, oppure NULL se non c'è un nodo successivo
 *
 * Side-effect:
 *    nessuno
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
 *
 * Side-effect:
 *    modifica la struttura della lista
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
 * Pre-condizione:
 *    nessuna
 *
 * Ritorna:
 *    Byte 1 se la lista è vuota (NULL),
 *    0 altrimenti
 *
 * Side-effect:
 *    nessuno
 */
Byte lista_vuota(Nodo lista);

#endif // LISTA_H