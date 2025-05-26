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

Byte gestione_noleggi(TabellaVeicoli tabella_veicoli);

Veicolo interfaccia_aggiungi_veicolo();

/*
 * Autore: Russo Nello Manuel
 * Data: 26/05/2025
 *
 * Funzione: interfaccia_rimuovi_veicolo
 * -------------------------------------
 * Interfaccia testuale che consente all’utente di rimuovere un veicolo dalla tabella
 *
 * Parametri:
 *    - tabella_veicoli: la tabella veicoli
 *
 * Pre-condizioni:
 *    tabella_veicoli: non deve essere NULL
 *
 * Post-condizioni:
 * 	  restituisce 0 in caso di uscita o fallimento nella rimozione.
 *
 * Side-effects:
 *    - Input/output su console
 *    - Allocazione e deallocazione dinamica della memoria
 *    - Il veicolo selezionato, se presente e confermato, viene rimosso dalla tabella.
 */
Byte interfaccia_rimuovi_veicolo(TabellaVeicoli tabella_veicoli);

void visualizza_veicoli(TabellaVeicoli tabella_veicoli);

#endif //INTERFACCIA_AMMINISTRATORE_H
