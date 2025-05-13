/*
 * Autore: Marco Visone
 * Data: 06/05/2025
 */

#include "modelli/intervallo.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define DIMENSIONE_BUFFER 64
#define DIMENSIONE_BUFFER_FINALE (2 * DIMENSIONE_BUFFER + 5)

static time_t converti_data_in_time_t(const char *data);

struct intervallo{
    time_t inizio;
    time_t fine;
};

Intervallo crea_intervallo(time_t inizio, time_t fine){
    Intervallo i = (Intervallo) malloc(sizeof(struct intervallo));
    if(i == NULL){
        return NULL;
    }

    i->inizio = inizio;
    i->fine = fine;

    return i;
}

void distruggi_intervallo(Intervallo i){
    if(i == NULL){
		return;
	}

	free(i);
}

time_t inizio_intervallo(Intervallo i) {
    if(i == NULL){
        return 0;
    }

    return i->inizio;
}

time_t fine_intervallo(Intervallo i){
    if(i == NULL){
        return 0;
    }

    return i->fine;
}

Byte intervalli_si_sovrappongono(Intervallo interno, Intervallo esterno){
    if((interno == NULL || esterno == NULL)){
        return 0;
    }

    return (interno->inizio <= esterno->fine) && (esterno->inizio <= interno->fine);
}

Intervallo duplica_intervallo(Intervallo p){
    if(p == NULL) return NULL;

    Intervallo copia = crea_intervallo(p->inizio, p->fine);

    return copia;
}

Byte compara_intervalli(Intervallo a, Intervallo b) {
    if (a->inizio < b->inizio) return -1;
    if (a->inizio > b->inizio) return 1;
    return 0;
}

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

Intervallo converti_data_in_intervallo(const char *inizio, const char *fine){
    time_t t_inizio = converti_data_in_time_t(inizio);
    time_t t_fine = converti_data_in_time_t(fine);

    if(t_inizio == -1 || t_fine == -1) return NULL;

    Intervallo intervallo = crea_intervallo(t_inizio, t_fine);

    return intervallo;
}

char *intervallo_in_stringa(Intervallo i) {
    if (i == NULL) {
        return NULL;
    }

    char buffer1[DIMENSIONE_BUFFER] = {0};
    char buffer2[DIMENSIONE_BUFFER] = {0};
    char *buffer_end = malloc(DIMENSIONE_BUFFER_FINALE);
    if (buffer_end == NULL) {
        return NULL;
    }

    struct tm *ptr1 = localtime(&(i->inizio));
    struct tm *ptr2 = localtime(&(i->fine));

    if (ptr1 == NULL || ptr2 == NULL) {
        free(buffer_end);
        return NULL;
    }

    struct tm temp1 = *ptr1;
    struct tm temp2 = *ptr2;

    strftime(buffer1, sizeof(buffer1), "%d/%m/%Y %H:%M", &temp1);
    strftime(buffer2, sizeof(buffer2), "%d/%m/%Y %H:%M", &temp2);

    snprintf(buffer_end, DIMENSIONE_BUFFER_FINALE, "%s -> %s", buffer1, buffer2);

    return buffer_end;
}
