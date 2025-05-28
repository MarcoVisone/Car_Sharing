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
 *
 * Crea e inizializza una nuova struttura Data.
 *
 * Parametri:
 *    nessuno
 *
 * Pre-condizione:
 *    nessuna
 *
 * Ritorna:
 *    un nuovo oggetto Data allocato dinamicamente,
 *    NULL in caso di errore di allocazione
 *
 * Side-effect:
 *    allocazione dinamica di memoria
 */
Data crea_data();

/*
 * Funzione: distruggi_data
 * ------------------------
 *
 * Dealloca la memoria associata a una struttura Data,
 * liberando anche le eventuali liste interne.
 *
 * Parametri:
 *    data: puntatore alla struttura Data da distruggere
 *
 * Pre-condizione:
 *    data non deve essere NULL
 *
 * Post-condizione:
 *    memoria liberata
 *
 * Side-effect:
 *    deallocazione dinamica di memoria
 */
void distruggi_data(Data data);

/*
 * Funzione: ottieni_storico_lista
 * -------------------------------
 *
 * Restituisce la lista delle prenotazioni associate alla Data.
 *
 * Parametri:
 *    data: puntatore alla struttura Data
 *
 * Pre-condizione:
 *    data non deve essere NULL
 *
 * Ritorna:
 *    la lista delle prenotazioni (ListaPre)
 *
 * Side-effect:
 *    nessuno
 */
ListaPre ottieni_storico_lista(Data data);

/*
 * Funzione: aggiungi_a_storico_lista
 * ----------------------------------
 *
 * Aggiunge una prenotazione alla lista interna della Data.
 *
 * Parametri:
 *    data: puntatore alla struttura Data
 *    prenotazione: prenotazione da aggiungere
 *
 * Pre-condizione:
 *    data e prenotazione non devono essere NULL
 *
 * Post-condizione:
 *    la lista interna della Data è aggiornata con la nuova prenotazione
 *
 * Ritorna:
 *    la lista aggiornata con la prenotazione aggiunta
 *
 * Side-effect:
 *    modifica la lista interna
 */
Byte aggiungi_a_storico_lista(Data data, Prenotazione prenotazione);

/*
 * Funzione: rimuovi_da_storico_lista
 * ----------------------------------
 *
 * Rimuove una prenotazione dalla lista interna della Data.
 *
 * Parametri:
 *    data: puntatore alla struttura Data
 *    prenotazione: prenotazione da rimuovere
 *
 * Pre-condizione:
 *    data e prenotazione non devono essere NULL
 *
 * Post-condizione:
 *    la lista interna della Data è aggiornata dopo la rimozione
 *
 * Ritorna:
 *    la lista aggiornata dopo la rimozione
 *
 * Side-effect:
 *    modifica la lista interna
 */
Byte rimuovi_da_storico_lista(Data data, Prenotazione prenotazione);

/*
 * Funzione: ottieni_vettore_storico
 * ---------------------------------
 *
 * Restituisce un array contenente tutte le prenotazioni presenti nello storico.
 *
 * Parametri:
 *    data: struttura contenente lo storico delle prenotazioni
 *    dimensione: puntatore a intero dove verrà memorizzata la dimensione del vettore
 *
 * Pre-condizione:
 *    data deve essere una struttura valida
 *
 * Post-condizione:
 *    viene restituito un vettore allocato dinamicamente contenente tutte le prenotazioni,
 *    oppure NULL se data è NULL o se l'allocazione fallisce
 *
 * Ritorna:
 *    vettore di prenotazioni o NULL in caso di errore
 *
 * Side-effect:
 *    allocazione dinamica di memoria
 */
Prenotazione *ottieni_vettore_storico(Data data, unsigned int *dimensione);


/*
 * Funzione: ottieni_numero_prenotazioni
 * -------------------------------------
 *
 * Restituisce il numero di prenotazioni contenute nella struttura Data.
 *
 * Parametri:
 *    data: struttura Data da cui ottenere il numero di prenotazioni
 *
 * Pre-condizione:
 *    data deve essere una struttura valida
 *
 * Post-condizione:
 *    nessuna
 *
 * Ritorna:
 *    numero di prenotazioni o -1 se data è NULL
 *
 * Side-effect:
 *    nessuno
 */
unsigned int ottieni_numero_prenotazioni(Data data);

/*
 * Funzione: imposta_numero_prenotazioni
 * -------------------------------------
 *
 * Imposta il numero di prenotazioni nella struttura Data.
 *
 * Parametri:
 *    data: struttura Data su cui effettuare la modifica
 *    numero_prenotazioni: nuovo valore da assegnare
 *
 * Pre-condizione:
 *    data deve essere una struttura valida
 *
 * Post-condizione:
 *    il campo numero_prenotazioni della struttura viene aggiornato
 *
 * Ritorna:
 *    nessun valore
 *
 * Side-effect:
 *    modifica della struttura Data
 */
void imposta_numero_prenotazioni(Data data, int numero_prenotazioni);

/*
 * Funzione: imposta_storico_lista
 * -------------------------------
 *
 * Imposta la lista delle prenotazioni storico nella struttura Data.
 *
 * Parametri:
 *    data: struttura Data da aggiornare
 *    lista_prenotazione: nuova lista storico da assegnare
 *
 * Pre-condizione:
 *    data deve essere una struttura valida
 *
 * Post-condizione:
 *    il campo storico della struttura viene aggiornato
 *
 * Ritorna:
 *    nessun valore
 *
 * Side-effect:
 *    modifica della struttura Data
 */
void imposta_storico_lista(Data data, ListaPre lista_prenotazione);

#endif // DATA_H
