/*
 * Autore: Marco Visone
 * Data: 06/05/2025
 */

#include <stdlib.h>
#include <stdio.h>
#include "modelli/prenotazione.h"
#include "modelli/intervallo.h"
#include "utils/utils.h"

#define DIMENSIONE_BUFFER 1024

struct prenotazione {
    char *cliente;
    Intervallo date;
    double costo;
};

/*
 * Funzione: crea_prenotazione
 * ---------------------------
 * Crea una nuova prenotazione.
 *
 * Implementazione:
 * Alloca memoria per una struttura prenotazione, duplica la stringa cliente,
 * assegna direttamente l'intervallo e imposta il costo.
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
 * Side-effect:
 *    Alloca memoria dinamica
 *
 * Ritorna:
 *    Prenotazione creata
 */
Prenotazione crea_prenotazione(char *cliente, Intervallo i, double costo) {
    Prenotazione p = malloc(sizeof(struct prenotazione));
    if (p == NULL) return NULL;

    p->cliente = mia_strdup(cliente);
    p->date = i;
    p->costo = costo;

    return p;
}

/*
 * Funzione: distruggi_prenotazione
 * -------------------------------
 * Libera la memoria allocata per la prenotazione.
 *
 * Implementazione:
 * Libera il campo cliente, distrugge l'intervallo e dealloca la struttura.
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
void distruggi_prenotazione(Prenotazione p) {
    if (p == NULL) return;

    distruggi_intervallo(p->date);
    free(p->cliente);
    free(p);
}

/*
 * Funzione: ottieni_cliente_prenotazione
 * -------------------------------------
 * Restituisce il nome del cliente della prenotazione.
 *
 * Implementazione:
 * Restituisce il campo cliente della struttura.
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
char *ottieni_cliente_prenotazione(Prenotazione p) {
    if (p == NULL) return NULL;

    return p->cliente;
}

/*
 * Funzione: ottieni_intervallo_prenotazione
 * ----------------------------------------
 * Restituisce l'intervallo della prenotazione.
 *
 * Implementazione:
 * Restituisce il campo date della struttura.
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
Intervallo ottieni_intervallo_prenotazione(Prenotazione p) {
    if (p == NULL) return NULL;

    return p->date;
}

/*
 * Funzione: ottieni_costo_prenotazione
 * -----------------------------------
 * Restituisce il costo della prenotazione.
 *
 * Implementazione:
 * Restituisce il campo costo della struttura.
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
double ottieni_costo_prenotazione(Prenotazione p) {
    if (p == NULL) return -1;

    return p->costo;
}

/*
 * Funzione: imposta_cliente_prenotazione
 * -------------------------------------
 * Modifica il nome del cliente associato alla prenotazione.
 *
 * Implementazione:
 * Libera la stringa precedente e ne duplica una nuova.
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
void imposta_cliente_prenotazione(Prenotazione p, char *cliente) {
    if (p == NULL) return;

    free(p->cliente);
    p->cliente = mia_strdup(cliente);
}

/*
 * Funzione: imposta_intervallo_prenotazione
 * ----------------------------------------
 * Modifica l'intervallo temporale della prenotazione.
 *
 * Implementazione:
 * Libera l'intervallo esistente e assegna il nuovo.
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
void imposta_intervallo_prenotazione(Prenotazione p, Intervallo i) {
    if (p == NULL) return;

    distruggi_intervallo(p->date);
    p->date = i;
}

/*
 * Funzione: imposta_costo_prenotazione
 * -----------------------------------
 * Modifica il costo della prenotazione.
 *
 * Implementazione:
 * Assegna direttamente il nuovo costo.
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
void imposta_costo_prenotazione(Prenotazione p, double costo) {
    if (p == NULL) return;

    p->costo = costo;
}

/*
 * Funzione: duplica_prenotazione
 * ------------------------------
 * Crea una copia della prenotazione.
 *
 * Implementazione:
 * Duplica cliente e intervallo, poi crea una nuova struttura.
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
 * Side-effect:
 *    Alloca memoria dinamica
 *
 * Ritorna:
 *    Nuova prenotazione duplicata
 */
Prenotazione duplica_prenotazione(Prenotazione p) {
    if (p == NULL) return NULL;

    Intervallo date_copia = duplica_intervallo(p->date);
    char *cliente_copia = mia_strdup(p->cliente);

    Prenotazione copia = crea_prenotazione(cliente_copia, date_copia, p->costo);
    free(cliente_copia);

    return copia;
}

/*
 * Funzione: prenotazione_in_stringa
 * --------------------------------
 * Crea una rappresentazione testuale della prenotazione.
 *
 * Implementazione:
 * Alloca un buffer e formatta i dati della prenotazione.
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
char* prenotazione_in_stringa(Prenotazione p) {
    if (p == NULL) return NULL;

    char *buffer = malloc(sizeof(char) * DIMENSIONE_BUFFER);
    if (buffer == NULL) return NULL;

    char *date = intervallo_in_stringa(p->date);

    snprintf(buffer, DIMENSIONE_BUFFER,
        "- Cliente: %s\n"
        "- Periodo: %s\n"
        "- Costo totale: %.2f euro\n",
        p->cliente,
        date,
        p->costo
    );

    free(date);
    return buffer;
}
