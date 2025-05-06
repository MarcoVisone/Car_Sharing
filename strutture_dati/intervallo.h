//
// Created by marco on 5/6/25.
//

#ifndef INTERVALLO_H
#define INTERVALLO_H
#include <time.h>
#include "strutture_dati/byte.h"

typedef struct intervallo* Intervallo;

Intervallo intervalloCrea(time_t inizio, time_t fine);

void intervalloDistruggi(Intervallo i);

time_t intervalloInizio(Intervallo i);

time_t intervalloFine(Intervallo i);

Byte intervalloContenutoIn(Intervallo interno, Intervallo esterno);

char *intervalloToString(Intervallo i);

#endif //INTERVALLO_H
