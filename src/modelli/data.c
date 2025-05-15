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
  int frequenza;
};

/*
 * Funzione: crea_data
 * -------------------
 * Crea e inizializza una nuova struttura Data.
 *
 * Implementazione:
 *    Alloca dinamicamente memoria per una struttura data,
 *    inizializza la lista storico con una lista vuota creata
 *    tramite crea_lista() e imposta frequenza a 0.
 *
 * Ritorna:
 *    un nuovo oggetto Data allocato dinamicamente,
 *    NULL in caso di errore di allocazione
 */
Data crea_data() {
    Data data = malloc(sizeof(struct data));
    if (data == NULL) {
        return NULL;
    }

    data->storico = crea_lista();
    data->frequenza = 0;

    return data;
}

/*
 * Funzione: distruggi_data
 * ------------------------
 * Dealloca la memoria associata a una struttura Data,
 * liberando anche le eventuali liste interne.
 *
 * Implementazione:
 *    Se il puntatore data è valido, chiama distruggi_lista_prenotazione
 *    per liberare la lista interno storico, quindi libera la memoria
 *    della struttura data stessa.
 *
 * Parametri:
 *    data: puntatore alla struttura Data da distruggere
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
 * Restituisce la lista delle prenotazioni associate alla Data.
 *
 * Implementazione:
 *    Restituisce semplicemente il campo storico della struttura Data,
 *    oppure NULL se il puntatore data è NULL.
 *
 * Parametri:
 *    data: puntatore alla struttura Data
 *
 * Ritorna:
 *    la lista delle prenotazioni (ListaPre)
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
 * Aggiunge una prenotazione alla lista interna della Data.
 *
 * Implementazione:
 *    Se data è valido, aggiorna il campo storico chiamando
 *    aggiungi_prenotazione_lista con la prenotazione da aggiungere,
 *    quindi restituisce la lista aggiornata.
 *
 * Parametri:
 *    data: puntatore alla struttura Data
 *    prenotazione: prenotazione da aggiungere
 *
 * Ritorna:
 *    la lista aggiornata con la prenotazione aggiunta
 */
ListaPre aggiungi_a_storico_lista(Data data, Prenotazione prenotazione) {
    if (data == NULL) {
        return NULL;
    }
    data->storico = aggiungi_prenotazione_lista(data->storico, prenotazione);
    return data->storico;
}

/*
 * Funzione: rimuovi_da_storico_lista
 * ----------------------------------
 * Rimuove una prenotazione dalla lista interna della Data.
 *
 * Implementazione:
 *    Se data è valido, aggiorna il campo storico chiamando
 *    rimuovi_prenotazione_lista con la prenotazione da rimuovere,
 *    quindi restituisce la lista aggiornata.
 *
 * Parametri:
 *    data: puntatore alla struttura Data
 *    prenotazione: prenotazione da rimuovere
 *
 * Ritorna:
 *    la lista aggiornata dopo la rimozione
 */
ListaPre rimuovi_da_storico_lista(Data data, Prenotazione prenotazione) {
    if (data == NULL) {
        return NULL;
    }

    data->storico = rimuovi_prenotazione_lista(data->storico, prenotazione);
    return data->storico;
}

/*
 * Funzione: ottieni_frequenza_lista
 * ---------------------------------
 * Restituisce la frequenza (ad esempio il numero di prenotazioni)
 * contenuta nella struttura Data.
 *
 * Implementazione:
 *    Se data è valido, restituisce il campo frequenza,
 *    altrimenti ritorna ERRORE_FREQUENZA.
 *
 * Parametri:
 *    data: puntatore alla struttura Data
 *
 * Ritorna:
 *    un intero che rappresenta la frequenza,
 *    oppure ERRORE_FREQUENZA in caso di errore
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
 * Resetta la frequenza della struttura Data a zero.
 *
 * Implementazione:
 *    Se data è valido, imposta il campo frequenza a zero.
 *
 * Parametri:
 *    data: puntatore alla struttura Data
 */
void azzera_frequenza(Data data){
    if (data == NULL) {
        return;
    }
    data->frequenza = 0;
}