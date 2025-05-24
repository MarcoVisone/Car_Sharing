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

struct intervallo{
    time_t inizio;
    time_t fine;
};

/*
 * Funzione: converti_data_in_time_t
 * ---------------------------------
 * Converte una stringa di data/ora in un valore time_t.
 *
 * Implementazione:
 *    Effettua il parsing della stringa nel formato "dd/mm/yyyy HH:MM"
 *    utilizzando sscanf e costruisce una struttura tm.
 *    La struttura tm viene poi convertita in time_t usando mktime.
 *
 * Parametri:
 *    data: stringa con data/ora da convertire
 *
 * Pre-condizioni:
 *    data non deve essere NULL e deve essere nel formato corretto
 *
 * Post-condizioni:
 *    restituisce il timestamp corrispondente,
 *    oppure -1 in caso di formato non valido
 */
 static time_t converti_data_in_time_t(const char *data){
    struct tm tm = {0};

    // Parsing di giorno/mese/anno e ora:minuto
    if (sscanf(data, "%d/%d/%d %d:%d", &tm.tm_mday, &tm.tm_mon, &tm.tm_year, &tm.tm_hour, &tm.tm_min) != 5) return (time_t)-1;

    tm.tm_year -= 1900;
    tm.tm_mon  -= 1;
    tm.tm_sec   = 0;
    tm.tm_isdst = -1;

    return mktime(&tm);
 }

/*
 * Funzione: crea_intervallo
 * --------------------------
 * Crea un nuovo intervallo temporale.
 *
 * Implementazione:
 *    Verifica che inizio <= fine, alloca memoria per la struttura
 *    e inizializza i campi. Se l'allocazione fallisce o i parametri
 *    non sono validi, restituisce NULL.
 *
 * Parametri:
 *    inizio: timestamp di inizio
 *    fine: timestamp di fine
 *
 * Pre-condizioni:
 *    inizio e fine devono essere timestamp validi
 *    inizio deve essere <= fine
 *
 * Post-condizioni:
 *    restituisce un nuovo Intervallo allocato,
 *    oppure NULL in caso di errore
 *
 * Side-effect:
 *    Alloca memoria per la struttura intervallo
 */
Intervallo crea_intervallo(time_t inizio, time_t fine){
    if(inizio >= fine) return NULL;
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
 * Libera la memoria di un intervallo.
 *
 * Implementazione:
 *    Verifica che il puntatore non sia NULL prima di deallocare.
 *
 * Parametri:
 *    i: intervallo da deallocare
 *
 * Pre-condizioni:
 *    i può essere NULL (in tal caso non fa nulla)
 *
 * Post-condizioni:
 *    la memoria è stata deallocata se i non era NULL
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
 *    Accesso semplice al campo inizio con controllo NULL.
 *
 * Parametri:
 *    i: intervallo da interrogare
 *
 * Pre-condizioni:
 *    i può essere NULL
 *
 * Post-condizioni:
 *    restituisce inizio o 0 se i è NULL
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
 *    Accesso semplice al campo fine con controllo NULL.
 *
 * Parametri:
 *    i: intervallo da interrogare
 *
 * Pre-condizioni:
 *    i può essere NULL
 *
 * Post-condizioni:
 *    restituisce fine o 0 se i è NULL
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
 * Verifica la sovrapposizione tra due intervalli.
 *
 * Implementazione:
 *    Verifica che l'inizio di un intervallo sia minore della fine dell'altro
 *    e viceversa, il che indica sovrapposizione.
 *
 * Parametri:
 *    interno: primo intervallo
 *    esterno: secondo intervallo
 *
 * Pre-condizioni:
 *    interno ed esterno non devono essere NULL
 *
 * Post-condizioni:
 *    restituisce 1 se c'è sovrapposizione, 0 altrimenti o in caso di errori
 */
Byte intervalli_si_sovrappongono(Intervallo interno, Intervallo esterno){
    if((interno == NULL || esterno == NULL)){
        return 0;
    }

    return (interno->inizio < esterno->fine) && (esterno->inizio < interno->fine);
}

/*
 * Funzione: duplica_intervallo
 * ----------------------------
 * Crea una copia dell'intervallo.
 *
 * Implementazione:
 *    Utilizza crea_intervallo per creare una nuova istanza con gli stessi valori.
 *
 * Parametri:
 *    i: intervallo da copiare
 *
 * Pre-condizioni:
 *    i può essere NULL (restituisce NULL in tal caso)
 *
 * Post-condizioni:
 *    restituisce una nuova copia o NULL se i è NULL o in caso di errore
 *
 * Side-effect:
 *    Alloca memoria per la nuova struttura
 */
Intervallo duplica_intervallo(Intervallo i){
    if(i == NULL) return NULL;

    Intervallo copia = crea_intervallo(i->inizio, i->fine);

    return copia;
}

/*
 * Funzione: compara_intervalli
 * ----------------------------
 * Confronta due intervalli per ordinarli.
 *
 * Implementazione:
 *    Confronta i timestamp di inizio dei due intervalli.
 *
 * Parametri:
 *    a: primo intervallo
 *    b: secondo intervallo
 *
 * Pre-condizioni:
 *    a e b non devono essere NULL
 *
 * Post-condizioni:
 *    restituisce:
 *    - -1 se a inizia prima di b
 *    - 1 se a inizia dopo b
 *    - 0 se iniziano insieme o in caso di errori
 */
Byte compara_intervalli(Intervallo a, Intervallo b) {
    if(a == NULL || b == NULL) return 0;
    if (a->inizio < b->inizio) return -1;
    if (a->inizio > b->inizio) return 1;
    return 0;
}

/*
 * Funzione: converti_data_in_intervallo
 * -------------------------------------
 * Converte stringhe di data in un intervallo.
 *
 * Implementazione:
 *    Utilizza converti_data_in_time_t per il parsing delle stringhe
 *    e crea_intervallo per la creazione della struttura.
 *
 * Parametri:
 *    inizio: stringa data di inizio
 *    fine: stringa data di fine
 *
 * Pre-condizioni:
 *    inizio e fine non devono essere NULL e devono essere nel formato corretto
 *
 * Post-condizioni:
 *    restituisce un nuovo Intervallo o NULL in caso di errori
 *
 * Side-effect:
 *    Alloca memoria per la struttura intervallo
 */
Intervallo converti_data_in_intervallo(const char *inizio, const char *fine){
    if(inizio == NULL || fine == NULL) return NULL;

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
 *    Utilizza strftime per formattare i timestamp e snprintf
 *    per combinare le due date in un'unica stringa.
 *
 * Parametri:
 *    i: intervallo da convertire
 *
 * Pre-condizioni:
 *    i può essere NULL (restituisce NULL in tal caso)
 *
 * Post-condizioni:
 *    restituisce una stringa allocata dinamicamente nel formato
 *    "dd/mm/yyyy HH:MM -> dd/mm/yyyy HH:MM",
 *    oppure NULL se i è NULL o in caso di errore
 *
 * Side-effect:
 *    Alloca memoria per la stringa risultante
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
