//
// Created by sicig on 21/05/2025.
//

#ifndef INTERFACCIA_H
#define INTERFACCIA_H

#include <time.h>
#include "modelli/byte.h"

typedef struct prenotazione *Prenotazione;
typedef struct veicolo *Veicolo;
typedef struct tabella_hash *TabellaUtenti;
typedef struct tabella_hash *TabellaVeicoli;
typedef struct intervallo *Intervallo;
typedef struct utente* Utente;

Byte interfaccia_accesso(TabellaUtenti tabella_utenti);

Byte interfaccia_registrazione(TabellaUtenti tabella_utenti, Byte permesso);

/*
 * Autore: Russo Nello Manuel
 * Data: 22/05/2025
 *
 * Funzione: richiedi_intervallo_prenotazione
 * ------------------------------------------
 *
 * richiede all'utente di inserire un intervallo di tempo per una prenotazione
 *
 * Parametri:
 *    nessuno
 *
 * Pre-condizioni:
 *    nessuna
 *
 * Post-condizioni:
 *    - Restituisce un puntatore a Intervallo se l’input è corretto
 *    - Restituisce NULL se l’utente decide di uscire o se non è stato possibile creare un intervallo valido
 *
 * Side-effect:
 *    - Legge input da tastiera
 *    - Stampa messaggi
 *    - Alloca memoria dinamicamente per l’intervallo restituito (da liberare)
 */
Intervallo richiedi_intervallo_prenotazione();

Veicolo interfaccia_seleziona_veicolo(TabellaVeicoli tabella_veicoli, Intervallo i);

void visualizza_veicoli_disponibili(TabellaVeicoli tabella_veicoli, time_t data_riferimento);

/*
 * Autore: Russo Nello Manuel
 * Data: 24/05/2025
 *
 * Funzione: prenota_veicolo
 * --------------------------
 *
 * gestisce la prenotazione di un veicolo, mostrando una ricevuta
 * con il dettaglio del costo, lo sconto applicato e il motivo dello sconto
 *
 * Parametri:
 *    v: veicolo da prenotare
 *    p: prenotazione da associare al veicolo
 *    percentuale: sconto da applicare (compreso tra 0.0 e 1.0)
 *    motivo: stringa che rappresenta la motivazione dello sconto
 *
 * Pre-condizioni:
 *    v: deve essere diverso da NULL
 *    p: deve essere diverso da NULL
 *    percentuale: deve essere compresa tra 0.0 e 1.0
 *    motivo: deve essere diverso da NULL
 *
 * Post-condizione:
 *    restituisce 1 se la prenotazione è confermata, altrimenti 0
 *
 * Side-effect:
 *    stampa a video, acquisizione input utente, allocazione e deallocazione di memoria
 */
Byte prenota_veicolo(Veicolo v, Prenotazione p, double percentuale, const char *motivo);

void visualizza_storico(Utente utente);

#endif //INTERFACCIA_H
