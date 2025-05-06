//
// Created by marco on 5/6/25.
//

#ifndef PRENOTAZIONE_H
#define PRENOTAZIONE_H
#include "strutture_dati/intervallo.h"
#include "strutture_dati/utente.h"
typedef struct prenotazione *Prenotazione;

Prenotazione prenotazioneCrea(Utente cliente, Intervallo i, double costo);

void prenotazioneDestroy(Prenotazione p);

Utente getCliente(Prenotazione p);

Intervallo getDateIntervallo(Prenotazione p);

double getCosto(Prenotazione p);

void setCliente(Prenotazione p, Utente cliente);

void setIntervallo(Prenotazione p, Intervallo i);

void setCosto(Prenotazione p, double costo);

#endif //PRENOTAZIONE_H
