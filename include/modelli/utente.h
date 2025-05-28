/*
 * Autore: Antonio Sicignano
 * Data: 09/05/2025
 */

#ifndef UTENTE_H
#define UTENTE_H
#include <stdint.h>
#include "modelli/byte.h"

#define DIMENSIONE_NOME (64 + 2)
#define DIMENSIONE_COGNOME (64 + 2)
#define DIMENSIONE_EMAIL (319 + 2)
#define DIMENSIONE_PASSWORD 16

#define ADMIN 0
#define CLIENTE 1
#define ERRORE_PERMESSO -1

typedef struct prenotazione *Prenotazione;
typedef struct nodo *ListaPre;
typedef struct utente *Utente;

/*
 * Funzione: crea_utente
 * ---------------------
 *
 * Crea un nuovo utente con email, password, nome, cognome e permesso.
 *
 * Parametri:
 *    email: stringa che rappresenta l'email dell'utente
 *    password: array di uint8_t che rappresenta la password dell'utente
 *    nome: stringa che rappresenta il nome dell'utente
 *    cognome: stringa che rappresenta il cognome dell'utente
 *    permesso: byte che rappresenta il livello di permesso (ADMIN o CLIENTE)
 *
 * Pre-condizioni:
 *    email, password, nome, cognome non devono essere NULL o vuoti
 *    permesso deve essere un valore valido (ADMIN o CLIENTE)
 *
 * Post-condizione:
 *    viene restituito un nuovo utente allocato dinamicamente
 *    oppure NULL se l'allocazione fallisce
 *
 * Side-effect:
 *    allocazione dinamica di memoria
 */
Utente crea_utente(const char *email, const uint8_t *password, const char *nome, const char *cognome, Byte permesso);

/*
 * Funzione: distruggi_utente
 * --------------------------
 *
 * Dealloca la memoria associata all'utente, inclusi eventuali dati interni.
 *
 * Parametri:
 *    utente: puntatore all'utente da distruggere
 *
 * Pre-condizione:
 *    utente non deve essere NULL
 *
 * Post-condizione:
 *    la memoria occupata dall'utente è liberata
 *
 * Side-effect:
 *    deallocazione dinamica di memoria
 */
void distruggi_utente(Utente utente);

/*
 * Funzione: imposta_nome
 * ----------------------
 *
 * Imposta il nome dell'utente.
 *
 * Parametri:
 *    utente: puntatore all'utente
 *    nome: stringa contenente il nuovo nome
 *
 * Pre-condizione:
 *    utente e nome non devono essere NULL
 *
 * Post-condizione:
 *    il nome dell'utente è aggiornato
 *
 * Side-effect:
 *    modifica interna dell'utente
 */
void imposta_nome(Utente utente, const char *nome);

/*
 * Funzione: imposta_cognome
 * -------------------------
 *
 * Imposta il cognome dell'utente.
 *
 * Parametri:
 *    utente: puntatore all'utente
 *    cognome: stringa contenente il nuovo cognome
 *
 * Pre-condizione:
 *    utente e cognome non devono essere NULL
 *
 * Post-condizione:
 *    il cognome dell'utente è aggiornato
 *
 * Side-effect:
 *    modifica interna dell'utente
 */
void imposta_cognome(Utente utente, const char *cognome);

/*
 * Funzione: imposta_email
 * -----------------------
 *
 * Imposta l'email dell'utente.
 *
 * Parametri:
 *    utente: puntatore all'utente
 *    email: stringa contenente la nuova email
 *
 * Pre-condizione:
 *    utente e email non devono essere NULL
 *
 * Post-condizione:
 *    l'email dell'utente è aggiornata
 *
 * Side-effect:
 *    modifica interna dell'utente
 */
void imposta_email(Utente utente, const char *email);

/*
 * Funzione: imposta_password
 * --------------------------
 *
 * Imposta la password dell'utente.
 *
 * Parametri:
 *    utente: puntatore all'utente
 *    password: array di uint8_t contenente la nuova password
 *
 * Pre-condizione:
 *    utente e password non devono essere NULL
 *
 * Post-condizione:
 *    la password dell'utente è aggiornata
 *
 * Side-effect:
 *    modifica interna dell'utente
 */
void imposta_password(Utente utente, const uint8_t *password);

/*
 * Funzione: imposta_permesso
 * --------------------------
 *
 * Imposta il livello di permesso dell'utente.
 *
 * Parametri:
 *    utente: puntatore all'utente
 *    permesso: byte che rappresenta il permesso (ADMIN o CLIENTE)
 *
 * Pre-condizione:
 *    utente non deve essere NULL
 *    permesso deve essere un valore valido
 *
 * Post-condizione:
 *    il permesso dell'utente è aggiornato
 *
 * Side-effect:
 *    modifica interna dell'utente
 */
void imposta_permesso(Utente utente, Byte permesso);

/*
 * Funzione: ottieni_cognome
 * -------------------------
 *
 * Restituisce il cognome dell'utente.
 *
 * Parametri:
 *    utente: puntatore all'utente
 *
 * Pre-condizione:
 *    utente non deve essere NULL
 *
 * Post-condizione:
 *    ritorna una stringa contenente il cognome
 *
 * Side-effect:
 *    nessuno
 */
const char *ottieni_cognome(const Utente utente);

/*
 * Funzione: ottieni_nome
 * ----------------------
 *
 * Restituisce il nome dell'utente.
 *
 * Parametri:
 *    utente: puntatore all'utente
 *
 * Pre-condizione:
 *    utente non deve essere NULL
 *
 * Post-condizione:
 *    ritorna una stringa contenente il nome
 *
 * Side-effect:
 *    nessuno
 */
const char *ottieni_nome(const Utente utente);

/*
 * Funzione: ottieni_email
 * -----------------------
 *
 * Restituisce l'email dell'utente.
 *
 * Parametri:
 *    utente: puntatore all'utente
 *
 * Pre-condizione:
 *    utente non deve essere NULL
 *
 * Post-condizione:
 *    ritorna una stringa contenente l'email
 *
 * Side-effect:
 *    nessuno
 */
const char *ottieni_email(const Utente utente);

/*
 * Funzione: ottieni_password
 * --------------------------
 *
 * Restituisce la password dell'utente.
 *
 * Parametri:
 *    utente: puntatore all'utente
 *
 * Pre-condizione:
 *    utente non deve essere NULL
 *
 * Post-condizione:
 *    ritorna un array di uint8_t contenente la password
 *
 * Side-effect:
 *    nessuno
 */
const uint8_t *ottieni_password(const Utente utente);

/*
 * Funzione: ottieni_permesso
 * --------------------------
 *
 * Restituisce il livello di permesso dell'utente.
 *
 * Parametri:
 *    utente: puntatore all'utente
 *
 * Pre-condizione:
 *    utente non deve essere NULL
 *
 * Post-condizione:
 *    ritorna un Byte rappresentante il permesso
 *
 * Side-effect:
 *    nessuno
 */
Byte ottieni_permesso(Utente utente);

/*
 * Funzione: ottieni_storico_utente
 * --------------------------------
 *
 * Restituisce la lista delle prenotazioni associate all'utente.
 *
 * Parametri:
 *    utente: puntatore all'utente
 *
 * Pre-condizione:
 *    utente non deve essere NULL
 *
 * Post-condizione:
 *    ritorna una lista contenente le prenotazioni
 *
 * Side-effect:
 *    nessuno
 */
ListaPre ottieni_storico_utente(Utente utente);

/*
 * Funzione: aggiungi_a_storico_utente
 * -----------------------------------
 *
 * Aggiunge una prenotazione allo storico dell'utente.
 *
 * Parametri:
 *    utente: puntatore all'utente
 *    prenotazione: prenotazione da aggiungere
 *
 * Pre-condizione:
 *    utente e prenotazione non devono essere NULL
 *
 * Post-condizione:
 *    aggiunge la prenotazione alla lista
 *    ritorna Byte (1) se l'operazione ha avuto successo,
 *    0 in caso di fallimento
 *
 * Side-effect:
 *    modifica interna della lista storico
 */
Byte aggiungi_a_storico_utente(Utente utente, Prenotazione prenotazione);

/*
 * Funzione: rimuovi_da_storico_utente
 * -----------------------------------
 *
 * Rimuove una prenotazione dallo storico dell'utente.
 *
 * Parametri:
 *    utente: puntatore all'utente
 *    prenotazione: prenotazione da rimuovere
 *
 * Pre-condizione:
 *    utente e prenotazione non devono essere NULL
 *
 * Post-condizione:
 *    rimuove la prenotazione dalla lista
 *    ritorna Byte (1) se l'operazione ha avuto successo,
 *    0 in caso di fallimento
 *
 * Side-effect:
 *    modifica interna della lista storico
 */
Byte rimuovi_da_storico_utente(Utente utente, Prenotazione prenotazione);

unsigned int ottieni_numero_prenotazioni_utente(const Utente u);

char *utente_in_stringa(const Utente utente);

#endif // UTENTE_H
