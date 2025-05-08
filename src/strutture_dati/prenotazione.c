/*
 * Autore: Marco Visone
 * Data: 06/05/2025
 */

#include "../../include/strutture_dati/prenotazione.h"
#include <stdlib.h>

struct prenotazione {
    Utente cliente;
    Intervallo date;
    double costo;
};

Prenotazione prenotazione_crea(Utente cliente, Intervallo i, double costo){
    Prenotazione p = malloc(sizeof(struct prenotazione));
    p->cliente = cliente;
    p->date = i;
    p->costo = costo;
    return p;
}

void prenotazione_distruggi(Prenotazione p){
    if(p == NULL){
        return;
    }
    free(p);
}

Utente prenotazione_ottieni_cliente(Prenotazione p){
    if(p == NULL){
        return NULL;
    }
    return p->cliente;
}

Intervallo prenotazione_ottieni_intervallo(Prenotazione p){
    if(p == NULL){
      return NULL;
    }
    return p->date;
}

double prenotazione_ottieni_costo(Prenotazione p){
    if(p == NULL){
        return 0;
    }
    return p->costo;
}

void prenotazione_imposta_cliente(Prenotazione p, Utente cliente){
    if(p == NULL){
        return;
    }
    p->cliente = cliente;
}

void prenotazione_imposta_intervallo(Prenotazione p, Intervallo i){
    if(p == NULL){
        return;
    }
    p->date = i;
}

void prenotazione_imposta_costo(Prenotazione p, double costo){
    if(p == NULL){
        return;
    }
    p->costo = costo;
}

Prenotazione prenotazione_duplica(Prenotazione p){
    if(p == NULL) return NULL;

    Prenotazione copia = prenotazione_crea(p->cliente, p->date,  p->costo);

    return copia;
}