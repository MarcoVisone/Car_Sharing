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
 * Crea e inizializza una nuova struttura Data per la gestione dello storico delle prenotazioni.
 *
 * Implementazione:
 *    - Alloca memoria per la struttura `Data` con `calloc`, inizializzando a 0.
 *    - Inizializza il campo `storico` con una lista vuota.
 *    - Imposta a zero il numero di prenotazioni.
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
Data crea_data() {
    Data data = calloc(1, sizeof(struct data));
    if (data == NULL) return NULL;

    data->storico = crea_lista();
    data->numero_prenotazioni = 0;

    return data;
}

/*
 * Funzione: distruggi_data
 * ------------------------
 * Dealloca la memoria occupata da una struttura `Data`, incluso il suo storico.
 *
 * Implementazione:
 *    - Verifica che `data` non sia NULL.
 *    - Chiama `distruggi_lista_prenotazione` per liberare lo storico.
 *    - Libera la memoria della struttura stessa.
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
void distruggi_data(Data data) {
    if (data == NULL) return;
    distruggi_lista_prenotazione(data->storico);
    free(data);
 }

/*
 * Funzione: ottieni_storico_lista
 * -------------------------------
 * Restituisce una copia dello storico delle prenotazioni associato a un utente.
 *
 * Implementazione:
 *    - Verifica che `data` non sia NULL.
 *    - Chiama `duplica_lista_prenotazioni` per restituire una copia della lista.
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
ListaPre ottieni_storico_lista(Data data){
    if (data == NULL) {
        return NULL;
    }

    return duplica_lista_prenotazioni(data->storico);
}

/*
 * Funzione: aggiungi_a_storico_lista
 * ----------------------------------
 * Aggiunge una prenotazione allo storico dell'utente.
 *
 * Implementazione:
 *    - Verifica che `data` non sia NULL.
 *    - Chiama `aggiungi_prenotazione_lista` per inserire la prenotazione.
 *    - Se il risultato è valido, aggiorna il campo `storico` e incrementa `numero_prenotazioni`.
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
Byte aggiungi_a_storico_lista(Data data, Prenotazione prenotazione) {
    if (data == NULL) {
        return 0;
    }

    Prenotazione p = duplica_prenotazione(prenotazione);
    ListaPre temp = aggiungi_prenotazione_lista(data->storico, p);

    if(temp == NULL){
        distruggi_prenotazione(p);
        return 0;
    }

    data->storico = temp;
    data->numero_prenotazioni +=1;

    return temp != NULL;
}

/*
 * Funzione: rimuovi_da_storico_lista
 * ----------------------------------
 * Rimuove una prenotazione dallo storico dell'utente.
 *
 * Implementazione:
 *    - Verifica che `data` non sia NULL.
 *    - Chiama `rimuovi_prenotazione_lista`.
 *    - Se il contatore `numero_prenotazioni` è maggiore di 0, lo decrementa.
 *    - Ritorna se la lista risultante è valida.
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
Byte rimuovi_da_storico_lista(Data data, Prenotazione prenotazione) {
    if (data == NULL) {
        return 0;
    }

    data->storico = rimuovi_prenotazione_lista(data->storico, prenotazione);

    if(data->numero_prenotazioni) data->numero_prenotazioni -=1;

    return data->storico != NULL;
}

/*
 * Funzione: ottieni_vettore_storico
 * ---------------------------------
 * Converte la lista dello storico delle prenotazioni in un array.
 *
 * Implementazione:
 *    - Verifica la validità dei parametri.
 *    - Alloca un array di dimensione `numero_prenotazioni`.
 *    - Scorre la lista e copia ciascun elemento nell’array.
 *    - Imposta `*dimensione` con il numero di elementi copiati.
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
 * Restituisce il numero totale di prenotazioni associate a una struttura `Data`.
 *
 * Implementazione:
 *    - Se `data` è NULL, ritorna -1 (cast implicito a unsigned darà valore massimo).
 *    - Altrimenti, ritorna `numero_prenotazioni`.
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
unsigned int ottieni_numero_prenotazioni(Data data){
    if (data == NULL) {
        return 0;
    }
    return data->numero_prenotazioni;
}

/*
 * Funzione: imposta_numero_prenotazioni
 * -------------------------------------
 * Imposta manualmente il numero di prenotazioni in una struttura `Data`.
 *
 * Implementazione:
 *    - Verifica che `data` non sia NULL.
 *    - Imposta `numero_prenotazioni` con il valore dato.
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
void imposta_numero_prenotazioni(Data data, int numero_prenotazioni){
    if (data == NULL) {
        return;
    }
    data->numero_prenotazioni = numero_prenotazioni;
}

/*
 * Funzione: imposta_storico_lista
 * -------------------------------
 * Imposta direttamente la lista dello storico in una struttura `Data`.
 *
 * Implementazione:
 *    - Verifica che `data` non sia NULL.
 *    - Assegna `lista_prenotazione` al campo `storico`.
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
void imposta_storico_lista(Data data, ListaPre lista_prenotazione){
    if (data == NULL) {
        return;
    }

    data->storico = lista_prenotazione;
}
