
#include "strutture_dati/veicolo.h"
#include <string.h>

#define NUM_CARATTERI_TARGA 7
#define MAX_LUNGHEZZA_MODELLO 50
#define MAX_LUNGHEZZA_DESCRIZIONE 1024

struct veicolo{
    char targa[NUM_CARATTERI_TARGA];
    char modello[MAX_LUNGHEZZA_MODELLO];
    char descrizione[MAX_LUNGHEZZA_DESCRIZIONE];
    double tariffa;
    AVLIntervalTree prenotazione;
};

char* getTarga(veicolo *v){
    return v->targa;
}

void setTarga(veicolo *v, char *targa){
    strcpy(v->targa,targa);
}

char* getModello(veicolo *v){
    return v->modello;
}

void setModello(veicolo *v, char *modello){
    strcpy(v->modello, modello);
}

char* getDescrizione(veicolo *v){
    return v->descrizione;
}

void setDescrizione(veicolo *v, char *descrizione){
    strcpy(v->descrizione, descrizione);
}

double getTariffa(veicolo *v){
    return v->tariffa;
}

void setTariffa(veicolo *v, double tariffa){
    v->tariffa = tariffa;
}

AVLIntervalTree getPrenotazione(veicolo *v){
    return v->prenotazione;
}

void setPrenotazione(veicolo *v, AVLIntervalTree p){
    v->prenotazione = p;
}

Byte confrontaTarghe(veicolo *v, char *targa){
    if(strcmp(targa,v->targa) == 0){
        return 1;
    }
    return 0;
}

