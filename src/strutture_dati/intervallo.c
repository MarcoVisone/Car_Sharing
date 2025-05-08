/*
 * Autore: Marco Visone
 * Data: 06/05/2025
 */

#include "../../include/strutture_dati/intervallo.h"
#include <stdlib.h>
#include <stdio.h>

#define DIMENSIONE_BUFFER 64
#define DIMENSIONE_BUFFER_FINALE (2 * DIMENSIONE_BUFFER + 5)

struct intervallo{
    time_t inizio;
    time_t fine;
};

Intervallo intervallo_crea(time_t inizio, time_t fine){
    Intervallo i = (Intervallo) malloc(sizeof(struct intervallo));
    if(i == NULL){
        return NULL;
    }
    i->inizio = inizio;
    i->fine = fine;
    return i;
}

void intervallo_distruggi(Intervallo i){
    free(i);
}

time_t intervallo_inizio(Intervallo i) {
    if(i == NULL){
        return 0;
    }
    return i->inizio;
}

time_t intervallo_fine(Intervallo i){
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

time_t converti_data_in_time(int anno, int mese, int giorno, int ora, int minuti){
    struct tm temp = {0};

    temp.tm_year = anno - 1900;
    temp.tm_mon = mese - 1;
    temp.tm_mday = giorno;
    temp.tm_hour = ora;
    temp.tm_min = minuti;
    temp.tm_sec = 0;
    temp.tm_isdst = -1;

    return mktime(&temp);
}

char *intervallo_in_stringa(Intervallo i) {
    if (i == NULL) {
        return NULL;
    }
    char buffer1[DIMENSIONE_BUFFER] = {0};
    char buffer2[DIMENSIONE_BUFFER] = {0};
    struct tm temp1, temp2;
    if (localtime_r(&(i->inizio), &temp1) == NULL || localtime_r(&(i->fine), &temp2) == NULL) {
        return NULL;
    }
    strftime(buffer1, sizeof(buffer1), "%d/%m/%Y %H:%M", &temp1);
    strftime(buffer2, sizeof(buffer2), "%d/%m/%Y %H:%M", &temp2);
    char *buffer_end = malloc(DIMENSIONE_BUFFER_FINALE);
    if (buffer_end == NULL) {
        return NULL;
    }
    snprintf(buffer_end, DIMENSIONE_BUFFER_FINALE, "%s -> %s", buffer1, buffer2);
    return buffer_end;
}