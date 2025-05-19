/*
 * Autore: Antonio Sicignano
 * Data: 09/05/2025
 */

#include <stdlib.h>

#include "modelli/data.h"
#include "strutture_dati/lista_prenotazione.h"
#include <strutture_dati/lista.h>

struct data{
  ListaPre storico;
  int numero_prenotazioni;
  int frequenza;
};

/*
 * Funzione: crea_data
 * -------------------
 *
 * Crea e inizializza una nuova struttura Data.
 *
 * Implementazione:
 *    Alloca dinamicamente una nuova struttura Data, inizializza la lista storico
 *    con una lista vuota e imposta la frequenza a 0. Restituisce il puntatore
 *    oppure NULL in caso di errore.
 *
 * Parametri:
 *    nessuno
 *
 * Pre-condizione:
 *    nessuna
 *
 * Ritorna:
 *    un nuovo oggetto Data allocato dinamicamente,
 *    NULL in caso di errore di allocazione
 *
 * Side-effect:
 *    allocazione dinamica di memoria
 */
Data crea_data() {
    Data data = malloc(sizeof(struct data));
    if (data == NULL) {
        return NULL;
    }

    data->storico = crea_lista();
    data->frequenza = 0;
    data->numero_prenotazioni = 0;

    return data;
}

/*
 * Funzione: distruggi_data
 * ------------------------
 *
 * Dealloca la memoria associata a una struttura Data,
 * liberando anche le eventuali liste interne.
 *
 * Implementazione:
 *    Se il puntatore non è NULL, distrugge la lista storico associata e libera
 *    la memoria della struttura Data.
 *
 * Parametri:
 *    data: puntatore alla struttura Data da distruggere
 *
 * Pre-condizione:
 *    data non deve essere NULL
 *
 * Post-condizione:
 *    memoria liberata
 *
 * Side-effect:
 *    deallocazione dinamica di memoria
 */
void distruggi_data(Data data) {
    if (data == NULL) {
        return;
    }

    distruggi_lista_prenotazione(data->storico);
    free(data);
}

/*
 * Funzione: ottieni_storico_lista
 * -------------------------------
 *
 * Restituisce la lista delle prenotazioni associate alla Data.
 *
 * Implementazione:
 *    Restituisce il campo storico della struttura Data se non è NULL,
 *    altrimenti restituisce NULL.
 *
 * Parametri:
 *    data: puntatore alla struttura Data
 *
 * Pre-condizione:
 *    data non deve essere NULL
 *
 * Ritorna:
 *    la lista delle prenotazioni (ListaPre)
 *
 * Side-effect:
 *    nessuno
 */
ListaPre ottieni_storico_lista(Data data){
    if (data == NULL) {
        return NULL;
    }

    return data->storico;
}

/*
 * Funzione: aggiungi_a_storico_lista
 * ----------------------------------
 *
 * Aggiunge una prenotazione alla lista interna della Data.
 *
 * Implementazione:
 *    Aggiunge una prenotazione alla lista storico e aggiorna il campo nella struttura.
 *    Restituisce la lista aggiornata, oppure NULL se Data è NULL.
 *
 * Parametri:
 *    data: puntatore alla struttura Data
 *    prenotazione: prenotazione da aggiungere
 *
 * Pre-condizione:
 *    data e prenotazione non devono essere NULL
 *
 * Post-condizione:
 *    la lista interna della Data è aggiornata con la nuova prenotazione
 *
 * Ritorna:
 *    la lista aggiornata con la prenotazione aggiunta
 *
 * Side-effect:
 *    modifica la lista interna
 */
ListaPre aggiungi_a_storico_lista(Data data, Prenotazione prenotazione) {
    if (data == NULL) {
        return NULL;
    }
    data->storico = aggiungi_prenotazione_lista(data->storico, prenotazione);
    data->numero_prenotazioni +=1;
    return data->storico;
}

/*
 * Funzione: rimuovi_da_storico_lista
 * ----------------------------------
 *
 * Rimuove una prenotazione dalla lista interna della Data.
 *
 * Implementazione:
 *    Rimuove una prenotazione dalla lista storico e aggiorna il campo nella struttura.
 *    Restituisce la lista aggiornata, oppure NULL se Data è NULL.
 *
 * Parametri:
 *    data: puntatore alla struttura Data
 *    prenotazione: prenotazione da rimuovere
 *
 * Pre-condizione:
 *    data e prenotazione non devono essere NULL
 *
 * Post-condizione:
 *    la lista interna della Data è aggiornata dopo la rimozione
 *
 * Ritorna:
 *    la lista aggiornata dopo la rimozione
 *
 * Side-effect:
 *    modifica la lista interna
 */
ListaPre rimuovi_da_storico_lista(Data data, Prenotazione prenotazione) {
    if (data == NULL) {
        return NULL;
    }

    data->storico = rimuovi_prenotazione_lista(data->storico, prenotazione);
    data->numero_prenotazioni -=1;
    return data->storico;
}

/*
 * Funzione: ottieni_frequenza_lista
 * ---------------------------------
 *
 * Restituisce la frequenza (ad esempio il numero di prenotazioni)
 * contenuta nella struttura Data.
 *
 * Implementazione:
 *    Restituisce il valore della frequenza, oppure un codice di errore se Data è NULL.
 *
 * Parametri:
 *    data: puntatore alla struttura Data
 *
 * Pre-condizione:
 *    data non deve essere NULL
 *
 * Ritorna:
 *    un intero che rappresenta la frequenza,
 *    oppure ERRORE_FREQUENZA in caso di errore
 *
 * Side-effect:
 *    nessuno
 */
int ottieni_frequenza_lista(Data data){
    if (data == NULL) {
        return ERRORE_FREQUENZA;
    }
    return data->frequenza;
}

/*
 * Funzione: azzera_frequenza
 * --------------------------
 *
 * Resetta la frequenza della struttura Data a zero.
 *
 * Implementazione:
 *    Se Data non è NULL, imposta la frequenza a 0.
 *
 * Parametri:
 *    data: puntatore alla struttura Data
 *
 * Pre-condizione:
 *    data non deve essere NULL
 *
 * Post-condizione:
 *    la frequenza è resettata a zero
 *
 * Side-effect:
 *    modifica la struttura Data
 */
void azzera_frequenza(Data data){
    if (data == NULL) {
        return;
    }
    data->frequenza = 0;
}


/*
 * Funzione: ottieni_vettore_storico
 * ---------------------------------
 *
 * Restituisce un array contenente tutte le prenotazioni presenti nello storico.
 *
 * Implementazione:
 *    Alloca dinamicamente un vettore di prenotazioni, copia gli elementi dalla lista storico
 *    e imposta la dimensione tramite un puntatore.
 *
 * Parametri:
 *    data: struttura contenente lo storico delle prenotazioni
 *    dimensione: puntatore a intero dove verrà memorizzata la dimensione del vettore
 *
 * Pre-condizione:
 *    data deve essere una struttura valida
 *
 * Post-condizione:
 *    viene restituito un vettore allocato dinamicamente contenente tutte le prenotazioni,
 *    oppure NULL se data è NULL o se l'allocazione fallisce
 *
 * Ritorna:
 *    vettore di prenotazioni o NULL in caso di errore
 *
 * Side-effect:
 *    allocazione dinamica di memoria
 */
Prenotazione *ottieni_vettore_storico(Data data, unsigned int *dimensione){
    if (data == NULL) {
      return NULL;
    }

    Prenotazione *vettore_prenotazione = (Prenotazione*) calloc(data->numero_prenotazioni, sizeof(Prenotazione));

    ListaPre curr = data->storico;
    unsigned int i = 0;
    while (curr != NULL) {
        vettore_prenotazione[i] = (Prenotazione)ottieni_item(curr);
        curr = ottieni_prossimo(curr);
        i++;
    }
    *dimensione = i;
    return vettore_prenotazione;
}

/*
 * Funzione: ottieni_numero_prenotazioni
 * -------------------------------------
 *
 * Restituisce il numero di prenotazioni contenute nella struttura Data.
 *
 * Implementazione:
 *    Controlla che la struttura sia valida e restituisce il campo numero_prenotazioni.
 *
 * Parametri:
 *    data: struttura Data da cui ottenere il numero di prenotazioni
 *
 * Pre-condizione:
 *    data deve essere una struttura valida
 *
 * Post-condizione:
 *    nessuna
 *
 * Ritorna:
 *    numero di prenotazioni o -1 se data è NULL
 *
 * Side-effect:
 *    nessuno
 */
int ottieni_numero_prenotazioni(Data data){
    if (data == NULL) {
        return -1;
    }
    return data->numero_prenotazioni;
}

/*
 * Funzione: imposta_numero_prenotazioni
 * -------------------------------------
 *
 * Imposta il numero di prenotazioni nella struttura Data.
 *
 * Implementazione:
 *    Verifica che data sia valida e assegna il valore al campo numero_prenotazioni.
 *
 * Parametri:
 *    data: struttura Data su cui effettuare la modifica
 *    numero_prenotazioni: nuovo valore da assegnare
 *
 * Pre-condizione:
 *    data deve essere una struttura valida
 *
 * Post-condizione:
 *    il campo numero_prenotazioni della struttura viene aggiornato
 *
 * Ritorna:
 *    nessun valore
 *
 * Side-effect:
 *    modifica della struttura Data
 */
void imposta_numero_prenotazioni(Data data, int numero_prenotazioni){
    if (data == NULL) {
        return;
    }
    data->numero_prenotazioni = numero_prenotazioni;
}

/*
 * Funzione: imposta_storico_lista
 * -------------------------------
 *
 * Imposta la lista delle prenotazioni storico nella struttura Data.
 *
 * Implementazione:
 *    Verifica che data sia valida e assegna il valore al campo storico.
 *
 * Parametri:
 *    data: struttura Data da aggiornare
 *    lista_prenotazione: nuova lista storico da assegnare
 *
 * Pre-condizione:
 *    data deve essere una struttura valida
 *
 * Post-condizione:
 *    il campo storico della struttura viene aggiornato
 *
 * Ritorna:
 *    nessun valore
 *
 * Side-effect:
 *    modifica della struttura Data
 */
void imposta_storico_lista(Data data, ListaPre lista_prenotazione){
    if (data == NULL) {
        return;
    }

    data->storico = lista_prenotazione;
}

void imposta_frequenza(Data data, int frequenza){
    if(data == NULL){
        return;
    }

    data->frequenza = frequenza;
}
