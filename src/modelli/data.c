/*
 * Autore: Antonio Sicignano
 * Data: 09/05/2025
 */

#include <stdlib.h>
#include <stdio.h>

#include "modelli/data.h"
#include "modelli/prenotazione.h"
#include "strutture_dati/lista_prenotazione.h"
#include <strutture_dati/lista.h>

struct data{
  ListaPre storico;
  unsigned int numero_prenotazioni;
};

/*
 * Funzione: crea_data
 * -------------------
 *
 * Crea e inizializza una nuova struttura Data.
 *
 * Implementazione:
 *    Alloca dinamicamente una nuova struttura Data, inizializza la lista storico
 *    con una lista vuota e imposta la frequenza a 0. Restituisce il puntatore
 *    oppure NULL in caso di errore.
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
Data crea_data() {
    Data data = calloc(1, sizeof(struct data));
    if (data == NULL) return NULL;

    data->storico = crea_lista();

    return data;
}

/*
 * Funzione: distruggi_data
 * ------------------------
 *
 * Dealloca la memoria associata a una struttura Data,
 * liberando anche le eventuali liste interne.
 *
 * Implementazione:
 *    Se il puntatore non è NULL, distrugge la lista storico associata e libera
 *    la memoria della struttura Data.
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
void distruggi_data(Data data) {
    if (data == NULL) return;
    distruggi_lista_prenotazione(data->storico);
    free(data);
 }

/*
 * Funzione: ottieni_storico_lista
 * -------------------------------
 *
 * Restituisce la lista delle prenotazioni associate alla Data.
 *
 * Implementazione:
 *    Restituisce il campo storico della struttura Data se non è NULL,
 *    altrimenti restituisce NULL.
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
ListaPre ottieni_storico_lista(Data data){
    if (data == NULL) {
        return NULL;
    }

    return duplica_lista_prenotazioni(data->storico);
}

/*
 * Funzione: aggiungi_a_storico_lista
 * ----------------------------------
 *
 * Aggiunge una prenotazione alla lista interna della Data.
 *
 * Implementazione:
 *    Aggiunge una prenotazione alla lista storico e aggiorna il campo nella struttura.
 *    Restituisce la lista aggiornata, oppure NULL se Data è NULL.
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
Byte aggiungi_a_storico_lista(Data data, Prenotazione prenotazione) {
    if (data == NULL) {
        return 0;
    }

    ListaPre temp = aggiungi_prenotazione_lista(data->storico, prenotazione);

    if(temp == NULL) return 0;

    data->storico = temp;
    data->numero_prenotazioni +=1;

    return temp != NULL;
}

/*
 * Funzione: rimuovi_da_storico_lista
 * ----------------------------------
 *
 * Rimuove una prenotazione dalla lista interna della Data.
 *
 * Implementazione:
 *    Rimuove una prenotazione dalla lista storico e aggiorna il campo nella struttura.
 *    Restituisce la lista aggiornata, oppure NULL se Data è NULL.
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
Byte rimuovi_da_storico_lista(Data data, Prenotazione prenotazione) {
    if (data == NULL) {
        return 0;
    }

    data->storico = rimuovi_prenotazione_lista(data->storico, prenotazione);

    data->numero_prenotazioni -=1;

    return data->storico != NULL;
}

/*
 * Funzione: ottieni_vettore_storico
 * ---------------------------------
 *
 * Restituisce un array contenente tutte le prenotazioni presenti nello storico.
 *
 * Implementazione:
 *    Alloca dinamicamente un vettore di prenotazioni, copia gli elementi dalla lista storico
 *    e imposta la dimensione tramite un puntatore.
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
Prenotazione *ottieni_vettore_storico(Data data, unsigned int *dimensione) {
    if (data == NULL || dimensione == NULL) {
        return NULL;
    }

    *dimensione = 0;
    if (data->numero_prenotazioni == 0) {
        return NULL;
    }

    Prenotazione *vettore = malloc(data->numero_prenotazioni * sizeof(Prenotazione));
    if (vettore == NULL) {
        return NULL;
    }

    ListaPre curr = data->storico;
    unsigned int i = 0;
    while (curr != NULL && i < data->numero_prenotazioni) {
        vettore[i] = ottieni_item(curr);

        curr = ottieni_prossimo(curr);
        i++;
    }
    *dimensione = i;

    return vettore;
 }

/*
 * Funzione: ottieni_numero_prenotazioni
 * -------------------------------------
 *
 * Restituisce il numero di prenotazioni contenute nella struttura Data.
 *
 * Implementazione:
 *    Controlla che la struttura sia valida e restituisce il campo numero_prenotazioni.
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
unsigned int ottieni_numero_prenotazioni(Data data){
    if (data == NULL) {
        return -1;
    }
    return data->numero_prenotazioni;
}

/*
 * Funzione: imposta_numero_prenotazioni
 * -------------------------------------
 *
 * Imposta il numero di prenotazioni nella struttura Data.
 *
 * Implementazione:
 *    Verifica che data sia valida e assegna il valore al campo numero_prenotazioni.
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
void imposta_numero_prenotazioni(Data data, int numero_prenotazioni){
    if (data == NULL) {
        return;
    }
    data->numero_prenotazioni = numero_prenotazioni;
}

/*
 * Funzione: imposta_storico_lista
 * -------------------------------
 *
 * Imposta la lista delle prenotazioni storico nella struttura Data.
 *
 * Implementazione:
 *    Verifica che data sia valida e assegna il valore al campo storico.
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
void imposta_storico_lista(Data data, ListaPre lista_prenotazione){
    if (data == NULL) {
        return;
    }

    data->storico = lista_prenotazione;
}
