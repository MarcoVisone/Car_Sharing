/*
 * Autore: Marco Visone
 * Data: 09/05/2025
 */

#ifndef LISTA_PRENOTAZIONE_H
#define LISTA_PRENOTAZIONE_H

#include "../include/strutture_dati/prenotazione.h"
#include "../include/adt/lista.h"
typedef Nodo ListaPre;

ListaPre aggiungi_prenotazione_lista(ListaPre l, Prenotazione p);

Prenotazione ottieni_prenotazione_lista(ListaPre l);

#endif //LISTA_PRENOTAZIONE_H
