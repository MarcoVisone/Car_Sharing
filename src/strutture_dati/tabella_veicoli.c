/*
 * Autore: Russo Nello Manuel
 * Data: 10/05/2025
 */

#include "strutture_dati/tabella_veicoli.h"
#include "modelli/veicolo.h"
#include "strutture_dati/tabella_hash.h"
#include <stddef.h>

TabellaVeicoli crea_tabella_veicoli(unsigned int grandezza){
    return nuova_tabella_hash(grandezza);
}

static void distruggi_veicolo_t(void *veicolo){
    Veicolo v = (Veicolo)veicolo;
    distruggi_veicolo(v);
}

void distruggi_tabella_veicoli(TabellaVeicoli tabella_veicoli){
    if(tabella_veicoli == NULL){
        return;
    }

    /* Viene passata la funzione distruggi_veicolo_t per rispettare il parametro
     * che deve restituire un void e avere come parametro un puntatore void
     */
    distruggi_tabella(tabella_veicoli, distruggi_veicolo_t);
}

Byte aggiungi_veicolo_in_tabella(TabellaVeicoli tabella_veicoli, Veicolo veicolo){
    if(tabella_veicoli == NULL){
        return 0;
    }

    return inserisci_in_tabella(tabella_veicoli, ottieni_targa(veicolo), (Veicolo)veicolo);
}

Veicolo cerca_veicolo_in_tabella(TabellaVeicoli tabella_veicoli, char *targa){
    if(tabella_veicoli == NULL){
        return NULL;
    }
    return (Veicolo)cerca_in_tabella(tabella_veicoli, targa);
}

Byte rimuovi_veicolo_in_tabella(TabellaVeicoli tabella_veicoli, char *targa){
    if(tabella_veicoli == NULL){
        return 0;
    }
    return cancella_dalla_tabella(tabella_veicoli, targa, distruggi_veicolo_t);
}
