//
// Created by marco on 5/6/25.
//
#ifndef BTREE_H
#define BTREE_H
#include "intervallo.h"

typedef struct node* IntervalTree;

IntervalTree treeInserisci(IntervalTree root, Intervallo i);

Intervallo treePrenotazioneOccupata(IntervalTree root, Intervallo i);

IntervalTree treeRimuovi(IntervalTree root, int key);

void treePreorder(IntervalTree root);

void treeInorder(IntervalTree root);

void treeFree(IntervalTree root);

#endif //BTREE_H
