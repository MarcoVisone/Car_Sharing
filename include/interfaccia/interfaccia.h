//
// Created by sicig on 21/05/2025.
//

#ifndef INTERFACCIA_H
#define INTERFACCIA_H

#include "modelli/byte.h"

typedef struct veicolo *Veicolo;
typedef struct tabella_hash *TabellaUtenti;
typedef struct tabella_hash *TabellaVeicoli;
typedef struct intervallo *Intervallo;

Byte interfaccia_accesso(TabellaUtenti tabella_utenti);

Byte interfaccia_registrazione(TabellaUtenti tabella_utenti, Byte permesso);

Intervallo richiedi_intervallo_prenotazione();

Veicolo interfaccia_seleziona_veicolo(TabellaVeicoli tabella_veicoli, Intervallo i);

void visualizza_veicoli_disponibili(TabellaVeicoli tabella_veicoli);

void prenota_veicolo(Veicolo v, Prenotazione p, double percentuale, const char *motivo);

#endif //INTERFACCIA_H
