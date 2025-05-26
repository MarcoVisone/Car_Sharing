/*
 * Autore: Marco Visone
 * Data: 09/05/2025
 */

#include "strutture_dati/lista_prenotazione.h"
#include "strutture_dati/lista.h"
#include "modelli/prenotazione.h"
#include "modelli/intervallo.h"
#include <stddef.h>

/*
 * Funzione: distruggi_prenotazione_t
 * ----------------------------------
 * Funzione ausiliaria per distruggere una prenotazione castata da void*.
 *
 * Implementazione:
 *    Effettua il cast del puntatore void* a Prenotazione
 *    e chiama la funzione specifica di distruzione.
 *
 * Parametri:
 *    prenotazione: puntatore generico alla prenotazione
 *
 * Pre-condizioni:
 *    prenotazione deve puntare a una struttura Prenotazione valida
 *
 * Post-condizioni:
 *    la memoria della prenotazione viene deallocata
 *
 * Side-effect:
 *    Dealloca memoria della prenotazione
 */
static void distruggi_prenotazione_t(void *prenotazione){
    Prenotazione p = (Prenotazione)prenotazione;
    distruggi_prenotazione(p);
}

/*
 * Funzione: distruggi_lista_prenotazione
 * --------------------------------------
 * Libera tutta la memoria della lista di prenotazioni.
 *
 * Implementazione:
 *    Scorre la lista nodo per nodo, deallocando ogni nodo
 *    e la prenotazione associata usando distruggi_prenotazione_t.
 *
 * Parametri:
 *    l: lista da distruggere
 *
 * Pre-condizioni:
 *    l può essere NULL (in tal caso non fa nulla)
 *
 * Post-condizioni:
 *    tutta la memoria della lista e delle prenotazioni viene liberata
 *
 * Side-effect:
 *    Dealloca memoria per tutti i nodi e prenotazioni
 */
void distruggi_lista_prenotazione(ListaPre l){
    if(lista_vuota(l)) return;

    ListaPre curr = l;
    while(!lista_vuota(curr)){
        ListaPre temp = ottieni_prossimo(curr);
        distruggi_nodo(curr, distruggi_prenotazione_t);
        curr = temp;
    }
}

/*
 * Funzione: aggiungi_prenotazione_lista
 * -------------------------------------
 * Aggiunge una prenotazione all'inizio della lista.
 *
 * Implementazione:
 *    Utilizza la funzione generica aggiungi_nodo per inserire
 *    la prenotazione in testa alla lista.
 *
 * Parametri:
 *    l: testa corrente della lista
 *    p: prenotazione da aggiungere
 *
 * Pre-condizioni:
 *    p non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce la nuova testa della lista con la prenotazione aggiunta,
 *    oppure NULL in caso di errore di allocazione
 *
 * Side-effect:
 *    Alloca memoria per un nuovo nodo
 *    Modifica la struttura della lista
 */
ListaPre aggiungi_prenotazione_lista(ListaPre l, Prenotazione p){
    return aggiungi_nodo(duplica_prenotazione(p), l);
}

/*
 * Funzione: rimuovi_prenotazione_lista
 * ------------------------------------
 * Rimuove la prima prenotazione con intervallo uguale a quello fornito.
 *
 * Implementazione:
 *    Scorre la lista cercando una prenotazione con intervallo uguale.
 *    Se trovata, rimuove il nodo e dealloca memoria.
 *
 * Parametri:
 *    l: testa corrente della lista
 *    p: prenotazione di riferimento per l'intervallo
 *
 * Pre-condizioni:
 *    p non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce la testa della lista (potenzialmente modificata)
 *    se trovata, la prenotazione viene rimossa e la memoria liberata
 *
 * Side-effect:
 *    Potrebbe deallocare memoria del nodo e della prenotazione
 *    Modifica la struttura della lista
 */
ListaPre rimuovi_prenotazione_lista(ListaPre l, Prenotazione p) {
    ListaPre curr = l;
    ListaPre prev = NULL;
    Intervallo i1 = ottieni_intervallo_prenotazione(p);
    while (curr != NULL) {
        Prenotazione pre = ottieni_item(curr);
        Intervallo i2 = ottieni_intervallo_prenotazione(pre);

        if (compara_intervalli(i1, i2) == 0) {
            ListaPre next = ottieni_prossimo(curr);
            if (prev == NULL) {
                // Rimozione della testa
                distruggi_nodo(curr, distruggi_prenotazione_t);
                return next;
            } else {
                // Rimozione nel mezzo o in coda
                imposta_prossimo(prev, next);
                distruggi_nodo(curr, distruggi_prenotazione_t);
                return l;
            }
        }

        prev = curr;
        curr = ottieni_prossimo(curr);
    }

    // Nessun elemento rimosso
    return l;
 }


/*
 * Funzione: ottieni_prenotazione_lista
 * ------------------------------------
 * Restituisce la prenotazione contenuta nel nodo corrente.
 *
 * Implementazione:
 *    Utilizza la funzione generica ottieni_item per estrarre
 *    la prenotazione dal nodo.
 *
 * Parametri:
 *    l: nodo della lista
 *
 * Pre-condizioni:
 *    l non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce la prenotazione contenuta nel nodo,
 *    oppure NULL se l è NULL
 */
Prenotazione ottieni_prenotazione_lista(ListaPre l){
    return ottieni_item(l);
}
