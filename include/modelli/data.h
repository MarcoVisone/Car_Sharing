/*
 * Autore: Antonio Sicignano
 * Data: 09/05/2025
 */

#ifndef DATA_H
#define DATA_H

#include "modelli/byte.h"

typedef struct prenotazione *Prenotazione;
typedef struct nodo *ListaPre;
typedef struct data *Data;

/*
 * Funzione: crea_data
 * -------------------
 * Crea e inizializza una nuova struttura Data per la gestione dello storico delle prenotazioni.
 *
 * Parametri:
 *    nessuno
 *
 * Pre-condizioni:
 *    nessuna
 *
 * Post-condizioni:
 *    restituisce un nuovo oggetto Data se l'allocazione è andata a buon fine,
 *    altrimenti restituisce NULL
 *
 * Ritorna:
 *    un puntatore alla nuova struttura `Data`, oppure NULL
 *
 * Side-effect:
 *    Alloca memoria.
 */
Data crea_data();

/*
 * Funzione: distruggi_data
 * ------------------------
 * Dealloca la memoria occupata da una struttura `Data`, incluso il suo storico.
 *
 * Parametri:
 *    data: puntatore alla struttura `Data` da distruggere.
 *
 * Pre-condizioni:
 *    data: non deve essere NULL
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    la memoria associata a `data` è stata liberata.
 */
void distruggi_data(Data data);

/*
 * Funzione: ottieni_storico_lista
 * -------------------------------
 * Restituisce una copia dello storico delle prenotazioni associato a un utente.
 *
 * Parametri:
 *    data: struttura `Data` contenente lo storico.
 *
 * Pre-condizioni:
 *    data: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce una copia della lista delle prenotazioni originale, oppure NULL in caso di errore
 *
 * Ritorna:
 *    puntatore ad una lista o NULL
 *
 * Side-effect:
 *    - Alloca memoria per la copia della lista.
 */
ListaPre ottieni_storico_lista(Data data);

/*
 * Funzione: aggiungi_a_storico_lista
 * ----------------------------------
 * Aggiunge una prenotazione allo storico dell'utente.
 *
 * Parametri:
 *    data: puntatore alla struttura `Data`.
 *    prenotazione: prenotazione da aggiungere.
 *
 * Pre-condizioni:
 *    data: non deve essere NULL
 *    prenotazione: non deve essere NULL
 *
 * Post-condizioni:
 *    - 1 se l'inserimento è avvenuto con successo.
 *    - 0 in caso di errore (puntatori NULL o fallimento nell'aggiunta alla lista).
 *
 * Ritorna:
 *    un valore di tipo Byte(0 o 1)
 *
 * Side-effect:
 *    modifica la lista `storico`
 */
Byte aggiungi_a_storico_lista(Data data, Prenotazione prenotazione);

/*
 * Funzione: rimuovi_da_storico_lista
 * ----------------------------------
 * Rimuove una prenotazione dallo storico dell'utente.
 *
 * Parametri:
 *    data: struttura `Data` da cui rimuovere.
 *    prenotazione: prenotazione da rimuovere.
 *
 * Pre-condizioni:
 *    data: non deve essere NULL
 *    prenotazione: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce 1 se la prenotazione è stata rimossa, altrimenti 0
 *
 * Ritorna:
 *    un valore di tipo Byte(0 o 1)
 *
 * Side-effect:
 *    modifica la lista
 */
Byte rimuovi_da_storico_lista(Data data, Prenotazione prenotazione);

/*
 * Funzione: ottieni_vettore_storico
 * ---------------------------------
 * Converte la lista dello storico delle prenotazioni in un array.
 *
 * Parametri:
 *    data: struttura `Data` contenente lo storico.
 *    dimensione: puntatore a variabile dove scrivere la dimensione dell’array restituito.
 *
 * Pre-condizioni:
 *    data: non deve essere NULL
 *    dimensione: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce un array contenente tutte le prenotazioni.
 *
 * Ritorna:
 *    un puntatore ad un vettore di prenotazioni o NULL
 *
 * Side-effect:
 *    Alloca memoria per l’array restituito.
 */
Prenotazione *ottieni_vettore_storico(Data data, unsigned int *dimensione);

/*
 * Funzione: ottieni_numero_prenotazioni
 * -------------------------------------
 * Restituisce il numero totale di prenotazioni associate a una struttura `Data`.
 *
 * Parametri:
 *    data: struttura `Data` di riferimento.
 *
 * Pre-condizioni:
 *    data: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce il numero di prenotazioni presenti
 *
 * Ritorna:
 *    un intero
 *
 * Side-effect:
 *    nessuno.
 */
unsigned int ottieni_numero_prenotazioni(Data data);

/*
 * Funzione: imposta_numero_prenotazioni
 * -------------------------------------
 * Imposta manualmente il numero di prenotazioni in una struttura `Data`.
 *
 * Parametri:
 *    data: struttura `Data` da modificare.
 *    numero_prenotazioni: valore da impostare.
 *
 * Pre-condizioni:
 *    data: non deve essere NULL
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    Il campo `numero_prenotazioni` viene aggiornato.
 */
void imposta_numero_prenotazioni(Data data, int numero_prenotazioni);

/*
 * Funzione: imposta_storico_lista
 * -------------------------------
 * Imposta direttamente la lista dello storico in una struttura `Data`.
 *
 * Parametri:
 *    data: struttura `Data` da modificare.
 *    lista_prenotazione: lista da assegnare al campo `storico`.
 *
 * Pre-condizioni:
 *    data: non deve essere NULL
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    Il campo `storico` della struttura viene aggiornato.
 */
void imposta_storico_lista(Data data, ListaPre lista_prenotazione);

#endif // DATA_H
