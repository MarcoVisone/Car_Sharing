/*
 * Autore: Antonio Sicignano
 * Data: 09/05/2025
 */

#ifndef UTENTE_H
#define UTENTE_H
#include <stdint.h>
#include "modelli/byte.h"
#include "modelli/data.h"

#define DIMENSIONE_NOME (64 + 2)
#define DIMENSIONE_COGNOME (64 + 2)
#define DIMENSIONE_EMAIL (319 + 2)
#define DIMENSIONE_PASSWORD 16

#define ADMIN 0
#define CLIENTE 1
#define ERRORE_PERMESSO -1

typedef struct utente *Utente;

/*
 * Funzione: crea_utente
 * ---------------------
 * Crea e inizializza un nuovo utente con le informazioni fornite.
 *
 * Parametri:
 *    email: stringa costante contenente l'email dell'utente.
 *    password: puntatore ai dati della password (array di byte).
 *    nome: stringa costante contenente il nome dell'utente.
 *    cognome: stringa costante contenente il cognome dell'utente.
 *    permesso: valore di tipo `Byte` che rappresenta il livello di permesso dell'utente.
 *
 * Pre-condizioni:
 *    email: non deve essere NULL
 *    nome: non deve essere NULL
 *    cognome: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce un nuovo utente, in caso di errore restituisce NULL
 *
 * Ritorna:
 *    un puntatore a utente o NULL
 *
 * Side-effect:
 *    - Alloca memoria dinamica per la struttura `utente` e, opzionalmente, per la struttura dati associata.
 *    La memoria deve essere liberata dal chiamante.
 */
Utente crea_utente(const char *email, const uint8_t *password, const char *nome, const char *cognome, Byte permesso);

/*
 * Funzione: distruggi_utente
 * --------------------------
 * Dealloca la memoria associata a un oggetto `Utente`, liberando anche le
 * eventuali risorse interne collegate.
 *
 * Parametri:
 *    utente: puntatore all'oggetto `Utente` da deallocare.
 *
 * Pre-condizioni:
 *    utente: non deve essere NULL
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    - Tutta la memoria associata all'utente e alle sue risorse interne è liberata.
 */
void distruggi_utente(Utente utente);

/*
 * Funzione: imposta_nome
 * ---------------------
 * Imposta il nome di un utente con la stringa fornita.
 *
 * Parametri:
 *    utente: puntatore all'oggetto `Utente` da modificare.
 *    nome: stringa costante contenente il nuovo nome da assegnare.
 *
 * Pre-condizioni:
 *    utente: non deve essere NULL
 *    nome: non deve essere NULL
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    - Il campo `nome` dell'utente viene aggiornato con il nuovo valore.
 */
void imposta_nome(Utente utente, const char *nome);

/*
 * Funzione: imposta_cognome
 * -------------------------
 * Imposta il cognome di un utente con la stringa fornita.
 *
 * Parametri:
 *    utente: puntatore all'oggetto `Utente` da modificare.
 *    cognome: stringa costante contenente il nuovo cognome da assegnare.
 *
 * Pre-condizioni:
 *    utente: non deve essere NULL
 *    cognome: non deve essere NULL
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    - Il campo `cognome` dell'utente viene aggiornato con il nuovo valore.
 */
void imposta_cognome(Utente utente, const char *cognome);

/*
 * Funzione: imposta_email
 * ----------------------
 * Imposta l'email di un utente con la stringa fornita.
 *
 * Parametri:
 *    utente: puntatore all'oggetto `Utente` da modificare.
 *    email: stringa costante contenente la nuova email da assegnare.
 *
 * Pre-condizioni:
 *    utente: non deve essere NULL
 *    email: non deve essere NULL
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    - Il campo `email` dell'utente viene aggiornato con il nuovo valore.
 */
void imposta_email(Utente utente, const char *email);

/*
 * Funzione: imposta_password
 * -------------------------
 * Imposta la password di un utente copiando i dati forniti.
 *
 * Parametri:
 *    utente: puntatore all'oggetto `Utente` da modificare.
 *    password: puntatore ai dati della nuova password (array di byte).
 *
 * Pre-condizioni:
 *    utente: non deve essere NULL
 *    password: deve puntare a un array di grandezza DIMENSIONE_PASSWORD
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    - Il campo `password` dell'utente viene aggiornato con i nuovi dati.
 */
void imposta_password(Utente utente, const uint8_t *password);

/*
 * Funzione: imposta_permesso
 * --------------------------
 * Imposta il livello di permesso di un utente.
 *
 * Parametri:
 *    utente: puntatore all'oggetto `Utente` da modificare.
 *    permesso: valore di tipo Byte che indica il nuovo livello di permesso.
 *
 * Pre-condizioni:
 *    utente: non deve essere NULL
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    - Il campo `permesso` dell'utente viene aggiornato con il nuovo valore.
 */
void imposta_permesso(Utente utente, Byte permesso);

/*
 * Funzione: imposta_data
 * ----------------------
 * Imposta la data associata a un utente, a meno che l'utente sia un admin.
 *
 * Parametri:
 *    utente: puntatore all'oggetto `Utente` da modificare.
 *    data: oggetto `Data` da assegnare all'utente.
 *
 * Pre-condizioni:
 *    utente: non deve essere NULL.
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    - Il campo `data` dell'utente è aggiornato con il nuovo valore, tranne se è admin.
 */
void imposta_data(Utente utente, Data data);

/*
 * Funzione: ottieni_cognome
 * -------------------------
 * Restituisce una copia dinamica della stringa cognome di un utente.
 *
 * Parametri:
 *    utente: puntatore costante all'oggetto `Utente`.
 *
 * Pre-condizioni:
 *    utente: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce il cognome dell'utente oppure NULL in caso di errore
 *
 * Ritorna:
 *    una stringa costante o NULL
 *
 * Side-effect:
 *    - Alloca memoria dinamica che deve essere liberata dal chiamante.
 */
const char *ottieni_cognome(const Utente utente);

/*
 * Funzione: ottieni_nome
 * ----------------------
 * Restituisce una copia dinamica della stringa nome di un utente.
 *
 * Parametri:
 *    utente: puntatore costante all'oggetto `Utente`.
 *
 * Pre-condizioni:
 *    utente: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce il nome dell'utente oppure NULL in caso di errore
 *
 * Ritorna:
 *    una stringa costante o NULL
 *
 * Side-effect:
 *    - Alloca memoria dinamica che deve essere liberata dal chiamante.
 */
const char *ottieni_nome(const Utente utente);

/*
 * Funzione: ottieni_email
 * -----------------------
 * Restituisce una copia dinamica della stringa email di un utente.
 *
 * Parametri:
 *    utente: puntatore costante all'oggetto `Utente`.
 *
 * Pre-condizioni:
 *    utente: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce l'email dell'utente oppure NULL in caso di errore
 *
 * Ritorna:
 *    una stringa costante o NULL
 *
 * Side-effect:
 *    - Alloca memoria dinamica che deve essere liberata dal chiamante.
 */
const char *ottieni_email(const Utente utente);

/*
 * Funzione: ottieni_password
 * --------------------------
 * Restituisce una copia dinamica della password di un utente.
 *
 * Parametri:
 *    utente: puntatore costante all'oggetto `Utente`.
 *
 * Pre-condizioni:
 *    utente: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce la password dell'utente oppure NULL in caso di errore
 *
 * Ritorna:
 *    un puntatore o NULL
 *
 * Side-effect:
 *    - Alloca memoria dinamica che deve essere liberata dal chiamante.
 */
const uint8_t *ottieni_password(const Utente utente);

/*
 * Funzione: ottieni_permesso
 * --------------------------
 * Restituisce il livello di permesso di un utente.
 *
 * Parametri:
 *    utente: puntatore all'oggetto `Utente`.
 *
 * Pre-condizioni:
 *    utente: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce la costante ERRORE_PERMESSO se c'è un errore, altrimenti il permesso dell'utente
 *
 * Ritorna:
 *     un valore di tipo Byte
 *
 * Side-effect:
 *    - Nessuno.
 */
Byte ottieni_permesso(Utente utente);

/*
 * Funzione: ottieni_storico_utente
 * --------------------------------
 * Restituisce la lista storico delle prenotazioni di un utente.
 *
 * Parametri:
 *    utente: puntatore all'oggetto `Utente`.
 *
 * Pre-condizioni:
 *    utente: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce la lista delle prenotazioni, oppure NULL se `utente` è NULL.
 *
 * Ritorna:
 *    una lista o NULL
 *
 * Side-effect:
 *    - Nessuno.
 */
ListaPre ottieni_storico_utente(Utente utente);

/*
 * Funzione: aggiungi_a_storico_utente
 * -----------------------------------
 * Aggiunge una prenotazione allo storico di un utente.
 *
 * Parametri:
 *    utente: puntatore all'oggetto `Utente`.
 *    prenotazione: prenotazione da aggiungere allo storico.
 *
 * Pre-condizioni:
 *    utente: non deve essere NULL
 *    prenotazione: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce 1 in caso di successo, 0 in caso di fallimento o utente NULL.
 *
 * Ritorna:
 *    un valore di tipo Byte(0 o 1)
 *
 * Side-effect:
 *    - Lo storico dati dell'utente è aggiornato con la nuova prenotazione.
 */
Byte aggiungi_a_storico_utente(Utente utente, Prenotazione prenotazione);

/*
 * Funzione: rimuovi_da_storico_utente
 * -----------------------------------
 * Rimuove una prenotazione dallo storico di un utente.
 * Se lo storico risulta vuoto dopo la rimozione, imposta lo storico a NULL.
 *
* Parametri:
 *    utente: puntatore all'oggetto `Utente`.
 *    prenotazione: prenotazione da rimuovere dallo storico.
 *
 * Pre-condizioni:
 *    utente: non deve essere NULL
 *    prenotazione: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce 1 se la rimozione ha avuto successo, altrimenti 0
 *
 * Ritorna:
 *    un valore di tipo Byte(0 o 1)
 *
 * Side-effect:
 *    - Lo storico dati dell'utente è aggiornato di conseguenza.
 */
Byte rimuovi_da_storico_utente(Utente utente, Prenotazione prenotazione);

/*
 * Funzione: ottieni_numero_prenotazioni_utente
 * --------------------------------------------
 * Restituisce il numero di prenotazioni nello storico di un utente.
 *
 * Parametri:
 *    u: puntatore all'oggetto `Utente`.
 *
 * Pre-condizioni:
 *    u: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce il numero di prenotazioni oppure 0 se c'è un errore
 *
 * Ritorna:
 *    un numero intero positivo
 *
 * Side-effect:
 *    - Nessuno.
 */
unsigned int ottieni_numero_prenotazioni_utente(const Utente u);

/*
 * Funzione: crea_nuova_data
 * --------------------------------------------
 * Distrugge la vecchia data e una nuova data dentro Utente
 *
 * Parametri:
 *    u: puntatore all'oggetto `Utente`.
 *
 * Pre-condizioni:
 *    u: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce 1 se la creazione è andata a buon fine, altrimenti 0
 *
 * Ritorna:
 *    un valore di tipo Byte(0 o 1)
 *
 * Side-effect:
 *    - Viene deallocata e allocata memoria dentro al campo data.
 */
Byte crea_nuova_data(Utente u);

/*
 * Funzione: utente_in_stringa
 * ---------------------------
 * Restituisce una stringa descrittiva dell'utente.
 *
 * Parametri:
 * utente: puntatore all'oggetto `Utente`.
 *
 * Pre-condizioni:
 * - `utente` può essere NULL.
 *
 * Post-condizioni:
 * - Viene restituita una stringa allocata dinamicamente contenente la descrizione.
 *
 * Ritorna:
 * - Puntatore a stringa allocata, oppure NULL se `utente` è NULL.
 *
 * Side-effect:
 * - Alloca memoria dinamica che deve essere liberata dal chiamante.
 */
char *utente_in_stringa(const Utente utente);

#endif // UTENTE_H
