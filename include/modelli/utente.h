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

typedef struct prenotazione *Prenotazione;
typedef struct nodo *ListaPre;
typedef struct utente *Utente;

/*
 * Funzione: crea_utente
 * ---------------------
 * Crea e inizializza un nuovo utente con le informazioni fornite.
 *
 * Parametri:
 * email: stringa contenente l'email dell'utente.
 * password: puntatore ai dati della password (array di byte).
 * nome: stringa contenente il nome dell'utente.
 * cognome: stringa contenente il cognome dell'utente.
 * permesso: valore di tipo `Byte` che rappresenta il livello di permesso dell'utente.
 *
 * Pre-condizioni:
 * - `email`, `nome` e `cognome` devono essere stringhe valide e non NULL.
 * - `password` può essere NULL.
 *
 * Post-condizioni:
 * - Viene creato un nuovo utente con i dati forniti.
 *
 * Ritorna:
 * - Un puntatore a una nuova struttura `Utente` allocata dinamicamente,
 *   o NULL in caso di errore di allocazione.
 *
 * Side-effect:
 * - Alloca memoria dinamica per la struttura `utente` e, opzionalmente, per la struttura dati associata.
 *   La memoria deve essere liberata dal chiamante.
 */
Utente crea_utente(const char *email, const uint8_t *password, const char *nome, const char *cognome, Byte permesso);

/*
 * Funzione: distruggi_utente
 * --------------------------
 * Dealloca la memoria associata a un oggetto `Utente`, liberando anche le
 * eventuali risorse interne collegate.
 *
 * Parametri:
 * utente: puntatore all'oggetto `Utente` da deallocare.
 *
 * Pre-condizioni:
 * - `utente` può essere NULL (in tal caso la funzione non fa nulla).
 *
 * Post-condizioni:
 * - Tutta la memoria associata all'utente e alle sue risorse interne è liberata.
 *
 * Ritorna:
 * - void
 *
 * Side-effect:
 * - Libera memoria dinamica associata all'utente e alle sue strutture interne.
 */
void distruggi_utente(Utente utente);

/*
 * Funzione: imposta_nome
 * ---------------------
 * Imposta il nome di un utente con la stringa fornita.
 *
 * Parametri:
 * utente: puntatore all'oggetto `Utente` da modificare.
 * nome: stringa contenente il nuovo nome da assegnare.
 *
 * Pre-condizioni:
 * - `utente` e `nome` devono essere non NULL.
 *
 * Post-condizioni:
 * - Il campo `nome` dell'utente viene aggiornato con il nuovo valore.
 *
 * Ritorna:
 * - void
 *
 * Side-effect:
 * - Modifica il campo `nome` della struttura `utente`.
 */
void imposta_nome(Utente utente, const char *nome);

/*
 * Funzione: imposta_cognome
 * -------------------------
 * Imposta il cognome di un utente con la stringa fornita.
 *
 * Parametri:
 * utente: puntatore all'oggetto `Utente` da modificare.
 * cognome: stringa contenente il nuovo cognome da assegnare.
 *
 * Pre-condizioni:
 * - `utente` deve essere non NULL.
 *
 * Post-condizioni:
 * - Il campo `cognome` dell'utente viene aggiornato con il nuovo valore.
 *
 * Ritorna:
 * - void
 *
 * Side-effect:
 * - Modifica il campo `cognome` della struttura `utente`.
 */
void imposta_cognome(Utente utente, const char *cognome);

/*
 * Funzione: imposta_email
 * ----------------------
 * Imposta l'email di un utente con la stringa fornita.
 *
 * Parametri:
 * utente: puntatore all'oggetto `Utente` da modificare.
 * email: stringa contenente la nuova email da assegnare.
 *
 * Pre-condizioni:
 * - `utente` deve essere non NULL.
 *
 * Post-condizioni:
 * - Il campo `email` dell'utente viene aggiornato con il nuovo valore.
 *
 * Ritorna:
 * - void
 *
 * Side-effect:
 * - Modifica il campo `email` della struttura `utente`.
 */
void imposta_email(Utente utente, const char *email);

/*
 * Funzione: imposta_password
 * -------------------------
 * Imposta la password di un utente copiando i dati forniti.
 *
 * Parametri:
 * utente: puntatore all'oggetto `Utente` da modificare.
 * password: puntatore ai dati della nuova password (array di byte).
 *
 * Pre-condizioni:
 * - `utente` deve essere non NULL.
 * - `password` deve puntare a un array di almeno `DIMENSIONE_PASSWORD` byte.
 *
 * Post-condizioni:
 * - Il campo `password` dell'utente viene aggiornato con i nuovi dati.
 *
 * Ritorna:
 * - void
 *
 * Side-effect:
 * - Modifica il campo `password` della struttura `utente`.
 */
void imposta_password(Utente utente, const uint8_t *password);

/*
 * Funzione: imposta_permesso
 * --------------------------
 * Imposta il livello di permesso di un utente.
 *
 * Parametri:
 * utente: puntatore all'oggetto `Utente` da modificare.
 * permesso: valore di tipo Byte che indica il nuovo livello di permesso.
 *
 * Pre-condizioni:
 * - `utente` deve essere non NULL.
 *
 * Post-condizioni:
 * - Il campo `permesso` dell'utente viene aggiornato con il nuovo valore.
 *
 * Ritorna:
 * - void
 *
 * Side-effect:
 * - Modifica il campo `permesso` della struttura `utente`.
 */
void imposta_permesso(Utente utente, Byte permesso);

/*
 * Funzione: imposta_data
 * ----------------------
 * Imposta la data associata a un utente, a meno che l'utente sia un admin.
 *
 * Parametri:
 * utente: puntatore all'oggetto `Utente` da modificare.
 * data: oggetto `Data` da assegnare all'utente.
 *
 * Pre-condizioni:
 * - `utente` deve essere non NULL.
 *
 * Post-condizioni:
 * - Il campo `data` dell'utente è aggiornato con il nuovo valore, tranne se è admin.
 *
 * Ritorna:
 * - void
 *
 * Side-effect:
 * - Modifica il campo `data` della struttura `utente`.
 */
void imposta_data(Utente utente, Data data);

/*
 * Funzione: ottieni_cognome
 * -------------------------
 * Restituisce una copia dinamica della stringa cognome di un utente.
 *
 * Parametri:
 * utente: puntatore costante all'oggetto `Utente`.
 *
 * Pre-condizioni:
 * - `utente` può essere NULL.
 *
 * Post-condizioni:
 * - Viene restituita una nuova stringa allocata contenente il cognome.
 *
 * Ritorna:
 * - Puntatore a stringa duplicata (malloc), oppure NULL se `utente` è NULL.
 *
 * Side-effect:
 * - Alloca memoria dinamica che deve essere liberata dal chiamante.
 */
const char *ottieni_cognome(const Utente utente);

/*
 * Funzione: ottieni_nome
 * ----------------------
 * Restituisce una copia dinamica della stringa nome di un utente.
 *
 * Parametri:
 * utente: puntatore costante all'oggetto `Utente`.
 *
 * Pre-condizioni:
 * - `utente` può essere NULL.
 *
 * Post-condizioni:
 * - Viene restituita una nuova stringa allocata contenente il nome.
 *
 * Ritorna:
 * - Puntatore a stringa duplicata (malloc), oppure NULL se `utente` è NULL.
 *
 * Side-effect:
 * - Alloca memoria dinamica che deve essere liberata dal chiamante.
 */
const char *ottieni_nome(const Utente utente);

/*
 * Funzione: ottieni_email
 * -----------------------
 * Restituisce una copia dinamica della stringa email di un utente.
 *
 * Parametri:
 * utente: puntatore costante all'oggetto `Utente`.
 *
 * Pre-condizioni:
 * - `utente` può essere NULL.
 *
 * Post-condizioni:
 * - Viene restituita una nuova stringa allocata contenente l'email.
 *
 * Ritorna:
 * - Puntatore a stringa duplicata (malloc), oppure NULL se `utente` è NULL.
 *
 * Side-effect:
 * - Alloca memoria dinamica che deve essere liberata dal chiamante.
 */
const char *ottieni_email(const Utente utente);

/*
 * Funzione: ottieni_password
 * --------------------------
 * Restituisce una copia dinamica della password di un utente.
 *
 * Parametri:
 * utente: puntatore costante all'oggetto `Utente`.
 *
 * Pre-condizioni:
 * - `utente` può essere NULL.
 *
 * Post-condizioni:
 * - Viene restituito un puntatore a un array di byte allocato dinamicamente.
 *
 * Ritorna:
 * - Puntatore a array di byte contenente la password, oppure NULL se `utente` è NULL.
 *
 * Side-effect:
 * - Alloca memoria dinamica che deve essere liberata dal chiamante.
 */
const uint8_t *ottieni_password(const Utente utente);

/*
 * Funzione: ottieni_permesso
 * --------------------------
 * Restituisce il livello di permesso di un utente.
 *
 * Parametri:
 * utente: puntatore all'oggetto `Utente`.
 *
 * Pre-condizioni:
 * - `utente` può essere NULL.
 *
 * Post-condizioni:
 * - Nessuna modifica allo stato dell'utente.
 *
 * Ritorna:
 * - Il valore di tipo Byte che rappresenta il permesso,
 *   oppure `ERRORE_PERMESSO` se `utente` è NULL.
 *
 * Side-effect:
 * - Nessuno.
 */
Byte ottieni_permesso(Utente utente);

/*
 * Funzione: ottieni_storico_utente
 * --------------------------------
 * Restituisce la lista storico delle prenotazioni di un utente.
 *
 * Parametri:
 * utente: puntatore all'oggetto `Utente`.
 *
 * Pre-condizioni:
 * - `utente` può essere NULL.
 *
 * Post-condizioni:
 * - Nessuna modifica allo stato dell'utente.
 *
 * Ritorna:
 * - La lista `ListaPre` delle prenotazioni, oppure NULL se `utente` è NULL.
 *
 * Side-effect:
 * - Nessuno.
 */
ListaPre ottieni_storico_utente(Utente utente);

/*
 * Funzione: aggiungi_a_storico_utente
 * -----------------------------------
 * Aggiunge una prenotazione allo storico di un utente.
 *
 * Parametri:
 * utente: puntatore all'oggetto `Utente`.
 * prenotazione: prenotazione da aggiungere allo storico.
 *
 * Pre-condizioni:
 * - `utente` può essere NULL.
 *
 * Post-condizioni:
 * - Lo storico dati dell'utente è aggiornato con la nuova prenotazione.
 *
 * Ritorna:
 * - 1 in caso di successo, 0 in caso di fallimento o utente NULL.
 *
 * Side-effect:
 * - Modifica lo storico dati dell'utente.
 */
Byte aggiungi_a_storico_utente(Utente utente, Prenotazione prenotazione);

/*
 * Funzione: rimuovi_da_storico_utente
 * -----------------------------------
 * Rimuove una prenotazione dallo storico di un utente.
 * Se lo storico risulta vuoto dopo la rimozione, imposta lo storico a NULL.
 *
 * Parametri:
 * utente: puntatore all'oggetto `Utente`.
 * prenotazione: prenotazione da rimuovere dallo storico.
 *
 * Pre-condizioni:
 * - `utente` può essere NULL.
 *
 * Post-condizioni:
 * - Lo storico dati dell'utente è aggiornato di conseguenza.
 *
 * Ritorna:
 * - 1 se lo storico è stato svuotato, 0 in caso di errore o fallimento.
 *
 * Side-effect:
 * - Modifica lo storico dati dell'utente.
 */
Byte rimuovi_da_storico_utente(Utente utente, Prenotazione prenotazione);

/*
 * Funzione: ottieni_numero_prenotazioni_utente
 * --------------------------------------------
 * Restituisce il numero di prenotazioni nello storico di un utente.
 *
 * Parametri:
 * u: puntatore all'oggetto `Utente`.
 *
 * Pre-condizioni:
 * - `u` può essere NULL.
 *
 * Post-condizioni:
 * - Nessuna modifica allo stato dell'utente.
 *
 * Ritorna:
 * - Numero di prenotazioni associate all'utente, 0 se `u` è NULL.
 *
 * Side-effect:
 * - Nessuno.
 */
unsigned int ottieni_numero_prenotazioni_utente(const Utente u);

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
