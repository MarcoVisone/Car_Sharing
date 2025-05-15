#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils/gestore_file.h"
#include "modelli/intervallo.h"
#include "modelli/prenotazione.h"
#include "strutture_dati/prenotazioni.h"
#include "modelli/veicolo.h"
#include "modelli/data.h"
#include "modelli/utente.h"

static void salva_prenotazione(FILE *fp, Prenotazione prenotazione);
static void salva_prenotazioni(FILE *fp, Prenotazioni prenotazioni);
static Prenotazioni carica_prenotazioni(FILE *fp);

/*
    Scrivere nel file la grandezza del vettore (funzione fwrite)
    poi iterare il vettore e fare fwrite di ogni campo del veicolo e per prenotazioni usare
    la funzione salva_prenotazioni passando il file_prenotazioni
*/
static void salva_veicolo(FILE *file_veicolo, FILE *file_prenotazioni, Veicolo v);

/*
    Prendere dal file la grandezza del veicolo con fread,
    leggere ogni campo del veicolo e alla fine creare un veicolo con
    quei campi (usare carica_prenotazioni quando si devono prendere le prenotazioni)
    e restituirlo
*/
static Veicolo carica_veicolo(FILE *file_veicolo, FILE *file_prenotazioni);

static void salva_data(FILE *file_data, Data d);

static Data carica_data(FILE *file_data, Data d);

static void salva_utente(FILE *file_utente, FILE *file_data, Utente u);

static Utente carica_utente(FILE *file_utente, FILE *file_data);

static void salva_prenotazione(FILE *fp, Prenotazione prenotazione){
    if(fp == NULL || prenotazione == NULL) return;

    char *cliente = ottieni_cliente_prenotazione(prenotazione);
    unsigned int len = (unsigned int)strlen(cliente) + 1;
    fwrite(&len, sizeof(len), 1, fp);
    fwrite(cliente, sizeof(char), len, fp);

    double costo = ottieni_costo_prenotazione(prenotazione);
    fwrite(&costo, sizeof(costo), 1, fp);

    Intervallo iv = ottieni_intervallo_prenotazione(prenotazione);
    time_t inizio = inizio_intervallo(iv);
    time_t fine   = fine_intervallo(iv);
    fwrite(&inizio, sizeof(inizio), 1, fp);
    fwrite(&fine, sizeof(fine), 1, fp);
}

static void salva_prenotazioni(FILE *fp, Prenotazioni prenotazioni) {
    if (fp == NULL || prenotazioni == NULL) return;
    unsigned int size = 0, i;
    Prenotazione *p = ottieni_vettore_prenotazioni(prenotazioni, &size);
    if (p == NULL) return;

    fwrite(&size, sizeof(size), 1, fp);

    for (i = 0; i < size; i++) {
        salva_prenotazione(fp, p[i]);
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

/*
    Iterare il vettore e usare per ogni cella la funzione salva_veicolo
*/
void salva_vettore_veicoli(const char *nome_file, Veicolo vettore[], int num_veicoli){
    return;
}

int carica_vettore_veicoli(const char *nome_file, Veicolo vettore[], int max_veicoli){
    return 0;
}

static void salva_data(FILE *file_data, Data d){
    if(file_data == NULL || d == NULL){
      return;
    }
    unsigned int dimensione;
    Prenotazione *lista_prenotazioni;
    lista_prenotazioni = ottieni_vettore_storico(d, &dimensione);
    int numero_prenotazioni = ottieni_numero_prenotazioni(d);
    int frequenza = ottieni_frequenza_lista(d);
    fwrite(&frequenza, sizeof(int), 1, file_data);
    fwrite(&numero_prenotazioni, sizeof(int), 1, file_data);
    for(int i = 0; i < numero_prenotazioni; i++){
        salva_prenotazione(file_data, lista_prenotazioni[i]);
    }
}

static Data carica_data(FILE *file_data, Data d){
    if(file_data == NULL || d == NULL){
        return NULL;
    }
    int numero_prenotazioni;
    int frequenza;

    fread(&numero_prenotazioni, sizeof(int), 1, file_data);
    fread(&frequenza, sizeof(int), 1, file_data);
}

static void salva_utente(FILE *file_utente, FILE *file_data, Utente u){
    if (file_utente == NULL || u == NULL) return;

    unsigned int len = strlen(ottieni_nome(u))+1;
    fwrite(&len, sizeof(unsigned int), 1, file_utente);
    fwrite(ottieni_nome(u), sizeof(char), len, file_utente);

    len = strlen(ottieni_cognome(u))+1;
    fwrite(&len, sizeof(unsigned int), 1, file_utente);
    fwrite(ottieni_cognome(u), sizeof(char), len, file_utente);

    len = strlen(ottieni_email(u)+1);
    fwrite(&len, sizeof(unsigned int), 1, file_utente);
    fwrite(ottieni_email(u), sizeof(char), len, file_utente);

    fwrite(ottieni_password(u), sizeof(uint8_t), DIMENSIONE_PASSWORD, file_utente);

    Byte permesso = ottieni_permesso(u);
    fwrite(&permesso, sizeof(Byte), 1, file_utente);

    salva_data(file_data, ottieni_data(u));
}

static Utente carica_utente(FILE *file_utente, FILE *file_data){
    if (file_utente == NULL) return NULL;

    unsigned int len = 0;
    fread(&len, sizeof(unsigned int), 1, file_utente);
    char *nome = malloc(len*sizeof(char));
    fread(nome, sizeof(char), len, file_utente);

    fread(&len, sizeof(unsigned int), 1, file_utente);
    char *cognome = malloc(len*sizeof(char));
    fread(cognome, sizeof(char), len, file_utente);

    fread(&len, sizeof(unsigned int), 1, file_utente);
    char *email = malloc(len*sizeof(char));
    fread(email, sizeof(char), len, file_utente);

    uint8_t *password = malloc(sizeof(uint8_t)*DIMENSIONE_PASSWORD);
    fread(password, sizeof(uint8_t), DIMENSIONE_PASSWORD, file_utente);

    Byte permesso;
    fread(&permesso, sizeof(Byte), 1, file_utente);

    Data data = NULL;
    if(permesso == CLIENTE){
      carica_data(file_data, data);
    }

    Utente u;
    u=crea_utente(email, password,  nome, cognome, permesso);
    free(nome);
    free(cognome);
    free(email);
    free(password);
    return u;
}

void salva_vettore_utenti(const char *nome_file, Utente vettore[], int num_utenti){
    return;
}

int carica_vettore_utenti(const char *nome_file, Utente vettore[], int max_utenti){
    return 0;
}