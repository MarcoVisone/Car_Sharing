/*
 * Autore: Marco Visone
 * Data: 06/05/2025
 */

#ifndef PRENOTAZIONI_H
#define PRENOTAZIONI_H
#define OK 0
#define OCCUPATO 1

#include "modelli/byte.h"
typedef struct intervallo *Intervallo;
typedef struct prenotazione *Prenotazione;
typedef struct node *Prenotazioni;

/*
 * Crea un nuovo albero di prenotazioni.
 * Inizializza una nuova struttura ad albero per la gestione delle prenotazioni
 * Ritorna:
 *     Un puntatore alla radice dell'albero vuoto
 */
Prenotazioni crea_prenotazioni();

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
 * Controlla se la prenotazione è disponibile.
 * Parametri:
 *     prenotazioni: Radice dell'albero delle prenotazioni
 *     i: Intervallo da cercare
 * Ritorna:
 *     OCCUPATO se l'intervallo è occupato, OK altrimenti
 */
Byte controlla_prenotazione(Prenotazioni prenotazioni, Intervallo i);

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

Prenotazione *prenotazioni_in_vettore(Prenotazioni prenotazioni, int *size);

Prenotazione *ottieni_vettore_prenotazioni(Prenotazioni prenotazioni, unsigned int *size);

#endif //PRENOTAZIONI_H
