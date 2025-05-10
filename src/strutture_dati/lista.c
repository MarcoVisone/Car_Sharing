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

Nodo crea_lista(){
    return NULL;
}

void distruggi_nodo(Nodo nodo, void (*funzione_distruggi_item)(void *)){
	if(nodo == NULL){
		return;
	}
	if(funzione_distruggi_item==NULL){
		funzione_distruggi_item(nodo->item);
	}
	free(nodo);
}

Nodo aggiungi_nodo(Item item, Nodo nodo){
	Nodo nodo2=malloc(sizeof(struct nodo));
	nodo2->item=item;
	nodo2->next=nodo;
	return nodo2;
}

Nodo ottieni_prossimo(Nodo nodo){
    if(nodo == NULL){
      return NULL;
    }
    return nodo->next;
}

Item ottieni_item(Nodo nodo){
    if(nodo == NULL){
      return NULL;
    }
    return nodo->item;
}

void imposta_prossimo(Nodo nodo, Nodo prossimo){
    if(nodo == NULL) return;

    nodo->next = prossimo;
}

Byte lista_vuota(Nodo lista){
    return lista == NULL;
}