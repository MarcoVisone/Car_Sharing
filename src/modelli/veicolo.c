/*
 * Autore: Russo Nello Manuel
 * Data: 09/05/2025
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "modelli/veicolo.h"
#include "modelli/intervallo.h"
#include "modelli/prenotazione.h"
#include "strutture_dati/prenotazioni.h"
#include "utils/utils.h"

struct veicolo{
    char targa[NUM_CARATTERI_TARGA];
    char modello[MAX_LUNGHEZZA_MODELLO];
    char posizione[MAX_LUNGHEZZA_POSIZIONE];
    double tariffa;
	char tipo_veicolo[MAX_LUNGHEZZA_TIPO];
    Prenotazioni prenotazioni;
};

/*
 * Funzione: crea_veicolo
 * ----------------------
 * Crea un nuovo veicolo con targa, modello, posizione,
 * tariffa e prenotazioni associate
 *
 * Implementazione:
 *    se sono rispettate le pre-condizioni alloca dinamicamente memoria per una struttura Veicolo e inizializza
 *    i relativi campi con i valori forniti come parametri
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
Veicolo crea_veicolo(char *tipo, char *targa, char *modello, char *posizione, double tariffa, Prenotazioni prenotazioni){
    Veicolo v = malloc(sizeof(struct veicolo));
    if(v == NULL || tipo == NULL || modello == NULL || posizione == NULL ||
	   tariffa <= 0 || strlen(targa) != NUM_CARATTERI_TARGA - 2) return NULL;

	snprintf(v->targa, NUM_CARATTERI_TARGA, "%s", targa);

    snprintf(v->modello, MAX_LUNGHEZZA_MODELLO, "%s", modello);

    snprintf(v->posizione, MAX_LUNGHEZZA_POSIZIONE, "%s", posizione);

	snprintf(v->tipo_veicolo, MAX_LUNGHEZZA_TIPO, "%s", tipo);

    v->tariffa = tariffa;

    v->prenotazioni = prenotazioni;

    return v;
}

/*
 * Funzione: distruggi_veicolo
 * ---------------------------
 * elimina un veicolo
 *
 * Implementazione:
 *    se il puntatore al veicolo è NULL, la funzione non fa nulla, altrimenti libera
 *    la memoria allocata per il veicolo e per le prenotazioni associate ad esso
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
void distruggi_veicolo(Veicolo v){
	if(v == NULL) return;
    distruggi_prenotazioni(v->prenotazioni);
    free(v);
}

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
 *	v: puntatore ad un veicolo
 *
 * Pre-condizioni:
 *	v: non deve essere NULL
 *
 * Post-condizione:
 *	restituisce una stringa contenente la targa del veicolo
 */
char *ottieni_targa(Veicolo v){
	if(v == NULL) return NULL;
    return v->targa;
}

/*
 * Funzione: imposta_targa
 * -----------------------
 *
 * Imposta la targa nel veicolo puntato da v
 *
 * Implementazione:
 *    se le pre-condizioni sono rispettate copia la stringa targa nel campo targa della struttura veicolo
 *    con snprintf per evitare overflow di buffer, altrimenti non fa nulla
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
void imposta_targa(Veicolo v, char *targa){
	if(v == NULL || targa == NULL || strlen(targa) != NUM_CARATTERI_TARGA - 1) return;
    snprintf(v->targa, NUM_CARATTERI_TARGA, "%s", targa);
}

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
char* ottieni_modello(Veicolo v){
	if(v == NULL) return NULL;
    return v->modello;
}

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
void imposta_modello(Veicolo v, char *modello){
    if(v == NULL || modello == NULL || strlen(modello) > MAX_LUNGHEZZA_MODELLO - 1) return;
    snprintf(v->modello, MAX_LUNGHEZZA_MODELLO, "%s", modello);
}

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
 *	v: puntatore ad un veicolo
 *
 * Pre-condizioni:
 *	v: non deve essere NULL
 *
 * Post-condizione:
 *	restituisce una stringa contenente la posizione del veicolo
 */
char* ottieni_posizione(Veicolo v){
	if(v == NULL) return NULL;
    return v->posizione;
}

/*
 * Funzione: imposta_posizione
 * -----------------------------
 *
 * imposta la posizione del veicolo puntato da v
 *
 * Implementazione:
 *    se le pre-condizioni sono rispettate copia la stringa posizione nel campo posizione della struttura veicolo
 *    con snprintf per evitare overflow di buffer, altrimenti non fa nulla
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
void imposta_posizione(Veicolo v, char *posizione){
    if(v == NULL || strlen(posizione) > MAX_LUNGHEZZA_POSIZIONE - 1) return;
    snprintf(v->posizione, MAX_LUNGHEZZA_POSIZIONE, "%s", posizione);
}

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
 *	v: puntatore ad un veicolo
 *
 * Pre-condizioni:
 *	v: non deve essere NULL
 *
 * Post-condizione:
 *	restituisce un double che è la tariffa al minuto del veicolo puntato da v
 */
double ottieni_tariffa(Veicolo v){
    if(v == NULL) return -1;
    return v->tariffa;
}

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
void imposta_tariffa(Veicolo v, double tariffa){
    if(v == NULL || tariffa <= 0) return;
    v->tariffa = tariffa;
}

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
 *	v: puntatore ad un veicolo
 *
 * Pre-condizioni:
 *	v: non deve essere NULL
 *
 * Post-condizione:
 *	restituisce l'albero contenente le prenotazioni del veicolo
 */
Prenotazioni ottieni_prenotazioni(Veicolo v){
    if(v == NULL) return NULL;
    return v->prenotazioni;
}

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

void imposta_prenotazioni(Veicolo v, Prenotazioni prenotazioni){
    if(v == NULL) return;
    v->prenotazioni = prenotazioni;
}

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
 *	v: puntatore ad un veicolo
 *
 * Pre-condizioni:
 *	v: non deve essere NULL
 *
 * Post-condizione:
 *	restituisce una stringa contenente il tipo del veicolo
 *
 */
char* ottieni_tipo_veicolo(Veicolo v){
	if(v == NULL) return NULL;
	return v->tipo_veicolo;
}

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
void imposta_tipo_veicolo(Veicolo v, char *tipo){
	if(v == NULL || tipo == NULL || strlen(tipo) > MAX_LUNGHEZZA_TIPO - 1) return;
	snprintf(v->tipo_veicolo, MAX_LUNGHEZZA_TIPO, "%s", tipo);
}

/*
 * Funzione: confronta_tipo
 * --------------------------
 *
 * confronta una stringa "tipo" con il tipo del veicolo puntato da v
 *
 * Implementazione:
 *    se le pre-condizioni sono rispettate e la stringa tipo è uguale al tipo del veicolo puntato da v restituisce 1,
 *    altrimenti 0. Se le pre-condizioni non sono rispettate restituisce -1
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
Byte confronta_tipo(Veicolo v, char *tipo){
	if(v == NULL || tipo == NULL) return -1;
	return (strcmp(tipo, v->tipo_veicolo) == 0);
}

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
Byte aggiungi_prenotazione_veicolo(Veicolo v, Prenotazione prenotazione){
	if(v == NULL || prenotazione == NULL) return 0;

	return aggiungi_prenotazione(v->prenotazioni, prenotazione);
}

/*
* Funzione: rimuovi_prenotazione_veicolo
* ---------------------------------------
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
Byte rimuovi_prenotazione_veicolo(Veicolo v, Intervallo intervallo){
	if(v == NULL || intervallo == NULL) return 0;

	Byte codice = cancella_prenotazione(v->prenotazioni, intervallo);

	if(!codice) return 0;

	return 1;
}

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
Byte confronta_targhe(Veicolo v, char *targa){
    if(v == NULL || targa == NULL || strlen(targa) != NUM_CARATTERI_TARGA - 1) return -1;
    return (strcmp(targa,v->targa) == 0);
}

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
 * 	v: puntatore ad un veicolo
 *
 * Pre-condizioni:
 *	v: non deve essere NULL
 *
 * Post-condizione:
 * 	restituisce una stringa che contiene tutte le informazioni di un veicolo
 */
char* veicolo_in_stringa(Veicolo v){
    if(v == NULL) return NULL;

    int size = MAX_LUNGHEZZA_TIPO +
			   NUM_CARATTERI_TARGA +
               MAX_LUNGHEZZA_MODELLO +
               MAX_LUNGHEZZA_TARIFFA +
               MAX_LUNGHEZZA_POSIZIONE + 100 + 1;

    char *buffer = malloc(sizeof(char) * size);
    char tariffa[MAX_LUNGHEZZA_TARIFFA];

    if((int)v->tariffa == v->tariffa){
        snprintf(tariffa, MAX_LUNGHEZZA_TARIFFA, "%0.1lf", v->tariffa);
    }else{
        snprintf(tariffa, MAX_LUNGHEZZA_TARIFFA, "%0.3lf", v->tariffa);
    }

    snprintf(buffer, size, "Tipo: %s\nModello: %s\nPosizione: %s\nTarga: %s\nTariffa: %s EUR/MIN",
			v->tipo_veicolo,
            v->modello,
            v->posizione,
            v->targa,
            tariffa);

    return buffer;
}
