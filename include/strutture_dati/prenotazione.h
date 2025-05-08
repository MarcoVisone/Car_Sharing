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
Prenotazione crea_prenotazione(Utente cliente, Intervallo i, double costo);

/*
 * Distrugge una prenotazione.
 * Libera la memoria allocata per la prenotazione
 * Parametri:
 *     p: Puntatore alla prenotazione da distruggere
 */
void distruggi_prenotazione(Prenotazione p);

/*
 * Ottiene il cliente della prenotazione.
 * Restituisce il cliente associato alla prenotazione specificata
 * Parametri:
 *     p: Puntatore alla prenotazione
 * Ritorna:
 *     Il cliente associato alla prenotazione, NULL se la prenotazione è NULL
 */
Utente ottieni_cliente_prenotazione(Prenotazione p);

/*
 * Ottiene l'intervallo della prenotazione.
 * Restituisce l'intervallo temporale associato alla prenotazione
 * Parametri:
 *     p: Puntatore alla prenotazione
 * Ritorna:
 *     L'intervallo temporale della prenotazione, NULL se la prenotazione è NULL
 */
Intervallo ottieni_intervallo_prenotazione(Prenotazione p);

/*
 * Ottiene il costo della prenotazione.
 * Restituisce il costo totale associato alla prenotazione
 * Parametri:
 *     p: Puntatore alla prenotazione
 * Ritorna:
 *     Il costo della prenotazione, 0 se la prenotazione è 0
 */
double ottieni_costo_prenotazione(Prenotazione p);

/*
 * Imposta il cliente della prenotazione.
 * Modifica il cliente associato alla prenotazione specificata
 * Parametri:
 *     p: Puntatore alla prenotazione
 *     cliente: Nuovo cliente da associare alla prenotazione
 */
void imposta_cliente_prenotazione(Prenotazione p, Utente cliente);

/*
 * Imposta l'intervallo della prenotazione.
 * Modifica l'intervallo temporale associato alla prenotazione
 * Parametri:
 *     p: Puntatore alla prenotazione
 *     i: Nuovo intervallo da associare alla prenotazione
 */
void imposta_intervallo_prenotazione(Prenotazione p, Intervallo i);

/*
 * Imposta il costo della prenotazione.
 * Modifica il costo totale associato alla prenotazione
 * Parametri:
 *     p: Puntatore alla prenotazione
 *     costo: Nuovo costo da associare alla prenotazione
 */
void imposta_costo_prenotazione(Prenotazione p, double costo);

/*
 * Duplica una prenotazione.
 * Crea una copia esatta della prenotazione specificata
 * Parametri:
 *     p: Puntatore alla prenotazione da duplicare
 * Ritorna:
 *     Una nuova prenotazione identica a quella fornita, NULL se la prenotazione è NULL
 */
Prenotazione duplica_prenotazione(Prenotazione p);

/*
 * Converte i valori di Prenotazione in stringa
 * Per facilitare la stampa nel'interfaccia
 * Parametri:
 *     p: Puntatore alla prenotazione da rendere stringa
 * Ritorna:
 *     Una stringa contenente tutti i valori di prenotazione formattati
 */
char* prenotazione_in_stringa(Prenotazione p);

#endif //PRENOTAZIONE_H