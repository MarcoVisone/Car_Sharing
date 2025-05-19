/*
 * Autore: Marco Visone
 * Data: 06/05/2025
 */

#include "strutture_dati/prenotazioni.h"
#include "modelli/prenotazione.h"
#include "modelli/intervallo.h"
#include "strutture_dati/coda.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct nodo{
    Prenotazione prenotazione;
    time_t massimo;
    int altezza;
	struct nodo *destra;
    struct nodo *sinistra;
};

struct albero{
    struct nodo *radice;
    unsigned int num_nodi;
};

static time_t massimo(time_t a, time_t b);
static int altezza(struct nodo *nodo);
static struct nodo* nuovo_nodo(Prenotazione prenotazione);
static void aggiorna_nodo(struct nodo *n);
static struct nodo *ruota_destra(struct nodo *y);
static struct nodo *ruota_sinistra(struct nodo *x);
static struct nodo *casi_bilanciamento(struct nodo *nodo, time_t inizio);
static struct nodo *aggiungi_prenotazione_t(struct nodo *albero, Prenotazione prenotazione);
static void distruggi_nodo_prenotazioni(struct nodo *nodo);
static void _distruggi_prenotazioni(struct nodo *nodo);
static Byte controlla_prenotazione_t(struct nodo *radice, Intervallo i);
static struct nodo *cancella_prenotazione_t(struct nodo *radice, Intervallo i, Byte *controllo);
static struct nodo *trova_minimo(struct nodo *nodo);
static void prenotazioni_in_vettore_t(struct nodo *radice, Prenotazione *result, int *index);

static time_t massimo(time_t a, time_t b){
    return a > b ? a: b;
}

static int altezza(struct nodo *nodo) {
    return nodo ? nodo->altezza : 0;
}

static struct nodo* nuovo_nodo(Prenotazione prenotazione) {
    struct nodo* nodo = malloc(sizeof(struct nodo));
    nodo->prenotazione = prenotazione;
    nodo->sinistra   = nodo->destra = NULL;
    nodo->altezza = 1;
    nodo->massimo = fine_intervallo(ottieni_intervallo_prenotazione(prenotazione));
    return nodo;
}

static time_t ottieni_massimo(struct nodo *nodo){
    return nodo ? nodo->massimo: 0;
}

static void aggiorna_nodo(struct nodo *n) {
    Intervallo iv = ottieni_intervallo_prenotazione(n->prenotazione);
    time_t fi = fine_intervallo(iv);

    n->altezza = 1 + massimo(altezza(n->sinistra), altezza(n->destra));

	/* Il massasimo intervallo presente fra il nodo e i suoi figli
     * utile per velocizzare la ricerca di intervalli
     * che si sovrappongono
	 */
    n->massimo = massimo(fi, massimo(ottieni_massimo(n->sinistra), ottieni_massimo(n->destra)));
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
static struct nodo *ruota_destra(struct nodo *y){
    struct nodo *x = y->sinistra;
    struct nodo *T2 = x->destra;

    x->destra = y;
    y->sinistra = T2;

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
static struct nodo *ruota_sinistra(struct nodo *x){
    struct nodo *y = x->destra;
    struct nodo *T2 = y->sinistra;

    y->sinistra = x;
    x->destra = T2;

    /* Ricalcolare il massimo fra il nodo e i suoi 2 figli */
	aggiorna_nodo(x);
	aggiorna_nodo(y);

    return y;
}

static struct nodo *casi_bilanciamento(struct nodo *nodo, time_t inizio) {
    int bilancio = altezza(nodo->sinistra) - altezza(nodo->destra);

    /* sinistra-sinistra o sinistra-destra */
    if (bilancio > 1 && nodo->sinistra) {
        time_t inizio_l = inizio_intervallo(ottieni_intervallo_prenotazione(nodo->sinistra->prenotazione));

        /* sinistra-sinistra */
        if (inizio < inizio_l)
            return ruota_destra(nodo);

        /* sinistra-destra */
        nodo->sinistra = ruota_sinistra(nodo->sinistra);
        return ruota_destra(nodo);
    }

    /* destra-destra o destra-sinistra */
    if (bilancio < -1 && nodo->destra) {
        time_t inizio_r = inizio_intervallo(ottieni_intervallo_prenotazione(nodo->destra->prenotazione));

        /* destra-destra */
        if (inizio > inizio_r)
            return ruota_sinistra(nodo);

        /* destra-sinistra */
        nodo->destra = ruota_destra(nodo->destra);
        return ruota_sinistra(nodo);
    }

    /* Nessun ribilanciamento necessario */
    return nodo;
}

static void distruggi_nodo_prenotazioni(struct nodo *nodo){
	if(nodo == NULL) return;

	/* prenotazione è allocata in memoria
	 * dinamicamente quindi va distrutta con
     * la sua funzione prima di liberare p
	 */
    distruggi_prenotazione(nodo->prenotazione);

    free(nodo);
}

static void _distruggi_prenotazioni(struct nodo *nodo) {
    if (nodo == NULL) return;
	/* Distrugge tutti i nodi in modo preorder */
    _distruggi_prenotazioni(nodo->sinistra);
    _distruggi_prenotazioni(nodo->destra);

    distruggi_nodo_prenotazioni(nodo);
}

static struct nodo *aggiungi_prenotazione_t(struct nodo *albero, Prenotazione prenotazione){
    if(prenotazione == NULL)
        return NULL;

    if(albero == NULL)
        return nuovo_nodo(prenotazione);

    time_t inizio = inizio_intervallo(ottieni_intervallo_prenotazione(albero->prenotazione));
    time_t nuovo_inizio = inizio_intervallo(ottieni_intervallo_prenotazione(prenotazione));

    if(nuovo_inizio < inizio){
        albero->sinistra = aggiungi_prenotazione_t(albero->sinistra, prenotazione);
    }
    else{
        albero->destra = aggiungi_prenotazione_t(albero->destra, prenotazione);
    }

	aggiorna_nodo(albero);

    /* Ribilancia l'albero se necessario */
    return casi_bilanciamento(albero, nuovo_inizio);
}

static Byte controlla_prenotazione_t(struct nodo *radice, Intervallo i){
    if(radice == NULL)
        return OK;

    Intervallo i_attuale = ottieni_intervallo_prenotazione(radice->prenotazione);
    time_t inizio = inizio_intervallo(i);

    if(intervalli_si_sovrappongono(i_attuale, i)) return OCCUPATO;

    /* Se esiste il nodo sinistro E il massimo intervallo presente
     * nel nodo sinistro è maggiore o uguale all'inizio della nuova prenotazione,
     * allora la potenziale sovrapposizione potrebbe essere nel sottoalbero sinistro
     */
    if(radice->sinistra && radice->sinistra->massimo >= inizio)
        return controlla_prenotazione_t(radice->sinistra, i);
	/* Altrimenti si controlla a destra */
    return controlla_prenotazione_t(radice->destra, i);
}

static struct nodo *trova_minimo(struct nodo *nodo){
    while(nodo->sinistra != NULL){
        nodo = nodo->sinistra;
    }
    return nodo;
}

static struct nodo *cancella_prenotazione_t(struct nodo *radice, Intervallo i, Byte *controllo) {
    if (radice == NULL) return radice;

    Intervallo i_attuale = ottieni_intervallo_prenotazione(radice->prenotazione);
    time_t inizio = inizio_intervallo(i);

    if (!compara_intervalli(i_attuale, i)) {
        /* Caso 0/1 figlio */
        if (radice->sinistra == NULL || radice->destra == NULL) {
            struct nodo *temp = radice->sinistra ? radice->sinistra : radice->destra;
            if (temp == NULL) {
                /* Nessun figlio */
                distruggi_nodo_prenotazioni(radice);
                *controllo = 1;
                return NULL;
            } else {
                /* Un figlio */
                distruggi_nodo_prenotazioni(radice);
                *controllo = 1;
                return temp;
            }
        } else {
            /* Caso due figli */
            struct nodo *temp = trova_minimo(radice->destra);
            Intervallo i_min = ottieni_intervallo_prenotazione(temp->prenotazione);

            distruggi_prenotazione(radice->prenotazione);
            radice->prenotazione = duplica_prenotazione(temp->prenotazione);

            Byte controllo_dx = 0;
            radice->destra = cancella_prenotazione_t(radice->destra, i_min, &controllo_dx);
            if (controllo_dx){
                *controllo = 1;
            }
        }
    }
    else if (radice->sinistra && radice->sinistra->massimo >= inizio) {
        radice->sinistra = cancella_prenotazione_t(radice->sinistra, i, controllo);
    }
    else {
        radice->destra = cancella_prenotazione_t(radice->destra, i, controllo);
    }

    aggiorna_nodo(radice);
    return casi_bilanciamento(radice, inizio_intervallo(i_attuale));
}

static void prenotazioni_in_vettore_t(struct nodo *radice, Prenotazione *result, int *index) {
    if (!radice) return;

    prenotazioni_in_vettore_t(radice->sinistra, result, index);

    result[*index] = radice->prenotazione;
    (*index)++;

    prenotazioni_in_vettore_t(radice->destra, result, index);
}

Prenotazioni crea_prenotazioni(){
    Prenotazioni albero = malloc(sizeof(struct albero));
    albero->num_nodi = 0;
    albero->radice = NULL;
    return albero;
}

void distruggi_prenotazioni(Prenotazioni prenotazioni) {
    if (prenotazioni == NULL) return;

    _distruggi_prenotazioni(prenotazioni->radice);

    /* Dopo aver distrutto la prenotazione imposto a NULL
     * il puntatore, per evitare dangling pointer e memory leak
     */
    prenotazioni->radice = NULL;
    prenotazioni->num_nodi = 0;
    free(prenotazioni);
}

Byte aggiungi_prenotazione(Prenotazioni albero, Prenotazione prenotazione){
    if(albero == NULL || prenotazione == NULL) return 0;
    albero->radice = aggiungi_prenotazione_t(albero->radice, prenotazione);
    if(albero->radice == NULL) return 0;
    albero->num_nodi += 1;
    return 1;
}

Byte controlla_prenotazione(Prenotazioni prenotazioni, Intervallo i){
    if(prenotazioni == NULL || i == NULL) return 0;
    return controlla_prenotazione_t(prenotazioni->radice, i);
}

Byte cancella_prenotazione(Prenotazioni prenotazioni, Intervallo i){
    if(prenotazioni == NULL || i == NULL) return 0;

    Byte controllo = 0;
    prenotazioni->radice = cancella_prenotazione_t(prenotazioni->radice, i, &controllo);
    if(controllo) prenotazioni->num_nodi -= 1;
    return controllo;
}

Prenotazione *ottieni_vettore_prenotazioni_ordinate(Prenotazioni prenotazioni, unsigned int *size) {
    if (!prenotazioni) return NULL;

    unsigned int num_nodi = prenotazioni->num_nodi;
    Prenotazione *result = malloc(sizeof(Prenotazione) * num_nodi);
    if (!result) return NULL;

    int index = 0;
    prenotazioni_in_vettore_t(prenotazioni->radice, result, &index);
    *size = num_nodi;
    return result;
}

Prenotazione *ottieni_vettore_prenotazioni_per_file(Prenotazioni prenotazioni, unsigned int *size) {
    if (prenotazioni == NULL) return NULL;

    unsigned int num_nodi = prenotazioni->num_nodi;
    Prenotazione *result = malloc(sizeof(Prenotazione) * num_nodi);
    if (result == NULL){
        return NULL;
    }

    unsigned int i = 0;

    Coda q = crea_coda();
    if (aggiungi_in_coda(prenotazioni->radice, q) < 0) {
        free(result);
        return NULL;
    }
    while (!coda_vuota(q)) {
        struct nodo *temp = (struct nodo *)rimuovi_dalla_coda(q);
        if (temp == NULL) continue;

        result[i++] = temp->prenotazione;

        if (temp->sinistra != NULL && aggiungi_in_coda(temp->sinistra, q) < 0) {
            free(result);
            return NULL;
        }

        if (temp->destra != NULL && aggiungi_in_coda(temp->destra, q) < 0) {
            free(result);
            return NULL;
        }
    }

    *size = i;

    distruggi_coda(q, NULL);

    return result;
}
