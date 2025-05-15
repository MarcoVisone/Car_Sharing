/*
 * Autore: Marco Visone
 * Data: 06/05/2025
 */

#include "modelli/intervallo.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define DIMENSIONE_BUFFER 25
#define DIMENSIONE_BUFFER_FINALE (2 * DIMENSIONE_BUFFER + 5)

static time_t converti_data_in_time_t(const char *data);

struct intervallo{
    time_t inizio;
    time_t fine;
};

/*
 * Funzione: crea_intervallo
 * --------------------------
 * Crea un intervallo tra due timestamp specificati.
 *
 * Implementazione:
 * Alloca memoria per la struttura intervallo e imposta i valori.
 *
 * Parametri:
 *    inizio: timestamp di inizio
 *    fine: timestamp di fine
 *
 * Pre-condizioni:
 *    inizio e fine devono essere timestamp validi
 *    inizio <= fine
 *
 * Post-condizione:
 *    ritorna un intervallo valido o NULL in caso di errore di allocazione
 *
 * Ritorna:
 *    Intervallo creato
 *
 * Side-effect:
 *    Alloca memoria
 */
Intervallo crea_intervallo(time_t inizio, time_t fine){
    Intervallo i = (Intervallo) malloc(sizeof(struct intervallo));
    if(i == NULL){
        return NULL;
    }

    i->inizio = inizio;
    i->fine = fine;

    return i;
}

/*
 * Funzione: distruggi_intervallo
 * -----------------------------
 * Dealloca un intervallo.
 *
 * Implementazione:
 * Se il puntatore è non NULL, libera la memoria.
 *
 * Parametri:
 *    i: intervallo da distruggere
 *
 * Pre-condizioni:
 *    i può essere NULL
 *
 * Post-condizione:
 *    la memoria è liberata se i non è NULL
 *
 * Ritorna:
 *    non restituisce niente
 *
 * Side-effect:
 *    Dealloca memoria
 */
void distruggi_intervallo(Intervallo i){
    if(i == NULL){
		return;
	}

	free(i);
}

/*
 * Funzione: inizio_intervallo
 * ---------------------------
 * Restituisce il timestamp di inizio.
 *
 * Implementazione:
 * Se i è NULL ritorna 0, altrimenti il campo inizio.
 *
 * Parametri:
 *    i: intervallo
 *
 * Pre-condizioni:
 *    i può essere NULL
 *
 * Post-condizione:
 *    restituisce il campo inizio o 0
 *
 * Ritorna:
 *    time_t del campo inizio
 *
 * Side-effect:
 *    Nessuno
 */
time_t inizio_intervallo(Intervallo i) {
    if(i == NULL){
        return 0;
    }

    return i->inizio;
}

/*
 * Funzione: fine_intervallo
 * --------------------------
 * Restituisce il timestamp di fine.
 *
 * Implementazione:
 * Se i è NULL ritorna 0, altrimenti il campo fine.
 *
 * Parametri:
 *    i: intervallo
 *
 * Pre-condizioni:
 *    i può essere NULL
 *
 * Post-condizione:
 *    restituisce il campo fine o 0
 *
 * Ritorna:
 *    time_t del campo fine
 *
 * Side-effect:
 *    Nessuno
 */
time_t fine_intervallo(Intervallo i){
    if(i == NULL){
        return 0;
    }

    return i->fine;
}

/*
 * Funzione: intervalli_si_sovrappongono
 * -------------------------------------
 * Verifica se due intervalli si sovrappongono.
 *
 * Implementazione:
 * Usa confronto tra inizio/fine dei due intervalli.
 *
 * Parametri:
 *    interno: primo intervallo
 *    esterno: secondo intervallo
 *
 * Pre-condizioni:
 *    interno ed esterno possono essere NULL
 *
 * Post-condizione:
 *    ritorna 1 se si sovrappongono, 0 altrimenti
 *
 * Ritorna:
 *    Byte booleano (1 o 0)
 *
 * Side-effect:
 *    Nessuno
 */
Byte intervalli_si_sovrappongono(Intervallo interno, Intervallo esterno){
    if((interno == NULL || esterno == NULL)){
        return 0;
    }

    return (interno->inizio <= esterno->fine) && (esterno->inizio <= interno->fine);
}

/*
 * Funzione: duplica_intervallo
 * -----------------------------
 * Duplica un intervallo.
 *
 * Implementazione:
 * Crea un nuovo intervallo copiando i valori di quello dato.
 *
 * Parametri:
 *    p: intervallo da duplicare
 *
 * Pre-condizioni:
 *    p può essere NULL
 *
 * Post-condizione:
 *    ritorna una copia o NULL
 *
 * Ritorna:
 *    Copia dell'intervallo
 *
 * Side-effect:
 *    Alloca memoria
 */
Intervallo duplica_intervallo(Intervallo p){
    if(p == NULL) return NULL;

    Intervallo copia = crea_intervallo(p->inizio, p->fine);

    return copia;
}

/*
 * Funzione: compara_intervalli
 * -----------------------------
 * Confronta due intervalli in base all'inizio.
 *
 * Implementazione:
 * Restituisce -1, 0 o 1 in base all’ordinamento dei timestamp.
 *
 * Parametri:
 *    a: primo intervallo
 *    b: secondo intervallo
 *
 * Pre-condizioni:
 *    a e b non devono essere NULL
 *
 * Post-condizione:
 *    ritorna un valore intero in base alla comparazione
 *
 * Ritorna:
 *    -1, 0, 1
 *
 * Side-effect:
 *    Nessuno
 */
Byte compara_intervalli(Intervallo a, Intervallo b) {
    if (a->inizio < b->inizio) return -1;
    if (a->inizio > b->inizio) return 1;
    return 0;
}

/*
 * Funzione: converti_data_in_time_t
 * ---------------------------------
 * Converte una stringa di data/ora nel formato "dd/mm/yyyy HH:MM" in un valore time_t.
 *
 * Implementazione:
 * Usa sscanf per estrarre i valori da giorno, mese, anno, ora e minuti.
 * Adatta i valori secondo la struttura tm e usa mktime per ottenere il time_t.
 *
 * Parametri:
 *    data: stringa con data/ora da convertire (formato "dd/mm/yyyy HH:MM")
 *
 * Pre-condizioni:
 *    data non deve essere NULL
 *    data deve rispettare il formato "dd/mm/yyyy HH:MM"
 *
 * Post-condizione:
 *    ritorna un valore time_t valido o -1 in caso di formato errato
 *
 * Ritorna:
 *    Valore time_t rappresentante la data/ora fornita
 *
 * Side-effect:
 *    Nessuno
 */
static time_t converti_data_in_time_t(const char *data){
    struct tm tm = {0};

    if(sscanf(data, "%d/%d/%d %d:%d",
              &tm.tm_mday, &tm.tm_mon, &tm.tm_year,
              &tm.tm_hour, &tm.tm_min) != 5)
        return -1;

    tm.tm_year -= 1900;
    tm.tm_mon -= 1;

    return mktime(&tm);
}

/*
 * Funzione: converti_data_in_intervallo
 * -------------------------------------
 * Converte due stringhe in un intervallo.
 *
 * Implementazione:
 * Effettua il parsing delle date e crea un intervallo.
 *
 * Parametri:
 *    inizio: stringa data di inizio
 *    fine: stringa data di fine
 *
 * Pre-condizioni:
 *    stringhe in formato "dd/mm/yyyy HH:MM"
 *
 * Post-condizione:
 *    ritorna intervallo o NULL
 *
 * Ritorna:
 *    Intervallo allocato
 *
 * Side-effect:
 *    Alloca memoria
 */
Intervallo converti_data_in_intervallo(const char *inizio, const char *fine){
    time_t t_inizio = converti_data_in_time_t(inizio);
    time_t t_fine = converti_data_in_time_t(fine);

    if(t_inizio == -1 || t_fine == -1) return NULL;

    Intervallo intervallo = crea_intervallo(t_inizio, t_fine);

    return intervallo;
}

/*
 * Funzione: intervallo_in_stringa
 * -------------------------------
 * Converte un intervallo in stringa leggibile.
 *
 * Implementazione:
 * Format del tipo "gg/mm/aaaa hh:mm -> gg/mm/aaaa hh:mm"
 *
 * Parametri:
 *    i: intervallo
 *
 * Pre-condizioni:
 *    i può essere NULL
 *
 * Post-condizione:
 *    ritorna stringa o NULL
 *
 * Ritorna:
 *    Stringa formattata
 *
 * Side-effect:
 *    Alloca memoria
 */
char *intervallo_in_stringa(Intervallo i) {
    if (i == NULL) {
        return NULL;
    }

    char buffer1[DIMENSIONE_BUFFER] = {0};
    char buffer2[DIMENSIONE_BUFFER] = {0};
    char *buffer_end = malloc(sizeof(char) * DIMENSIONE_BUFFER_FINALE);
    if (buffer_end == NULL) {
        return NULL;
    }

    strftime(buffer1, sizeof(buffer1), "%d/%m/%Y %H:%M", localtime(&(i->inizio)));
    strftime(buffer2, sizeof(buffer2), "%d/%m/%Y %H:%M", localtime(&(i->fine)));

    snprintf(buffer_end, DIMENSIONE_BUFFER_FINALE, "%s -> %s", buffer1, buffer2);

    return buffer_end;
}
