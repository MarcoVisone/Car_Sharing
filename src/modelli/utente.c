/*
 * Autore: Antonio Sicignano
 * Data: 09/05/2025
 */

#include <stdlib.h>
#include <stdio.h>
#include "strutture_dati/lista.h"
#include "modelli/utente.h"
#include "modelli/data.h"
#include <string.h>

struct utente {
    char nome[DIMENSIONE_NOME];
    char cognome[DIMENSIONE_COGNOME];
    char email[DIMENSIONE_EMAIL];
    uint8_t password[DIMENSIONE_PASSWORD];
    Byte permesso;
    Data data;
};

Utente crea_utente(char *email, uint8_t *password,  char *nome, char *cognome, Byte permesso){
    Utente u = malloc(sizeof(struct utente));

    if(u == NULL){
        return NULL;
    }

    snprintf(u->nome, DIMENSIONE_NOME, "%s", nome);
    snprintf(u->cognome, DIMENSIONE_COGNOME, "%s", cognome);
    snprintf(u->email, DIMENSIONE_EMAIL, "%s", email);
    memcpy(u->password, password, DIMENSIONE_PASSWORD);

    u->permesso = permesso;
    if (permesso == CLIENTE) {
        u->data = crea_data();
    }
    else {
        u->data = NULL;
    }

    return u;
}

void distruggi_utente(Utente utente){
        if(utente == NULL) return;
        distruggi_data(utente->data);
        free(utente);
}

void imposta_nome(Utente utente, char *nome) {
    if(utente == NULL) {
        return;
    }

    snprintf(utente->nome, DIMENSIONE_NOME, "%s", nome);
}

void imposta_cognome(Utente utente, char *cognome) {
    if(utente == NULL) {
        return;
    }

    snprintf(utente->cognome, DIMENSIONE_COGNOME, "%s", cognome);
}

void imposta_email(Utente utente, char *email) {
    if(utente == NULL) {
        return;
    }

    snprintf(utente->email, DIMENSIONE_EMAIL, "%s", email);
}

void imposta_password(Utente utente, uint8_t *password) {
    if(utente == NULL) {
        return;
    }

    memcpy(utente->password, password, DIMENSIONE_PASSWORD);
}

void imposta_permesso(Utente utente, Byte permesso) {
    if(utente == NULL) {
        return;
    }

    utente->permesso = permesso;
}

void imposta_data(Utente utente, Data data) {
    if(utente == NULL) {
        return;
    }

    if (utente->permesso == ADMIN) {
        return;
    }

    if (utente->data != NULL) {
        distruggi_data(utente->data);
    }

    utente->data = data;
}

char *ottieni_nome(Utente utente){
    if (utente == NULL) {
        return NULL;
    }
    return utente->nome;
}

char *ottieni_cognome(Utente utente){
    if (utente == NULL) {
        return NULL;
    }
    return utente->cognome;
}

char *ottieni_email(Utente utente){
    if (utente == NULL) {
        return NULL;
    }
    return utente->email;
}

uint8_t *ottieni_password(Utente utente){
    if (utente == NULL) {
        return NULL;
    }
    return utente->password;
}

int ottieni_frequenza_cliente(Utente utente) {
    return ottieni_frequenza_lista(utente->data);
}

Byte ottieni_permesso(Utente utente){
    if (utente == NULL) {
        return ERRORE_PERMESSO;
    }

    return utente->permesso;
}

ListaPre ottieni_storico_utente(Utente utente) {
    if (utente == NULL) {
        return NULL;
    }

    return ottieni_storico_lista(utente->data);
}

Byte aggiungi_a_storico_utente(Utente utente, Prenotazione prenotazione) {
    if (utente == NULL) {
        return 0;
    }

    return aggiungi_a_storico_lista(utente->data, prenotazione) != NULL;
}

Byte rimuovi_da_storico_utente(Utente utente, Prenotazione prenotazione) {
    if (utente == NULL) {
        return 0;
    }

    return rimuovi_da_storico_lista(utente->data, prenotazione) != NULL;
}
