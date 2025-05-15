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
 * Crea e inizializza una nuova struttura Data.
 *
 * Ritorna:
 *    un nuovo oggetto Data allocato dinamicamente,
 *    NULL in caso di errore di allocazione
 */
Data crea_data();

/*
 * Funzione: distruggi_data
 * ------------------------
 * Dealloca la memoria associata a una struttura Data,
 * liberando anche le eventuali liste interne.
 *
 * Parametri:
 *    data: puntatore alla struttura Data da distruggere
 */
void distruggi_data(Data data);

/*
 * Funzione: ottieni_storico_lista
 * -------------------------------
 * Restituisce la lista delle prenotazioni associate alla Data.
 *
 * Parametri:
 *    data: puntatore alla struttura Data
 *
 * Ritorna:
 *    la lista delle prenotazioni (ListaPre)
 */
ListaPre ottieni_storico_lista(Data data);

/*
 * Funzione: aggiungi_a_storico_lista
 * ----------------------------------
 * Aggiunge una prenotazione alla lista interna della Data.
 *
 * Parametri:
 *    data: puntatore alla struttura Data
 *    prenotazione: prenotazione da aggiungere
 *
 * Ritorna:
 *    la lista aggiornata con la prenotazione aggiunta
 */
ListaPre aggiungi_a_storico_lista(Data data, Prenotazione prenotazione);

/*
 * Funzione: rimuovi_da_storico_lista
 * ----------------------------------
 * Rimuove una prenotazione dalla lista interna della Data.
 *
 * Parametri:
 *    data: puntatore alla struttura Data
 *    prenotazione: prenotazione da rimuovere
 *
 * Ritorna:
 *    la lista aggiornata dopo la rimozione
 */
ListaPre rimuovi_da_storico_lista(Data data, Prenotazione prenotazione);

/*
 * Funzione: ottieni_frequenza_lista
 * ---------------------------------
 * Restituisce la frequenza (ad esempio il numero di prenotazioni)
 * contenuta nella struttura Data.
 *
 * Parametri:
 *    data: puntatore alla struttura Data
 *
 * Ritorna:
 *    un intero che rappresenta la frequenza,
 *    oppure ERRORE_FREQUENZA in caso di errore
 */
int ottieni_frequenza_lista(Data data);

/*
 * Funzione: azzera_frequenza
 * --------------------------
 * Resetta la frequenza della struttura Data a zero.
 *
 * Parametri:
 *    data: puntatore alla struttura Data
 */
void azzera_frequenza(Data data);

#endif // DATA_H