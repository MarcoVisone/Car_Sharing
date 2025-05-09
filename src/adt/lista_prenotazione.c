/*
 * Autore: Marco Visone
 * Data: 09/05/2025
 */

#include "../include/adt/lista_prenotazione.h"

Lista_Pre aggiungi_prenotazione_lista(Lista_Pre l, Prenotazione p){
    return aggiungi_nodo(p, l);
}

Prenotazione ottieni_prenotazione_lista(Lista_Pre l){
    return ottieni_item(l);
}