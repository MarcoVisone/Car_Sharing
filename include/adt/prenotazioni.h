/*
* Autore: Marco Visone
 * Data: 06/05/2025
 */

#ifndef HASHMAP_UTENTI_H
#define HASHMAP_UTENTI_H

#include "../include/strutture_dati/prenotazione.h"

typedef struct node *Prenotazioni;

/*
 * Crea un nuovo albero di prenotazioni.
 * Inizializza una nuova struttura ad albero per la gestione delle prenotazioni
 * Ritorna:
 *     Un puntatore alla radice dell'albero vuoto
 */
Prenotazioni nuovo_prenotazioni();

/*
 * Distrugge l'albero di prenotazioni.
 * Libera tutta la memoria occupata dall'albero e dalle prenotazioni contenute
 * Parametri:
 *     prenotazioni: Puntatore al puntatore alla radice dell'albero da distruggere
 */
void distruggi_prenotazioni(Prenotazioni *prenotazioni);

/*
 * Aggiunge una prenotazione all'albero.
 * Inserisce una nuova prenotazione nella struttura ad albero secondo un criterio di ordinamento
 * Parametri:
 *     prenotazioni: Radice dell'albero corrente
 *     p: Prenotazione da aggiungere
 * Ritorna:
 *     La nuova radice dell'albero aggiornato
 */
Prenotazioni aggiungi_prenotazione(Prenotazioni prenotazioni, Prenotazione p);

/*
 * Controlla l'esistenza di una prenotazione nell'albero.
 * Verifica se una determinata prenotazione è già presente nell'albero
 * Parametri:
 *     prenotazioni: Radice dell'albero delle prenotazioni
 *     p: Prenotazione da cercare
 * Ritorna:
 *     1 se la prenotazione è presente, 0 altrimenti
 */
Byte controlla_prenotazione(Prenotazioni prenotazioni, Prenotazione p);

/*
 * Cancella una prenotazione dall'albero.
 * Rimuove una prenotazione specifica dalla struttura ad albero, mantenendo la struttura bilanciata
 * Parametri:
 *     prenotazioni: Radice dell'albero corrente
 *     p: Prenotazione da rimuovere
 * Ritorna:
 *     La nuova radice dell'albero aggiornato
 */
Prenotazioni cancella_prenotazione(Prenotazioni prenotazioni, Prenotazione p);


#endif //HASHMAP_UTENTI_H
