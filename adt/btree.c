//
// Created by marco on 5/6/25.
//
#include <stdlib.h>
#include <stdio.h>
#include "btree.h"
#include "byte.h"

struct node {
    Intervallo intervallo;
    time_t max;
    struct node *left;
    struct node *right;
};

time_t max(time_t a, time_t b){
    return a > b ? a : b;
}

IntervalTree nuovoNodo(Intervallo i){
    IntervalTree nodo = (IntervalTree) malloc(sizeof(struct node));
    if (nodo == NULL) {
        return NULL;
    }
    
    nodo->intervallo = i;
    nodo->max = intervalloFine(i);
    nodo->left = NULL;
    nodo->right = NULL;
    
    return nodo;
}

IntervalTree treeInserisci(IntervalTree root, Intervallo i){
	if(root == NULL){
    	return nuovoNodo(i);
	}
	time_t low = intervalloInizio(root->intervallo);

	if(intervalloInizio(i) < low)
		root->left = treeInserisci(root->left, i);
	else
		root->right = treeInserisci(root->right, i);

	root->max = max(root->max, intervalloFine(i));

	return root;
}

Intervallo treePrenotazioneOccupata(IntervalTree root, Intervallo i){
	if(root == NULL) return NULL;
	if(intervalloContenutoIn(root->intervallo, i)) return root->intervallo;
	if(root->left && root->left->max >= intervalloInizio(i)) return treePrenotazioneOccupata(root->left, i);
	return treePrenotazioneOccupata(root->right, i);
}

void treePreorder(IntervalTree root){
	if(root == NULL) return;
	treePreorder(root->left);
	treePreorder(root->right);
	printf("%s", intervalloToString(root->intervallo));
}

void treeFree(IntervalTree root){
	if(root == NULL) return;
	treeFree(root->left);
	treeFree(root->right);
	free(root);
}


