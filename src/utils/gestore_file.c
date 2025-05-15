#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils/gestore_file.h"
#include "modelli/intervallo.h"
#include "modelli/prenotazione.h"
#include "strutture_dati/prenotazioni.h"
#include "modelli/veicolo.h"
#include "modelli/utente.h"

static void salva_veicolo(FILE *fp, Veicolo v);
static void salva_prenotazioni(FILE *fp, Prenotazioni prenotazioni);
static Veicolo carica_veicolo(FILE *fp);
static Prenotazioni carica_prenotazioni(FILE *fp);

static void salva_prenotazioni(FILE *fp, Prenotazioni prenotazioni) {
    if (fp == NULL || prenotazioni == NULL) return;
    unsigned int size = 0, i;
    Prenotazione *p = ottieni_vettore_prenotazioni(prenotazioni, &size);
    if (p == NULL) return;

    fwrite(&size, sizeof(size), 1, fp);

    for (i = 0; i < size; i++) {
        char *cliente = ottieni_cliente_prenotazione(p[i]);
        unsigned int len = (unsigned int)strlen(cliente) + 1;
        fwrite(&len, sizeof(len), 1, fp);
        fwrite(cliente, sizeof(char), len, fp);

        double costo = ottieni_costo_prenotazione(p[i]);
        fwrite(&costo, sizeof(costo), 1, fp);

        Intervallo iv = ottieni_intervallo_prenotazione(p[i]);
        time_t inizio = inizio_intervallo(iv);
        time_t fine   = fine_intervallo(iv);
        fwrite(&inizio, sizeof(inizio), 1, fp);
        fwrite(&fine, sizeof(fine), 1, fp);
    }
}

static Prenotazioni carica_prenotazioni(FILE *fp) {
    if (fp == NULL) return NULL;
    unsigned int size = 0, i;
    if (fread(&size, sizeof size, 1, fp) != 1) return NULL;

    Prenotazioni pren = crea_prenotazioni();
    char nome[DIMENSIONE_NOME];

    for (i = 0; i < size; i++) {
        unsigned int len;
        fread(&len, sizeof(len), 1, fp);
        fread(nome, sizeof(char), len, fp);

        double costo;
        fread(&costo, sizeof(costo), 1, fp);

        time_t inizio, fine;
        fread(&inizio, sizeof(inizio), 1, fp);
        fread(&fine, sizeof(fine),   1, fp);

        Intervallo iv = crea_intervallo(inizio, fine);
        Prenotazione p = crea_prenotazione(nome, iv, costo);
        pren = aggiungi_prenotazione(pren, p);
    }
    return pren;
}


void salva_vettore_veicoli(const char *nome_file, Veicolo vettore[], int num_veicoli);

int carica_vettore_veicoli(const char *nome_file, Veicolo vettore[], int max_veicoli);
