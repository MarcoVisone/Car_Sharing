/*
 * Autore: Russo Nello Manuel
 * Data: 10/05/2025
 */

#include <stddef.h>
#include "strutture_dati/prenotazioni.h"
#include "modelli/veicolo.h"
#include "strutture_dati/tabella_hash.h"
#include "strutture_dati/tabella_veicoli.h"
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

Veicolo *ottieni_veicoli_disponibili(TabellaVeicoli tabella_veicoli, Intervallo intervallo, unsigned int *dimensione){
    Veicolo *vettore = (Veicolo *)ottieni_vettore(tabella_veicoli, dimensione);
    if(vettore == NULL){
        return NULL;
    }

    for(unsigned int i = 0; i < *dimensione; i++){
        if(controlla_prenotazione(ottieni_prenotazioni(vettore[i]), intervallo) == OCCUPATO){
            vettore[i] = NULL;
        }
    }
    return vettore;
}
