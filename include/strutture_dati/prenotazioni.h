/*
 * Autore: Marco Visone
 * Data: 06/05/2025
 */

#ifndef PRENOTAZIONI_H
#define PRENOTAZIONI_H
#define OK 0
#define OCCUPATO 1

#include "modelli/byte.h"
typedef struct intervallo *Intervallo;
typedef struct prenotazione *Prenotazione;
typedef struct albero *Prenotazioni;


Prenotazioni crea_prenotazioni();

void distruggi_prenotazioni(Prenotazioni prenotazioni);

Byte aggiungi_prenotazione(Prenotazioni prenotazioni, Prenotazione p);

Byte controlla_prenotazione(Prenotazioni prenotazioni, Intervallo i);

Byte cancella_prenotazione(Prenotazioni prenotazioni, Intervallo i);

Prenotazione *ottieni_vettore_prenotazioni_ordinate(Prenotazioni prenotazioni, unsigned int *size);

Prenotazione *ottieni_vettore_prenotazioni_per_file(Prenotazioni prenotazioni, unsigned int *size);

#endif //PRENOTAZIONI_H
