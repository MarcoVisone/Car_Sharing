/*
 * Autore: Marco Visone
 * Data: 06/05/2025
 */

#ifndef INTERVALLO_H
#define INTERVALLO_H

#include <time.h>
#include "../include/strutture_dati/byte.h"

typedef struct intervallo* Intervallo;

/*
 * Crea un nuovo intervallo.
 * Utilizzata per creare un intervallo temporale con tempo di inizio e fine specificati
 * Parametri:
 *     inizio: Il timestamp di inizio dell'intervallo
 *     fine: Il timestamp di fine dell'intervallo
 * Ritorna:
 *     Restituisce l'intervallo creato
 */
Intervallo intervallo_crea(time_t inizio, time_t fine);

/*
 * Distrugge un intervallo.
 * Libera la memoria allocata per l'intervallo
 * Parametri:
 *     i: Puntatore all'intervallo da distruggere
 */
void intervallo_distruggi(Intervallo i);

/*
 * Ottiene il timestamp di inizio dell'intervallo.
 * Restituisce il tempo di inizio dell'intervallo specificato
 * Parametri:
 *     i: Puntatore all'intervallo
 * Ritorna:
 *     Il timestamp di inizio, 0 se l'intervallo è NULL
 */
time_t intervallo_inizio(Intervallo i);

/*
 * Ottiene il timestamp di fine dell'intervallo.
 * Restituisce il tempo di fine dell'intervallo specificato
 * Parametri:
 *     i: Puntatore all'intervallo
 * Ritorna:
 *     Il timestamp di fine, 0 se l'intervallo è NULL
 */
time_t intervallo_fine(Intervallo i);

/*
 * Verifica la sovrapposizione tra due intervalli.
 * Controlla se due intervalli temporali si sovrappongono
 * Parametri:
 *     interno: Primo intervallo da controllare
 *     esterno: Secondo intervallo da controllare
 * Ritorna:
 *     1 se gli intervalli si sovrappongono, 0 altrimenti
 */
Byte intervalli_si_sovrappongono(Intervallo interno, Intervallo esterno);

/*
 * Converte una data in timestamp.
 * Converte una data specificata in formato numerico in un timestamp time_t
 * Parametri:
 *     anno: Anno della data
 *     mese: Mese della data (1-12)
 *     giorno: Giorno del mese
 *     ora: Ora del giorno (0-23)
 *     minuti: Minuti (0-59)
 * Ritorna:
 *     Il timestamp corrispondente alla data specificata
 */
time_t converti_data_in_time(int anno, int mese, int giorno, int ora, int minuti);

/*
 * Converte un intervallo in stringa.
 * Crea una rappresentazione testuale dell'intervallo nel formato "dd/mm/yyyy HH:MM -> dd/mm/yyyy HH:MM"
 * Parametri:
 *     i: Puntatore all'intervallo da convertire
 * Ritorna:
 *     Una stringa rappresentante l'intervallo, NULL in caso di errore
 */
char *intervallo_in_stringa(Intervallo i);

#endif //INTERVALLO_H