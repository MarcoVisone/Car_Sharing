#define _POSIX_C_SOURCE 200809L  // Per usare strdup

#include "modelli/prenotazione.h"
#include "modelli/intervallo.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DIMENSIONE_BUFFER 1024

struct prenotazione {
    char *cliente;
    Intervallo date;
    double costo;
};

Prenotazione crea_prenotazione(char *cliente, Intervallo i, double costo) {
    Prenotazione p = malloc(sizeof(struct prenotazione));

    p->cliente = strdup(cliente);
    p->date = i;
    p->costo = costo;

    return p;
}

void distruggi_prenotazione(Prenotazione p) {
    if (p == NULL) return;

    distruggi_intervallo(p->date);
    free(p->cliente);
    free(p);
}

char *ottieni_cliente_prenotazione(Prenotazione p) {
    if (p == NULL) return NULL;

    return p->cliente;
}

Intervallo ottieni_intervallo_prenotazione(Prenotazione p) {
    if (p == NULL) return NULL;

    return p->date;
}

double ottieni_costo_prenotazione(Prenotazione p) {
    if (p == NULL) return -1;

    return p->costo;
}

void imposta_cliente_prenotazione(Prenotazione p, char *cliente) {
    if (p == NULL) return;

    free(p->cliente);
    p->cliente = strdup(cliente);
}

void imposta_intervallo_prenotazione(Prenotazione p, Intervallo i) {
    if (p == NULL) return;

    distruggi_intervallo(p->date);
    p->date = i;
}

void imposta_costo_prenotazione(Prenotazione p, double costo) {
    if (p == NULL) return;

    p->costo = costo;
}

Prenotazione duplica_prenotazione(Prenotazione p) {
    if (p == NULL) return NULL;

    Intervallo date_copia = duplica_intervallo(p->date);
    char *cliente_copia = strdup(p->cliente);

    Prenotazione copia = crea_prenotazione(cliente_copia, date_copia, p->costo);

    // Libera le copie temporanee perché crea_prenotazione fa strdup
    free(cliente_copia);

    return copia;
}

char *prenotazione_in_stringa(Prenotazione p) {
    if (p == NULL) return NULL;

    char *buffer = malloc(sizeof(char) * DIMENSIONE_BUFFER);
    if (buffer == NULL) return NULL;

    char *date = intervallo_in_stringa(p->date);

    snprintf(buffer, DIMENSIONE_BUFFER,
        "- Cliente: %s\n"
        "- Periodo: %s\n"
        "- Costo totale: %.2f euro\n",
        p->cliente,
        date,
        p->costo
    );

    free(date);
    return buffer;
}
