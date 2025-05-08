#include <stdlib.h>
#include "../../include/adt/lista.h"

struct nodo{
    void *item;
    struct nodo *next;
};

Nodo crea_lista(){
    return NULL;
}

void distruggi_nodo(Nodo nodo){
  if(nodo != NULL){
    free(nodo);
  }
}

Nodo aggiungi_nodo(Item item, Nodo nodo){
  Nodo nodo2=malloc(sizeof(struct nodo));
  nodo2->item=item;
  nodo2->next=nodo;
  return nodo2;
}

Nodo ottieni_prossimo(Nodo nodo){
  if(nodo==NULL){
    return NULL;
  }
    return nodo->next;
}

Item ottieni_item(Nodo nodo){
  if(nodo==NULL){
    return NULL;
  }
  return nodo->item;
}