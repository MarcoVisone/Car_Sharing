/*
 * Autore: Marco Visone
 * Data: 06/05/2025
 */

#ifndef PRENOTAZIONI_H
#define PRENOTAZIONI_H

#define OK 1
#define OCCUPATO 0

#include "modelli/byte.h"

typedef struct intervallo *Intervallo;
typedef struct prenotazione *Prenotazione;
typedef struct albero *Prenotazioni;

/*
 * Funzione: crea_prenotazioni
 * ---------------------------
 * Crea e inizializza una nuova struttura `Prenotazioni` (un albero AVL vuoto).
 *
 * Parametri:
 * Nessuno.
 *
 * Pre-condizioni:
 * - Nessuna.
 *
 * Post-condizioni:
 * - Restituisce un puntatore a una nuova struttura `Prenotazioni` inizializzata
 * se l'allocazione ha successo.
 * - Restituisce NULL in caso di fallimento dell'allocazione di memoria.
 *
 * Side-effect:
 * - Alloca memoria dinamicamente per la struttura `Prenotazioni`. Questa memoria
 * deve essere liberata successivamente chiamando `distruggi_prenotazioni`.
 */
Prenotazioni crea_prenotazioni();

/*
 * Funzione: distruggi_prenotazioni
 * --------------------------------
 * Dealloca tutta la memoria associata a una struttura `Prenotazioni`,
 * inclusi tutti i nodi dell'albero e le `Prenotazione` contenute in essi.
 *
 * Parametri:
 * prenotazioni: il puntatore alla struttura `Prenotazioni` da distruggere.
 *
 * Pre-condizioni:
 * - `prenotazioni` può essere NULL (gestito internamente per robustezza).
 *
 * Post-condizioni:
 * - Tutta la memoria dinamicamente allocata per l'albero delle prenotazioni
 * e i suoi nodi viene liberata.
 *
 * Side-effect:
 * - Dealloca memoria dinamicamente.
 */
void distruggi_prenotazioni(Prenotazioni prenotazioni);

/*
 * Funzione: aggiungi_prenotazione
 * -------------------------------
 * Tenta di aggiungere una nuova prenotazione all'albero delle prenotazioni.
 *
 * Parametri:
 * albero: il puntatore alla struttura `Prenotazioni` a cui aggiungere la prenotazione.
 * prenotazione: la prenotazione da aggiungere.
 *
 * Pre-condizioni:
 * - `albero` non deve essere NULL.
 * - `prenotazione` non deve essere NULL.
 *
 * Post-condizioni:
 * - Restituisce `OK` (0) se l'inserimento è avvenuto con successo e senza sovrapposizioni.
 * - Restituisce `OCCUPATO` (1) se la `prenotazione` si sovrappone con una esistente.
 * - Restituisce 0 in caso di altri errori (es. fallimento dell'allocazione).
 *
 * Side-effect:
 * - Modifica la struttura dell'albero `prenotazioni` aggiungendo un nodo.
 * - Incrementa il contatore `num_nodi`.
 * - Può allocare memoria (tramite `aggiungi_prenotazione_t`).
 */
Byte aggiungi_prenotazione(Prenotazioni prenotazioni, Prenotazione p);

/*
 * Funzione: controlla_prenotazione
 * --------------------------------
 * Verifica se un dato intervallo di tempo è disponibile per una nuova prenotazione
 * nell'albero delle prenotazioni, ovvero se non si sovrappone con alcuna prenotazione esistente.
 *
 * Parametri:
 * prenotazioni: il puntatore alla struttura `Prenotazioni` da interrogare.
 * i: l'intervallo di tempo da verificare.
 *
 * Pre-condizioni:
 * - `prenotazioni` non deve essere NULL.
 * - `i` non deve essere NULL.
 *
 * Post-condizioni:
 * - Restituisce `OCCUPATO` (1) se l'intervallo `i` si sovrappone con almeno una prenotazione esistente.
 * - Restituisce `OK` (0) se l'intervallo `i` è completamente disponibile.
 * - Restituisce `OK` (0) se `prenotazioni` o `i` sono NULL (comportamento robusto).
 *
 * Side-effect:
 * - Nessuno. La funzione esegue solo una query sullo stato dell'albero.
 */
Byte controlla_prenotazione(Prenotazioni prenotazioni, Intervallo i);

/*
 * Funzione: cancella_prenotazione
 * ------------------------------
 * Rimuove una prenotazione specifica dall'albero delle prenotazioni,
 * identificandola tramite il suo intervallo di tempo.
 *
 * Parametri:
 * prenotazioni: il puntatore alla struttura `Prenotazioni` da cui rimuovere la prenotazione.
 * i: l'intervallo di tempo della prenotazione da rimuovere.
 *
 * Pre-condizioni:
 * - `prenotazioni` non deve essere NULL.
 * - `i` non deve essere NULL.
 *
 * Post-condizioni:
 * - Restituisce 1 se la prenotazione corrispondente all'intervallo `i` è stata
 * trovata e rimossa con successo.
 * - Restituisce 0 se la prenotazione non è stata trovata o in caso di input NULL.
 *
 * Side-effect:
 * - Modifica la struttura dell'albero `prenotazioni`.
 * - Decrementa il contatore `num_nodi` se la cancellazione ha successo.
 * - Dealloca memoria (tramite `cancella_prenotazione_t`).
 */
Byte cancella_prenotazione(Prenotazioni prenotazioni, Intervallo i);

/*
 * Funzione: ottieni_vettore_prenotazioni_ordinate
 * -----------------------------------------------
 * Estrae tutte le prenotazioni dall'albero e le restituisce in un array
 * allocato dinamicamente, ordinate cronologicamente in base al loro timestamp di inizio.
 *
 * Parametri:
 * prenotazioni: il puntatore alla struttura `Prenotazioni` da cui estrarre le prenotazioni.
 * size: un puntatore a un `unsigned int` dove verrà salvata la dimensione dell'array risultante.
 *
 * Pre-condizioni:
 * - `prenotazioni` non deve essere NULL.
 * - `size` non deve essere NULL.
 *
 * Post-condizioni:
 * - Restituisce un puntatore a un array di `Prenotazione` allocato dinamicamente
 * contenente tutte le prenotazioni dell'albero, ordinate per data di inizio.
 * - `*size` conterrà il numero di elementi nell'array.
 * - Restituisce NULL in caso di errori (es. fallimento dell'allocazione di memoria o input NULL).
 *
 * Side-effect:
 * - Alloca memoria dinamicamente per l'array risultante. La memoria deve essere
 * liberata dal chiamante (`free`).
 */
Prenotazione *ottieni_vettore_prenotazioni_ordinate(Prenotazioni prenotazioni, unsigned int *size);

/*
 * Funzione: ottieni_vettore_prenotazioni_per_file
 * ----------------------------------------------
 * Estrae tutte le prenotazioni dall'albero e le restituisce in un array
 * allocato dinamicamente, in ordine di livello (BFS - Breadth-First Search).
 * Questo metodo è particolarmente utile per salvare l'albero su file e poi
 * ricostruirlo, poiché preserva la struttura BFS indipendentemente dalle rotazioni AVL.
 *
 * Parametri:
 * prenotazioni: il puntatore alla struttura `Prenotazioni` da cui estrarre le prenotazioni.
 * size: un puntatore a un `unsigned int` dove verrà salvata la dimensione dell'array risultante.
 *
 * Pre-condizioni:
 * - `prenotazioni` non deve essere NULL.
 * - `size` non deve essere NULL.
 *
 * Post-condizioni:
 * - Restituisce un puntatore a un array di `Prenotazione` allocato dinamicamente
 * contenente tutte le prenotazioni dell'albero in ordine di livello.
 * - `*size` conterrà il numero di elementi nell'array.
 * - Restituisce NULL in caso di errori (es. fallimento dell'allocazione di memoria o input NULL).
 *
 * Side-effect:
 * - Alloca memoria dinamicamente per l'array `result` e per la coda temporanea.
 * La memoria dell'array restituito deve essere liberata dal chiamante (`free`).
 */
Prenotazione *ottieni_vettore_prenotazioni_per_file(Prenotazioni prenotazioni, unsigned int *size);

/*
 * Funzione: ottieni_intervallo_disponibile
 * ----------------------------------------
 * Restituisce un intervallo disponibile all'interno di un intervallo dato `i`
 * cercando tra le prenotazioni memorizzate in una struttura `Prenotazioni`.
 *
 * Parametri:
 * prenotazioni: struttura contenente le prenotazioni (albero binario).
 * i: intervallo temporale da verificare per disponibilità.
 *
 * Pre-condizioni:
 * - `prenotazioni` deve essere un puntatore valido a una struttura `Prenotazioni` o NULL.
 * - `i` deve essere un intervallo valido o NULL.
 *
 * Post-condizioni:
 * - Restituisce un intervallo disponibile all'interno di `i` se trovato.
 * - Restituisce NULL se non ci sono intervalli disponibili o se input non valido.
 *
 * Side-effect:
 * - Nessuno diretto, ma la funzione chiamata può allocare memoria.
 * - La memoria dell'intervallo restituito deve essere gestita dal chiamante.
 */
Intervallo ottieni_intervallo_disponibile(Prenotazioni prenotazioni, Intervallo i);

#endif //PRENOTAZIONI_H
