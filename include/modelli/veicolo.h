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
 *    tipo: stringa che rappresenta il tipo del veicolo
 *    targa: stringa che rappresenta la targa del veicolo
 *    modello: stringa che rappresenta il modello del veicolo
 *    posizione: stringa che rappresenta la posizione del veicolo
 *    tariffa: numero che rappresenta la tariffa al minuto in euro di un veicolo
 *    prenotazioni: puntatore alle prenotazioni associate ad un veicolo
 *
 * Pre-condizioni:
 *	 targa: non deve essere NULL e deve essere di 7 caratteri
 *   modello: non deve essere NULL
 *   posizione: non deve essere NULL
 *   tariffa: deve essere maggiore di 0
 *
 * Post-condizione:
 *   restituisce un nuovo oggetto Veicolo se l'allocazione è andata a buon fine,
 *   altrimenti restituisce NULL
 *
 * Side-effect:
 *    alloca memoria dinamicamente per il veicolo
 */
Veicolo crea_veicolo(char *tipo, char *targa, char *modello, char *posizione, double tariffa, Prenotazioni prenotazioni);

/*
 * Funzione: distruggi_veicolo
 * ---------------------------
 * elimina un veicolo
 *
 * Parametri:
 *	v: puntatore ad un veicolo
 *
 * Pre-condizioni:
 *	v: non deve essere NULL
 *
 * Post-condizione:
 *	non restituisce niente
 *
 * Side-effect:
 *	libera la memoria occupata dalla struttura Veicolo e dalle sue prenotazioni
 */
void distruggi_veicolo(Veicolo v);

/*
 * Funzione: ottieni_targa
 * -----------------------
 *
 * restituisce la targa del veicolo puntato da v
 *
 * Parametri:
 *	v: puntatore ad un veicolo
 *
 * Pre-condizioni:
 *	v: non deve essere NULL
 *
 * Post-condizione:
 *	restituisce una stringa contenente la targa del veicolo
 */
char *ottieni_targa(Veicolo v);

/*
 * Funzione: imposta_targa
 * -----------------------
 *
 * Imposta la targa nel veicolo puntato da v
 *
 * Parametri:
 *	v: puntatore ad un veicolo
 *	targa: stringa contenente la targa da impostare
 *
 * Pre-condizioni:
 *	v: non deve essere NULL
 *	targa: non deve essere NULL e deve essere di 7 caratteri
 *
 * Post-condizione:
 *	non restituisce niente
 *
 * Side-effect:
 * 	aggiorna il campo targa del veicolo v con il valore fornito
 */
void imposta_targa(Veicolo v, char *targa);

/*
 * Funzione: ottieni_modello
 * -------------------------
 *
 * Restituisce il modello del veicolo puntato da v
 *
 * Parametri:
 *	v: puntatore ad un veicolo
 *
 * Pre-condizioni:
 *	v: non deve essere NULL
 *
 * Post-condizione:
 *	restituisce una stringa contenente il modello del veicolo
 *
 * Ritorna:
 *	il modello del veicolo puntato da v
 */
char* ottieni_modello(Veicolo v);

/*
 * Funzione: imposta_modello
 * -------------------------
 *
 * imposta il modello del veicolo puntato da v
 *
 * Parametri:
 * 	v: puntatore ad un veicolo
 *	modello: stringa contenente il modello da impostare
 *
 * Pre-condizioni:
 *	v: non deve essere NULL
 *	modello: non deve essere NULL e deve essere lungo al massimo 50 caratteri
 *
 * Post-condizione:
 *	non restituisce niente
 *
 * Side-effect:
 * 	aggiorna il campo modello del veicolo v con il valore fornito
 */
void imposta_modello(Veicolo v, char *modello);

/*
 * Funzione: ottieni_posizione
 * ---------------------------
 *
 * restituisce la posizione del veicolo puntato da v.
 *
 * Parametri:
 *	v: puntatore ad un veicolo
 *
 * Pre-condizioni:
 *	v: non deve essere NULL
 *
 * Post-condizione:
 *	restituisce una stringa contenente la posizione del veicolo
 */
char* ottieni_posizione(Veicolo v);

/*
 * Funzione: imposta_posizione
 * -----------------------------
 *
 * imposta la posizione del veicolo puntato da v
 *
 * Parametri:
 * 	v: puntatore ad un veicolo
 *	posizione: stringa contenente la posizione da impostare
 *
 * Pre-condizioni:
 *	v: non deve essere NULL
 *	posizione: non deve essere NULL e deve essere lunga al massimo 200 caratteri
 *
 * Post-condizione:
 *	non restituisce niente
 *
 * Side-effect:
 * 	aggiorna il campo posizione del veicolo con il valore fornito
 */
void imposta_posizione(Veicolo v, char *posizione);

/*
 * Funzione: ottieni_tariffa
 * -------------------------
 *
 * restituisce la tariffa al minuto del veicolo puntato da v
 *
 * Parametri:
 *	v: puntatore ad un veicolo
 *
 * Pre-condizioni:
 *	v: non deve essere NULL
 *
 * Post-condizione:
 *	restituisce un double che è la tariffa al minuto del veicolo puntato da v
 */
double ottieni_tariffa(Veicolo v);

/*
 * Funzione: imposta_tariffa
 * -------------------------
 *
 *  imposta la tariffa al minuto del veicolo puntato da v
 *
 * Parametri:
 *	v: puntatore ad un veicolo
 *	tariffa: double che contiene la tariffa al minuto di un veicolo
 *
 * Pre-condizioni:
 *	v: non deve essere NULL
 *	tariffa: deve essere maggiore di 0
 *
 * Post-condizione:
 *	non restituisce niente
 *
 * Side-effect:
 * 	aggiorna il campo tariffa del veicolo con il valore fornito
 */
void imposta_tariffa(Veicolo v, double tariffa);

/*
 * Funzione: ottieni_prenotazioni
 * ------------------------------
 *
 * restituisce l'albero delle prenotazioni associate al veicolo puntato da v
 *
 * Parametri:
 *	v: puntatore ad un veicolo
 *
 * Pre-condizioni:
 *	v: non deve essere NULL
 *
 * Post-condizione:
 *	restituisce l'albero contenente le prenotazioni del veicolo
 */
Prenotazioni ottieni_prenotazioni(Veicolo v);

/*
 * Funzione: imposta_prenotazioni
 * ------------------------------
 *
 * imposta l'albero delle prenotazioni nel veicolo puntato da v
 *
 * Parametri:
 *	v: puntatore ad un veicolo
 *	prenotazioni: albero contenente le prenotazioni da assegnare al veicolo
 *
 * Pre-condizioni:
 *	v: non deve essere NULL
 *
 * Post-condizioni:
 *	non restituisce niente
 *
 * Side-effect:
 * 	aggiorna il campo prenotazioni del veicolo con il puntatore fornito
 */
void imposta_prenotazioni(Veicolo v, Prenotazioni prenotazioni);

/*
 * Funzione: ottieni_tipo_veicolo
 * ------------------------------
 *
 * Restituisce il tipo del veicolo puntato da v
 *
 * Parametri:
 *	v: puntatore ad un veicolo
 *
 * Pre-condizioni:
 *	v: non deve essere NULL
 *
 * Post-condizione:
 *	restituisce una stringa contenente il tipo del veicolo
 *
 */
char* ottieni_tipo_veicolo(Veicolo v);

/*
 * Funzione: imposta_tipo_veicolo
 * ------------------------------
 *
 * Imposta il tipo del veicolo puntato da v
 *
 * Parametri:
 *	v: puntatore ad un veicolo
 *	tipo: stringa che contiene il tipo di un veicolo
 *
 * Pre-condizioni:
 *	v: non deve essere NULL
 *	tipo: non deve essere NULL e deve essere lungo al massimo 30 caratteri
 *
 * Post-condizioni:
 *	non restituisce niente
 *
 * Side-effect:
 * 	modifica il campo tipo_veicolo nella struttura veicolo
 */
void imposta_tipo_veicolo(Veicolo v, char *tipo);

/*
 * Funzione: confronta_tipo
 * --------------------------
 *
 * confronta una stringa "tipo" con il tipo del veicolo puntato da v
 *
 * Parametri:
 * 	v: puntatore ad un veicolo
 * 	tipo: stringa che rappresenta il tipo di un veicolo
 *
 * Pre-condizioni:
 *	v: non deve essere NULL
 *  tipo: non deve essere NULL
 *
 * Post-condizione:
 *	restituisce 1 se il tipo del veicolo è uguale a "tipo", altrimenti 0
 */
Byte confronta_tipo(Veicolo v, char *tipo);

/*
* Funzione: aggiungi_prenotazione_veicolo
* ---------------------------------------
*
* aggiunge una prenotazione al veicolo puntato da v
*
* Parametri:
*	v: puntatore ad un veicolo
*	prenotazione: puntatore alla struttura prenotazione
*
* Pre-condizioni:
*	v: non deve essere NULL
*	prenotazione: non deve essere NULL
*
* Post-condizione:
*	restituisce 1 se la prenotazione è stata aggiunta, altrimenti 0
 */
Byte aggiungi_prenotazione_veicolo(Veicolo v, Prenotazione prenotazione);

/*
* Funzione: rimuovi_prenotazione_veicolo
* ---------------------------------------
*
* rimuove una prenotazione dato il suo intervallo temporale dal veicolo puntato da v
*
* Parametri:
*	v: puntatore ad un veicolo
*	intervallo: puntatore alla struttura intervallo
*
* Pre-condizioni:
*	v: non deve essere NULL
*	prenotazione: non deve essere NULL
*
* Post-condizione:
*	restituisce 1 se la prenotazione è stata rimossa, altrimenti 0
 */
Byte rimuovi_prenotazione_veicolo(Veicolo v, Intervallo intervallo);

/*
 * Funzione: confronta_targhe
 * --------------------------
 *
 * confronta la targa fornita con quella del veicolo puntato da v
 *
 * Parametri:
 * 	v: puntatore ad un veicolo
 * 	targa: stringa che contiene la targa di un veicolo
 *
 * Pre-condizioni:
 *	v: non deve essere NULL
 *  targa: non deve essere NULL e deve essere lunga 7 caratteri
 *
 * Post-condizione:
 *	restituisce 1 se le targhe sono uguali e 0 se sono diverse
 */
Byte confronta_targhe(Veicolo v, char *targa);

/*
 * Funzione: veicolo_in_stringa
 * ----------------------------
 *
 * restituisce una stringa che contiene tutte le informazioni del veicolo puntato da v
 *
 * Parametri:
 * 	v: puntatore ad un veicolo
 *
 * Pre-condizioni:
 *	v: non deve essere NULL
 *
 * Post-condizione:
 * 	restituisce una stringa che contiene tutte le informazioni di un veicolo
 */
char* veicolo_in_stringa(Veicolo v);

#endif //VEICOLO_H
