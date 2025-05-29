/*
 * Autore: Marco Visone
 * Data: 09/05/2025
 */

#ifndef LISTA_PRENOTAZIONE_H
#define LISTA_PRENOTAZIONE_H

/**
 * @brief Tipo opaco per la gestione di una prenotazione.
 */
typedef struct prenotazione *Prenotazione;

/**
 * @brief Tipo opaco per un nodo di una lista generica.
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
 *    l può essere NULL (in tal caso non fa nulla)
 *
 * Post-condizioni:
 *    tutta la memoria associata alla lista e alle prenotazioni viene liberata
 *
 * Side-effect:
 *    Dealloca memoria per tutti i nodi e le prenotazioni contenute
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
 *    p non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce la testa della lista (potenzialmente modificata)
 *    se la prenotazione viene trovata e rimossa, libera la memoria
 *    del nodo e della prenotazione
 *
 * Side-effect:
 *    Potrebbe deallocare memoria del nodo e della prenotazione rimossi
 *    Modifica la struttura della lista
 */
ListaPre rimuovi_prenotazione_lista(ListaPre l, Prenotazione p);

/*
 * Funzione: ottieni_prenotazione_lista
 * ------------------------------------
 * Restituisce la prenotazione contenuta nel nodo corrente.
 *
 * Parametri:
 *    l: nodo della lista da cui estrarre la prenotazione
 *
 * Pre-condizioni:
 *    l non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce la prenotazione contenuta nel nodo,
 *    oppure NULL se l è NULL
 */
Prenotazione ottieni_prenotazione_lista(ListaPre l);

/*
 * Funzione: duplica_lista_prenotazioni
 * ------------------------------------
 * Crea una copia duplicata di una lista di prenotazioni, preservandone l'ordine originale.
 *
 * Parametri:
 * l: lista di prenotazioni da duplicare.
 *
 * Pre-condizioni:
 * - `l` è una lista valida (può essere vuota).
 *
 * Post-condizioni:
 * - Restituisce una nuova lista allocata dinamicamente con gli stessi elementi di `l`
 *   nell'ordine originale.
 *
 * Side-effect:
 * - Alloca memoria per la nuova lista e i suoi nodi.
 * - La memoria della lista duplicata deve essere gestita e liberata dal chiamante.
 */
ListaPre duplica_lista_prenotazioni(ListaPre l);

#endif // LISTA_PRENOTAZIONE_H
