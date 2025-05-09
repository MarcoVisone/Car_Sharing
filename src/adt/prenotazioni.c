/*
 * Autore: Marco Visone
 * Data: 06/05/2025
 */

#include "../include/adt/prenotazioni.h"
#include <stdio.h>
#include <limits.h>

struct node{
    Prenotazione prenotazione;
    struct node *right;
    struct node *left;
    time_t max;
    int height;
};

time_t max(time_t a, time_t b){
    return a > b ? a: b;
}

int height(struct node* nodo) {
    return nodo ? nodo->height : 0;
}

struct node* nuovo_nodo(Prenotazione prenotazione) {
    struct node* nodo = malloc(sizeof(struct node));
    nodo->prenotazione = prenotazione;
    nodo->left   = nodo->right = NULL;
    nodo->height = 1;
    nodo->max = fine_intervallo(ottieni_intervallo_prenotazione(prenotazione));
    return nodo;
}

time_t ottieni_max(struct node *nodo){
    /* Restituisco il max se il nodo c'è altrimenti INT_MIN
       per "annullare" il nodo */
    return nodo ? nodo->max: INT_MIN;
}

struct node *gira_destra(struct node *y){
    struct node *x = y->left;
    struct node *T2 = x->right;
    time_t fine = 0;

    x->right = y;
    x->left = T2;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    /* Ricalcolare il massimo fra il nodo e i suoi 2 figli*/
    fine = fine_intervallo(ottieni_intervallo_prenotazione(x->prenotazione));;
    x->max = max(fine, max(ottieni_max(x->left), ottieni_max(x->right)));

    return x;
}

struct node *gira_sinistra(struct node *x){
    struct node *y = x->right;
    struct node *T2 = y->left;
    time_t fine = 0;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    /* Ricalcolare il massimo fra il nodo e i suoi 2 figli*/
    fine = fine_intervallo(ottieni_intervallo_prenotazione(y->prenotazione));
    y->max = max(fine, max(ottieni_max(y->left), ottieni_max(y->right)));

    return y;
}

struct node *casi_bilanciamento(struct node *nodo, time_t inizio) {
    int bilancio = height(nodo->left) - height(nodo->right);

    /* LEFT-LEFT (rotazione singola a destra) */
    if (bilancio > 1 && nodo->left) {
        time_t inizio_l = inizio_intervallo(ottieni_intervallo_prenotazione(nodo->left->prenotazione));
        if (inizio < inizio_l)
            return gira_destra(nodo);

        /* LEFT-RIGHT (rotazione doppia sinistra-destra)*/
        if (inizio > inizio_l) {
            nodo->left = gira_sinistra(nodo->left);
            return gira_destra(nodo);
        }
    }

    /* RIGHT-RIGHT (rotazione singola a sinistra)*/
    if (bilancio < -1 && nodo->right) {
        time_t inizio_r = inizio_intervallo(ottieni_intervallo_prenotazione(nodo->right->prenotazione));
        if (inizio > inizio_r)
            return gira_sinistra(nodo);

        /* RIGHT-LEFT (rotazione doppia destra-sinistra)*/
        if (inizio < inizio_r) {
            nodo->right = gira_destra(nodo->right);
            return gira_sinistra(nodo);
        }
    }

    return nodo;
}

struct node *nuovo_prenotazioni(){
    return NULL;
}

void distruggi_nodo(Prenotazioni p){
    distruggi_prenotazione(p->prenotazione);
    free(p);
}

void _distruggi_prenotazioni(Prenotazioni nodo) {
    if (nodo == NULL) return;

    _distruggi_prenotazioni(nodo->left);
    _distruggi_prenotazioni(nodo->right);

    distruggi_nodo(nodo);
}

void distruggi_prenotazioni(Prenotazioni *prenotazioni) {
    if (*prenotazioni == NULL) return;

    _distruggi_prenotazioni(*prenotazioni);
    *prenotazioni = NULL;
}

struct node *aggiungi_prenotazione(struct node *tree, Prenotazione prenotazione){
    if(prenotazione == NULL)
        return NULL;

    if(tree == NULL)
        return nuovo_nodo(prenotazione);

    size_t inizio = inizio_intervallo(ottieni_intervallo_prenotazione(tree->prenotazione));
    size_t nuovo_inizio = inizio_intervallo(ottieni_intervallo_prenotazione(prenotazione));

    if(nuovo_inizio < inizio)
        tree->left = aggiungi_prenotazione(tree->left, prenotazione);
    else
        tree->right = aggiungi_prenotazione(tree->right, prenotazione);

    size_t fine = fine_intervallo(ottieni_intervallo_prenotazione(tree->prenotazione));

    /* Ricalcolo max*/
    tree->max = max(fine, max(ottieni_max(tree->left), ottieni_max(tree->right)));

    /* Ricalcolo altezza*/
    tree->height = 1 + max(height(tree->left), height(tree->right));

    /* Controllo se l'altezza va ancora bene*/
    return casi_bilanciamento(tree, inizio_intervallo(ottieni_intervallo_prenotazione(prenotazione)));
}

Byte controlla_prenotazione(Prenotazioni prenotazioni, Prenotazione p){
    if(prenotazioni == NULL)
        return 1;

    Intervallo i_attuale = ottieni_intervallo_prenotazione(prenotazioni->prenotazione);
    Intervallo i_nuovo = ottieni_intervallo_prenotazione(p);
    time_t inizio = inizio_intervallo(i_nuovo);

    if(intervalli_si_sovrappongono(i_attuale, i_nuovo)) return 0;

    if(prenotazioni->left && prenotazioni->left->max >= inizio)
        return controlla_prenotazione(prenotazioni->left, p);

    return controlla_prenotazione(prenotazioni->right, p);
}

struct node *trova_minimo(struct node *nodo){
    while(nodo->left != NULL){
        nodo = nodo->left;
    }
    return nodo;
}

Prenotazioni cancella_prenotazione(Prenotazioni prenotazioni, Prenotazione p) {
    if (prenotazioni == NULL) return prenotazioni;

    Intervallo i_attuale = ottieni_intervallo_prenotazione(prenotazioni->prenotazione);
    Intervallo i_nuovo = ottieni_intervallo_prenotazione(p);
    time_t inizio = inizio_intervallo(i_nuovo);

    if (!compara_intervalli(i_attuale, i_nuovo)) {
        // Caso 0/1 figlio
        if (prenotazioni->left == NULL || prenotazioni->right == NULL) {
            struct node *temp = prenotazioni->left ? prenotazioni->left : prenotazioni->right;
            if (temp == NULL) {
                /* Nessun figlio*/
                distruggi_nodo(prenotazioni);
                return NULL;
            } else {
                /* Un figlio*/
                distruggi_nodo(prenotazioni);
                return temp;
            }
        } else {
            /* Caso due figli*/
            struct node *temp = trova_minimo(prenotazioni->right);
            distruggi_prenotazione(prenotazioni->prenotazione);
            prenotazioni->prenotazione = duplica_prenotazione(temp->prenotazione);
            prenotazioni->right = cancella_prenotazione(prenotazioni->right, temp->prenotazione);
        }
    } else if (prenotazioni->left && prenotazioni->left->max >= inizio) {
        prenotazioni->left = cancella_prenotazione(prenotazioni->left, p);
    } else {
        prenotazioni->right = cancella_prenotazione(prenotazioni->right, p);
    }

    /* Aggiorna max e height*/
    time_t fine = fine_intervallo(ottieni_intervallo_prenotazione(prenotazioni->prenotazione));
    prenotazioni->max = max(fine, max(ottieni_max(prenotazioni->left), ottieni_max(prenotazioni->right)));
    prenotazioni->height = 1 + max(height(prenotazioni->left), height(prenotazioni->right));

    /* Ribilancia il nodo*/
    return casi_bilanciamento(prenotazioni, inizio_intervallo(i_attuale));
}