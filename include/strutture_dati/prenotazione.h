/*
 * Autore: Marco Visone
 * Data: 06/05/2025
 */

#ifndef PRENOTAZIONE_H
#define PRENOTAZIONE_H
#include <stdlib.h>
#include <stdio.h>
#include "../include/strutture_dati/intervallo.h"
#include "../include/strutture_dati/utente.h"

typedef struct prenotazione *Prenotazione;

/*
 * Crea una prenotazione.
 * Utilizzata per creare una prenotazione da inserire nel Albero Binario
 * Parametri:
 *     cliente: Il cliente della prenotazione
 *     i: L'intervallo temporale della prenotazione
 *     costo: Il costo totale della prenotazione
 * Ritorna:
 *     Restituisce la prenotazione creata
 */
Prenotazione prenotazione_crea(Utente cliente, Intervallo i, double costo);

/*
 * Distrugge una prenotazione.
 * Libera la memoria allocata per la prenotazione
 * Parametri:
 *     p: Puntatore alla prenotazione da distruggere
 */
void prenotazione_distruggi(Prenotazione p);

/*
 * Ottiene il cliente della prenotazione.
 * Restituisce il cliente associato alla prenotazione specificata
 * Parametri:
 *     p: Puntatore alla prenotazione
 * Ritorna:
 *     Il cliente associato alla prenotazione, NULL se la prenotazione è NULL
 */
Utente prenotazione_ottieni_cliente(Prenotazione p);

/*
 * Ottiene l'intervallo della prenotazione.
 * Restituisce l'intervallo temporale associato alla prenotazione
 * Parametri:
 *     p: Puntatore alla prenotazione
 * Ritorna:
 *     L'intervallo temporale della prenotazione, NULL se la prenotazione è NULL
 */
Intervallo prenotazione_ottieni_intervallo(Prenotazione p);

/*
 * Ottiene il costo della prenotazione.
 * Restituisce il costo totale associato alla prenotazione
 * Parametri:
 *     p: Puntatore alla prenotazione
 * Ritorna:
 *     Il costo della prenotazione, 0 se la prenotazione è 0
 */
double prenotazione_ottieni_costo(Prenotazione p);

/*
 * Imposta il cliente della prenotazione.
 * Modifica il cliente associato alla prenotazione specificata
 * Parametri:
 *     p: Puntatore alla prenotazione
 *     cliente: Nuovo cliente da associare alla prenotazione
 */
void prenotazione_imposta_cliente(Prenotazione p, Utente cliente);

/*
 * Imposta l'intervallo della prenotazione.
 * Modifica l'intervallo temporale associato alla prenotazione
 * Parametri:
 *     p: Puntatore alla prenotazione
 *     i: Nuovo intervallo da associare alla prenotazione
 */
void prenotazione_imposta_intervallo(Prenotazione p, Intervallo i);

/*
 * Imposta il costo della prenotazione.
 * Modifica il costo totale associato alla prenotazione
 * Parametri:
 *     p: Puntatore alla prenotazione
 *     costo: Nuovo costo da associare alla prenotazione
 */
void prenotazione_imposta_costo(Prenotazione p, double costo);

/*
 * Duplica una prenotazione.
 * Crea una copia esatta della prenotazione specificata
 * Parametri:
 *     p: Puntatore alla prenotazione da duplicare
 * Ritorna:
 *     Una nuova prenotazione identica a quella fornita, NULL se la prenotazione è NULL
 */
Prenotazione prenotazione_duplica(Prenotazione p);

#endif //PRENOTAZIONE_H