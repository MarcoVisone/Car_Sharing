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

/*
 * Funzione: crea_utente
 * ---------------------
 * Crea un nuovo utente con email, password, nome, cognome e permesso.
 *
 * Implementazione:
 *    Alloca dinamicamente la struttura utente, inizializza i campi con le
 *    informazioni fornite copiandoli nei rispettivi buffer. Se il permesso è CLIENTE,
 *    crea una struttura Data associata all'utente, altrimenti imposta data a NULL.
 *    Ritorna NULL in caso di fallimento dell'allocazione.
 *
 * Parametri:
 *    email: stringa che rappresenta l'email dell'utente
 *    password: array di uint8_t che rappresenta la password dell'utente
 *    nome: stringa che rappresenta il nome dell'utente
 *    cognome: stringa che rappresenta il cognome dell'utente
 *    permesso: byte che rappresenta il livello di permesso (ADMIN o CLIENTE)
 *
 * Ritorna:
 *    Un nuovo utente o NULL in caso di errore
 */
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

/*
 * Funzione: distruggi_utente
 * --------------------------
 * Dealloca la memoria associata all'utente, inclusi eventuali dati interni.
 *
 * Implementazione:
 *    Libera la memoria associata alla struttura Data se presente, poi libera
 *    la memoria della struttura utente stessa.
 *
 * Parametri:
 *    utente: puntatore all'utente da distruggere
 */
void distruggi_utente(Utente utente){
    if(utente == NULL) return;
    distruggi_data(utente->data);
    free(utente);
}

/*
 * Funzione: imposta_nome
 * ----------------------
 * Imposta il nome dell'utente.
 *
 * Implementazione:
 *    Copia la nuova stringa nome nel campo nome dell'utente.
 *
 * Parametri:
 *    utente: puntatore all'utente
 *    nome: stringa contenente il nuovo nome
 */
void imposta_nome(Utente utente, char *nome) {
    if(utente == NULL) {
        return;
    }

    snprintf(utente->nome, DIMENSIONE_NOME, "%s", nome);
}

/*
 * Funzione: imposta_cognome
 * -------------------------
 * Imposta il cognome dell'utente.
 *
 * Implementazione:
 *    Copia la nuova stringa cognome nel campo cognome dell'utente.
 *
 * Parametri:
 *    utente: puntatore all'utente
 *    cognome: stringa contenente il nuovo cognome
 */
void imposta_cognome(Utente utente, char *cognome) {
    if(utente == NULL) {
        return;
    }

    snprintf(utente->cognome, DIMENSIONE_COGNOME, "%s", cognome);
}

/*
 * Funzione: imposta_email
 * -----------------------
 * Imposta l'email dell'utente.
 *
 * Implementazione:
 *    Copia la nuova stringa email nel campo email dell'utente.
 *
 * Parametri:
 *    utente: puntatore all'utente
 *    email: stringa contenente la nuova email
 */
void imposta_email(Utente utente, char *email) {
    if(utente == NULL) {
        return;
    }

    snprintf(utente->email, DIMENSIONE_EMAIL, "%s", email);
}

/*
 * Funzione: imposta_password
 * --------------------------
 * Imposta la password dell'utente.
 *
 * Implementazione:
 *    Copia il nuovo array password nel campo password dell'utente.
 *
 * Parametri:
 *    utente: puntatore all'utente
 *    password: array di uint8_t contenente la nuova password
 */
void imposta_password(Utente utente, uint8_t *password) {
    if(utente == NULL) {
        return;
    }

    memcpy(utente->password, password, DIMENSIONE_PASSWORD);
}

/*
 * Funzione: imposta_permesso
 * --------------------------
 * Imposta il livello di permesso dell'utente.
 *
 * Implementazione:
 *    Aggiorna il campo permesso con il valore fornito.
 *
 * Parametri:
 *    utente: puntatore all'utente
 *    permesso: byte che rappresenta il permesso (ADMIN o CLIENTE)
 */
void imposta_permesso(Utente utente, Byte permesso) {
    if(utente == NULL) {
        return;
    }

    utente->permesso = permesso;
}

/*
 * Funzione: imposta_data
 * ----------------------
 * Imposta la data associata all'utente (es. data di registrazione).
 *
 * Implementazione:
 *    Se il permesso è CLIENTE, distrugge la data esistente se presente
 *    e assegna la nuova struttura Data.
 *    Se l'utente è ADMIN, la funzione non modifica nulla.
 *
 * Parametri:
 *    utente: puntatore all'utente
 *    data: puntatore a una struttura Data
 */
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

/*
 * Funzione: ottieni_nome
 * ----------------------
 * Restituisce il nome dell'utente.
 *
 * Implementazione:
 *    Ritorna un puntatore al campo nome della struttura utente.
 *
 * Parametri:
 *    utente: puntatore all'utente
 *
 * Ritorna:
 *    nome dell'utente o NULL se utente è NULL
 */
char *ottieni_nome(Utente utente){
    if (utente == NULL) {
        return NULL;
    }
    return utente->nome;
}

/*
 * Funzione: ottieni_cognome
 * -------------------------
 * Restituisce il cognome dell'utente.
 *
 * Implementazione:
 *    Ritorna un puntatore al campo cognome della struttura utente.
 *
 * Parametri:
 *    utente: puntatore all'utente
 *
 * Ritorna:
 *    cognome dell'utente o NULL se utente è NULL
 */
char *ottieni_cognome(Utente utente){
    if (utente == NULL) {
        return NULL;
    }
    return utente->cognome;
}

/*
 * Funzione: ottieni_email
 * -----------------------
 * Restituisce l'email dell'utente.
 *
 * Implementazione:
 *    Ritorna un puntatore al campo email della struttura utente.
 *
 * Parametri:
 *    utente: puntatore all'utente
 *
 * Ritorna:
 *    email dell'utente o NULL se utente è NULL
 */
char *ottieni_email(Utente utente){
    if (utente == NULL) {
        return NULL;
    }
    return utente->email;
}

/*
 * Funzione: ottieni_password
 * --------------------------
 * Restituisce la password dell'utente.
 *
 * Implementazione:
 *    Ritorna un puntatore all'array password della struttura utente.
 *
 * Parametri:
 *    utente: puntatore all'utente
 *
 * Ritorna:
 *    password dell'utente o NULL se utente è NULL
 */
uint8_t *ottieni_password(Utente utente){
    if (utente == NULL) {
        return NULL;
    }
    return utente->password;
}

/*
 * Funzione: ottieni_frequenza_cliente
 * -----------------------------------
 * Restituisce un intero che indica la frequenza (es. numero di prenotazioni)
 * associate all'utente cliente.
 *
 * Implementazione:
 *    Chiama la funzione ottieni_frequenza_lista sulla struttura data dell'utente.
 *
 * Parametri:
 *    utente: puntatore all'utente
 *
 * Ritorna:
 *    frequenza cliente (intero)
 */
int ottieni_frequenza_cliente(Utente utente) {
    return ottieni_frequenza_lista(utente->data);
}

/*
 * Funzione: ottieni_permesso
 * --------------------------
 * Restituisce il livello di permesso dell'utente.
 *
 * Implementazione:
 *    Ritorna il valore del campo permesso, o ERRORE_PERMESSO se utente è NULL.
 *
 * Parametri:
 *    utente: puntatore all'utente
 *
 * Ritorna:
 *    permesso utente o ERRORE_PERMESSO
 */
Byte ottieni_permesso(Utente utente){
    if (utente == NULL) {
        return ERRORE_PERMESSO;
    }

    return utente->permesso;
}

/*
 * Funzione: ottieni_storico_utente
 * --------------------------------
 * Restituisce la lista delle prenotazioni associate all'utente.
 *
 * Implementazione:
 *    Ritorna la lista storica delle prenotazioni dalla struttura data.
 *
 * Parametri:
 *    utente: puntatore all'utente
 *
 * Ritorna:
 *    lista delle prenotazioni o NULL
 */
ListaPre ottieni_storico_utente(Utente utente) {
    if (utente == NULL) {
        return NULL;
    }

    return ottieni_storico_lista(utente->data);
}

/*
 * Funzione: aggiungi_a_storico_utente
 * -----------------------------------
 * Aggiunge una prenotazione allo storico dell'utente.
 *
 * Implementazione:
 *    Invoca la funzione aggiungi_a_storico_lista sulla struttura data dell'utente,
 *    ritorna 1 se aggiunta con successo, 0 altrimenti.
 *
 * Parametri:
 *    utente: puntatore all'utente
 *    prenotazione: prenotazione da aggiungere
 *
 * Ritorna:
 *    1 se successo, 0 altrimenti
 */
Byte aggiungi_a_storico_utente(Utente utente, Prenotazione prenotazione) {
    if (utente == NULL) {
        return 0;
    }

    return aggiungi_a_storico_lista(utente->data, prenotazione) != NULL;
}

/*
 * Funzione: rimuovi_da_storico_utente
 * -----------------------------------
 * Rimuove una prenotazione dallo storico dell'utente.
 *
 * Implementazione:
 *    Invoca la funzione rimuovi_da_storico_lista sulla struttura data dell'utente,
 *    ritorna 1 se rimozione con successo, 0 altrimenti.
 *
 * Parametri:
 *    utente: puntatore all'utente
 *    prenotazione: prenotazione da rimuovere
 *
 * Ritorna:
 *    1 se successo, 0 altrimenti
 */
Byte rimuovi_da_storico_utente(Utente utente, Prenotazione prenotazione) {
    if (utente == NULL) {
        return 0;
    }

    return rimuovi_da_storico_lista(utente->data, prenotazione) != NULL;
}