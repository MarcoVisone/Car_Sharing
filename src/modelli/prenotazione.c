/*
 * Autore: Marco Visone
 * Data: 06/05/2025
 */

#include "modelli/prenotazione.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DIMENSIONE_BUFFER 1024
#define DIMENSIONE_EMAIL 254 + 1

struct prenotazione {
    char cliente[DIMENSIONE_EMAIL];
    Intervallo date;
    double costo;
};

Prenotazione crea_prenotazione(char *cliente, Intervallo i, double costo){
    Prenotazione p = malloc(sizeof(struct prenotazione));
    snprintf(p->cliente, DIMENSIONE_EMAIL, "%s", cliente);
    p->date = i;
    p->costo = costo;
    return p;
}

void distruggi_prenotazione(Prenotazione p){
    if(p == NULL){
        return;
    }
    distruggi_intervallo(p->date);
    free(p);
}

char *ottieni_cliente_prenotazione(Prenotazione p){
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

void imposta_cliente_prenotazione(Prenotazione p, char *cliente){
    if(p == NULL){
        return;
    }
    snprintf(p->cliente, DIMENSIONE_EMAIL, "%s%c", cliente, 0);
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

    char *cliente_copia = strndup(p->cliente, DIMENSIONE_EMAIL);

    Prenotazione copia = crea_prenotazione(cliente_copia, date_copia,  p->costo);

    return copia;
}


char *prenotazione_in_stringa(Prenotazione p){
	if(p == NULL){
		return NULL;
	}
	char *buffer = malloc(sizeof(char) * DIMENSIONE_BUFFER);
	char *date = intervallo_in_stringa(p->date);
	double costo = p->costo;
	snprintf(buffer, DIMENSIONE_BUFFER, "Cliente: %s\nDurata Prenotazione: %s\nPrezzo Prenotazione: %0.2lf\n",
			p->cliente,
			date,
			costo);

	return buffer;
}