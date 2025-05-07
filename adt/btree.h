//
// Created by marco on 5/6/25.
//
#ifndef BTREE_H
#define BTREE_H
#include "intervallo.h"
#include "byte.h"

typedef struct node* Prenotazioni;

Prenotazioni aggiungiPrenotazione(Prenotazioni root, Intervallo i);

Byte prenotazioneOccupata(Prenotazioni root, Intervallo i);

Prenotazioni cancellaPrenotazione(Prenotazioni root, Prenotazione p);

void treePreorder(Prenotazioni root);

void treeInorder(Prenotazioni root);

void treeFree(Prenotazioni root);

#endif //BTREE_H
