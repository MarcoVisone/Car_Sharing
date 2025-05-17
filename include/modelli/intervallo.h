/*
 * Autore: Marco Visone
 * Data: 06/05/2025
 */

#ifndef INTERVALLO_H
#define INTERVALLO_H

#include <time.h>
#include "modelli/byte.h"

typedef struct intervallo* Intervallo;

/*
 * Funzione: crea_intervallo
 * --------------------------
 * Crea un nuovo intervallo temporale con tempo di inizio e fine specificati.
 *
 * Parametri:
 *    inizio: timestamp di inizio dell'intervallo
 *    fine: timestamp di fine dell'intervallo
 *
 * Pre-condizioni:
 *    inizio deve essere un timestamp valido
 *    fine deve essere un timestamp valido
 *    inizio deve essere <= fine
 *
 * Post-condizione:
 *    restituisce un nuovo intervallo se l'allocazione è andata a buon fine,
 *    altrimenti restituisce NULL
 *
 * Restituisce:
 *    Un nuovo intervallo
 *
 * Side-effect:
 *    Alloca memoria
 */

Intervallo crea_intervallo(time_t inizio, time_t fine);

/*
 * Funzione: distruggi_intervallo
 * -----------------------------
 * Libera la memoria allocata per l'intervallo.
 *
 * Parametri:
 *    i: puntatore all'intervallo da distruggere
 *
 * Pre-condizioni:
 *    i non può essere NULL
 *
 * Post-condizione:
 *    la memoria dell'intervallo viene deallocata
 *
 * Ritorna:
 *    non restituisce niente
 *
 * Side-effect:
 *    Dealloca memoria
 */
void distruggi_intervallo(Intervallo i);

/*
 * Funzione: inizio_intervallo
 * ---------------------------
 * Restituisce il tempo di inizio dell'intervallo specificato.
 *
 * Parametri:
 *    i: puntatore all'intervallo
 *
 * Pre-condizioni:
 *    i non può essere NULL
 *
 * Post-condizione:
 *    ritorna il timestamp di inizio o 0 se l'intervallo è NULL
 *
 * Ritorna:
 *    Il timestamp di inizio
 *
 * Side-effect:
 *    Nessuno
 */
time_t inizio_intervallo(Intervallo i);

/*
 * Funzione: fine_intervallo
 * --------------------------
 * Restituisce il tempo di fine dell'intervallo specificato.
 *
 * Parametri:
 *    i: puntatore all'intervallo
 *
 * Pre-condizioni:
 *    i non può essere NULL
 *
 * Post-condizione:
 *    ritorna il timestamp di fine o 0 se l'intervallo è NULL
 *
 * Ritorna:
 *    Il timestamp di fine
 *
 * Side-effect:
 *    Nessuno
 */
time_t fine_intervallo(Intervallo i);

/*
 * Funzione: intervalli_si_sovrappongono
 * -------------------------------------
 * Controlla se due intervalli temporali si sovrappongono.
 *
 * Parametri:
 *    interno: primo intervallo da controllare
 *    esterno: secondo intervallo da controllare
 *
 * Pre-condizioni:
 *    entrambi gli intervalli non possono essere NULL
 *
 * Post-condizione:
 *    ritorna 1 se gli intervalli si sovrappongono, 0 altrimenti
 *
 * Ritorna:
 *    1 se c'è sovrapposizione, 0 altrimenti
 *
 * Side-effect:
 *    Nessuno
 */
Byte intervalli_si_sovrappongono(Intervallo interno, Intervallo esterno);

/*
 * Funzione: converti_data_in_intervallo
 * -------------------------------------
 * Converte due stringhe di data in un intervallo temporale.
 *
 * Parametri:
 *    inizio: stringa con data/ora di inizio (formato "dd/mm/yyyy HH:MM")
 *    fine: stringa con data/ora di fine (formato "dd/mm/yyyy HH:MM")
 *
 * Pre-condizioni:
 *    Entrambe le stringhe devono essere nel formato corretto
 *    e devono essere non NULL
 *
 * Post-condizione:
 *    ritorna un nuovo intervallo o NULL in caso di errore
 *
 * Ritorna:
 *    Un nuovo intervallo
 *
 * Side-effect:
 *    Alloca memoria
 */
Intervallo converti_data_in_intervallo(const char *inizio, const char *fine);

/*
 * Funzione: duplica_intervallo
 * -----------------------------
 * Crea una copia dell'intervallo specificato.
 *
 * Parametri:
 *    i: puntatore all'intervallo da duplicare
 *
 * Pre-condizioni:
 *    i non può essere NULL
 *
 * Post-condizione:
 *    ritorna una copia dell'intervallo o NULL se p è NULL
 *
 * Ritorna:
 *    Un nuovo intervallo identico a quello passato
 *
 * Side-effect:
 *    Alloca memoria
 */
Intervallo duplica_intervallo(Intervallo i);

/*
 * Funzione: compara_intervalli
 * -----------------------------
 * Confronta due intervalli in base al loro tempo di inizio.
 *
 * Parametri:
 *    a: primo intervallo da confrontare
 *    b: secondo intervallo da confrontare
 *
 * Pre-condizioni:
 *    a e b non devono essere NULL
 *
 * Post-condizione:
 *    ritorna -1, 0 o 1 in base all'ordinamento
 *
 * Ritorna:
 *    -1 se a inizia prima di b, 1 se a inizia dopo b, 0 se iniziano insieme
 *
 * Side-effect:
 *    Nessuno
 */
Byte compara_intervalli(Intervallo a, Intervallo b);

/*
 * Funzione: intervallo_in_stringa
 * -------------------------------
 * Crea una rappresentazione testuale dell'intervallo.
 *
 * Parametri:
 *    i: puntatore all'intervallo da convertire
 *
 * Pre-condizioni:
 *    i non può essere NULL
 *
 * Post-condizione:
 *    ritorna una stringa formattata o NULL se i è NULL
 *
 * Ritorna:
 *    Stringa nel formato "dd/mm/yyyy HH:MM -> dd/mm/yyyy HH:MM"
 *
 * Side-effect:
 *    Alloca memoria
 */
char *intervallo_in_stringa(Intervallo i);

#endif // INTERVALLO_H
