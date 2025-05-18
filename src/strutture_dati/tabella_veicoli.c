/*
 * Autore: Russo Nello Manuel
 * Data: 10/05/2025
 */

#include <stddef.h>
#include "strutture_dati/prenotazioni.h"
#include "modelli/veicolo.h"
#include "strutture_dati/tabella_hash.h"
#include "strutture_dati/tabella_veicoli.h"

/*
 * Funzione: crea_tabella_veicoli
 * ------------------------------
 *
 * Crea una nuova tabella hash per la memorizzazione dei veicoli.
 *
 * Implementazione:
 *    Sfrutta la funzione nuova_tabella_hash per creare e inizializzare
 *    una nuova tabella hash con la grandezza specificata.
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
TabellaVeicoli crea_tabella_veicoli(unsigned int grandezza){
    return nuova_tabella_hash(grandezza);
}

/*
 * Funzione: distruggi_veicolo_t
 * -----------------------------
 *
 * funzione di supporto che effettua il cast del puntatore generico void *
 * a un oggetto di tipo Veicolo, permettendo l'utilizzo della funzione distruggi_veicolo
 *
 * Parametri:
 *    veicolo: puntatore generico a un veicolo
 *
 * Pre-condizioni:
 *    veicolo: non deve essere NULL
 *
 * Post-condizioni:
 *    la memoria associata al veicolo viene liberata
 */
static void distruggi_veicolo_t(void *veicolo){
    if (veicolo == NULL) return;

    Veicolo v = (Veicolo)veicolo;
    distruggi_veicolo(v);
}

/*
 * Funzione: distruggi_tabella_veicoli
 * -----------------------------------
 *
 * libera tutta la memoria associata alla tabella dei veicoli,
 * inclusi tutti i veicoli memorizzati
 *
 * Implementazione:
 *    Utilizza la funzione `distruggi_tabella`, passando una funzione
 *    di distruzione specifica per i veicoli (`distruggi_veicolo_t`).
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
void distruggi_tabella_veicoli(TabellaVeicoli tabella_veicoli){
    if(tabella_veicoli == NULL){
        return;
    }

    /* Viene passata la funzione distruggi_veicolo_t per rispettare il parametro
     * che deve restituire un void e avere come parametro un puntatore void
     */
    distruggi_tabella(tabella_veicoli, distruggi_veicolo_t);
}

/*
 * Funzione: aggiungi_veicolo_in_tabella
 * -------------------------------------
 *
 * inserisce un veicolo all'interno della tabella hash dei veicoli, utilizzando la targa come chiave
 *
 * Implementazione:
 *    chiama la funzione inserisci_in_tabella utilizzando la targa del veicolo come chiave
 *    e il puntatore al veicolo come valore.
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
Byte aggiungi_veicolo_in_tabella(TabellaVeicoli tabella_veicoli, Veicolo veicolo){
    if(tabella_veicoli == NULL || veicolo == NULL) return 0;

    return inserisci_in_tabella(tabella_veicoli, ottieni_targa(veicolo), (Veicolo)veicolo);
}

/*
 * Funzione: cerca_veicolo_in_tabella
 * -----------------------------------
 *
 * cerca un veicolo nella tabella hash dei veicoli utilizzando la targa come chiave
 *
 * Implementazione:
 *    utilizza la funzione cerca_in_tabella passando la targa come chiave,
 *    e restituisce il puntatore al veicolo trovato se esiste
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
Veicolo cerca_veicolo_in_tabella(TabellaVeicoli tabella_veicoli, char *targa){
    if(tabella_veicoli == NULL || targa == NULL) return NULL;

    return (Veicolo)cerca_in_tabella(tabella_veicoli, targa);
}

/*
 * Funzione: rimuovi_veicolo_in_tabella
 * ------------------------------------
 *
 * rimuove un veicolo dalla tabella dei veicoli utilizzando la targa come chiave
 *
 * Implementazione:
 *    richiama la funzione cancella_dalla_tabella passando la targa come chiave
 *    e la funzione distruggi_veicolo_t per liberare la memoria del veicolo
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
Byte rimuovi_veicolo_in_tabella(TabellaVeicoli tabella_veicoli, char *targa){
    if(tabella_veicoli == NULL || targa == NULL) return 0;

    return cancella_dalla_tabella(tabella_veicoli, targa, distruggi_veicolo_t);
}

/*
 * Funzione: ottieni_veicoli_disponibili
 * -------------------------------------
 *
 * restituisce un array di veicoli disponibili in un determinato intervallo di tempo
 *
 * Implementazione:
 *    estrae tutti i veicoli dalla tabella hash e verifica per ciascuno
 *    se è occupato nell'intervallo specificato. Se lo è, imposta il corrispondente
 *    elemento del vettore a NULL.
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
Veicolo *ottieni_veicoli_disponibili(TabellaVeicoli tabella_veicoli, Intervallo intervallo, unsigned int *dimensione){
    Veicolo *vettore = (Veicolo *)ottieni_vettore(tabella_veicoli, dimensione);
    if(vettore == NULL || dimensione == NULL) return NULL;

    for(unsigned int i = 0; i < *dimensione; i++){
        if(controlla_prenotazione(ottieni_prenotazioni(vettore[i]), intervallo) == OCCUPATO){
            vettore[i] = NULL;
        }
    }
    return vettore;
}


void carica_veicoli(TabellaVeicoli tabella_veicoli, Veicolo *veicolo, unsigned int dimensione){
	if(tabella_veicoli == NULL || veicolo == NULL || !dimensione) return;

	for(unsigned int i = 0; i < dimensione; i++){
		aggiungi_veicolo_in_tabella(tabella_veicoli, veicolo[i]);
	}
}