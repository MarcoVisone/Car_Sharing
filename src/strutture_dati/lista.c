/*
 * Autore: Antonio Sicignano
 * Data: 09/05/2025
 */

#include <stdlib.h>
#include "strutture_dati/lista.h"

struct nodo{
    void *item;
    struct nodo *next;
};

/*
 * Funzione: crea_lista
 * --------------------
 * Crea una nuova lista vuota, rappresentata da un puntatore Nodo.
 *
 * Implementazione:
 *    La funzione restituisce semplicemente NULL, indicando che la lista è vuota.
 *
 * Ritorna:
 *    un Nodo che rappresenta la lista vuota (NULL o nodo sentinella)
 */
Nodo crea_lista(){
    return NULL;
}

/*
 * Funzione: distruggi_nodo
 * ------------------------
 * Dealloca la memoria del nodo passato come parametro,
 * e chiama la funzione di distruzione per l'item contenuto nel nodo.
 *
 * Implementazione:
 *    Se il nodo è NULL, la funzione non fa nulla.
 *    Se la funzione di distruzione dell'item è fornita, viene chiamata
 *    per liberare la memoria dell'item contenuto nel nodo.
 *    Infine viene liberata la memoria del nodo stesso.
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
void distruggi_nodo(Nodo nodo, void (*funzione_distruggi_item)(void *)){
    if(nodo == NULL){
        return;
    }
    if(funzione_distruggi_item != NULL){
        funzione_distruggi_item(nodo->item);
    }
    free(nodo);
}

/*
 * Funzione: aggiungi_nodo
 * -----------------------
 * Inserisce un nuovo nodo contenente l'item in testa alla lista.
 *
 * Implementazione:
 *    La funzione alloca memoria per un nuovo nodo, imposta il campo item
 *    al puntatore fornito e collega il nuovo nodo come testa, puntando al nodo precedente.
 *
 * Parametri:
 *    item: puntatore all'elemento da inserire nella lista
 *    nodo: puntatore al nodo testa della lista esistente
 *
 * Ritorna:
 *    il nuovo nodo testa della lista con l'item aggiunto
 */
Nodo aggiungi_nodo(Item item, Nodo nodo){
    Nodo nodo2 = malloc(sizeof(struct nodo));
    nodo2->item = item;
    nodo2->next = nodo;
    return nodo2;
}

/*
 * Funzione: ottieni_prossimo
 * --------------------------
 * Restituisce il puntatore al nodo successivo della lista.
 *
 * Implementazione:
 *    Se il nodo è NULL, restituisce NULL.
 *    Altrimenti restituisce il campo next del nodo.
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
Nodo ottieni_prossimo(Nodo nodo){
    if(nodo == NULL){
        return NULL;
    }
    return nodo->next;
}

/*
 * Funzione: ottieni_item
 * ----------------------
 * Restituisce l'item contenuto nel nodo.
 *
 * Implementazione:
 *    Se il nodo è NULL, restituisce NULL.
 *    Altrimenti restituisce il campo item del nodo.
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
Item ottieni_item(Nodo nodo){
    if(nodo == NULL){
        return NULL;
    }
    return nodo->item;
}

/*
 * Funzione: imposta_prossimo
 * --------------------------
 * Imposta il puntatore al nodo successivo per il nodo corrente.
 *
 * Implementazione:
 *    Se il nodo è NULL non fa nulla.
 *    Altrimenti assegna il puntatore prossimo al campo next del nodo.
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
void imposta_prossimo(Nodo nodo, Nodo prossimo){
    if(nodo == NULL) return;

    nodo->next = prossimo;
}

/*
 * Funzione: lista_vuota
 * ---------------------
 * Verifica se la lista è vuota.
 *
 * Implementazione:
 *    Verifica se il puntatore lista è NULL e restituisce 1 se vero, 0 altrimenti.
 *
 * Parametri:
 *    lista: puntatore alla lista (nodo testa)
 *
 * Ritorna:
 *    1 (Byte) se la lista è vuota (NULL),
 *    0 (Byte) altrimenti
 */
Byte lista_vuota(Nodo lista){
    return lista == NULL;
}