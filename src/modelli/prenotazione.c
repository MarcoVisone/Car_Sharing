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
    char *targa;
    Intervallo date;
    double costo;
};

/*
 * Funzione: crea_prenotazione
 * ---------------------------
 * Crea una nuova prenotazione con i dati specificati.
 *
 * Implementazione:
 * Alloca memoria per una nuova struttura 'prenotazione'. Se l'allocazione fallisce,
 * restituisce NULL. Duplica le stringhe 'cliente' e 'targa' usando `mia_strdup`
 * per assicurare che la prenotazione abbia le proprie copie indipendenti.
 * L'intervallo `i` viene assegnato direttamente (si assume che la sua gestione
 * della memoria sia esterna o che `crea_prenotazione` ne prenda la proprietà).
 * Infine, il costo viene assegnato. In caso di fallimento della duplicazione delle stringhe,
 * la memoria allocata per la struttura e le stringhe già duplicate viene liberata.
 *
 * Parametri:
 * cliente: nome del cliente che effettua la prenotazione.
 * targa: targa del veicolo associato alla prenotazione.
 * i: intervallo temporale della prenotazione.
 * costo: costo totale della prenotazione.
 *
 * Pre-condizioni:
 * - 'cliente' deve essere una stringa non nulla.
 * - 'targa' deve essere una stringa non nulla.
 * - 'i' deve essere un intervallo valido e non nullo.
 *
 * Post-condizioni:
 * - Restituisce un puntatore ad una nuova struttura 'Prenotazione' se l'allocazione
 * e l'inizializzazione hanno successo.
 * - Restituisce NULL in caso di errore di allocazione di memoria.
 *
 * Side-effect:
 * - Alloca memoria dinamica per la struttura 'Prenotazione' e per le stringhe 'cliente' e 'targa'.
 *
 * Ritorna:
 * Un puntatore di tipo 'Prenotazione' alla prenotazione creata,  in caso di fallimento.
 */
Prenotazione crea_prenotazione(char *cliente, char *targa, Intervallo i, double costo) {
    Prenotazione p = malloc(sizeof(struct prenotazione));
    if (p == NULL) return NULL;

    p->cliente = mia_strdup(cliente);
    p->targa = mia_strdup(targa);
    p->date = i;
    p->costo = costo;

    return p;
}

/*
 * Funzione: distruggi_prenotazione
 * -------------------------------
 * Libera la memoria allocata per una data prenotazione.
 *
 * Implementazione:
 * Verifica che il puntatore 'p' non sia NULL per evitare dereferenziamenti invalidi.
 * Invoca `distruggi_intervallo` per deallocare correttamente l'intervallo associato,
 * poiché si tratta di un tipo opaco e la sua gestione della memoria è esterna.
 * Successivamente, libera la memoria allocata per le stringhe 'targa' e 'cliente'
 * (precedentemente duplicate con `mia_strdup`). Infine, dealloca la struttura 'prenotazione' stessa.
 *
 * Parametri:
 * p: puntatore alla prenotazione da distruggere.
 *
 * Pre-condizioni:
 * - 'p' deve essere un puntatore valido ad una struttura 'Prenotazione'
 *
 * Post-condizioni:
 * - La memoria associata alla prenotazione 'p' (inclusi i campi interni 'cliente', 'targa' e 'intervallo')
 * viene deallocata.
 * - Se 'p' è NULL, la funzione non ha alcun effetto.
 *
 * Side-effect:
 * - Dealloca memoria dinamica precedentemente allocata per la prenotazione e i suoi campi.
 *
 * Ritorna:
 * Questa funzione non restituisce alcun valore.
 */
void distruggi_prenotazione(Prenotazione p) {
    if (p == NULL) return;

    distruggi_intervallo(p->date); // Distrugge l'intervallo associato
    free(p->targa);
    free(p->cliente);
    free(p);
}

/*
 * Funzione: ottieni_cliente_prenotazione
 * -------------------------------------
 * Restituisce il nome del cliente associato alla prenotazione.
 *
 * Implementazione:
 * Verifica se il puntatore alla prenotazione 'p' è valido.
 * Se 'p' è valido, restituisce direttamente il puntatore alla stringa 'cliente'
 * interna alla struttura. Non viene creata una copia.
 *
 * Parametri:
 * p: puntatore alla prenotazione.
 *
 * Pre-condizioni:
 * - 'p' deve essere un puntatore valido ad una struttura 'Prenotazione'
 *
 * Post-condizioni:
 * - Restituisce una stringa contenente il nome del cliente se 'p' è valido.
 * - Restituisce NULL se 'p' è NULL.
 *
 * Side-effect:
 * - Nessuno.
 *
 * Ritorna:
 * Una stringa (puntatore a char) con il nome del cliente. La stringa non deve essere modificata o liberata dal chiamante.
 */
char *ottieni_cliente_prenotazione(Prenotazione p) {
    if (p == NULL) return NULL;

    return mia_strdup(p->cliente);
}

/*
 * Funzione: ottieni_veicolo_prenotazione
 * -------------------------------------
 * Restituisce la targa del veicolo associato alla prenotazione.
 *
 * Implementazione:
 * Verifica se il puntatore alla prenotazione 'p' è valido.
 * Se 'p' è valido, restituisce direttamente il puntatore alla stringa 'targa'
 * interna alla struttura. Non viene creata una copia.
 *
 * Parametri:
 * p: puntatore alla prenotazione.
 *
 * Pre-condizioni:
 * - 'p' deve essere un puntatore valido ad una struttura 'Prenotazione'
 *
 * Post-condizioni:
 * - Restituisce una stringa contenente la targa del veicolo se 'p' è valido.
 * - Restituisce NULL se 'p' è NULL.
 *
 * Side-effect:
 * - Nessuno.
 *
 * Ritorna:
 * Una stringa (puntatore a char) con la targa del veicolo. La stringa non deve essere modificata o liberata dal chiamante.
 */
char *ottieni_veicolo_prenotazione(Prenotazione p){
    if(p == NULL) return NULL;

    return mia_strdup(p->targa);
}

/*
 * Funzione: ottieni_intervallo_prenotazione
 * ----------------------------------------
 * Restituisce l'intervallo temporale della prenotazione.
 *
 * Implementazione:
 * Verifica se il puntatore alla prenotazione 'p' è valido.
 * Se 'p' è valido, restituisce direttamente il puntatore all'oggetto 'Intervallo'
 * interno alla struttura. Non viene creata una copia.
 *
 * Parametri:
 * p: puntatore alla prenotazione.
 *
 * Pre-condizioni:
 * - 'p' deve essere un puntatore valido ad una struttura 'Prenotazione'
 *
 * Post-condizioni:
 * - Restituisce un puntatore all'intervallo temporale se 'p' è valido.
 * - Restituisce NULL se 'p' è NULL.
 *
 * Side-effect:
 * - Nessuno.
 *
 * Ritorna:
 * Un puntatore di tipo 'Intervallo' all'intervallo temporale della prenotazione. L'intervallo non deve essere modificato o liberato dal chiamante.
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
 * Verifica se il puntatore alla prenotazione 'p' è valido.
 * Se 'p' è valido, restituisce il valore 'costo' direttamente dal campo della struttura.
 * Se 'p' è NULL, restituisce un valore sentinella -1.0.
 *
 * Parametri:
 * p: puntatore alla prenotazione.
 *
 * Pre-condizioni:
 * - 'p' deve essere un puntatore valido ad una struttura 'Prenotazione'
 *
 * Post-condizioni:
 * - Restituisce il valore del costo della prenotazione se 'p' è valido.
 * - Restituisce -1.0 (o un altro valore sentinella) se 'p' è NULL.
 *
 * Side-effect:
 * - Nessuno.
 *
 * Ritorna:
 * Un valore double rappresentante il costo della prenotazione.
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
 * Verifica che il puntatore 'p' non sia NULL. Prima di assegnare il nuovo nome,
 * la vecchia stringa del cliente viene liberata per evitare memory leak.
 * Successivamente, la nuova stringa 'cliente' viene duplicata usando `mia_strdup`
 * e il puntatore risultante viene assegnato al campo 'cliente' della struttura.
 *
 * Parametri:
 * p: puntatore alla prenotazione.
 * cliente: la nuova stringa contenente il nome del cliente.
 *
 * Pre-condizioni:
 * - 'p' deve essere un puntatore valido ad una struttura 'Prenotazione'
 * - 'cliente' deve essere una stringa non nulla.
 *
 * Post-condizioni:
 * - Il nome del cliente nella prenotazione 'p' viene aggiornato con la nuova stringa 'cliente'.
 * - Se 'p' è NULL, la funzione non ha alcun effetto.
 *
 * Side-effect:
 * - Dealloca la memoria precedentemente allocata per il vecchio nome del cliente.
 * - Alloca nuova memoria dinamica per duplicare la stringa 'cliente'.
 * - Modifica la memoria interna della struttura 'Prenotazione'.
 *
 * Ritorna:
 * Questa funzione non restituisce alcun valore.
 */
void imposta_cliente_prenotazione(Prenotazione p, const char *cliente) {
    if (p == NULL) return;

    free(p->cliente); // Libera la vecchia stringa
    p->cliente = mia_strdup(cliente); // Alloca e copia la nuova stringa
}

/*
 * Funzione: imposta_veicolo_prenotazione
 * -------------------------------------
 * Modifica la targa del veicolo associato alla prenotazione.
 *
 * Implementazione:
 * Verifica che il puntatore 'p' non sia NULL. Prima di assegnare la nuova targa,
 * la vecchia stringa della targa viene liberata per evitare memory leak.
 * Successivamente, la nuova stringa 'targa' viene duplicata usando `mia_strdup`
 * e il puntatore risultante viene assegnato al campo 'targa' della struttura.
 *
 * Parametri:
 * p: puntatore alla prenotazione.
 * targa: la nuova stringa contenente la targa del veicolo.
 *
 * Pre-condizioni:
 * - 'p' deve essere un puntatore valido ad una struttura 'Prenotazione'
 * - 'targa' deve essere una stringa non nulla.
 *
 * Post-condizioni:
 * - La targa del veicolo nella prenotazione 'p' viene aggiornata con la nuova stringa 'targa'.
 * - Se 'p' è NULL, la funzione non ha alcun effetto.
 *
 * Side-effect:
 * - Dealloca la memoria precedentemente allocata per la vecchia targa del veicolo.
 * - Alloca nuova memoria dinamica per duplicare la stringa 'targa'.
 * - Modifica la memoria interna della struttura 'Prenotazione'.
 *
 * Ritorna:
 * Questa funzione non restituisce alcun valore.
 */
void imposta_veicolo_prenotazione(Prenotazione p, const char *targa){
    if(p == NULL) return;

    free(p->targa); // Libera la vecchia stringa
    p->targa = mia_strdup(targa); // Alloca e copia la nuova stringa
}

/*
 * Funzione: imposta_intervallo_prenotazione
 * ----------------------------------------
 * Modifica l'intervallo temporale della prenotazione.
 *
 * Implementazione:
 * Verifica che il puntatore 'p' non sia NULL. Prima di assegnare il nuovo intervallo,
 * il vecchio intervallo viene distrutto utilizzando `distruggi_intervallo` per gestire
 * correttamente la sua memoria. Il nuovo intervallo `i` viene quindi assegnato al campo 'date'
 * della struttura.
 *
 * Parametri:
 * p: puntatore alla prenotazione.
 * i: il nuovo intervallo temporale.
 *
 * Pre-condizioni:
 * - 'p' deve essere un puntatore valido ad una struttura 'Prenotazione'
 * - 'i' deve essere un puntatore valido ad una struttura 'Intervallo'
 *
 * Post-condizioni:
 * - L'intervallo temporale nella prenotazione 'p' viene aggiornato con il nuovo intervallo 'i'.
 * - Se 'p' è NULL, la funzione non ha alcun effetto.
 *
 * Side-effect:
 * - Dealloca la memoria precedentemente allocata per il vecchio intervallo.
 * - Modifica la memoria interna della struttura 'Prenotazione'.
 *
 * Ritorna:
 * Questa funzione non restituisce alcun valore.
 */
void imposta_intervallo_prenotazione(Prenotazione p, Intervallo i) {
    if (p == NULL) return;

    distruggi_intervallo(p->date); // Distrugge il vecchio intervallo
    p->date = i; // Assegna il nuovo intervallo
}

/*
 * Funzione: imposta_costo_prenotazione
 * -----------------------------------
 * Modifica il costo della prenotazione.
 *
 * Implementazione:
 * Verifica che il puntatore 'p' non sia NULL. Il nuovo valore 'costo' viene
 * semplicemente assegnato al campo 'costo' della struttura 'prenotazione'.
 *
 * Parametri:
 * p: puntatore alla prenotazione.
 * costo: il nuovo valore double del costo.
 *
 * Pre-condizioni:
 * - 'p' deve essere un puntatore valido ad una struttura 'Prenotazione'
 *
 * Post-condizioni:
 * - Il costo della prenotazione 'p' viene aggiornato con il nuovo valore 'costo'.
 * - Se 'p' è NULL, la funzione non ha alcun effetto.
 *
 * Side-effect:
 * - Modifica la memoria interna della struttura 'Prenotazione'.
 *
 * Ritorna:
 * Questa funzione non restituisce alcun valore.
 */
void imposta_costo_prenotazione(Prenotazione p, double costo) {
    if (p == NULL) return;

    p->costo = costo;
}

/*
 * Funzione: duplica_prenotazione
 * ------------------------------
 * Crea una copia profonda della prenotazione data.
 *
 * Implementazione:
 * Verifica se il puntatore 'p' è NULL. Crea una copia dell'intervallo
 * utilizzando la funzione `duplica_intervallo` (si assume che esista).
 * Successivamente, crea una nuova prenotazione utilizzando la funzione
 * `crea_prenotazione`, passando le stringhe originali 'cliente' e 'targa'
 * (che verranno duplicate internamente da `crea_prenotazione`) e la copia
 * dell'intervallo e il costo.
 *
 * Parametri:
 * p: puntatore alla prenotazione da duplicare.
 *
 * Pre-condizioni:
 * - 'p' deve essere un puntatore valido ad una struttura 'Prenotazione'
 *
 * Post-condizioni:
 * - Restituisce un puntatore ad una nuova struttura 'Prenotazione' che è una copia esatta di 'p' se 'p' è valido.
 * - La copia include duplicazioni delle stringhe 'cliente' e 'targa' e dell'oggetto 'Intervallo'.
 * - Restituisce NULL se 'p' è NULL o in caso di errore di allocazione di memoria durante la duplicazione.
 *
 * Side-effect:
 * - Alloca nuova memoria dinamica per la prenotazione duplicata e per le sue stringhe e l'intervallo.
 *
 * Ritorna:
 * Un puntatore di tipo 'Prenotazione' alla copia della prenotazione,  in caso di fallimento.
 */
Prenotazione duplica_prenotazione(Prenotazione p) {
    if (p == NULL) return NULL;

    // Duplica l'intervallo per una copia profonda
    Intervallo date_copia = duplica_intervallo(p->date);
    if (date_copia == NULL) return NULL; // Errore nella duplicazione dell'intervallo

    // Crea la nuova prenotazione usando i dati duplicati
    Prenotazione copia = crea_prenotazione(p->cliente, p->targa, date_copia, p->costo);

    // Se la creazione della copia fallisce, distruggi l'intervallo duplicato
    if (copia == NULL) {
        distruggi_intervallo(date_copia);
    }

    return copia;
}

/*
 * Funzione: prenotazione_in_stringa
 * --------------------------------
 * Genera una rappresentazione testuale formattata dei dati della prenotazione.
 *
 * Implementazione:
 * Verifica se il puntatore 'p' è NULL. Alloca un buffer di dimensioni fisse
 * (`DIMENSIONE_BUFFER`) per costruire la stringa. Ottiene la rappresentazione
 * in stringa dell'intervallo utilizzando `intervallo_in_stringa`.
 * Utilizza `snprintf` per formattare tutti i campi della prenotazione nel buffer.
 * Infine, libera la memoria allocata per la stringa dell'intervallo e restituisce
 * il puntatore al buffer contenente la stringa formattata della prenotazione.
 * Gestisce gli errori di allocazione del buffer.
 *
 * Parametri:
 * p: puntatore alla prenotazione di cui si vuole ottenere la rappresentazione in stringa.
 *
 * Pre-condizioni:
 * - 'p' deve essere un puntatore valido ad una struttura 'Prenotazione'
 *
 * Post-condizioni:
 * - Restituisce una stringa allocata dinamicamente contenente i dettagli della prenotazione (cliente, veicolo, periodo, costo).
 * - La stringa sarà formattata su più righe.
 * - Restituisce NULL se 'p' è NULL o in caso di errore di allocazione di memoria per il buffer.
 *
 * Side-effect:
 * - Alloca memoria dinamica per la stringa risultante. È responsabilità del chiamante liberare questa memoria.
 *
 * Ritorna:
 * Una stringa (puntatore a char) con la rappresentazione testuale della prenotazione.
 */
char* prenotazione_in_stringa(Prenotazione p) {
    if (p == NULL) return NULL;

    char *buffer = malloc(sizeof(char) * DIMENSIONE_BUFFER);
    if (buffer == NULL) return NULL;

    // Ottiene la stringa dell'intervallo. Si assume che intervallo_in_stringa allochi memoria.
    char *date_str = intervallo_in_stringa(p->date);
    if (date_str == NULL) {
        free(buffer);
        return NULL;
    }

    // Formatta la stringa completa della prenotazione
    snprintf(buffer, DIMENSIONE_BUFFER,
        "- Cliente: %s\n"
        "- Veicolo: %s\n"
        "- Periodo: %s\n"
        "- Costo totale: %.2f euro\n",
        p->cliente,
        p->targa,
        date_str,
        p->costo
    );

    free(date_str); // Libera la memoria allocata da intervallo_in_stringa
    return buffer;
}
