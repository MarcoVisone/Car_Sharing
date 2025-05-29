/*
 * Autore: Russo Nello Manuel
 * Data: 09/05/2025
 */

#ifndef VEICOLO_H
#define VEICOLO_H
#include "modelli/byte.h"

#define NUM_CARATTERI_TARGA 7 + 2
#define MAX_LUNGHEZZA_MODELLO 50 + 2
#define MAX_LUNGHEZZA_POSIZIONE 200 + 2
#define MAX_LUNGHEZZA_TARIFFA 9 + 2
#define MAX_LUNGHEZZA_TIPO 30 + 2

typedef struct intervallo *Intervallo;
typedef struct prenotazione *Prenotazione;
typedef struct albero *Prenotazioni;
typedef struct veicolo *Veicolo;

/*
 * Funzione: crea_veicolo
 * ----------------------
 * Crea un nuovo veicolo con targa, modello, posizione,
 * tariffa e prenotazioni associate
 *
 * Parametri:
 *    tipo: stringa costante che rappresenta il tipo del veicolo
 *    targa: stringa costante che rappresenta la targa del veicolo
 *    modello: stringa costante che rappresenta il modello del veicolo
 *    posizione: stringa costante che rappresenta la posizione del veicolo
 *    tariffa: numero che rappresenta la tariffa al minuto in euro di un veicolo
 *    prenotazioni: puntatore alle prenotazioni associate ad un veicolo
 *
 * Pre-condizioni:
 *    targa: non deve essere NULL e deve essere di 7 caratteri
 *    modello: non deve essere NULL
 *    posizione: non deve essere NULL
 *    tariffa: deve essere maggiore di 0
 *
 * Post-condizione:
 *    restituisce un nuovo oggetto Veicolo se l'allocazione è andata a buon fine,
 *    altrimenti restituisce NULL
 *
 * Ritorna:
 *    Un oggetto di tipo Veicolo oppure NULL
 *
 * Side-effect:
 *    alloca memoria dinamicamente per il veicolo
 */
Veicolo crea_veicolo(const char *tipo, const char *targa, const char *modello, const char *posizione, double tariffa, Prenotazioni prenotazioni);

/*
 * Funzione: distruggi_veicolo
 * ---------------------------
 * elimina un veicolo
 *
 * Parametri:
 *	   v: puntatore ad un veicolo
 *
 * Pre-condizioni:
 *	   v: non deve essere NULL
 *
 * Post-condizione:
 *	   non restituisce niente
 *
 * Side-effect:
 *	   libera la memoria occupata dalla struttura Veicolo e dalle sue prenotazioni
 */
void distruggi_veicolo(Veicolo v);

/*
 * Funzione: ottieni_targa
 * -----------------------
 *
 * restituisce la targa del veicolo puntato da v
 *
 * Implementazione:
 *    Se il puntatore al veicolo è NULL, restituisce NULL, altrimenti
 *    restituisce la stringa contenuta nel campo targa del veicolo
 *
 * Parametri:
 *    v: puntatore ad un veicolo
 *
 * Pre-condizioni:
 *	   v: non deve essere NULL
 *
 * Post-condizione:
 *    restituisce una stringa costante contenente la targa del veicolo
 *
 * Ritorna:
 *    una stringa costante oppure NULL
 */
const char *ottieni_targa(const Veicolo v);

/*
 * Funzione: imposta_targa
 * -----------------------
 *
 * Imposta la targa nel veicolo puntato da v
 *
 * Parametri:
 *	   v: puntatore ad un veicolo
 *	   targa: stringa costante contenente la targa da impostare
 *
 * Pre-condizioni:
 *	   v: non deve essere NULL
 *	   targa: non deve essere NULL e deve essere di 7 caratteri
 *
 * Post-condizione:
 *	   non restituisce niente
 *
 * Side-effect:
 *    aggiorna il campo targa del veicolo v con il valore fornito
 */
void imposta_targa(Veicolo v, const char *targa);

/*
 * Funzione: ottieni_modello
 * -------------------------
 *
 * Restituisce il modello del veicolo puntato da v
 *
 * Implementazione:
 *    Se il puntatore al veicolo è NULL, restituisce NULL, altrimenti
 *    restituisce la stringa contenuta nel campo modello del veicolo
 *
 * Parametri:
 *	   v: puntatore ad un veicolo
 *
 * Pre-condizioni:
 *    v: non deve essere NULL
 *
 * Post-condizione:
 *    restituisce il modello del veicolo puntato da v
 *
 * Ritorna:
 *    una stringa costante contenente il modello del veicolo
 */
const char* ottieni_modello(const Veicolo v);

/*
 * Funzione: imposta_modello
 * -------------------------
 *
 * imposta il modello del veicolo puntato da v
 *
 * Implementazione:
 *    se le pre-condizioni sono rispettate copia la stringa targa nel campo targa della struttura veicolo
 *    con snprintf per evitare overflow di buffer, altrimenti non fa nulla
 *
 * Parametri:
 *    v: puntatore ad un veicolo
 *	  modello: stringa costante contenente il modello da impostare
 *
 * Pre-condizioni:
 *	  v: non deve essere NULL
 *	  modello: non deve essere NULL e deve essere lungo al massimo 50 caratteri
 *
 * Post-condizione:
 *	  non restituisce niente
 *
 * Side-effect:
 * 	  aggiorna il campo modello del veicolo v con il valore fornito
 */
void imposta_modello(Veicolo v, const char *modello);

/*
 * Funzione: ottieni_posizione
 * ---------------------------
 *
 * restituisce la posizione del veicolo puntato da v.
 *
 * Implementazione:
 *    Se il puntatore al veicolo è NULL, restituisce NULL, altrimenti
 *    restituisce la stringa contenuta nel campo posizione del veicolo
 *
 * Parametri:
 *    v: puntatore ad un veicolo
 *
 * Pre-condizioni:
 *	  v: non deve essere NULL
 *
 * Post-condizione:
 *	  restituisce la posizione del veicolo
 *
 * Ritorna:
 *    una stringa costante
 */
const char* ottieni_posizione(const Veicolo v);

/*
 * Funzione: imposta_posizione
 * -----------------------------
 *
 * imposta la posizione del veicolo puntato da v
 *
 * Implementazione:
 *    se non ci sono errori copia la stringa posizione nel campo posizione della struttura veicolo
 *    con snprintf per evitare overflow di buffer, altrimenti non fa nulla
 *
 * Parametri:
 *    v: puntatore ad un veicolo
 *	  posizione: stringa costante contenente la posizione da impostare
 *
 * Pre-condizioni:
 *	  v: non deve essere NULL
 *	  posizione: non deve essere NULL e deve essere lunga al massimo 200 caratteri
 *
 * Post-condizione:
 *	  non restituisce niente
 *
 * Side-effect:
 * 	  aggiorna il campo posizione del veicolo con il valore fornito
 */
void imposta_posizione(Veicolo v, const char *posizione);

/*
 * Funzione: ottieni_tariffa
 * -------------------------
 *
 * restituisce la tariffa al minuto del veicolo puntato da v
 *
 * Implementazione:
 *    Se il puntatore al veicolo è NULL, restituisce -1, altrimenti
 *    restituisce il numero contenuto nel campo tariffa del veicolo
 *
 * Parametri:
 *    v: puntatore ad un veicolo
 *
 * Pre-condizioni:
 *    v: non deve essere NULL
 *
 * Post-condizione:
 *    restituisce un double che è la tariffa al minuto del veicolo puntato da vù
 *
 * Ritorna:
 *    un double
 */
double ottieni_tariffa(const Veicolo v);

/*
 * Funzione: imposta_tariffa
 * -------------------------
 *
 *  imposta la tariffa al minuto del veicolo puntato da v
 *
 * Implementazione:
 *    se le pre-condizioni sono rispettate copia il double tariffa nel campo tariffa della struttura veicolo,
 *    altrimenti non fa nulla
 *
 * Parametri:
 *    v: puntatore ad un veicolo
 *    tariffa: double che contiene la tariffa al minuto di un veicolo
 *
 * Pre-condizioni:
 *    v: non deve essere NULL
 *    tariffa: deve essere maggiore di 0
 *
 * Post-condizione:
 *    non restituisce niente
 *
 * Side-effect:
 *    aggiorna il campo tariffa del veicolo con il valore fornito
 */
void imposta_tariffa(const Veicolo v, double tariffa);

/*
 * Funzione: ottieni_prenotazioni
 * ------------------------------
 *
 * restituisce l'albero delle prenotazioni associate al veicolo puntato da v
 *
 * Implementazione:
 *    Se il puntatore al veicolo è NULL, restituisce NULL, altrimenti
 *    restituisce l'albero contenente le prenotazioni del veicolo
 *
 * Parametri:
 *    v: puntatore ad un veicolo
 *
 * Pre-condizioni:
 *    v: non deve essere NULL
 *
 * Post-condizione:
 *    restituisce le prenotazioni del veicolo
 *
 * Ritorna:
 *    un albero AVL
 */
Prenotazioni ottieni_prenotazioni(const Veicolo v);

/*
 * Funzione: imposta_prenotazioni
 * ------------------------------
 *
 * imposta l'albero delle prenotazioni nel veicolo puntato da v
 *
 * Implementazione:
 *    se il puntatore al veicolo non è NULL, assegna il puntatore prenotazioni
 *    al campo prenotazioni, altrimenti non fa nulla.
 *    Se il puntatore a prenotazioni è NULL allora le prenotazioni associate in precedenza al
 *    veicolo vengono cancellate
 *
 * Parametri:
 *    v: puntatore ad un veicolo
 *    prenotazioni: albero contenente le prenotazioni da assegnare al veicolo
 *
 * Pre-condizioni:
 *    v: non deve essere NULL
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    aggiorna il campo prenotazioni del veicolo con il puntatore fornito
 */
void imposta_prenotazioni(const Veicolo v, Prenotazioni prenotazioni);

/*
 * Funzione: ottieni_tipo_veicolo
 * ------------------------------
 *
 * Restituisce il tipo del veicolo puntato da v
 *
 * Implementazione:
 *    Se il puntatore al veicolo è NULL, restituisce NULL, altrimenti
 *    restituisce la stringa contenuta nel campo tipo_veicolo del veicolo
 *
 * Parametri:
 *    v: puntatore ad un veicolo
 *
 * Pre-condizioni:
 *    v: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce il tipo del veicolo
 *
 * Ritorna:
 *     una stringa costante
 */
const char* ottieni_tipo_veicolo(const Veicolo v);

/*
 * Funzione: imposta_tipo_veicolo
 * ------------------------------
 *
 * Imposta il tipo del veicolo puntato da v
 *
 * Implementazione:
 *    se le pre-condizioni sono rispettate copia la stringa tipo nel campo tipo della struttura veicolo
 *    con snprintf per evitare overflow di buffer, altrimenti non fa nulla
 *
 * Parametri:
 *    v: puntatore ad un veicolo
 *    tipo: stringa costante che contiene il tipo di un veicolo
 *
 * Pre-condizioni:
 *    v: non deve essere NULL
 *    tipo: non deve essere NULL e deve essere lungo al massimo 30 caratteri
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    modifica il campo tipo_veicolo nella struttura veicolo
 */
void imposta_tipo_veicolo(Veicolo v, const char *tipo);

/*
 * Funzione: confronta_tipo
 * --------------------------
 *
 * confronta una stringa "tipo" con il tipo del veicolo puntato da v
 *
 * Implementazione:
 *    se v e tipo non sono NULL e la stringa tipo è uguale al tipo del veicolo puntato da v restituisce 1,
 *    altrimenti 0. Se v e tipo sono NULL restituisce -1
 *
 * Parametri:
 *    v: puntatore ad un veicolo
 *    tipo: stringa che rappresenta il tipo di un veicolo
 *
 * Pre-condizioni:
 *    v: non deve essere NULL
 *    tipo: non deve essere NULL
 *
 * Post-condizione:
 *    restituisce 1 se il tipo del veicolo è uguale a "tipo", altrimenti 0
 *
 * Ritorna:
 *    un tipo Byte(1 oppure 0)
 */
Byte confronta_tipo(const Veicolo v, const char *tipo);

/*
 * Funzione: aggiungi_prenotazione_veicolo
 * ---------------------------------------
 *
 * aggiunge una prenotazione al veicolo puntato da v
 *
 * Implementazione:
 *    Se il puntatore al veicolo o alla prenotazione è NULL, la funzione restituisce 0.
 *    Altrimenti, chiama la funzione aggiungi_prenotazione, che inserisce la prenotazione
 *    nell'albero delle prenotazioni del veicolo. Se l'inserimento ha successo, restituisce 1,
 *    altrimenti restituisce 0.
 *
 * Parametri:
 *    v: puntatore ad un veicolo
 *    prenotazione: puntatore alla struttura prenotazione
 *
 * Pre-condizioni:
 *    v: non deve essere NULL
 *    prenotazione: non deve essere NULL
 *
 * Post-condizione:
 *    restituisce 1 se la prenotazione è stata aggiunta, altrimenti 0
 *
 * Ritorna:
 *    un valore di tipo Byte(1 oppure 0)
 */
Byte aggiungi_prenotazione_veicolo(const Veicolo v, const Prenotazione prenotazione);

/*
 * Funzione: rimuovi_prenotazione_veicolo
 * --------------------------------------
 *
 * rimuove una prenotazione dato il suo intervallo temporale dal veicolo puntato da v
 *
 * Implementazione:
 *    se il puntatore al veicolo o alla prenotazione è NULL, la funzione restituisce 0.
 *    Altrimenti, chiama la funzione cancella_prenotazione, che cancella la prenotazione
 *    dall'albero delle prenotazioni del veicolo. Se la rimozione ha successo, restituisce 1,
 *    altrimenti restituisce 0.
 *
 * Parametri:
 *    v: puntatore ad un veicolo
 *    intervallo: puntatore alla struttura intervallo
 *
 * Pre-condizioni:
 *    v: non deve essere NULL
 *    prenotazione: non deve essere NULL
 *
 * Post-condizione:
 *    restituisce 1 se la prenotazione è stata rimossa, altrimenti 0
 *
 * Ritorna:
 *    un valore di tipo Byte(1 oppure 0)
 */
Byte rimuovi_prenotazione_veicolo(const Veicolo v, const Intervallo intervallo);

/*
 * Funzione: confronta_targhe
 * --------------------------
 *
 * confronta la targa fornita con quella del veicolo puntato da v
 *
 * Implementazione:
 *    se il puntatore al veicolo o la targa è NULL o la lunghezza della targa è diversa da 7 restituisce -1,
 *    altrimenti confronta la targa fornita con quella del veicolo usando strcmp.
 *    Se sono uguali restituisce 1, altrimenti restituisce 0.
 *
 * Parametri:
 *    v: puntatore ad un veicolo
 *    targa: stringa costante che contiene la targa di un veicolo
 *
 * Pre-condizioni:
 *    v: non deve essere NULL
 *    targa: non deve essere NULL e deve essere lunga 7 caratteri
 *
 * Post-condizione:
 *    restituisce 1 se le targhe sono uguali e 0 se sono diverse
 *
 * Ritorna:
 *    un valore di tipo Byte(1 oppure 0)
 */
Byte confronta_targhe(const Veicolo v, const char *targa);

/*
 * Funzione: veicolo_in_stringa
 * ----------------------------
 *
 * restituisce una stringa che contiene tutte le informazioni del veicolo puntato da v
 *
 * Implementazione:
 *    se il puntatore al veicolo è NULL, la funzione restituisce NULL.
 *    Altrimenti, calcola una dimensione sufficiente per contenere tutte le informazioni
 *    del veicolo (tipo, modello, posizione, targa e tariffa). Alloca dinamicamente
 *    una stringa di tale dimensione, quindi formatta i dati del veicolo in essa usando snprintf.
 *    La stringa risultante è restituita al chiamante, che dovrà occuparsi di liberarne la memoria.
 *
 * Parametri:
 *    v: puntatore ad un veicolo
 *
 * Pre-condizioni:
 *    v: non deve essere NULL
 *
 * Post-condizione:
 *    restituisce una stringa che contiene tutte le informazioni di un veicolo
 *
 * Ritorna:
 *    una stringa
 */
char* veicolo_in_stringa(const Veicolo v);

#endif //VEICOLO_H
