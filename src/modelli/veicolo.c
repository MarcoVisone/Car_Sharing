/*
 * Autore: Russo Nello Manuel
 * Data: 09/05/2025
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "modelli/intervallo.h"
#include "modelli/prenotazione.h"
#include "strutture_dati/prenotazioni.h"
#include "modelli/veicolo.h"

#define NUM_CARATTERI_TARGA 7 + 1
#define MAX_LUNGHEZZA_MODELLO 50 + 1
#define MAX_LUNGHEZZA_DESCRIZIONE 1024 + 1
#define MAX_LUNGHEZZA_TARIFFA 9 + 1
#define MAX_LUNGHEZZA_TIPO 30 + 1

struct veicolo{
    char targa[NUM_CARATTERI_TARGA];
    char modello[MAX_LUNGHEZZA_MODELLO];
    char descrizione[MAX_LUNGHEZZA_DESCRIZIONE];
    double tariffa;
	char tipo_veicolo[MAX_LUNGHEZZA_TIPO];
    Prenotazioni prenotazioni;
};

Veicolo crea_veicolo(char *tipo, char *targa, char *modello, char *descrizione, double tariffa, Prenotazioni prenotazioni){
    Veicolo v = malloc(sizeof(struct veicolo));
    if(v == NULL) return NULL;

	snprintf(v->targa, NUM_CARATTERI_TARGA, "%s", targa);

    snprintf(v->modello, MAX_LUNGHEZZA_MODELLO, "%s", modello);

    snprintf(v->descrizione, MAX_LUNGHEZZA_DESCRIZIONE, "%s", descrizione);

	snprintf(v->tipo_veicolo, MAX_LUNGHEZZA_TIPO, "%s", tipo);

    v->tariffa = tariffa;

    v->prenotazioni = prenotazioni;

    return v;
}

void distruggi_veicolo(Veicolo v){
	if(v == NULL) return;
    distruggi_prenotazioni(&(v->prenotazioni));
    free(v);
}

char *ottieni_targa(Veicolo v){
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

char* ottieni_tipo_veicolo(Veicolo v){
	if(v == NULL) return NULL;
	return v->tipo_veicolo;
}

void imposta_tipo_veicolo(Veicolo v, char *tipo){
	if(v == NULL) return;
	snprintf(v->tipo_veicolo, MAX_LUNGHEZZA_TIPO, "%s", tipo);
}

Byte confronta_tipo(Veicolo v, char *tipo){
	if(v == NULL) return 0;
	return (strcmp(tipo, v->tipo_veicolo) == 0);
}

Byte aggiungi_prenotazione_veicolo(Veicolo v, Prenotazione prenotazione){
	if(v == NULL) return 0;
	if(prenotazione == NULL) return 0;

	Prenotazioni temp = aggiungi_prenotazione(v->prenotazioni, prenotazione);

	if(temp == NULL) return 0;

	v->prenotazioni = temp;

	return 1;
}

Byte rimuovi_prenotazione_veicolo(Veicolo v, Prenotazione prenotazione, char *cliente){
	if(v == NULL) return 0;
    if(prenotazione == NULL) return 0;

	Intervallo i = ottieni_intervallo_prenotazione(prenotazione);
	char *cliente_a = ottieni_cliente_prenotazione(prenotazione);

	if((controlla_prenotazione(v->prenotazioni, i) == 1) && (strcmp(cliente, cliente_a) == 0)){
		v->prenotazioni = cancella_prenotazione(v->prenotazioni, prenotazione);
		return 1;
	}
	return 0;
}

Byte confronta_targhe(Veicolo v, char *targa){
    if(v == NULL) return -1;
    return (strcmp(targa,v->targa) == 0);
}

char* veicolo_in_stringa(Veicolo v){
    if(v == NULL) return NULL;

    int size = MAX_LUNGHEZZA_TIPO +
			   NUM_CARATTERI_TARGA +
               MAX_LUNGHEZZA_MODELLO +
               MAX_LUNGHEZZA_TARIFFA +
               MAX_LUNGHEZZA_DESCRIZIONE + 100 + 1;

    char *buffer = malloc(sizeof(char) * size);

    snprintf(buffer, size, "Tipo: %s\nModello: %s\nDescrizione: %s\nTarga: %s\nTariffa: %0.3lf",
			v->tipo_veicolo,
            v->modello,
            v->descrizione,
            v->targa,
            v->tariffa);

    return buffer;
}
