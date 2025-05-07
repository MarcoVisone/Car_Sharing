//
// Created by marco on 5/6/25.
//
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include "btree.h"
#include "byte.h"

struct node {
    Prenotazione prenotazione;
    time_t max;
    struct node *left;
    struct node *right;
};

time_t getMax(Prenotazioni root){
	if(root == NULL) return INT_MIN;
	return root->max;
}
time_t max(time_t a, time_t b){
    return a > b ? a : b;
}

Prenotazioni nuovoNodo(Prenotazione prenotazione){
    Prenotazioni nodo = (Prenotazioni) malloc(sizeof(struct node));
    if (nodo == NULL) {
        return NULL;
    }
    
    nodo->prenotazione = prenotazione;
    nodo->max = intervalloFine(getDateIntervallo(prenotazione));
    nodo->left = NULL;
    nodo->right = NULL;
    
    return nodo;
}

Prenotazioni aggiungiPrenotazione(Prenotazioni root, Prenotazione prenotazione){
    if(root == NULL){
        return nuovoNodo(prenotazione);
    }

    Intervallo nuovo_intervallo = getDateIntervallo(prenotazione);
    Intervallo attuale_intervallo = getDateIntervallo(root->prenotazione);

    if(intervalliSiSovrappongono(attuale_intervallo, nuovo_intervallo))
        return NULL;

    if(inizioIntervallo(nuovo_intervallo) < inizioIntervallo(attuale_intervallo))
        root->left = aggiungiPrenotazione(root->left, prenotazione);
    else
        root->right = aggiungiPrenotazione(root->right, prenotazione);

    root->max = max(fineIntervallo(attuale_intervallo), max(getMax(root->left), getMax(root->right)));

    return root;
}

Byte prenotazioneOccupata(Prenotazioni root, Intervallo i) {
    if (root == NULL || i == NULL) {
        return 0;
    }

    Intervallo attuale = getDateIntervallo(root->prenotazione);

    if (intervalliSiSovrappongono(attuale, i)) {
        return 1;
    }

    if ((root->left != NULL) && (getMax(root->left) >= InizioIntervallo(i))) {
        return prenotazioneOccupata(root->left, i);
    }

    return prenotazioneOccupata(root->right, i);
}

Prenotazioni successore(Prenotazioni attuale){
    attuale = attuale->right;
    while(attuale != NULL && attuale->left != NULL)
        attuale = attuale->left;
    return attuale;
}

Prenotazioni cancellaPrenotazione(Prenotazioni root, Prenotazione p){
    if(root == NULL || p == NULL) return NULL;

    Intervallo attuale = getDateIntervallo(root->prenotazione);
    Intervallo nuovo = getDateIntervallo(p);

    if(getId(root->prenotazione) == getId(p)){
        if(root->left == NULL){
            Prenotazioni temp = root->right;
            prenotazioneDestroy(root->prenotazione);
            free(root);
            return temp;
        }
        if(root->right == NULL){
            Prenotazioni temp = root->left;
            prenotazioneDestroy(root->prenotazione);
            free(root);
            return temp;
        }
        Prenotazioni succ = successore(root);
        root->prenotazione = dublicaPrenotazione(succ->prenotazione);
        root->right = cancellaPrenotazione(root->right, succ->prenotazione);
    }

    else if ((root->left != NULL) && (getMax(root->left) >= InizioIntervallo(nuovo))){
        root->left = cancellaPrenotazione(root->left, p);
    }
    else root->right = cancellaPrenotazione(root->right, p);

    root->max = max(fineIntervallo(attuale), max(getMax(root->left), getMax(root->right)));

    return root;
}

void treePreorder(Prenotazioni root){
	if(root == NULL) return;
	treePreorder(root->left);
	treePreorder(root->right);
	printf("%s", intervalloToString(root->intervallo));
}

void treeFree(Prenotazioni root){
	if(root == NULL) return;
	treeFree(root->left);
	treeFree(root->right);
	free(root);
}


