/*
 * Autore: Marco Visone
 * Data: 09/05/2025
 */

#include "strutture_dati/lista_prenotazione.h"
#include "strutture_dati/lista.h"
#include "modelli/prenotazione.h"
#include "modelli/intervallo.h"

#include <stddef.h>

static void distruggi_prenotazione_t(void *p);

/*
 * Funzione: distruggi_prenotazione_t
 * ----------------------------------
 * Funzione ausiliaria per distruggere una prenotazione castata da void*.
 *
 * Implementazione:
 * Prenotazione p = (Prenotazione)prenotazione;
 * distruggi_prenotazione(p);
 *
 * Parametri:
 *    prenotazione: puntatore generico a una prenotazione
 *
 * Pre-condizioni:
 *    prenotazione deve puntare a una struttura Prenotazione valida.
 *
 * Post-condizione:
 *    La prenotazione viene distrutta liberando la memoria associata.
 *
 * Ritorna:
 *    Non restituisce niente
 */
static void distruggi_prenotazione_t(void *prenotazione){
    Prenotazione p = (Prenotazione)prenotazione;
    distruggi_prenotazione(p);
}

/*
 * Funzione: distruggi_lista_prenotazione
 * --------------------------------------
 * Libera tutta la memoria occupata dalla lista delle prenotazioni,
 * distruggendo ogni nodo e la prenotazione associata.
 *
 * Implementazione:
 * Controlla se la lista è vuota, altrimenti itera sui nodi distruggendoli
 * e rilasciando la memoria delle prenotazioni tramite la funzione ausiliaria.
 *
 * Parametri:
 *    l: la lista di prenotazioni da distruggere
 *
 * Pre-condizioni:
 *    La lista può essere vuota o contenere nodi validi.
 *
 * Post-condizione:
 *    Tutti i nodi e le prenotazioni contenute nella lista vengono distrutti.
 *
 * Ritorna:
 *    Non restituisce niente
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
 * Chiama la funzione generica aggiungi_nodo per inserire la prenotazione
 * all'inizio della lista.
 *
 * Parametri:
 *    l: lista di prenotazioni
 *    p: prenotazione da aggiungere
 *
 * Pre-condizioni:
 *    La lista può essere vuota o non vuota.
 *    La prenotazione p deve essere valida.
 *
 * Post-condizione:
 *    La prenotazione viene aggiunta in testa alla lista.
 *
 * Ritorna:
 *    La nuova testa della lista contenente la prenotazione aggiunta
 */
ListaPre aggiungi_prenotazione_lista(ListaPre l, Prenotazione p){
    return aggiungi_nodo(p, l);
}

/*
 * Funzione: rimuovi_prenotazione_lista
 * ------------------------------------
 * Rimuove dalla lista la prenotazione che ha lo stesso intervallo
 * temporale della prenotazione passata come parametro.
 *
 * Implementazione:
 * Scorre la lista cercando una prenotazione con intervallo uguale;
 * se la trova, la rimuove aggiornando i puntatori.
 *
 * Parametri:
 *    l: lista di prenotazioni
 *    p: prenotazione da rimuovere (usata come riferimento per l'intervallo)
 *
 * Pre-condizioni:
 *    La lista può contenere o meno la prenotazione.
 *    La prenotazione p deve essere valida.
 *
 * Post-condizione:
 *    Se presente, la prenotazione con intervallo uguale viene rimossa dalla lista.
 *
 * Ritorna:
 *    La testa della lista eventualmente modificata
 */
ListaPre rimuovi_prenotazione_lista(ListaPre l, Prenotazione p){
    ListaPre curr = l;
    ListaPre prev = NULL;
    while(!lista_vuota(curr)){
        Prenotazione pre = ottieni_item(curr);
        if(compara_intervalli(ottieni_intervallo_prenotazione(pre), ottieni_intervallo_prenotazione(p)) == 0){
            if(prev){
               imposta_prossimo(prev, ottieni_prossimo(curr));
            } else {
              return ottieni_prossimo(curr);
            }
            distruggi_nodo(curr, distruggi_prenotazione_t);
        }
        prev = curr;
        curr = ottieni_prossimo(curr);
    }
    return l;
}

/*
 * Funzione: ottieni_prenotazione_lista
 * ------------------------------------
 * Restituisce la prenotazione contenuta nel nodo corrente della lista.
 *
 * Implementazione:
 * Chiama la funzione generica ottieni_item sul nodo corrente.
 *
 * Parametri:
 *    l: lista di prenotazioni
 *
 * Pre-condizioni:
 *    La lista deve contenere almeno un nodo valido.
 *
 * Post-condizione:
 *    Nessuna
 *
 * Ritorna:
 *    La prenotazione contenuta nel nodo corrente della lista
 */
Prenotazione ottieni_prenotazione_lista(ListaPre l){
    return ottieni_item(l);
}
