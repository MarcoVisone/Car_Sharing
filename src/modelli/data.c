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

Data crea_data() {
    Data data = malloc(sizeof(struct data));
    if (data == NULL) {
        return NULL;
    }

    data->storico = crea_lista();
    data->frequenza = 0;

    return data;
}

void distruggi_data(Data data) {
    if (data == NULL) {
        return;
    }

    distruggi_lista_prenotazione(data->storico);
    free(data);
}

ListaPre ottieni_storico_lista(Data data){
    if (data == NULL) {
        return NULL;
    }

    return data->storico;
}

ListaPre aggiungi_a_storico_lista(Data data, Prenotazione prenotazione) {
    if (data == NULL) {
        return NULL;
    }
    data->storico = aggiungi_prenotazione_lista(data->storico, prenotazione);
    return data->storico;
}

ListaPre rimuovi_da_storico_lista(Data data, Prenotazione prenotazione) {
    if (data == NULL) {
        return NULL;
    }

    data->storico = rimuovi_prenotazione_lista(data->storico, prenotazione);
    return data->storico;
}

int ottieni_frequenza_lista(Data data){
    if (data == NULL) {
        return ERRORE_FREQUENZA;
    }
    return data->frequenza;
}

void azzera_frequenza(Data data){
    if (data == NULL) {
        return;
    }
    data->frequenza = 0;
}
