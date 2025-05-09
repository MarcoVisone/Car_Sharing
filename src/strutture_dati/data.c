/*
 * Autore: Antonio Sicignano
 * Data: 09/05/2025
 */

#include "include/adt/data.h"
#include <stdlib.h>

struct data{
  Lista storico;
  int frequenza;
  };

  struct storico{
    Prenotazione prenotazione;
    struct storico *next;
  }

ListaPre ottieni_storico(Data data){
  return data->storico;
}

ListaPre aggiungi_a_storico(Data data, Prenotazione prenotazione){
  struct storico *s = malloc(sizeof(struct storico));
  if(s == NULL){
    printf("Errore allocazione memoria\n");
    exit(1);
  }
  s->prenotazione = prenotazione;
  s->next = data->storico;
  data->storico = s;
  data->frequenza++;
  return storico;
}

ListaPre rimuovi_da_storico(Data data, Prenotazione prenotazione){
  struct storico *s = malloc(sizeof(struct storico));
  if(s == NULL){
    printf("Errore allocazione memoria\n");
    exit(1);
  }

int ottieni_frequenza(Data data){
  return data->frequenza;
}

void azzera_frequenza(Data data){
  data->frequenza = 0;
}