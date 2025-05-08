#ifndef VEICOLO_H
#define VEICOLO_H

#include "../include/strutture_dati/byte.h"

typedef struct veicolo *Veicolo;

/*
* Funzione: crea_veicolo
* ----------------------
* Restituisce un nuovo veicolo con targa, modello, descrizione,
* tariffa, prenotazioni passati come parametri alla funzione.
*
* Parametri:
*    targa: stringa che rappresenta la targa del veicolo
*    modello: stringa che rappresenta il modello del veicolo
*    descrizione: stringa che rappresenta la descrizione del veicolo
*    tariffa: numero che rappresenta la tariffa oraria in euro di un veicolo
*    prenotazioni: puntatore alle prenotazioni relative ad un veicolo
*
* Pre-condizioni:
*    targa: deve contenere una targa valida di 7 caratteri
*    modello: non deve essere nullo e non deve essere vuoto
*    descrizione: non deve essere nulla non deve essere vuota
*    tariffa: deve essere > 0
*
* Post-condizione:
*   ritorna un nuovo veicolo v se l'allocazione dinamica della memoria è andata a buon fine,
*   altrimenti ritorna NULL
*
* Ritorna:
*   Un nuovo veicolo v
*/
Veicolo crea_veicolo(char *targa, char *modello, char *descrizione, double tariffa, Prenotazioni prenotazioni);


void distruggi_veicolo(Veicolo v);

char* get_targa(Veicolo *v);

void set_targa(Veicolo *v, char *targa);

char* get_modello(Veicolo *v);

void set_modello(Veicolo *v, char *modello);

char* get_descrizione(Veicolo *v);

void set_descrizione(Veicolo *v, char *descrizione);

double get_tariffa(Veicolo *v);

void set_tariffa(Veicolo *v, double tariffa);

Prenotazioni get_prenotazioni(Veicolo *v);

void set_prenotazioni(Veicolo *v, Prenotazioni prenotazioni);

Byte confronta_targhe(Veicolo *v, char *targa);

char* veicolo_in_stringa(Veicolo *v);

#endif //VEICOLO_H
