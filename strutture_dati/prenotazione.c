//
// Created by marco on 5/6/25.
//
#include "prenotazione.h"
#include <stdlib.h>

struct prenotazione {
    Utente cliente;
    Intervallo date;
    double costo;
};

Prenotazione prenotazioneCrea(Utente cliente, Intervallo i, double costo){
    Prenotazione p = malloc(sizeof(struct prenotazione));
    p->cliente = cliente;
    p->date = i;
    p->costo = costo;
    return p;
}

void prenotazioneDestroy(Prenotazione p){
    if(p == NULL){
        return;
    }
    free(p);
}

Utente getCliente(Prenotazione p){
    if(p == NULL){
        return NULL;
    }
    return p->cliente;
}

Intervallo getDateIntervallo(Prenotazione p){
    if(p == NULL){
      return NULL;
    }
    return p->date;
}

double getCosto(Prenotazione p){
    if(p == NULL){
        return NULL;
    }
    return p->costo;
}

void setCliente(Prenotazione p, Utente cliente){
    if(p == NULL){
        return;
    }
    p->cliente = cliente;
}

void setDateIntervallo(Prenotazione p, Intervallo i){
    if(p == NULL){
        return;
    }
    p->date = i;
}

void setCosto(Prenotazione p, double costo){
    if(p == NULL){
        return;
    }
    p->costo = costo;
}