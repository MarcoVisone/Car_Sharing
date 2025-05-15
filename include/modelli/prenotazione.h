/*
 * Autore: Marco Visone
 * Data: 06/05/2025
 */

#ifndef PRENOTAZIONE_H
#define PRENOTAZIONE_H

#include "modelli/intervallo.h"

typedef struct prenotazione *Prenotazione;

/*
 * Funzione: crea_prenotazione
 * ---------------------------
 * Crea una nuova prenotazione.
 *
 * Parametri:
 *    cliente: nome del cliente
 *    i: intervallo temporale della prenotazione
 *    costo: costo della prenotazione
 *
 * Pre-condizioni:
 *    cliente deve essere una stringa valida
 *    i deve essere un intervallo valido (può essere NULL)
 *
 * Post-condizione:
 *    ritorna una nuova prenotazione o NULL in caso di errore
 *
 * Ritorna:
 *    Prenotazione creata
 */
Prenotazione crea_prenotazione(char *cliente, Intervallo i, double costo);

/*
 * Funzione: distruggi_prenotazione
 * -------------------------------
 * Libera la memoria allocata per la prenotazione.
 *
 * Parametri:
 *    p: puntatore alla prenotazione da distruggere
 *
 * Pre-condizioni:
 *    p può essere NULL
 *
 * Post-condizione:
 *    la memoria della prenotazione viene deallocata
 */
void distruggi_prenotazione(Prenotazione p);

/*
 * Funzione: ottieni_cliente_prenotazione
 * -------------------------------------
 * Restituisce il nome del cliente della prenotazione.
 *
 * Parametri:
 *    p: puntatore alla prenotazione
 *
 * Pre-condizioni:
 *    p può essere NULL
 *
 * Post-condizione:
 *    ritorna il nome del cliente o NULL se p è NULL
 *
 * Ritorna:
 *    Nome del cliente
 */
char *ottieni_cliente_prenotazione(Prenotazione p);

/*
 * Funzione: ottieni_intervallo_prenotazione
 * ----------------------------------------
 * Restituisce l'intervallo della prenotazione.
 *
 * Parametri:
 *    p: puntatore alla prenotazione
 *
 * Pre-condizioni:
 *    p può essere NULL
 *
 * Post-condizione:
 *    ritorna l'intervallo o NULL se p è NULL
 *
 * Ritorna:
 *    Intervallo temporale
 */
Intervallo ottieni_intervallo_prenotazione(Prenotazione p);

/*
 * Funzione: ottieni_costo_prenotazione
 * -----------------------------------
 * Restituisce il costo della prenotazione.
 *
 * Parametri:
 *    p: puntatore alla prenotazione
 *
 * Pre-condizioni:
 *    p può essere NULL
 *
 * Post-condizione:
 *    ritorna il costo o -1 se p è NULL
 *
 * Ritorna:
 *    Costo della prenotazione
 */
double ottieni_costo_prenotazione(Prenotazione p);

/*
 * Funzione: imposta_cliente_prenotazione
 * -------------------------------------
 * Modifica il nome del cliente associato alla prenotazione.
 *
 * Parametri:
 *    p: puntatore alla prenotazione
 *    cliente: nuovo nome del cliente
 *
 * Pre-condizioni:
 *    p deve essere non NULL
 *    cliente deve essere una stringa valida
 *
 * Post-condizione:
 *    aggiorna il nome del cliente
 */
void imposta_cliente_prenotazione(Prenotazione p, char *cliente);

/*
 * Funzione: imposta_intervallo_prenotazione
 * ----------------------------------------
 * Modifica l'intervallo temporale della prenotazione.
 *
 * Parametri:
 *    p: puntatore alla prenotazione
 *    i: nuovo intervallo
 *
 * Pre-condizioni:
 *    p deve essere non NULL
 *    i deve essere un intervallo valido
 *
 * Post-condizione:
 *    aggiorna l'intervallo della prenotazione
 */
void imposta_intervallo_prenotazione(Prenotazione p, Intervallo i);

/*
 * Funzione: imposta_costo_prenotazione
 * -----------------------------------
 * Modifica il costo della prenotazione.
 *
 * Parametri:
 *    p: puntatore alla prenotazione
 *    costo: nuovo valore del costo
 *
 * Pre-condizioni:
 *    p deve essere non NULL
 *
 * Post-condizione:
 *    aggiorna il costo della prenotazione
 */
void imposta_costo_prenotazione(Prenotazione p, double costo);

/*
 * Funzione: duplica_prenotazione
 * ------------------------------
 * Crea una copia della prenotazione.
 *
 * Parametri:
 *    p: puntatore alla prenotazione da duplicare
 *
 * Pre-condizioni:
 *    p può essere NULL
 *
 * Post-condizione:
 *    ritorna una nuova prenotazione identica o NULL se p è NULL
 *
 * Ritorna:
 *    Nuova prenotazione duplicata
 */
Prenotazione duplica_prenotazione(Prenotazione p);

/*
 * Funzione: prenotazione_in_stringa
 * --------------------------------
 * Crea una rappresentazione testuale della prenotazione.
 *
 * Parametri:
 *    p: puntatore alla prenotazione
 *
 * Pre-condizioni:
 *    p può essere NULL
 *
 * Post-condizione:
 *    ritorna una stringa formattata o NULL se p è NULL
 *
 * Ritorna:
 *    Stringa contenente i dati della prenotazione
 */
char* prenotazione_in_stringa(Prenotazione p);

#endif //PRENOTAZIONE_H
