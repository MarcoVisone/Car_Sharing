/*
 * Autore: Russo Nello Manuel
 * Data: 09/05/2025
 */

#ifndef VEICOLO_H
#define VEICOLO_H
#include "modelli/byte.h"
#include "strutture_dati/prenotazioni.h"

typedef struct veicolo *Veicolo;

/*
 * Funzione: crea_veicolo
 * ----------------------
 * Crea un nuovo veicolo con targa, modello, descrizione,
 * tariffa, prenotazioni passati come parametri alla funzione.
 *
 * Parametri:
 *    targa: stringa che rappresenta la targa del veicolo
 *    modello: stringa che rappresenta il modello del veicolo
 *    descrizione: stringa che rappresenta la descrizione del veicolo
 *    tariffa: numero che rappresenta la tariffa al minuto in euro di un veicolo
 *    prenotazioni: puntatore alle prenotazioni relative ad un veicolo
 *
 * Pre-condizioni:
 *	targa: deve contenere una targa valida di 7 caratteri
 *   modello: non deve essere nullo e non deve essere vuoto
 *   descrizione: non deve essere nulla non deve essere vuota
 *   tariffa: deve essere > 0
 *
 * Post-condizione:
 *   ritorna un nuovo veicolo v se l'allocazione dinamica della memoria è andata a buon fine,
 *   altrimenti ritorna NULL
 *
 * Ritorna:
 *   Un nuovo veicolo v
 */
Veicolo crea_veicolo(char *tipo, char *targa, char *modello, char *descrizione, double tariffa, Prenotazioni prenotazioni);

/*
 * Funzione: distruggi_veicolo
 * ---------------------------
 *
 * dealloca un veicolo liberando la memoria allocata sia per il veicolo,
 * sia per le prenotazioni relative al veicolo
 *
 * Parametri:
 *	v: puntatore ad un veicolo
 *
 * Pre-condizioni:
 *	v: non deve essere NULL
 *
 * Post-condizione:
 *	non ritorna niente
 *
 * Side-effect:
 *	la memoria a cui punta v viene liberata
 */
void distruggi_veicolo(Veicolo v);

/*
 * Funzione: ottieni_targa
 * -----------------------
 *
 * ritorna una stringa che è la targa del veicolo puntato da v
 *
 * Parametri:
 *	v: puntatore ad un veicolo
 *
 * Pre-condizione:
 *	v: non deve essere NULL
 *
 * Post-condizione:
 *	ritorna una stringa che è la targa del veicolo puntato da v
 *
 * Ritorna:
 *	la targa del veicolo
 */
char *ottieni_targa(Veicolo v);

/*
 * Funzione: imposta_targa
 * -----------------------
 *
 * imposta una targa nel veicolo puntato da v
 *
 * Parametri:
 *	v: puntatore ad un veicolo
 *	targa: stringa che contiene la targa di un veicolo
 *
 * Pre-condizione:
 *	v: non deve essere NULL
 *	targa: non deve essere NULL e deve essere di 7 caratteri
 *
 * Post-condizione:
 *	non restituisce niente
 *
 * Side-effect:
 * 	modifica la stringa targa nella struttura veicolo
 */
void imposta_targa(Veicolo v, char *targa);

/*
 * Funzione: ottieni_modello
 * -------------------------
 *
 * ritorna una stringa che è il modello del veicolo puntato da v
 *
 * Parametri:
 *	v: puntatore ad un veicolo
 *
 * Pre-condizione:
 *	v: non deve essere NULL
 *
 * Post-condizione:
 *	ritorna una stringa che è il modello del veicolo puntato da v
 *
 * Ritorna:
 *	il modello del veicolo
 */
char* ottieni_modello(Veicolo v);

/*
 * Funzione: imposta_modello
 * -------------------------
 *
 * imposta un modello nel veicolo puntato da v
 *
 * Parametri:
 * 	v: puntatore ad un veicolo
 *	modello: stringa che contiene il modello di un veicolo
 *
 * Pre-condizioni:
 *	v: non deve essere NULL
 *	modello: non deve essere NULL e deve essere di massimo 50 caratteri
 *
 * Post-condizione:
 *	non restituisce niente
 *
 * Side-effect:
 * 	modifica la stringa modello nella struttura veicolo
 */
void imposta_modello(Veicolo v, char *modello);

/*
 * Funzione: ottieni_descrizione
 * -----------------------------
 *
 * ritorna una stringa che è la descrizione del veicolo puntato da v
 *
 * Parametri:
 *	v: puntatore ad un veicolo
 *
 * Pre-condizione:
 *	v: non deve essere NULL
 *
 * Post-condizione:
 *	ritorna una stringa che è la descrizione del veicolo puntato da v
 *
 * Ritorna:
 *	la descrizione del veicolo
 */
char* ottieni_descrizione(Veicolo v);

/*
 * Funzione: imposta_descrizione
 * -----------------------------
 *
 * imposta una descrizione nel veicolo puntato da v
 *
 * Parametri:
 * 	v: puntatore ad un veicolo
 *	descrizione: stringa che contiene la descrizione di un veicolo
 *
 * Pre-condizioni:
 *	v: non deve essere NULL
 *	descrizione: non deve essere NULL e deve essere di massimo 1024 caratteri
 *
 * Post-condizione:
 *	non restituisce niente
 *
 * Side-effect:
 * 	modifica la stringa descrizione nella struttura veicolo
 */
void imposta_descrizione(Veicolo v, char *descrizione);

/*
 * Funzione: ottieni_tariffa
 * -------------------------
 *
 * ritorna un double che è la tariffa al minuto del veicolo puntato da v
 *
 * Parametri:
 *	v: puntatore ad un veicolo
 *
 * Pre-condizione:
 *	v: non deve essere NULL
 *
 * Post-condizione:
 *	ritorna un double che è la tariffa al minuto del veicolo puntato da v
 *
 * Ritorna:
 *	la tariffa del veicolo
 */
double ottieni_tariffa(Veicolo v);

/*
 * Funzione: imposta_tariffa
 * -------------------------
 *
 * imposta una tariffa nel veicolo puntato da v
 *
 * Parametri:
 *	v: puntatore ad un veicolo
 *	tariffa: double che contiene la tariffa al minuto di un veicolo
 *
 * Pre-condizione:
 *	v: non deve essere NULL
 *	tariffa: deve essere >0
 *
 * Post-condizione:
 *	non restituisce niente
 *
 * Side-effect:
 * 	modifica il double tariffa nella struttura veicolo
 */
void imposta_tariffa(Veicolo v, double tariffa);

/*
 * Funzione: ottieni_prenotazioni
 * ------------------------------
 *
 * ritorna un albero che contiene tutte le prenotazioni del veicolo puntato da v
 *
 * Parametri:
 *	v: puntatore ad un veicolo
 *
 * Pre-condizione:
 *	v: non deve essere NULL
 *
 * Post-condizione:
 *	ritorna un albero che contiene tutte le prenotazioni del veicolo puntato da v
 *
 * Ritorna:
 *	le prenotazioni del veicolo
 */
Prenotazioni ottieni_prenotazioni(Veicolo v);

/*
 * Funzione: imposta_prenotazioni
 * ------------------------------
 *
 * imposta le prenotazioni nel veicolo puntato da v
 *
 * Parametri:
 *	v: puntatore ad un veicolo
 *	prenotazioni: albero che contiene le prenotazioni di un veicolo
 *
 * Pre-condizione:
 *	v: non deve essere NULL
 *	prenotazioni: nessuna
 *
 * Post-condizione:
 *	non restituisce niente
 *
 * Side-effect:
 * 	modifica il puntatore prenotazioni nella struttura veicolo
 */
void imposta_prenotazioni(Veicolo v, Prenotazioni prenotazioni);


char* ottieni_tipo_veicolo(Veicolo v);

void imposta_tipo_veicolo(Veicolo v, char *tipo);

Byte confronta_tipo(Veicolo v, char *tipo);

Byte aggiungi_prenotazione_veicolo(Veicolo v, Prenotazione prenotazione);

Byte rimuovi_prenotazione_veicolo(Veicolo v, Prenotazione prenotazione);

/*
 * Funzione: confronta_targhe
 * --------------------------
 *
 * confronta una stringa targa con la targa del veicolo puntato da v, restituisce 1 se sono uguali
 * e 0 se sono diverse
 *
 * Parametri:
 * 	v: puntatore ad un veicolo
 * 	targa: stringa che contiene la targa di un veicolo
 *
 * Pre-condizioni:
 * 	v: non deve essere NULL
 *   targa: non deve essere NULL e deve essere di 7 caratteri
 *
 * Post-condizione:
 *	restituisce 1 se le targhe sono uguali e 0 se sono diverse
 */
Byte confronta_targhe(Veicolo v, char *targa);

/*
 * Funzione: veicolo_in_stringa
 * ----------------------------
 *
 * restituisce una stringa che contiene tutte le informazioni di un veicolo
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
