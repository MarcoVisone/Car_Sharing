/*
 * Autore: Marco Visone
 * Data: 09/05/2025
 */

#ifndef LISTA_PRENOTAZIONE_H
#define LISTA_PRENOTAZIONE_H

/**
 * Tipo opaco per la gestione di una prenotazione.
 */
typedef struct prenotazione *Prenotazione;

/*
 * Tipo opaco per un nodo di una lista generica.
 * Usato qui per rappresentare un nodo nella lista di prenotazioni.
 */
typedef struct nodo *ListaPre;

/*
 * Funzione: distruggi_lista_prenotazione
 * --------------------------------------
 * Libera tutta la memoria occupata da una lista di prenotazioni,
 * inclusi tutti i nodi e le prenotazioni contenute.
 *
 * Parametri:
 *    l: lista di prenotazioni da distruggere
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
void distruggi_lista_prenotazione(ListaPre l);

/*
 * Funzione: aggiungi_prenotazione_lista
 * -------------------------------------
 * Aggiunge una nuova prenotazione all'inizio della lista.
 *
 * Parametri:
 *    l: testa corrente della lista (può essere NULL)
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
ListaPre aggiungi_prenotazione_lista(ListaPre l, Prenotazione p);

/*
 * Funzione: rimuovi_prenotazione_lista
 * ------------------------------------
 * Rimuove dalla lista la prima prenotazione con intervallo
 * temporale uguale a quello della prenotazione fornita.
 *
 * Parametri:
 *    l: testa corrente della lista
 *    p: prenotazione di riferimento per l'intervallo da cercare
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
ListaPre rimuovi_prenotazione_lista(ListaPre l, Prenotazione p);

/*
 * Funzione: ottieni_prenotazione_lista
 * ------------------------------------
 * Restituisce la prenotazione contenuta nel nodo corrente.
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
Prenotazione ottieni_prenotazione_lista(ListaPre l);

/*
 * Funzione: duplica_lista_prenotazioni
 * ------------------------------------
 * Crea una copia duplicata di una lista di prenotazioni, preservandone l'ordine originale.
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
ListaPre duplica_lista_prenotazioni(ListaPre l);

#endif // LISTA_PRENOTAZIONE_H
