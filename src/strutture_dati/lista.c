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
 * Crea e restituisce una lista vuota (inizialmente NULL).
 *
 * Implementazione:
 *    Ritorna semplicemente NULL, che rappresenta una lista vuota.
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
Nodo crea_lista(){
    return NULL;
}

/*
 * Funzione: distruggi_nodo
 * ------------------------
 * Libera la memoria occupata da un nodo, distruggendo anche l'item se indicato.
 *
 * Implementazione:
 *    - Se il nodo è NULL, ritorna subito.
 *    - Se è fornita una funzione di distruzione dell'item, viene chiamata con l'item.
 *    - Libera la memoria del nodo.
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
 * Aggiunge un nuovo nodo in testa alla lista, contenente l'item fornito.
 *
 * Implementazione:
 *    - Alloca memoria per un nuovo nodo.
 *    - Imposta il campo `item` e collega il `next` al nodo esistente.
 *    - Restituisce il nuovo nodo.
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
Nodo aggiungi_nodo(Item item, Nodo nodo){
    if(nodo == NULL || item == NULL) return nodo;

    Nodo nodo2 = malloc(sizeof(struct nodo));
    nodo2->item = item;
    nodo2->next = nodo;
    return nodo2;
}

/*
 * Funzione: ottieni_prossimo
 * --------------------------
 * Restituisce il puntatore al nodo successivo nella lista.
 *
 * Implementazione:
 *    - Se `nodo` è NULL, ritorna NULL.
 *    - Altrimenti ritorna il campo `next` del nodo.
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
Nodo ottieni_prossimo(Nodo nodo){
    if(nodo == NULL){
        return NULL;
    }
    return nodo->next;
}

/*
 * Funzione: ottieni_item
 * ----------------------
 * Restituisce il contenuto `item` di un nodo.
 *
 * Implementazione:
 *    - Se `nodo` è NULL, ritorna NULL.
 *    - Altrimenti ritorna il campo `item`.
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
Item ottieni_item(Nodo nodo){
    if(nodo == NULL){
        return NULL;
    }
    return nodo->item;
}

/*
 * Funzione: imposta_prossimo
 * --------------------------
 * Imposta il nodo successivo per un nodo corrente.
 *
 * Implementazione:
 *    - Se `nodo` è NULL, ritorna subito.
 *    - Imposta il campo `next` con il valore fornito.
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
void imposta_prossimo(Nodo nodo, Nodo prossimo){
    if(nodo == NULL) return;

    nodo->next = prossimo;
}

/*
 * Funzione: inverti_lista
 * ----------------------
 * Inverte l'ordine degli elementi di una lista collegata singolarmente.
 *
 * Implementazione:
 *    - Inizializza tre puntatori: `curr` per il nodo corrente, `prossimo` per il nodo successivo,
 *    e `prev` per il nodo precedente (inizialmente NULL).
 *    - Scorre la lista originale modificando il puntatore `next` di ogni nodo per farlo
 *    puntare al nodo precedente.
 *    - Aggiorna i puntatori `prev` e `curr` fino a raggiungere la fine della lista.
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
Nodo inverti_lista(Nodo nodo){
    Nodo curr = nodo;
    Nodo prossimo = NULL;
    Nodo prev = NULL;

    while(curr != NULL){
        prossimo = curr->next;
        curr->next = prev;
        prev = curr;
        curr = prossimo;
    }

    return prev;
}

/*
 * Funzione: lista_vuota
 * ---------------------
 * Verifica se una lista (rappresentata da un nodo) è vuota.
 *
 * Implementazione:
 *    - Restituisce vero (1) se la lista è NULL, falso (0) altrimenti.
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
Byte lista_vuota(Nodo lista){
    return lista == NULL;
}
