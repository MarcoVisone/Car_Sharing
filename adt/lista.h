typedef struct nodo *Nodo;
typedef void *Item;

Nodo creaLista();
Nodo distruggi_lista(Nodo nodo);
Nodo aggiungi_nodo(Item item, Nodo nodo);
Item ottieni_item(Nodo nodo);
Nodo ottieni_prossimo(Nodo nodo);