/*
 * Autore: Marco Visone
 * Data: 09/05/2025
 */

#include "../include/adt/lista_prenotazione.h"

ListaPre aggiungi_prenotazione_lista(ListaPre l, Prenotazione p){
    return aggiungi_nodo(p, l);
}

Prenotazione ottieni_prenotazione_lista(ListaPre l){
    return ottieni_item(l);
}