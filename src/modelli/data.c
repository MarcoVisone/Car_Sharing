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
 * - Alloca memoria per la struttura `Data` con `calloc`, inizializzando a 0.
 * - Inizializza il campo `storico` con una lista vuota.
 * - Imposta a zero il numero di prenotazioni.
 *
 * Parametri:
 * - Nessuno.
 *
 * Pre-condizioni:
 * - Deve essere disponibile memoria sufficiente per allocare la struttura `Data`.
 * - La funzione `crea_lista()` deve essere disponibile, correttamente implementata e in grado di restituire una lista valida.
 * - Il sistema deve consentire l'uso dell'heap tramite `calloc`.
 *
 * Post-condizioni:
 * - La struttura `Data` è pronta per l'uso, con lista storica vuota e contatore a zero.
 *
 * Ritorna:
 * - Puntatore alla nuova struttura `Data`, oppure NULL se l'allocazione fallisce.
 *
 * Side-effect:
 * - Alloca memoria.
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
 * - Verifica che `data` non sia NULL.
 * - Chiama `distruggi_lista_prenotazione` per liberare lo storico.
 * - Libera la memoria della struttura stessa.
 *
 * Parametri:
 * data: puntatore alla struttura `Data` da distruggere.
 *
 * Pre-condizioni:
 * - `data` deve essere un puntatore valido o NULL.
 *
 * Post-condizioni:
 * - La memoria associata a `data` è stata liberata.
 *
 * Ritorna:
 * - Nessun valore restituito (void).
 *
 * Side-effect:
 * - Dealloca memoria.
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
 * - Verifica che `data` non sia NULL.
 * - Chiama `duplica_lista_prenotazioni` per restituire una copia della lista.
 *
 * Parametri:
 * data: struttura `Data` contenente lo storico.
 *
 * Pre-condizioni:
 * - `data` deve essere valido.
 *
 * Post-condizioni:
 * - Nessuna modifica alla struttura originale.
 *
 * Ritorna:
 * - Una copia della lista delle prenotazioni, oppure NULL se errore.
 *
 * Side-effect:
 * - Alloca memoria per la copia della lista.
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
 * - Verifica che `data` non sia NULL.
 * - Chiama `aggiungi_prenotazione_lista` per inserire la prenotazione.
 * - Se il risultato è valido, aggiorna il campo `storico` e incrementa `numero_prenotazioni`.
 *
 * Parametri:
 * data: puntatore alla struttura `Data`.
 * prenotazione: prenotazione da aggiungere.
 *
 * Pre-condizioni:
 * - `data` e `prenotazione` devono essere validi.
 *
 * Post-condizioni:
 * - La prenotazione è stata aggiunta allo storico.
 *
 * Ritorna:
 * - 1 se l'aggiunta è andata a buon fine, 0 altrimenti.
 *
 * Side-effect:
 * - Modifica la lista `storico` e incrementa il contatore.
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
 * Rimuove una prenotazione dallo storico dell'utente.
 *
 * Implementazione:
 * - Verifica che `data` non sia NULL.
 * - Chiama `rimuovi_prenotazione_lista`.
 * - Se il contatore `numero_prenotazioni` è maggiore di 0, lo decrementa.
 * - Ritorna se la lista risultante è valida.
 *
 * Parametri:
 * data: struttura `Data` da cui rimuovere.
 * prenotazione: prenotazione da rimuovere.
 *
 * Pre-condizioni:
 * - `data` e `prenotazione` devono essere validi.
 *
 * Post-condizioni:
 * - La prenotazione viene rimossa, e il contatore aggiornato.
 *
 * Ritorna:
 * - 1 se la lista risultante non è NULL, 0 se è NULL.
 *
 * Side-effect:
 * - Modifica la lista e il contatore.
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
 * - Verifica la validità dei parametri.
 * - Alloca un array di dimensione `numero_prenotazioni`.
 * - Scorre la lista e copia ciascun elemento nell’array.
 * - Imposta `*dimensione` con il numero di elementi copiati.
 *
 * Parametri:
 * data: struttura `Data` contenente lo storico.
 * dimensione: puntatore a variabile dove scrivere la dimensione dell’array restituito.
 *
 * Pre-condizioni:
 * - `data` e `dimensione` devono essere validi.
 *
 * Post-condizioni:
 * - Viene restituito un array contenente tutte le prenotazioni.
 *
 * Ritorna:
 * - Puntatore all’array delle prenotazioni, oppure NULL in caso di errore.
 *
 * Side-effect:
 * - Alloca memoria per l’array restituito.
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
 * - Se `data` è NULL, ritorna -1 (cast implicito a unsigned darà valore massimo).
 * - Altrimenti, ritorna `numero_prenotazioni`.
 *
 * Parametri:
 * data: struttura `Data` di riferimento.
 *
 * Pre-condizioni:
 * - `data` può essere NULL.
 *
 * Post-condizioni:
 * - Nessuna modifica a `data`.
 *
 * Ritorna:
 * - Il numero di prenotazioni oppure -1 (come unsigned) se `data` è NULL.
 *
 * Side-effect:
 * - Nessuno.
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
 * Imposta manualmente il numero di prenotazioni in una struttura `Data`.
 *
 * Implementazione:
 * - Verifica che `data` non sia NULL.
 * - Imposta `numero_prenotazioni` con il valore dato.
 *
 * Parametri:
 * data: struttura `Data` da modificare.
 * numero_prenotazioni: valore da impostare.
 *
 * Pre-condizioni:
 * - `data` deve essere valido.
 *
 * Post-condizioni:
 * - Il campo `numero_prenotazioni` viene aggiornato.
 *
 * Ritorna:
 * - Nessun valore restituito (void).
 *
 * Side-effect:
 * - Modifica lo stato della struttura.
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
 * - Verifica che `data` non sia NULL.
 * - Assegna `lista_prenotazione` al campo `storico`.
 *
 * Parametri:
 * data: struttura `Data` da modificare.
 * lista_prenotazione: lista da assegnare al campo `storico`.
 *
 * Pre-condizioni:
 * - `data` deve essere valido.
 *
 * Post-condizioni:
 * - Il campo `storico` della struttura viene aggiornato.
 *
 * Ritorna:
 * - Nessun valore restituito (void).
 *
 * Side-effect:
 * - Modifica la lista associata.
 */
void imposta_storico_lista(Data data, ListaPre lista_prenotazione){
    if (data == NULL) {
        return;
    }

    data->storico = lista_prenotazione;
}
