/*
 * Autore: Marco Visone
 * Data: 06/05/2025
 */

#ifndef PRENOTAZIONE_H
#define PRENOTAZIONE_H

typedef struct intervallo *Intervallo;
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
 *    cliente deve essere una stringa non nulla
 *    i deve essere un intervallo valido non nullo
 *
 * Post-condizione:
 *    restituisce una nuova prenotazione o NULL in caso di errore
 *
 * Ritorna:
 *    Prenotazione creata
 */
Prenotazione crea_prenotazione(char *cliente, char *targa, Intervallo i, double costo);

/*
 * Funzione: distruggi_prenotazione
 * -------------------------------
 * Libera la memoria allocata per la prenotazione.
 *
 * Parametri:
 *    p: puntatore alla prenotazione da distruggere
 *
 * Pre-condizioni:
 *    p deve essere non NULL
 *
 * Post-condizione:
 *    la memoria della prenotazione viene deallocata
 *
 * Side-effect:
 *    Dealloca memoria dinamica
 *
 * Ritorna:
 *    non restituisce niente
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
 *    p deve essere non NULL
 *
 * Post-condizione:
 *    restituisce il nome del cliente
 *
 * Ritorna:
 *    Nome del cliente
 */
char *ottieni_cliente_prenotazione(Prenotazione p);

char *ottieni_veicolo_prenotazione(Prenotazione p);

/*
 * Funzione: ottieni_intervallo_prenotazione
 * ----------------------------------------
 * Restituisce l'intervallo della prenotazione.
 *
 * Parametri:
 *    p: puntatore alla prenotazione
 *
 * Pre-condizioni:
 *    p deve essere non NULL
 *
 * Post-condizione:
 *    restituisce l'intervallo associato
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
 *    p deve essere non NULL
 *
 * Post-condizione:
 *    restituisce il costo
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
 *
 * Side-effect:
 *    Modifica memoria interna della struttura
 *
 * Ritorna:
 *    non restituisce niente
 */
void imposta_cliente_prenotazione(Prenotazione p, const char *cliente);

void imposta_veicolo_prenotazione(Prenotazione p, const char *targa);


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
 *
 * Side-effect:
 *    Modifica memoria interna della struttura
 *
 * Ritorna:
 *    non restituisce niente
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
 *
 * Side-effect:
 *    Modifica memoria interna della struttura
 *
 * Ritorna:
 *    non restituisce niente
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
 *    p deve essere non NULL
 *
 * Post-condizione:
 *    restituisce una nuova prenotazione identica
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
 *    p deve essere non NULL
 *
 * Post-condizione:
 *    restituisce una stringa formattata
 *
 * Side-effect:
 *    Alloca memoria dinamica
 *
 * Ritorna:
 *    Stringa contenente i dati della prenotazione
 */
char* prenotazione_in_stringa(Prenotazione p);

#endif //PRENOTAZIONE_H
