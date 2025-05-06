//
// Created by marco on 5/6/25.
//
#include "intervallo.h"
#include <stdlib.h>
#include <stdio.h>

#define DIMENSIONE_BUFFER 64
#define DIMENSIONE_BUFFER_FINALE (2 * DIMENSIONE_BUFFER + 5)

struct intervallo{
    time_t inizio;
    time_t fine;
};

Intervallo intervalloCrea(time_t inizio, time_t fine){
    Intervallo i = (Intervallo) malloc(sizeof(struct intervallo));
    if(i == NULL){
        return NULL;
    }
    i->inizio = inizio;
    i->fine = fine;
    return i;
}

void intervalloDistruggi(Intervallo i){
    free(i);
}

time_t intervalloInizio(Intervallo i) {
    if(i == NULL){
        return 0;
    }
    return i->inizio;
}

time_t intervalloFine(Intervallo i){
    if(i == NULL){
        return 0;
    }
    return i->fine;
}

Byte intervalloContenutoIn(Intervallo interno, Intervallo esterno){
    if((interno == NULL || esterno == NULL)){
        return 0;
    }
    return (interno->inizio <= esterno->fine) && (esterno->inizio <= interno->fine);
}

char *intervalloToString(Intervallo i) {
    if (i == NULL) {
        return NULL;
    }
    char buffer1[DIMENSIONE_BUFFER] = {0};
    char buffer2[DIMENSIONE_BUFFER] = {0};
    struct tm temp1, temp2;
    if (localtime_r(&(i->inizio), &temp1) == NULL || localtime_r(&(i->fine), &temp2) == NULL) {
        return NULL;
    }
    strftime(buffer1, sizeof(buffer1), "[%d/%m/%Y %H:%M]", &temp1);
    strftime(buffer2, sizeof(buffer2), "[%d/%m/%Y %H:%M]", &temp2);
    char *buffer_end = malloc(DIMENSIONE_BUFFER_FINALE);
    if (buffer_end == NULL) {
        return NULL;
    }
    snprintf(buffer_end, DIMENSIONE_BUFFER_FINALE, "%s -> %s", buffer1, buffer2);
    return buffer_end;
}
