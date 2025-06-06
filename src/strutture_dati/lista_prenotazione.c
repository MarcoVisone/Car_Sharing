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
 *    prenotazione: deve puntare a una struttura Prenotazione valida
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    la memoria della prenotazione viene deallocata
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
 *    l: non deve essere NULL
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    tutta la memoria della lista e delle prenotazioni viene liberata
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
 *    p: non deve essere NULL
 *    l: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce la nuova testa della lista con la prenotazione aggiunta,
 *    oppure NULL in caso di errore di allocazione
 *
 * Ritorna:
 *    una lista
 *
 * Side-effect:
 *    Alloca memoria per un nuovo nodo
 *    Modifica la struttura della lista
 */
ListaPre aggiungi_prenotazione_lista(ListaPre l, Prenotazione p){
    return aggiungi_nodo(p, l);
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
 *    p: non deve essere NULL
 *    l: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce la testa della lista (potenzialmente modificata)
 *    se trovata, la prenotazione viene rimossa e la memoria liberata
 *
 * Ritorna:
 *    una lista
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
 *    l: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce la prenotazione contenuta nel nodo,
 *    oppure NULL se l è NULL
 *
 * Ritorna:
 *    una prenotazione
 */
Prenotazione ottieni_prenotazione_lista(ListaPre l){
    return ottieni_item(l);
}

/*
 * Funzione: duplica_lista_prenotazioni
 * ------------------------------------
 * Crea una copia duplicata di una lista di prenotazioni, preservandone l'ordine originale.
 *
 * Implementazione:
 *    - Crea una nuova lista vuota chiamata `nuova_lista`.
 *    - Scorre la lista `l` originale finché non è vuota:
 *    - Per ogni nodo, ottiene l'elemento corrente con `ottieni_item` e lo aggiunge
 *    in testa alla `nuova_lista` usando `aggiungi_nodo`.
 *    - Avanza al nodo successivo con `ottieni_prossimo`.
 *    - Al termine, la lista duplicata `nuova_lista` è in ordine inverso rispetto all'originale,
 *    quindi viene invertita tramite la funzione `inverti_lista` per mantenere l'ordine originale.
 *
 * Parametri:
 *    l: lista di prenotazioni da duplicare.
 *
 * Pre-condizioni:
 *    l: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce un duplicato della lista originale
 *
 * Ritorna:
 *    una lista
 *
 * Side-effect:
 *    Alloca memoria per la nuova lista e i suoi nodi.
 *    La memoria della lista duplicata deve essere gestita e liberata dal chiamante.
 */
ListaPre duplica_lista_prenotazioni(ListaPre l){
    ListaPre nuova_lista = crea_lista();

    while(!lista_vuota(l)){
        nuova_lista = aggiungi_nodo(duplica_prenotazione(ottieni_item(l)), nuova_lista);
        l = ottieni_prossimo(l);
    }

    return inverti_lista(nuova_lista);
}
