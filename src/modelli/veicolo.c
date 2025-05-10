/*
 * Autore: Russo Nello Manuel
 * Data: 09/05/2025
 */

#include "modelli/veicolo.h"
#include <string.h>

#define NUM_CARATTERI_TARGA 7 + 1
#define MAX_LUNGHEZZA_MODELLO 50 + 1
#define MAX_LUNGHEZZA_DESCRIZIONE 1024 + 1
#define MAX_LUNGHEZZA_TARIFFA 9 + 1

struct veicolo{
    char targa[NUM_CARATTERI_TARGA];
    char modello[MAX_LUNGHEZZA_MODELLO];
    char descrizione[MAX_LUNGHEZZA_DESCRIZIONE];
    double tariffa;
    Prenotazioni prenotazioni;
};

Veicolo crea_veicolo(char *targa, char *modello, char *descrizione, double tariffa, Prenotazioni prenotazioni){
    Veicolo v = malloc(sizeof(struct veicolo));
    if(v == NULL) return NULL;

	snprintf(v->targa, NUM_CARATTERI_TARGA, "%s", targa);

    snprintf(v->modello, MAX_LUNGHEZZA_MODELLO, "%s", modello);

    snprintf(v->descrizione, MAX_LUNGHEZZA_DESCRIZIONE, "%s", descrizione);

    v->tariffa = tariffa;

    v->prenotazioni = prenotazioni;

    return v;
}

void distruggi_veicolo(Veicolo v){
	if(v == NULL) return;
    distruggi_prenotazioni(&(v->prenotazioni));
    free(v);
}

char* ottieni_targa(Veicolo v){
	if(v == NULL) return NULL;
    return v->targa;
}

void imposta_targa(Veicolo v, char *targa){
	if(v == NULL) return;
    snprintf(v->targa, NUM_CARATTERI_TARGA, "%s", targa);
}

char* ottieni_modello(Veicolo v){
	if(v == NULL) return NULL;
    return v->modello;
}

void imposta_modello(Veicolo v, char *modello){
    if(v == NULL) return;
    snprintf(v->modello, MAX_LUNGHEZZA_MODELLO, "%s", modello);
}

char* ottieni_descrizione(Veicolo v){
	if(v == NULL) return NULL;
    return v->descrizione;
}

void imposta_descrizione(Veicolo v, char *descrizione){
    if(v == NULL) return;
    snprintf(v->descrizione, MAX_LUNGHEZZA_DESCRIZIONE, "%s", descrizione);
}

double ottieni_tariffa(Veicolo v){
    if(v == NULL) return -1;
    return v->tariffa;
}

void imposta_tariffa(Veicolo v, double tariffa){
    if(v == NULL) return;
    v->tariffa = tariffa;
}

Prenotazioni ottieni_prenotazioni(Veicolo v){
    if(v == NULL) return NULL;
    return v->prenotazioni;
}

void imposta_prenotazioni(Veicolo v, Prenotazioni prenotazioni){
    if(v == NULL) return;
    v->prenotazioni = prenotazioni;
}

Byte confronta_targhe(Veicolo v, char *targa){
    if(v == NULL) return -1;
    return (strcmp(targa,v->targa) == 0);
}

char* veicolo_in_stringa(Veicolo v){
    if(v == NULL) return NULL;

    int size = NUM_CARATTERI_TARGA +
               MAX_LUNGHEZZA_MODELLO +
               MAX_LUNGHEZZA_TARIFFA +
               MAX_LUNGHEZZA_DESCRIZIONE + 100 + 1;

    char *buffer = malloc(sizeof(char) * size);

    snprintf(buffer, size, "Modello: %s\nDescrizione: %s\nTarga: %s\nTariffa: %0.2lf",
            v->modello,
            v->descrizione,
            v->targa,
            v->tariffa);

    return buffer;
}