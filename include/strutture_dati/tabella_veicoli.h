/*
 * Autore: Russo Nello Manuel
 * Data: 10/05/2025
 */

#ifndef HASHMAP_VEICOLI_H
#define HASHMAP_VEICOLI_H

#include "strutture_dati/tabella_hash.h"
#include "modelli/veicolo.h"

// Rinominata TabellaHash in TabellaVeicoli
typedef TabellaHash TabellaVeicoli;

TabellaVeicoli crea_tabella_veicoli(unsigned int grandezza);

void distruggi_tabella_veicoli(TabellaVeicoli tabella_veicoli);

Byte aggiungi_veicolo_in_tabella(TabellaVeicoli tabella_veicoli, Veicolo veicolo);

Veicolo cerca_veicolo_in_tabella(TabellaVeicoli tabella_veicoli, char *targa);

Byte rimuovi_veicolo_in_tabella(TabellaVeicoli tabella_veicoli, char *targa);

#endif //HASHMAP_VEICOLI_H
