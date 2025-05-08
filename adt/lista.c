#include <stdlib.h>
#include "lista.h"

struct nodo{
    void *item;
    struct nodo *next;
};

Nodo creaLista(){
    return NULL;
}

Nodo aggiungi_nodo(Item item, Nodo nodo){
  Nodo nodo2=malloc(sizeof(Nodo));
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