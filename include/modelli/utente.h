/*
 * Autore: Antonio Sicignano
 * Data: 09/05/2025
 */

#include "modelli/byte.h"
typedef struct utente *Utente;

Utente crea_utente(char*email, char*password, char*nome, char*cognome, Byte permesso, Data data);
char *ottieni_cognome(Utente);
char *ottieni_nome(Utente);
char *ottieni_email(Utente);
char *ottieni_password(Utente);
Byte ottieni_permesso(Utente);