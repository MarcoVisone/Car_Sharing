/*
 * Autore: Antonio Sicignano
 * Data: 09/05/2025
 */

#include <stdlib.h>
#include <string.h>
#include "strutture_dati/lista.h"
#include "modelli/utente.h"
#include "modelli/data.h"
#define MAX 30

struct utente {
    char nome[MAX];
    char cognome[MAX];
    char email[MAX];
    char password[MAX];
    Byte permesso;
    Data data;
};

Utente crea_utente(char*email, char*password,  char* nome, char*cognome, Byte permesso, Data data){
    Utente u=malloc(sizeof(struct utente));
    if(u==NULL){
        return NULL;
    }
    strncpy(u->email,email,MAX-1);
    strncpy(u->password,password,MAX-1);
    strncpy(u->nome,nome,MAX-1);
    strncpy(u->cognome,cognome,MAX-1);
    u->permesso=permesso;
    u->data=data;
    return u;
}

char *ottieni_nome(Utente utente){
    return utente->nome;
}

char *ottieni_cognome(Utente utente){
    return utente->cognome;
}

char *ottieni_email(Utente utente){
    return utente->email;
}

char *ottieni_password(Utente utente){
    return utente->password;
}

Byte ottieni_permesso(Utente utente){
    return utente->permesso;
}