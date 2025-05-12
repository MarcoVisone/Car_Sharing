/*
 * Autore: Antonio Sicignano
 * Data: 09/05/2025
 */

#include "modelli/data.h"
#include "modelli/prenotazione.h"
#include "strutture_dati/lista_prenotazione.h"
#include <stddef.h>

//#include <stdlib.h>

struct data{
  ListaPre storico;
  int frequenza;
};

struct storico{
   Prenotazione prenotazione;
   struct storico *next;
};

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
