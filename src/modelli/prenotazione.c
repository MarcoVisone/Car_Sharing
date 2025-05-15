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
 * --------------------------
 * Crea una nuova prenotazione con cliente, intervallo e costo specificati.
 *
 * Implementazione:
 * Alloca memoria per una struttura prenotazione, duplica la stringa cliente,
 * assegna direttamente l'intervallo e imposta il costo.
 *
 * Parametri:
 *    cliente: nome del cliente associato alla prenotazione
 *    i: intervallo temporale della prenotazione
 *    costo: costo totale della prenotazione
 *
 * Pre-condizioni:
 *    cliente deve essere una stringa valida
 *    i deve essere un Intervallo valido (non NULL)
 *
 * Post-condizione:
 *    ritorna una nuova prenotazione allocata in memoria
 *
 * Ritorna:
 *    La nuova prenotazione creata, oppure NULL in caso di errore
 *
 * Side-effect:
 *    Alloca memoria dinamica
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
 * Libera la memoria associata a una prenotazione.
 *
 * Implementazione:
 * Controlla se la prenotazione è NULL, altrimenti libera cliente,
 * distrugge l'intervallo e libera la struttura stessa.
 *
 * Parametri:
 *    p: prenotazione da distruggere
 *
 * Pre-condizioni:
 *    Nessuna, p può essere NULL
 *
 * Post-condizione:
 *    La memoria della prenotazione è liberata
 *
 * Ritorna:
 *    Non restituisce niente
 *
 * Side-effect:
 *    Dealloca memoria dinamica
 */
void distruggi_prenotazione(Prenotazione p) {
    if (p == NULL) return;

    distruggi_intervallo(p->date);
    free(p->cliente);
    free(p);
}

/*
 * Funzione: ottieni_cliente_prenotazione
 * --------------------------------------
 * Restituisce il cliente associato alla prenotazione.
 *
 * Implementazione:
 * Restituisce direttamente il campo cliente della prenotazione.
 *
 * Parametri:
 *    p: prenotazione da cui ottenere il cliente
 *
 * Pre-condizioni:
 *    Nessuna, p può essere NULL
 *
 * Post-condizione:
 *    Nessuna
 *
 * Ritorna:
 *    Puntatore al nome del cliente, o NULL se p è NULL
 *
 * Side-effect:
 *    Nessuno
 */
char *ottieni_cliente_prenotazione(Prenotazione p) {
    if (p == NULL) return NULL;

    return p->cliente;
}

/*
 * Funzione: ottieni_intervallo_prenotazione
 * -----------------------------------------
 * Restituisce l'intervallo associato alla prenotazione.
 *
 * Implementazione:
 * Restituisce direttamente il campo date della prenotazione.
 *
 * Parametri:
 *    p: prenotazione da cui ottenere l'intervallo
 *
 * Pre-condizioni:
 *    Nessuna, p può essere NULL
 *
 * Post-condizione:
 *    Nessuna
 *
 * Ritorna:
 *    L'intervallo della prenotazione, o NULL se p è NULL
 *
 * Side-effect:
 *    Nessuno
 */
Intervallo ottieni_intervallo_prenotazione(Prenotazione p) {
    if (p == NULL) return NULL;

    return p->date;
}

/*
 * Funzione: ottieni_costo_prenotazione
 * ------------------------------------
 * Restituisce il costo della prenotazione.
 *
 * Implementazione:
 * Restituisce direttamente il campo costo della prenotazione.
 *
 * Parametri:
 *    p: prenotazione da cui ottenere il costo
 *
 * Pre-condizioni:
 *    Nessuna, p può essere NULL
 *
 * Post-condizione:
 *    Nessuna
 *
 * Ritorna:
 *    Il costo, oppure -1 se p è NULL
 *
 * Side-effect:
 *    Nessuno
 */
double ottieni_costo_prenotazione(Prenotazione p) {
    if (p == NULL) return -1;

    return p->costo;
}

/*
 * Funzione: imposta_cliente_prenotazione
 * --------------------------------------
 * Imposta un nuovo cliente nella prenotazione.
 *
 * Implementazione:
 * Libera il vecchio cliente e duplica la nuova stringa.
 *
 * Parametri:
 *    p: prenotazione da modificare
 *    cliente: nuovo nome del cliente
 *
 * Pre-condizioni:
 *    p deve essere non NULL
 *    cliente deve essere una stringa valida
 *
 * Post-condizione:
 *    Il cliente nella prenotazione viene aggiornato
 *
 * Ritorna:
 *    Non restituisce niente
 *
 * Side-effect:
 *    Modifica memoria interna della struttura
 */
void imposta_cliente_prenotazione(Prenotazione p, char *cliente) {
    if (p == NULL) return;

    free(p->cliente);
    p->cliente = mia_strdup(cliente);
}

/*
 * Funzione: imposta_intervallo_prenotazione
 * -----------------------------------------
 * Imposta un nuovo intervallo nella prenotazione.
 *
 * Implementazione:
 * Distrugge l'intervallo esistente e lo sostituisce con il nuovo.
 *
 * Parametri:
 *    p: prenotazione da modificare
 *    i: nuovo intervallo
 *
 * Pre-condizioni:
 *    p deve essere non NULL
 *    i deve essere un Intervallo valido
 *
 * Post-condizione:
 *    L'intervallo viene aggiornato nella prenotazione
 *
 * Ritorna:
 *    Non restituisce niente
 *
 * Side-effect:
 *    Modifica memoria interna
 */
void imposta_intervallo_prenotazione(Prenotazione p, Intervallo i) {
    if (p == NULL) return;

    distruggi_intervallo(p->date);
    p->date = i;
}

/*
 * Funzione: imposta_costo_prenotazione
 * ------------------------------------
 * Imposta un nuovo costo nella prenotazione.
 *
 * Implementazione:
 * Modifica direttamente il campo costo.
 *
 * Parametri:
 *    p: prenotazione da modificare
 *    costo: nuovo costo
 *
 * Pre-condizioni:
 *    p deve essere non NULL
 *
 * Post-condizione:
 *    Il costo della prenotazione viene aggiornato
 *
 * Ritorna:
 *    Non restituisce niente
 *
 * Side-effect:
 *    Nessuno
 */
void imposta_costo_prenotazione(Prenotazione p, double costo) {
    if (p == NULL) return;

    p->costo = costo;
}

/*
 * Funzione: duplica_prenotazione
 * ------------------------------
 * Crea una copia identica di una prenotazione.
 *
 * Implementazione:
 * Duplica il cliente, duplica l'intervallo e crea una nuova struttura.
 *
 * Parametri:
 *    p: prenotazione da duplicare
 *
 * Pre-condizioni:
 *    p può essere NULL
 *
 * Post-condizione:
 *    Viene creata una nuova prenotazione identica
 *
 * Ritorna:
 *    La copia della prenotazione, o NULL se p è NULL
 *
 * Side-effect:
 *    Alloca memoria dinamica
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
 * ---------------------------------
 * Restituisce una rappresentazione testuale della prenotazione.
 *
 * Implementazione:
 * Crea una stringa contenente i dati della prenotazione formattati.
 *
 * Parametri:
 *    p: prenotazione da convertire
 *
 * Pre-condizioni:
 *    p può essere NULL
 *
 * Post-condizione:
 *    Ritorna una stringa formattata con i dati, o NULL se errore
 *
 * Ritorna:
 *    Stringa allocata dinamicamente con i dati della prenotazione
 *
 * Side-effect:
 *    Alloca memoria dinamica
 */
char *prenotazione_in_stringa(Prenotazione p) {
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
