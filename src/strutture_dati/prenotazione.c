/*
 * Autore: Marco Visone
 * Data: 06/05/2025
 */

#include "../../include/strutture_dati/prenotazione.h"
#include <stdlib.h>
#include <stdio.h>
#define DIMENSIONE_BUFFER 1024

struct prenotazione {
    Utente cliente;
    Intervallo date;
    double costo;
};

Prenotazione crea_prenotazione(Utente cliente, Intervallo i, double costo){
    Prenotazione p = malloc(sizeof(struct prenotazione));
    p->cliente = cliente;
    p->date = i;
    p->costo = costo;
    return p;
}

void distruggi_prenotazione(Prenotazione p){
    if(p == NULL){
        return;
    }
    distruggi_intervallo(p->date);
    distruggi_utente(p->cliente);
    free(p);
}

Utente ottieni_cliente_prenotazione(Prenotazione p){
    if(p == NULL){
        return NULL;
    }

    return p->cliente;
}

Intervallo ottieni_intervallo_prenotazione(Prenotazione p){
    if(p == NULL){
      return NULL;
    }

    return p->date;
}

double ottieni_costo_prenotazione(Prenotazione p){
    if(p == NULL){
        return 0;
    }

    return p->costo;
}

void imposta_cliente_prenotazione(Prenotazione p, Utente cliente){
    if(p == NULL){
        return;
    }

    p->cliente = cliente;
}

void imposta_intervallo_prenotazione(Prenotazione p, Intervallo i){
    if(p == NULL){
        return;
    }

    p->date = i;
}

void imposta_costo_prenotazione(Prenotazione p, double costo){
    if(p == NULL){
        return;
    }

    p->costo = costo;
}

Prenotazione duplica_prenotazione(Prenotazione p){
    if(p == NULL) return NULL;

    Intervallo date_copia = duplica_intervallo(p->date);

    Utente cliente_copia = duplica_utente(p->cliente);

    Prenotazione copia = crea_prenotazione(NULL, date_copia,  p->costo);

    return copia;
}


char *prenotazione_in_stringa(Prenotazione p){
	if(p == NULL){
		return NULL;
	}
	char *buffer = malloc(sizeof(char) * DIMENSIONE_BUFFER);
	char *cliente = utente_in_stringa(p->cliente);
	char *date = intervallo_in_stringa(p->date);
	double costo = p->costo;
	snprintf(buffer, DIMENSIONE_BUFFER, "%s\nDurata Prenotazione: %s\nPrezzo Prenotazione: %0.2lf\n",
			cliente,
			date,
			costo);

	return buffer;
}