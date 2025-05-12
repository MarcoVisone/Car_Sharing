/*
 * Autore: Antonio Sicignano
 * Data: 09/05/2025
 */
#ifndef UTENTE_H
#define UTENTE_H

#include "modelli/byte.h"
#define ADMIN 0
#define CLIENTE 1
#define ERRORE_PERMESSO -1

typedef struct nodo *ListaPre;
typedef struct data *Data;
typedef struct utente *Utente;
typedef struct prenotazione *Prenotazione;

Utente crea_utente(char *email, char *password, char *nome, char *cognome, Byte permesso);

void imposta_nome(Utente utente, char *nome);

void imposta_cognome(Utente utente, char *cognome);

void imposta_email(Utente utente, char *email);

void imposta_password(Utente utente, char *password);

void imposta_permesso(Utente utente, Byte permesso);

void imposta_data(Utente utente, Data data);

char *ottieni_cognome(Utente utente);

char *ottieni_nome(Utente utente);

char *ottieni_email(Utente utente);

char *ottieni_password(Utente utente);

Byte ottieni_permesso(Utente utente);

ListaPre ottieni_storico(Utente utente);

Byte aggiungi_a_storico(Utente utente, Prenotazione prenotazione);

Byte rimuovi_da_storico(Utente utente, Prenotazione prenotazione);

int ottieni_frequenza(Utente utente);

#endif