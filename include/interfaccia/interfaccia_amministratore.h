#ifndef INTERFACCIA_AMMINISTRATORE_H
#define INTERFACCIA_AMMINISTRATORE_H

#include "modelli/byte.h"

typedef struct veicolo *Veicolo;
typedef struct tabella_hash *TabellaVeicoli;
typedef struct tabella_hash *TabellaUtenti;

/*
 * Autore: Marco Visone
 * Data: 26/05/2025
 *
 * Funzione: storico_noleggi
 * -------------------------
 * Interfaccia che permette all'amministratore di visualizzare lo storico dei noleggi
 * per un utente specifico selezionato dalla lista degli utenti registrati
 *
 * Parametri:
 *    - tabella_utenti: tabella contenente tutti gli utenti registrati
 *    - tabella_veicoli: tabella contenente tutti i veicoli per recuperare le informazioni complete
 *
 * Pre-condizioni:
 *    - tabella_utenti: non deve essere NULL
 *    - tabella_veicoli: non deve essere NULL
 *
 * Post-condizioni:
 *    Restituisce 0 in caso di successo, -1 se non ci sono utenti o in caso di errore
 *
 * Side-effects:
 *    - Input/output su console
 *    - Allocazione e deallocazione dinamica della memoria
 */
Byte storico_noleggi(TabellaUtenti tabella_utenti, TabellaVeicoli tabella_veicoli);

/*
 * Autore: Marco Visone
 * Data: 26/05/2025
 *
 * Funzione: gestione_noleggi
 * --------------------------
 * Visualizza tutti i veicoli e le relative prenotazioni in formato tabellare
 *
 * Parametri:
 *    - tabella_veicoli: tabella contenente tutti i veicoli
 *
 * Pre-condizioni:
 *    - tabella_veicoli: non deve essere NULL
 *
 * Post-condizioni:
 *    Restituisce 1 in caso di successo, -1 in caso di errore
 *
 * Side-effects:
 *    - Output formattato su console
 *    - Allocazione e deallocazione dinamica della memoria
 */
Byte gestione_noleggi(TabellaVeicoli tabella_veicoli);

/*
 * Autore: Marco Visone
 * Data: 26/05/2025
 *
 * Funzione: interfaccia_aggiungi_veicolo
 * --------------------------------------
 * Interfaccia interattiva per l'aggiunta di un nuovo veicolo alla tabella
 *
 * Parametri:
 *    - tabella_veicoli: tabella in cui verificare l'unicità della targa
 *
 * Pre-condizioni:
 *    - tabella_veicoli: non deve essere NULL
 *
 * Post-condizioni:
 *    Restituisce il nuovo veicolo creato se l'operazione ha successo, NULL altrimenti
 *
 * Side-effects:
 *    - Input/output su console
 *    - Allocazione dinamica della memoria per il nuovo veicolo
 *    - Creazione di una nuova struttura prenotazioni
 */
Veicolo interfaccia_aggiungi_veicolo(TabellaVeicoli tabella_veicoli);

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
 * Ritorna:
 *    un valore di tipo Byte(0)
 *
 *
 * Side-effects:
 *    - Input/output su console
 *    - Allocazione e deallocazione dinamica della memoria
 *    - Il veicolo selezionato, se presente e confermato, viene rimosso dalla tabella.
 */
Byte interfaccia_rimuovi_veicolo(TabellaVeicoli tabella_veicoli);

#endif //INTERFACCIA_AMMINISTRATORE_H
