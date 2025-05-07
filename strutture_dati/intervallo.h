//
// Created by marco on 5/6/25.
//

#ifndef INTERVALLO_H
#define INTERVALLO_H

#include <time.h>
#include "byte.h"

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
 * @brief Verifica se gli intervalli si sovrappongono
 * @param interno Intervallo interno da verificare
 * @param esterno Intervallo esterno in cui verificare la presenza
 * @return 1 se contenuto, 0 altrimenti
 */
Byte intervalliSiSovrappongono(Intervallo interno, Intervallo esterno);

/**
 * @brief Rende anno, mese, giorno, ora e minuti in un valore time_t
 * @param anno  Anno
 * @param mese  Mese
 * @param giorno Giorno del mese
 * @param ora   Ora
 * @param minuti Minuti
 * @return      Timestamp corrispondente o -1 in caso di errore
 */
time_t convertiDataToTime(int anno, int mese, int giorno, int ora, int minuti);

/**
 * @brief Converte un intervallo in una stringa formattata
 * @param i Puntatore a Intervallo
 * @return Stringa formattata o NULL in caso di errore
 */
char *intervalloToString(Intervallo i);

#endif //INTERVALLO_H