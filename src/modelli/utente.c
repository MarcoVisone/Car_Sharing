/*
 * Autore: Antonio Sicignano
 * Data: 09/05/2025
 */

#include <stdlib.h>
#include <stdio.h>
#include "strutture_dati/lista.h"
#include "modelli/utente.h"
#include "modelli/data.h"
#define MAX_NOME (64 + 1)
#define MAX_COGNOME (64 + 1)
#define MAX_EMAIL (319 + 1)
#define MAX_PASSOWORD (64 + 1)

struct utente {
    char nome[MAX_NOME];
    char cognome[MAX_COGNOME];
    char email[MAX_EMAIL];
    char password[MAX_PASSOWORD];
    Byte permesso;
    Data data;
};

Utente crea_utente(char *email, char *password,  char *nome, char *cognome, Byte permesso){
    Utente u = malloc(sizeof(struct utente));

    if(u == NULL){
        return NULL;
    }

    snprintf(u->nome, MAX_NOME, "%s", nome);
    snprintf(u->cognome, MAX_COGNOME, "%s", cognome);
    snprintf(u->email, MAX_EMAIL, "%s", email);
    snprintf(u->password, MAX_PASSOWORD, "%s", password);

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

    snprintf(utente->nome, MAX_NOME, "%s", nome);
}

void imposta_cognome(Utente utente, char *cognome) {
    if(utente == NULL) {
        return;
    }

    snprintf(utente->cognome, MAX_COGNOME, "%s", cognome);
}

void imposta_email(Utente utente, char *email) {
    if(utente == NULL) {
        return;
    }

    snprintf(utente->email, MAX_EMAIL, "%s", email);
}

void imposta_password(Utente utente, char *password) {
    if(utente == NULL) {
        return;
    }

    snprintf(utente->password, MAX_PASSOWORD, "%s", password);
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

char *ottieni_password(Utente utente){
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
