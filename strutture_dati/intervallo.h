//
// Created by marco on 5/6/25.
//

#ifndef INTERVALLO_H
#define INTERVALLO_H

#include <time.h>
#include "strutture_dati/byte.h"

// Definizione del tipo puntatore a struct intervallo
typedef struct intervallo* Intervallo;

/**
 * @brief Crea un intervallo temporale con valori di inizio e fine
 * @param inizio Timestamp di inizio intervallo
 * @param fine Timestamp di fine intervallo
 * @return Puntatore a Intervallo creato o NULL in caso di errore
 */
Intervallo intervalloCrea(time_t inizio, time_t fine);

/**
 * @brief Libera la memoria allocata per un intervallo
 * @param i Puntatore a Intervallo da distruggere
 */
void intervalloDistruggi(Intervallo i);

/**
 * @brief Restituisce il timestamp di inizio dell'intervallo
 * @param i Puntatore a Intervallo
 * @return Timestamp di inizio o 0 se nullo
 */
time_t intervalloInizio(Intervallo i);

/**
 * @brief Restituisce il timestamp di fine dell'intervallo
 * @param i Puntatore a Intervallo
 * @return Timestamp di fine o 0 se nullo
 */
time_t intervalloFine(Intervallo i);

/**
 * @brief Verifica se un intervallo è contenuto in un altro
 * @param interno Intervallo interno da verificare
 * @param esterno Intervallo esterno in cui verificare la presenza
 * @return 1 se contenuto, 0 altrimenti
 */
Byte intervalloContenutoIn(Intervallo interno, Intervallo esterno);

/**
 * @brief Converte un intervallo in una stringa formattata
 * @param i Puntatore a Intervallo
 * @return Stringa formattata o NULL in caso di errore
 */
char *intervalloToString(Intervallo i);

#endif //INTERVALLO_H