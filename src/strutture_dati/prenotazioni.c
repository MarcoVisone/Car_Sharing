/*
 * Autore: Marco Visone
 * Data: 06/05/2025
 */

#include "strutture_dati/prenotazioni.h"
#include "modelli/prenotazione.h"
#include "modelli/intervallo.h"
#include <stdlib.h>
#include <time.h>

static time_t massimo(time_t a, time_t b);
static int height(struct node* nodo);
static struct node* nuovo_nodo(Prenotazione prenotazione);
static void aggiorna_nodo(struct node *n);
static struct node *ruota_destra(struct node *y);
static struct node *ruota_sinistra(struct node *x);
static struct node *casi_bilanciamento(struct node *nodo, time_t inizio);
static void distruggi_nodo_prenotazioni(Prenotazioni p);
static void _distruggi_prenotazioni(Prenotazioni nodo);
static struct node *trova_minimo(struct node *nodo);


struct node{
    Prenotazione prenotazione;
    time_t max;
    int height;
	struct node *right;
    struct node *left;
};

static time_t massimo(time_t a, time_t b){
    return a > b ? a: b;
}

static int height(struct node* nodo) {
    return nodo ? nodo->height : 0;
}

static struct node* nuovo_nodo(Prenotazione prenotazione) {
    struct node* nodo = malloc(sizeof(struct node));
    nodo->prenotazione = prenotazione;
    nodo->left   = nodo->right = NULL;
    nodo->height = 1;
    nodo->max = fine_intervallo(ottieni_intervallo_prenotazione(prenotazione));
    return nodo;
}

static time_t ottieni_max(struct node *nodo){
    return nodo ? nodo->max: 0;
}

static void aggiorna_nodo(struct node *n) {
    Intervallo iv = ottieni_intervallo_prenotazione(n->prenotazione);
    time_t fi = fine_intervallo(iv);

    n->height = 1 + massimo(height(n->left), height(n->right));

	/* Il massasimo intervallo presente fra il nodo e i suoi figli
     * utile per velocizzare la ricerca di intervalli
     * che si sovrappongono
	 */
    n->max = massimo(fi, massimo(ottieni_max(n->left), ottieni_max(n->right)));
}

/*
 * Ruota a destra un nodo.
 * Prima della rotazione:
 *      y
 *     / \
 *    x   C
 *   / \
 *  A   T2
 *
 * Dopo la rotazione a destra:
 *      x
 *     / \
 *    A   y
 *       / \
 *      T2  C
 *
 * E poi aggiorna massimo e altezza di x e y
 * con "aggiorna_nodo(nodo)"
 */
static struct node *ruota_destra(struct node *y){
    struct node *x = y->left;
    struct node *T2 = x->right;

    x->right = y;
    y->left = T2;

	aggiorna_nodo(x);
	aggiorna_nodo(y);

    return x;
}

/*
 * Ruota a sinistra un nodo.
 * Prima della rotazione:
 *      x
 *     / \
 *    A   y
 *       / \
 *      T2  C
 *
 * Dopo la rotazione a sinistra:
 *      y
 *     / \
 *    x   C
 *   / \
 *  A  T2
 *
 * E poi aggiorna massimo e altezza di x e y
 * con "aggiorna_nodo(nodo)"
 */
static struct node *ruota_sinistra(struct node *x){
    struct node *y = x->right;
    struct node *T2 = y->left;

    y->left = x;
    x->right = T2;

    /* Ricalcolare il massimo fra il nodo e i suoi 2 figli */
	aggiorna_nodo(x);
	aggiorna_nodo(y);

    return y;
}

static struct node *casi_bilanciamento(struct node *nodo, time_t inizio) {
    int bilancio = height(nodo->left) - height(nodo->right);

    /* LEFT-LEFT o LEFT-RIGHT */
    if (bilancio > 1 && nodo->left) {
        time_t inizio_l = inizio_intervallo(ottieni_intervallo_prenotazione(nodo->left->prenotazione));

        /* LEFT-LEFT */
        if (inizio < inizio_l)
            return ruota_destra(nodo);

        /* LEFT-RIGHT */
        nodo->left = ruota_sinistra(nodo->left);
        return ruota_destra(nodo);
    }

    /* RIGHT-RIGHT o RIGHT-LEFT */
    if (bilancio < -1 && nodo->right) {
        time_t inizio_r = inizio_intervallo(ottieni_intervallo_prenotazione(nodo->right->prenotazione));

        /* RIGHT-RIGHT */
        if (inizio > inizio_r)
            return ruota_sinistra(nodo);

        /* RIGHT-LEFT */
        nodo->right = ruota_destra(nodo->right);
        return ruota_sinistra(nodo);
    }

    /* Nessun ribilanciamento necessario */
    return nodo;
}

struct node *crea_prenotazioni(){
    return NULL;
}

static void distruggi_nodo_prenotazioni(Prenotazioni p){
	if(p == NULL) return;

	/* prenotazione è allocata in memoria
	 * dinamicamente quindi va distrutta con
     * la sua funzione prima di liberare p
	 */
    distruggi_prenotazione(p->prenotazione);

    free(p);
}

static void _distruggi_prenotazioni(Prenotazioni nodo) {
    if (nodo == NULL) return;
	/* Distrugge tutti i nodi in modo preorder */
    _distruggi_prenotazioni(nodo->left);
    _distruggi_prenotazioni(nodo->right);

    distruggi_nodo_prenotazioni(nodo);
}

void distruggi_prenotazioni(Prenotazioni *prenotazioni) {
    if (*prenotazioni == NULL) return;

    _distruggi_prenotazioni(*prenotazioni);

    /* Dopo aver distrutto la prenotazione imposto a NULL
     * il puntatore, per evitare dangling pointer e memory leak
     */
    *prenotazioni = NULL;
}

struct node *aggiungi_prenotazione(struct node *tree, Prenotazione prenotazione){
    if(prenotazione == NULL)
        return NULL;

    if(tree == NULL)
        return nuovo_nodo(prenotazione);

    time_t inizio = inizio_intervallo(ottieni_intervallo_prenotazione(tree->prenotazione));
    time_t nuovo_inizio = inizio_intervallo(ottieni_intervallo_prenotazione(prenotazione));

    if(nuovo_inizio < inizio){
        tree->left = aggiungi_prenotazione(tree->left, prenotazione);
    }
    else{
        tree->right = aggiungi_prenotazione(tree->right, prenotazione);
    }

	aggiorna_nodo(tree);

    /* Ribilancia l'albero se necessario */
    return casi_bilanciamento(tree, nuovo_inizio);
}

Byte controlla_prenotazione(Prenotazioni prenotazioni, Prenotazione p){
    if(prenotazioni == NULL)
        return 1;

    Intervallo i_attuale = ottieni_intervallo_prenotazione(prenotazioni->prenotazione);
    Intervallo i_nuovo = ottieni_intervallo_prenotazione(p);
    time_t inizio = inizio_intervallo(i_nuovo);

    if(intervalli_si_sovrappongono(i_attuale, i_nuovo)) return 0;

    /* Se esiste il nodo sinistro E il massimo intervallo presente
     * nel nodo sinistro è maggiore o uguale all'inizio della nuova prenotazione,
     * allora la potenziale sovrapposizione potrebbe essere nel sottoalbero sinistro
     */
    if(prenotazioni->left && prenotazioni->left->max >= inizio)
        return controlla_prenotazione(prenotazioni->left, p);
	/* Altrimenti si controlla a destra */
    return controlla_prenotazione(prenotazioni->right, p);
}

static struct node *trova_minimo(struct node *nodo){
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
        /* Caso 0/1 figlio */
        if (prenotazioni->left == NULL || prenotazioni->right == NULL) {
            struct node *temp = prenotazioni->left ? prenotazioni->left : prenotazioni->right;
            if (temp == NULL) {
                /* Nessun figlio */
                distruggi_nodo_prenotazioni(prenotazioni);
                return NULL;
            } else {
                /* Un figlio */
                distruggi_nodo_prenotazioni(prenotazioni);
                return temp;
            }
        } else {
            /* Caso due figli */
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

    /* Aggiorna max e height */
   	aggiorna_nodo(prenotazioni);

	/* Ribilancia l'albero se necessario */
    return casi_bilanciamento(prenotazioni, inizio_intervallo(i_attuale));
}
