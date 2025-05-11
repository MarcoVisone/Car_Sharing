#define _POSIX_C_SOURCE 200809L  // Per usare strdup

#include "modelli/prenotazione.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DIMENSIONE_BUFFER 1024

struct prenotazione {
    char *cliente;
    char *veicolo;
    Intervallo date;
    double costo;
};

Prenotazione crea_prenotazione(char *cliente, Intervallo i, char *targa_veicolo, double costo) {
    Prenotazione p = malloc(sizeof(struct prenotazione));

    p->cliente = strdup(cliente);
    p->veicolo = strdup(targa_veicolo);
    p->date = i;
    p->costo = costo;

    return p;
}

void distruggi_prenotazione(Prenotazione p) {
    if (p == NULL) return;

    distruggi_intervallo(p->date);
    free(p->veicolo);
    free(p->cliente);
    free(p);
}

char *ottieni_cliente_prenotazione(Prenotazione p) {
    if (p == NULL) return NULL;

    return p->cliente;
}

char *ottieni_veicolo_prenotazione(Prenotazione p) {
    if (p == NULL) return NULL;

    return p->veicolo;
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

void imposta_veicolo_prenotazione(Prenotazione p, char *veicolo) {
    if (p == NULL) return;

    free(p->veicolo);
    p->veicolo = strdup(veicolo);
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
    char *veicolo_copia = strdup(p->veicolo);

    Prenotazione copia = crea_prenotazione(cliente_copia, date_copia, veicolo_copia, p->costo);

    // Libera le copie temporanee perché crea_prenotazione fa strdup
    free(cliente_copia);
    free(veicolo_copia);

    return copia;
}

char *prenotazione_in_stringa(Prenotazione p) {
    if (p == NULL) return NULL;

    char *buffer = malloc(sizeof(char) * DIMENSIONE_BUFFER);
    if (buffer == NULL) return NULL;

    char *date = intervallo_in_stringa(p->date);

    snprintf(buffer, DIMENSIONE_BUFFER,
        "Prenotazione per il cliente %s:\n"
        "- Targa Veicolo: %s\n"
        "- Periodo: %s\n"
        "- Costo totale: %.2f euro\n",
        p->cliente,
        p->veicolo,
        date,
        p->costo
    );

    free(date);
    return buffer;
}
