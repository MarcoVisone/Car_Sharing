/*
 * Autore: Russo Nello Manuel
 * Data: 10/05/2025
 */

#ifndef HASHMAP_VEICOLI_H
#define HASHMAP_VEICOLI_H

#include "modelli/byte.h"

// Rinominata TabellaHash in TabellaVeicoli
typedef struct intervallo *Intervallo;
typedef struct tabella_hash *TabellaVeicoli;
typedef struct veicolo *Veicolo;

/*
 * Funzione: crea_tabella_veicoli
 * ------------------------------
 *
 * Crea una nuova tabella hash per la memorizzazione dei veicoli.
 *
 * Parametri:
 *    grandezza: dimensione iniziale della tabella hash
 *
 * Pre-condizioni:
 *    grandezza: deve essere maggiore di 0
 *
 * Post-condizioni:
 *    restituisce un oggetto TabellaVeicoli inizializzato,
 *    oppure NULL in caso di errore di allocazione
 *
 * Side-effect:
 *    Alloca dinamicamente memoria per la struttura tabella hash
 */
TabellaVeicoli crea_tabella_veicoli(unsigned int grandezza);

/*
 * Funzione: distruggi_tabella_veicoli
 * -----------------------------------
 *
 * libera tutta la memoria associata alla tabella dei veicoli,
 * inclusi tutti i veicoli memorizzati
 *
 * Parametri:
 *    tabella_veicoli: tabella hash contenente i veicoli
 *
 * Pre-condizioni:
 *    tabella_veicoli: non deve essere NULL
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    tutta la memoria associata alla tabella e ai veicoli viene liberata
 */
void distruggi_tabella_veicoli(TabellaVeicoli tabella_veicoli);

/*
 * Funzione: aggiungi_veicolo_in_tabella
 * -------------------------------------
 *
 * inserisce un veicolo all'interno della tabella hash dei veicoli, utilizzando la targa come chiave
 *
 * Parametri:
 *    tabella_veicoli: puntatore alla tabella hash dei veicoli
 *    veicolo: puntatore al veicolo da inserire
 *
 * Pre-condizioni:
 *    tabella_veicoli: non deve essere NULL
 *    veicolo: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce 1 se l'inserimento è avvenuto con successo, 0 altrimenti
 *
 * Side-effect:
 *    modifica la tabella hash aggiungendo il veicolo
 */
Byte aggiungi_veicolo_in_tabella(TabellaVeicoli tabella_veicoli, Veicolo veicolo);

/*
 * Funzione: cerca_veicolo_in_tabella
 * -----------------------------------
 *
 * cerca un veicolo nella tabella hash dei veicoli utilizzando la targa come chiave
 *
 * Parametri:
 *    tabella_veicoli: puntatore alla tabella hash dei veicoli
 *    targa: stringa contenente la targa del veicolo da cercare
 *
 * Pre-condizioni:
 *    tabella_veicoli: non deve essere NULL
 *    targa: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce un puntatore al veicolo se presente nella tabella,
 *    altrimenti restituisce NULL
 */
Veicolo cerca_veicolo_in_tabella(TabellaVeicoli tabella_veicoli, char *targa);

/*
 * Funzione: rimuovi_veicolo_in_tabella
 * ------------------------------------
 *
 * rimuove un veicolo dalla tabella dei veicoli utilizzando la targa come chiave
 *
 * Parametri:
 *    tabella_veicoli: puntatore alla tabella hash contenente i veicoli
 *    targa: stringa contenente la targa del veicolo da rimuovere
 *
 * Pre-condizioni:
 *    tabella_veicoli: non deve essere NULL
 *    targa: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce 1 se il veicolo è stato rimosso correttamente,
 *    0 se la targa non è presente o si è verificato un errore
 *
 * Side-effect:
 *    Modifica la tabella dei veicoli rimuovendo l'elemento specificato
 *    e libera la memoria associata al veicolo
 */
Byte rimuovi_veicolo_in_tabella(TabellaVeicoli tabella_veicoli, char *targa);

/*
 * Funzione: ottieni_veicoli_disponibili
 * -------------------------------------
 *
 * restituisce un array di veicoli disponibili in un determinato intervallo di tempo
 *
 * Parametri:
 *    tabella_veicoli: puntatore alla tabella hash contenente i veicoli
 *    intervallo: l'intervallo di tempo da controllare
 *    dimensione: puntatore a un intero dove verrà salvata la dimensione del vettore restituito
 *
 * Pre-condizioni:
 *    tabella_veicoli: non deve essere NULL
 *    dimensione: non deve essere NULL
 *
 * Post-condizioni:
 *    Restituisce un array allocato dinamicamente di puntatori a veicoli:
 *    - i veicoli occupati nell'intervallo vengono posti a NULL
 *    - quelli disponibili mantengono il puntatore originale
 *    - restituisce NULL in caso di errore
 *
 * Side-effect:
 *    Alloca dinamicamente un array che dovrà essere liberato dal chiamante.
 */
Veicolo *ottieni_veicoli_disponibili(TabellaVeicoli tabella_veicoli, Intervallo intervallo, unsigned int *dimensione);

#endif //HASHMAP_VEICOLI_H
