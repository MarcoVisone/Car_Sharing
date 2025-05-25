/*
 * Autore: Russo Nello Manuel
 * Data: 25/05/2025
 */

#ifndef INTERFACCIA_AMMINISTRATORE_H
#define INTERFACCIA_AMMINISTRATORE_H

#include "modelli/byte.h"

typedef struct tabella_hash *TabellaVeicoli;
typedef struct tabella_hash *TabellaUtenti;

Byte storico_noleggi(TabellaUtenti tabella_utenti, TabellaVeicoli tabella_veicoli);

#endif //INTERFACCIA_AMMINISTRATORE_H