/*
 * Autore: Antonio Sicignano
 * Data: 09/05/2025
 */

#include "modelli/data.h"
#include "modelli/prenotazione.h"
#include "strutture_dati/lista_prenotazione.h"

#include <stdlib.h>
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

ListaPre ottieni_storico(Data data){
  return data->storico;
}

ListaPre aggiungi_a_storico(Data data, Prenotazione prenotazione) {
    (void)data;
    (void)prenotazione;
    /* FUNZIONE ANCORA DA FARE */
    return NULL;
}

ListaPre rimuovi_da_storico(Data data, Prenotazione prenotazione) {
    (void)data;
    (void)prenotazione;
    /* FUNZIONE ANCORA DA FARE */
    return NULL;
}

int ottieni_frequenza(Data data){
  return data->frequenza;
}

void azzera_frequenza(Data data){
  data->frequenza = 0;
}
