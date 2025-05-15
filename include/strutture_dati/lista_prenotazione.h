/*
 * Autore: Marco Visone
 * Data: 09/05/2025
 */

#ifndef LISTA_PRENOTAZIONE_H
#define LISTA_PRENOTAZIONE_H

typedef struct prenotazione *Prenotazione;
typedef struct nodo *ListaPre;


void distruggi_lista_prenotazione(ListaPre l);

ListaPre aggiungi_prenotazione_lista(ListaPre l, Prenotazione p);

ListaPre rimuovi_prenotazione_lista(ListaPre l, Prenotazione p);

Prenotazione ottieni_prenotazione_lista(ListaPre l);

#endif //LISTA_PRENOTAZIONE_H
