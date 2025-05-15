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

Prenotazione *ottieni_vettore_storico(Data data, unsigned int *dimensione){
  if (data == NULL) {
    return NULL;
  }
  Prenotazione *vettore_prenotazione = malloc(sizeof(Prenotazione)*data->numero_prenotazioni);

  ListaPre curr = data->storico;
  unsigned int i = 0;
  while (curr != NULL) {
    vettore_prenotazione[i] = ottieni_item(curr);
    curr = ottieni_prossimo(curr);
  }
  *dimensione = data->numero_prenotazioni;
  return vettore_prenotazione;
}

int ottieni_numero_prenotazioni(Data data){
  if (data == NULL) {
    return -1;
  }
  return data->numero_prenotazioni;
}

void imposta_numero_prenotazioni(Data data, int numero_prenotazioni){
  if (data == NULL) {
    return;
  }
  data->numero_prenotazioni = numero_prenotazioni;
}