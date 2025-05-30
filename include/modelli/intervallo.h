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
 *    - inizio deve essere un timestamp valido
 *    - fine deve essere un timestamp valido
 *    - inizio deve essere <= fine
 *
 * Post-condizioni:
 *    restituisce un nuovo Intervallo allocato dinamicamente,
 *    oppure NULL in caso di errore o parametri non validi
 *
 * Ritorna:
 *    un nuovo intervallo o NULL
 *
 * Side-effect:
 *    Alloca memoria per la struttura intervallo
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
 *    i: non deve essere NULL
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    Dealloca memoria se i non è NULL
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
 *    i: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce inizio o 0 se i è NULL
 *
 * Ritorna:
 *    un time_t o 0
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
 *    i: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce fine o 0 se i è NULL
 *
 * Ritorna:
 *    un time_t o 0
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
 *    interno: non deve essere NULL
 *    esterno: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce 1 se c'è sovrapposizione, 0 altrimenti o in caso di errori
 *
 * Ritorna:
 *    un valore di tipo Byte(0 o 1)
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
 *    inizio: non deve essere NULL
 *    fine: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce un nuovo Intervallo o NULL in caso di errori
 *
 * Ritorna:
 *    un nuovo intervallo o NULL
 *
 * Side-effect:
 *    Alloca memoria per la struttura intervallo
 */
Intervallo converti_data_in_intervallo(const char *inizio, const char *fine);

/*
 * Funzione: duplica_intervallo
 * ----------------------------
 * Crea una copia dell'intervallo specificato.
 *
 * Parametri:
 *    i: puntatore all'intervallo da duplicare
 *
 * Pre-condizioni:
 *    i: deve essere diverso da NULL
 *
 * Post-condizioni:
 *    restituisce una nuova copia o NULL se i è NULL o in caso di errore
 *
 * Ritorna:
 *    un intervallo o NULL
 *
 * Side-effect:
 *    Alloca memoria per la nuova struttura
 */
Intervallo duplica_intervallo(Intervallo i);

/*
 * Funzione: compara_intervalli
 * ----------------------------
 * Confronta due intervalli in base al loro tempo di inizio.
 *
 * Parametri:
 *    a: primo intervallo da confrontare
 *    b: secondo intervallo da confrontare
 *
 * Pre-condizioni:
 *    a: deve essere diverso da NULL
 *    b: deve essere diverso da NULL
 *
 * Post-condizioni:
 *    restituisce:
 *    - -1 se a inizia prima di b
 *    - 1 se a inizia dopo b
 *    - 0 se iniziano insieme o in caso di errori
 *
 * Ritorna:
 *    un valore di tipo Byte(0, -1 o 1)
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
 *    i: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce una stringa allocata dinamicamente nel formato
 *    "dd/mm/yyyy HH:MM -> dd/mm/yyyy HH:MM",
 *    oppure NULL se i è NULL o in caso di errore
 *
 * Ritorna:
 *    una stringa o NULL
 *
 * Side-effect:
 *    Alloca memoria per la stringa risultante
 */
char *intervallo_in_stringa(Intervallo i);

#endif // INTERVALLO_H
