/*
 * Autore: Marco Visone
 * Data: 09/05/2025
 */

#ifndef LISTA_PRENOTAZIONE_H
#define LISTA_PRENOTAZIONE_H

typedef struct prenotazione *Prenotazione;
typedef struct nodo *ListaPre;

/*
 * Funzione: distruggi_lista_prenotazione
 * --------------------------------------
 * Libera tutta la memoria occupata dalla lista delle prenotazioni,
 * distruggendo ogni nodo e la prenotazione associata.
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
 * Side-effect:
 *    La memoria occupata da tutti i nodi con elementi annessi della lista viene liberata
 */
void distruggi_lista_prenotazione(ListaPre l);

/*
 * Funzione: aggiungi_prenotazione_lista
 * -------------------------------------
 * Aggiunge una prenotazione all'inizio della lista.
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
 *    La nuova testa della lista contiene la prenotazione aggiunta.
 *
 * Ritorna:
 *    La nuova testa della lista
 */
ListaPre aggiungi_prenotazione_lista(ListaPre l, Prenotazione p);

/*
 * Funzione: rimuovi_prenotazione_lista
 * ------------------------------------
 * Rimuove dalla lista la prenotazione che ha lo stesso intervallo
 * temporale della prenotazione passata come parametro.
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
 *    La lista non contiene più la prenotazione specificata (se presente).
 *
 * Ritorna:
 *    La testa della lista eventualmente aggiornata
 */
ListaPre rimuovi_prenotazione_lista(ListaPre l, Prenotazione p);

/*
 * Funzione: ottieni_prenotazione_lista
 * ------------------------------------
 * Restituisce la prenotazione contenuta nel nodo corrente della lista.
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
Prenotazione ottieni_prenotazione_lista(ListaPre l);

#endif // LISTA_PRENOTAZIONE_H
