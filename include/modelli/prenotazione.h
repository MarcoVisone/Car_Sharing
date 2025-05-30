/*
 * Autore: Marco Visone
 * Data: 06/05/2025
 */

#ifndef PRENOTAZIONE_H
#define PRENOTAZIONE_H

/*
 * tipo opaco per la gestione di un intervallo temporale.
 */
typedef struct intervallo *Intervallo;

/*
 * Tipo opaco per la gestione di una prenotazione.
 */
typedef struct prenotazione *Prenotazione;

/*
 * Funzione: crea_prenotazione
 * ---------------------------
 * Crea una nuova prenotazione con i dati specificati.
 *
 * Parametri:
 *    cliente: stringa costante contenente il nome del cliente che effettua la prenotazione.
 *    targa: stringa costante contenente la targa del veicolo associato alla prenotazione.
 *    i: intervallo temporale della prenotazione.
 *    costo: costo totale della prenotazione.
 *
 * Pre-condizioni:
 *    cliente: deve essere diverso da NULL
 *    targa: deve essere diverso da NULL
 *    i: deve essere diverso da NULL
 *
 * Post-condizioni:
 *    - Restituisce un puntatore ad una nuova struttura 'Prenotazione' se l'allocazione
 *    e l'inizializzazione hanno successo.
 *    - Restituisce NULL in caso di errore di allocazione di memoria.
 *
 * Ritorna:
 *    un puntatore a prenotazione o NULL
 *
 * Side-effect:
 *    - Alloca memoria dinamica per la struttura 'Prenotazione' e per le stringhe 'cliente' e 'targa'.
 */
Prenotazione crea_prenotazione(const char *cliente, const char *targa, Intervallo i, double costo);

/*
 * Funzione: distruggi_prenotazione
 * -------------------------------
 * Libera la memoria allocata per una data prenotazione.
 *
 * Parametri:
 *    p: puntatore alla prenotazione da distruggere.
 *
 * Pre-condizioni:
 *    p: non deve essere NULL
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    - La memoria associata alla prenotazione 'p' (inclusi i campi interni 'cliente', 'targa' e 'intervallo')
 *    viene deallocata.
 *    - Se 'p' è NULL, la funzione non ha alcun effetto.
 */
void distruggi_prenotazione(Prenotazione p);

/*
 * Funzione: ottieni_cliente_prenotazione
 * -------------------------------------
 * Restituisce il nome del cliente associato alla prenotazione.
 *
 * Parametri:
 *    p: puntatore alla prenotazione.
 *
 * Pre-condizioni:
 *    p: non deve essere NULL
 *
 * Post-condizioni:
 *    - Restituisce una stringa contenente il nome del cliente se 'p' è valido.
 *    - Restituisce NULL se 'p' è NULL.
 *
 * Ritorna:
 *    una stringa o NULL
 *
 * Side-effect:
 *    nessuno
 */
const char *ottieni_cliente_prenotazione(Prenotazione p);

/*
 * Funzione: ottieni_veicolo_prenotazione
 * -------------------------------------
 * Restituisce la targa del veicolo associato alla prenotazione.
 *
 * Parametri:
 *    p: puntatore alla prenotazione.
 *
 * Pre-condizioni:
 *    p: non deve essere NULL
 *
 * Post-condizioni:
 *    - Restituisce una stringa contenente la targa del veicolo se 'p' è valido.
 *    - Restituisce NULL se 'p' è NULL.
 *
 * Ritorna:
 *    una stringa o NULL
 *
 * Side-effect:
 *    nessuno
 */
const char *ottieni_veicolo_prenotazione(Prenotazione p);

/*
 * Funzione: ottieni_intervallo_prenotazione
 * ----------------------------------------
 * Restituisce l'intervallo temporale della prenotazione.
 *
 * Parametri:
 *    p: puntatore alla prenotazione.
 *
 * Pre-condizioni:
 *    p: non deve essere NULL
 *
 * Post-condizioni:
 *    - Restituisce un puntatore all'intervallo temporale se 'p' è valido.
 *    - Restituisce NULL se 'p' è NULL.
 *
 * Ritorna:
 *    un puntatore a intervallo o NULL
 *
 * Side-effect:
 *    nessuno
 */
Intervallo ottieni_intervallo_prenotazione(Prenotazione p);

/*
 * Funzione: ottieni_costo_prenotazione
 * -----------------------------------
 * Restituisce il costo della prenotazione.
 *
 * Parametri:
 *    p: puntatore alla prenotazione.
 *
 * Pre-condizioni:
 *    p: non deve essere NULL
 *
 * Post-condizioni:
 *    - Restituisce il valore del costo della prenotazione se 'p' è valido.
 *    - Restituisce -1.0 se 'p' è NULL.
 *
 * Ritorna:
 *    un double o -1
 *
 * Side-effect:
 *    nessuno
 */
double ottieni_costo_prenotazione(Prenotazione p);

/*
 * Funzione: imposta_cliente_prenotazione
 * -------------------------------------
 * Modifica il nome del cliente associato alla prenotazione.
 *
 * Parametri:
 *    p: puntatore alla prenotazione.
 *    cliente: stringa costante contenente il nome del cliente.
 *
 * Pre-condizioni:
 *    p: non deve essere NULL
 *    cliente: non deve essere NULL
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    - Il nome del cliente nella prenotazione 'p' viene aggiornato con la nuova stringa 'cliente'.
 *    - Se 'p' è NULL, la funzione non ha alcun effetto.
 *    - Dealloca la memoria precedentemente allocata per il vecchio nome del cliente.
 *    - Alloca nuova memoria dinamica per duplicare la stringa 'cliente'.
 *    - Modifica la memoria interna della struttura 'Prenotazione'.
 */
void imposta_cliente_prenotazione(Prenotazione p, const char *cliente);

/*
 * Funzione: imposta_veicolo_prenotazione
 * -------------------------------------
 * Modifica la targa del veicolo associato alla prenotazione.
 *
* Parametri:
 *    p: puntatore alla prenotazione.
 *    targa: stringa costante contenente la targa del veicolo.
 *
 * Pre-condizioni:
 *    p: non deve essere NULL
 *    targa: non deve essere NULL
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    - La targa del veicolo nella prenotazione 'p' viene aggiornata con la nuova stringa 'targa'.
 *    - Se 'p' è NULL, la funzione non ha alcun effetto.
 *    - Dealloca la memoria precedentemente allocata per la vecchia targa del veicolo.
 *    - Alloca nuova memoria dinamica per duplicare la stringa 'targa'.
 *    - Modifica la memoria interna della struttura 'Prenotazione'.
 */
void imposta_veicolo_prenotazione(Prenotazione p, const char *targa);

/*
 * Funzione: imposta_intervallo_prenotazione
 * ----------------------------------------
 * Modifica l'intervallo temporale della prenotazione.
 *
 * Parametri:
 *    p: puntatore alla prenotazione.
 *    i: il nuovo intervallo temporale.
 *
 * Pre-condizioni:
 *    p: non deve essere NULL
 *    i: non deve essere NULL
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    - L'intervallo temporale nella prenotazione 'p' viene aggiornato con il nuovo intervallo 'i'.
 *    - Se 'p' è NULL, la funzione non ha alcun effetto.
 *    - Dealloca la memoria precedentemente allocata per il vecchio intervallo.
 *    - Modifica la memoria interna della struttura 'Prenotazione'.
 */
void imposta_intervallo_prenotazione(Prenotazione p, Intervallo i);

/*
 * Funzione: imposta_costo_prenotazione
 * -----------------------------------
 * Modifica il costo della prenotazione.
 *
 * Parametri:
 *    p: puntatore alla prenotazione.
 *    costo: il nuovo valore double del costo.
 *
 * Pre-condizioni:
 *    p: non deve essere NULL
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    - Il costo della prenotazione 'p' viene aggiornato con il nuovo valore 'costo'.
 *    - Se 'p' è NULL, la funzione non ha alcun effetto.
 *    - Modifica la memoria interna della struttura 'Prenotazione'.
 */
void imposta_costo_prenotazione(Prenotazione p, double costo);

/*
 * Funzione: duplica_prenotazione
 * ------------------------------
 * Crea una copia profonda della prenotazione data.
 *
 * Parametri:
 *    p: puntatore alla prenotazione da duplicare.
 *
 * Pre-condizioni:
 *    p: non deve essere NULL
 *
 * Post-condizioni:
 *    - Restituisce un puntatore ad una nuova struttura 'Prenotazione' che è una copia esatta di 'p' se 'p' è valido.
 *    - La copia include duplicazioni delle stringhe 'cliente' e 'targa' e dell'oggetto 'Intervallo'.
 *    - Restituisce NULL se 'p' è NULL o in caso di errore di allocazione di memoria durante la duplicazione.
 *
 * Ritorna:
 *    un puntatore a prenotazione o NULL
 *
 * Side-effect:
 *    - Alloca nuova memoria dinamica per la prenotazione duplicata e per le sue stringhe e l'intervallo.
 */
Prenotazione duplica_prenotazione(Prenotazione p);

/*
 * Funzione: prenotazione_in_stringa
 * --------------------------------
 * Genera una rappresentazione testuale formattata dei dati della prenotazione.
 *
 * Parametri:
 *    p: puntatore alla prenotazione di cui si vuole ottenere la rappresentazione in stringa.
 *
 * Pre-condizioni:
 *    p: non deve essere NULL
 *
 * Post-condizioni:
 *    - Restituisce una stringa allocata dinamicamente contenente i dettagli della prenotazione (cliente, veicolo, periodo, costo).
 *    - La stringa sarà formattata su più righe.
 *    - Restituisce NULL se 'p' è NULL o in caso di errore di allocazione di memoria per il buffer.
 *
 * Ritorna:
 *    una stringa o NULL
 *
 * Side-effect:
 *    - Alloca memoria dinamica per la stringa risultante. È responsabilità del chiamante liberare questa memoria.
 */
char* prenotazione_in_stringa(Prenotazione p);

#endif // PRENOTAZIONE_H
