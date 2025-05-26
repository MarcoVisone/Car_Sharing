/*
 * Autore: Russo Nello Manuel
 * Data: 25/05/2025
 */

#ifndef INTERFACCIA_AMMINISTRATORE_H
#define INTERFACCIA_AMMINISTRATORE_H

#include "modelli/byte.h"

typedef struct veicolo *Veicolo;
typedef struct tabella_hash *TabellaVeicoli;
typedef struct tabella_hash *TabellaUtenti;

Byte storico_noleggi(TabellaUtenti tabella_utenti, TabellaVeicoli tabella_veicoli);

Veicolo interfaccia_aggiungi_veicolo();

Byte interfaccia_rimuovi_veicolo(TabellaVeicoli tabella_veicoli);

void visualizza_veicoli(TabellaVeicoli tabella_veicoli);

#endif //INTERFACCIA_AMMINISTRATORE_H
