/*
 * Autore: Antonio Sicignano
 * Data: 09/05/2025
 */

#ifndef DATA_H
#define DATA_H

#define ERRORE_FREQUENZA -2

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
ListaPre aggiungi_a_storico_lista(Data data, Prenotazione prenotazione);

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
ListaPre rimuovi_da_storico_lista(Data data, Prenotazione prenotazione);

/*
 * Funzione: ottieni_frequenza_lista
 * ---------------------------------
 *
 * Restituisce la frequenza (ad esempio il numero di prenotazioni)
 * contenuta nella struttura Data.
 *
 * Parametri:
 *    data: puntatore alla struttura Data
 *
 * Pre-condizione:
 *    data non deve essere NULL
 *
 * Ritorna:
 *    un intero che rappresenta la frequenza,
 *    oppure ERRORE_FREQUENZA in caso di errore
 *
 * Side-effect:
 *    nessuno
 */
int ottieni_frequenza_lista(Data data);

/*
 * Funzione: azzera_frequenza
 * --------------------------
 *
 * Resetta la frequenza della struttura Data a zero.
 *
 * Parametri:
 *    data: puntatore alla struttura Data
 *
 * Pre-condizione:
 *    data non deve essere NULL
 *
 * Post-condizione:
 *    la frequenza è resettata a zero
 *
 * Side-effect:
 *    modifica la struttura Data
 */
void azzera_frequenza(Data data);

Prenotazione *ottieni_vettore_storico(Data data, unsigned int *dimensione);

int ottieni_numero_prenotazioni(Data data);

void imposta_numero_prenotazioni(Data data, int numero_prenotazioni);

void imposta_storico_lista(Data data, ListaPre lista_prenotazione);

#endif // DATA_H