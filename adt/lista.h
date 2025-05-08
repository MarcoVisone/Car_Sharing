typedef struct nodo *Nodo;
typedef void *Item;

/*
 * La funzione crea lista crea una lista vuota
 * Parametri:
 *     Nessun parametro
 * Ritorna:
 *     Restituisce un nodo alla lista
 */
Nodo crea_lista();

/*
 * La funzione libera la memoria che occupa il nodo
 * Parametri:
 *     nodo: Il Nodo
 * Ritorna:
 *     Non restituisce nulla
 */
void distruggi_nodo(Nodo nodo);

/*
 * La funzione aggiunge un nodo alla lista
 * Parametri:
 *     item: L'Item da aggiungere alla lista
 *     nodo: La testa della lista
 * Ritorna:
 *     Restituisce il puntatore alla testa della lista
 */
Nodo aggiungi_nodo(Item item, Nodo nodo);

/*
 * La funzione fa ottenere l'item della lista
 * Parametri:
 *     nodo: Un Nodo della lista
 * Ritorna:
 *     Item: L'Item del nodo
 */
Item ottieni_item(Nodo nodo);

/*
 * La funzione fa ottenere la posizione successiva della lista
 * Parametri:
 *     nodo: Un nodo della lista
 * Ritorna:
 *     Nodo: Un puntatore al nodo successivo
 */
Nodo ottieni_prossimo(Nodo nodo);