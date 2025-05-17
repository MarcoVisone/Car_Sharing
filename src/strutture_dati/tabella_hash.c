/*
 * Autore: Russo Nello Manuel
 * Data: 09/05/2025
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "strutture_dati/tabella_hash.h"
#include "strutture_dati/lista.h"
#include "utils/utils.h"

#define PERCENTUALE_DI_RIEMPIMENTO 0.75

static unsigned long djb2_hash(const char *str);

struct item{
    char *chiave;
	void *valore;
};

struct tabella_hash{
	unsigned int grandezza;
	Nodo *buckets;
	unsigned int numero_buckets;
};

/*
 * Funzione: djb2_hash
 * -------------------
 *
 * Calcola un valore hash per una stringa usando l'algoritmo DJB2.
 *
 * Implementazione:
 *    - Inizializza il valore di hash a 5381 che è stato scelto da djb (Daniel J. Bernstein) perché
 *    è il numero che permette di generare meno collisioni
 *    - Per ogni carattere della stringa:
 *        - Moltiplica il valore corrente di hash per 33 (ottenuto con (hash << 5) + hash).
 *        - Aggiunge il valore del carattere corrente.
 *    - Restituisce il valore finale di hash.
 *
 * Parametri:
 *    str: stringa di input di cui calcolare l'hash
 *
 * Pre-condizioni:
 *    str: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce un numero intero non negativo che rappresenta il valore hash della stringa
 */
static unsigned long djb2_hash(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {  // Aggiunto parentesi extra
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

/*
 * Funzione: nuova_tabella_hash
 * -----------------------------
 *
 * crea una nuova tabella hash per la memorizzazione degli oggetti con la dimensione specificata
 *
 * Implementazione:
 *    Alloca memoria per una struttura TabellaHash e per un array di bucket.
 *    Ogni bucket è inizializzato come una nuova lista vuota creata con crea_lista().
 *
 * Parametri:
 *    grandezza: dimensione iniziale della tabella hash
 *
 * Pre-condizioni:
 *    grandezza: deve essere maggiore di 0
 *
 * Post-condizioni:
 *    restituisce un puntatore a una nuova struttura TabellaHash se l'allocazione è riuscita,
 *    altrimenti restituisce NULL
 *
 * Side-effect:
 *   alloca memoria dinamicamente per la tabella hash e i suoi bucket
 */
TabellaHash nuova_tabella_hash(unsigned int grandezza){
	if(grandezza <= 0) return NULL;

	TabellaHash tabella_hash = malloc(sizeof(struct tabella_hash));
	if(tabella_hash == NULL){
		return NULL;
	}

	tabella_hash->numero_buckets = 0;
	tabella_hash->grandezza = grandezza;
	tabella_hash->buckets = calloc(grandezza, sizeof(Nodo));

	if(tabella_hash->buckets == NULL){
		free(tabella_hash);
		return NULL;
	}

	unsigned int i = 0;
	for(i = 0; i < grandezza; i++){
		tabella_hash->buckets[i] = crea_lista();
	}

	return tabella_hash;
}

/*
 * Funzione: distruggi_tabella
 * -----------------------------
 *
 * libera la memoria allocata per una tabella hash, inclusi tutti gli elementi memorizzati
 *
 * Implementazione:
 *    Scorre ogni bucket della tabella e distrugge la lista associata, liberando ogni nodo e il valore associato
 *    tramite la funzione funzione_distruggi_valore in caso essa non sia NULL.
 *    Poi libera l'array dei bucket e la struttura TabellaHash.
 *
 * Parametri:
 *    tabella_hash: puntatore alla tabella hash da eliminare
 *    funzione_distruggi_valore: funzione da applicare ad ogni valore per liberare la memoria associata
 *
 * Pre-condizioni:
 *    tabella_hash: non deve essere NULL
 *
 * Post-condizioni:
 *    non restituisce nulla
 *
 * Side-effect:
 *    libera la memoria associata alla struttura TabellaHash e ai suoi elementi
 */
void distruggi_tabella(TabellaHash tabella_hash, void (*funzione_distruggi_valore)(void *)){
	if(tabella_hash == NULL) return;

	for(unsigned int i = 0; i < tabella_hash->grandezza; i++){
		Nodo curr = tabella_hash->buckets[i];
		while(!lista_vuota(curr)){
			struct item *item = (struct item *)ottieni_item(curr);
			free(item->chiave);
			free(item);
		}
		Nodo temp = ottieni_prossimo(curr);
		distruggi_nodo(curr, funzione_distruggi_valore);
        curr = temp;
	}
	free(tabella_hash->buckets);
	free(tabella_hash);
}

/*
 * Funzione: ridimensiona_tabella_hash
 * -----------------------------------
 *
 * raddoppia la dimensione della tabella hash per ridurre i conflitti e migliorare le prestazioni.
 *
 * Implementazione:
 *    - Calcola una nuova dimensione doppia rispetto all'attuale.
 *    - Alloca un nuovo array di bucket inizializzati come liste vuote.
 *    - Scorre tutti i bucket esistenti e reinserisce ogni elemento nella nuova posizione
 *      calcolata in base all'hash della chiave e alla nuova dimensione.
 *    - Dopo il reinserimento, libera i nodi della vecchia tabella (ma non i dati, che vengono mantenuti).
 *    - Sostituisce l'array di bucket e la dimensione nella struttura TabellaHash
 *
 * Parametri:
 *    tabella_hash: puntatore alla struttura della tabella hash da ridimensionare
 *
 * Pre-condizioni:
 *    tabella_hash: non deve essere NULL, e deve contenere bucket validi
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    la tabella hash avrà il doppio della dimensione iniziale
 *    e conterrà tutti gli elementi precedenti nei nuovi bucket
 */
static void ridimensiona_tabella_hash(TabellaHash tabella_hash){
    unsigned int nuova_grandezza = tabella_hash->grandezza * 2;
    Nodo *nuovi_buckets = calloc(nuova_grandezza, sizeof(Nodo));

    if (nuovi_buckets == NULL) return;

    for (unsigned int j = 0; j < nuova_grandezza; j++) {
        nuovi_buckets[j] = crea_lista();
    }

    for (unsigned int i = 0; i < tabella_hash->grandezza; i++) {
        Nodo curr = tabella_hash->buckets[i];
        while (!lista_vuota(curr)) {
            struct item *item = (struct item *)ottieni_item(curr);
            unsigned long nuovo_indice = djb2_hash(item->chiave) % nuova_grandezza;

            nuovi_buckets[nuovo_indice] = aggiungi_nodo(item, nuovi_buckets[nuovo_indice]);

            Nodo next = ottieni_prossimo(curr);
            distruggi_nodo(curr, NULL);  //distruggi solo nodo, non item
            curr = next;
        }
    }

    free(tabella_hash->buckets);
    tabella_hash->buckets = nuovi_buckets;
    tabella_hash->grandezza = nuova_grandezza;
}

/*
 * Funzione: inserisci_in_tabella
 * ------------------------------------
 *
 * inserisce un elemento nella tabella hash associando una chiave a un valore
 *
 * Implementazione:
 *    - Calcola la percentuale di riempimento e ridimensiona la tabella se necessario.
 *    - Calcola l'indice del bucket usando una funzione hash (djb2_hash).
 *    - Scorre la lista associata a quel bucket per verificare se la chiave è già presente.
 *    - Se la chiave è duplicata, l'inserimento viene annullato.
 *    - Altrimenti, crea una nuova struttura item, duplica la chiave, e la inserisce
 *      in testa alla lista del bucket.
 *    - Incrementa il numero di elementi della tabella.
 *
 * Parametri:
 *    tabella_hash: puntatore alla tabella hash
 *    chiave: stringa contenente la chiave dell'elemento
 *    valore: puntatore al valore da associare alla chiave
 *
 * Pre-condizioni:
 *    tabella_hash: non deve essere NULL
 *    chiave: non deve essere NULL
 *    valore: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce 1 se l'inserimento è avvenuto con successo, 0 in caso di errore
 *
 * Side-effect:
 *    modifica la tabella hash aggiungendo un nuovo elemento e ridimensiona la tabella se necessario
 */
Byte inserisci_in_tabella(TabellaHash tabella_hash, char *chiave, void *valore){
	if(tabella_hash == NULL || chiave == NULL || valore == NULL) return 0;

	// Limita la percentuale di collisioni ad una percentuale minore del 100%
	double percentuale = (double)tabella_hash->numero_buckets / (double)tabella_hash->grandezza;;
	if(percentuale > PERCENTUALE_DI_RIEMPIMENTO){
		ridimensiona_tabella_hash(tabella_hash);
	}

	unsigned long indice = djb2_hash(chiave) % tabella_hash->grandezza;

	Nodo lista = tabella_hash->buckets[indice];
	Nodo i;

	for(i = tabella_hash->buckets[indice]; !lista_vuota(i); i = ottieni_prossimo(i)){
		struct item *nuovo_item = (struct item *)ottieni_item(i);
		if(strcmp(nuovo_item->chiave, chiave) == 0){
			return 0;
		}
	}
	struct item *nuovo_item = malloc(sizeof(struct item));
	if(nuovo_item == NULL){
		return 0;
	}

	nuovo_item->chiave = mia_strdup(chiave); //alloca una nuova stringa chiave dentro alla chiave
	nuovo_item->valore = valore;
	tabella_hash->buckets[indice] = aggiungi_nodo(nuovo_item, lista);
	tabella_hash->numero_buckets++;
	return 1;
}

/*
 * Funzione: cancella_dalla_tabella
 * -----------------------------------
 *
 * rimuove un oggetto dalla tabella hash utilizzando la chiave fornita
 *
 * Implementazione:
 *    - Calcola l'indice del bucket tramite la funzione hash.
 *    - Scorre la lista associata al bucket, confrontando ogni chiave.
 *    - Se trova la chiave, rimuove il nodo aggiornando il puntatore del nodo precedente.
 *    - Libera la memoria associata alla chiave e al valore tramite la funzione passata.
 *    - Aggiorna il conteggio degli elementi nella tabella.
 *    - Restituisce 1 in caso di successo, 0 se la chiave non è presente.
 *
 * Parametri:
 *    tabella_utenti: puntatore alla tabella hash
 *    chiave: stringa contenente la chiave dell'elemento da rimuovere
 *    funzione_distruggi_valore: funzione da applicare al valore per liberare la memoria associata
 *
 * Pre-condizioni:
 *    tabella_hash: non deve essere NULL
 *    chiave: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce 1 se la rimozione ha avuto successo, 0 se la chiave non è presente
 *    o se si verifica un errore
 *
 * Side-effect:
 *    - modifica la tabella hash rimuovendo l'elemento associato alla chiave
 *    - libera memoria dinamicamente associata al nodo e al valore
 */
Byte cancella_dalla_tabella(TabellaHash tabella_hash, char *chiave, void (*funzione_distruggi_valore)(void *)){
	if(tabella_hash == NULL || chiave == NULL) return 0;

	unsigned long indice = djb2_hash(chiave) % tabella_hash->grandezza;
	Nodo *head = &tabella_hash->buckets[indice];
	Nodo curr = *head;
	Nodo prec = NULL;

	/* Scorre la lista finchè non è vuota, quando trova il nodo con la chiave corrispondente
	 * lo elimina facendo puntare il next del nodo precedente al next del nodo attuale
	 */
	while(!lista_vuota(curr)){
		struct item *item = (struct item *)ottieni_item(curr);
		if(strcmp(item->chiave, chiave) == 0){
            if(prec){
				imposta_prossimo(prec, ottieni_prossimo(curr));
			}
            else{
				*head = ottieni_prossimo(curr);
			}
			free(item->chiave);
			free(item);
			distruggi_nodo(curr, funzione_distruggi_valore);
			tabella_hash->numero_buckets--;
			return 1;
		}
		prec = curr;
		curr = ottieni_prossimo(curr);
	}
	return 0;
}

/*
 * Funzione: cerca_in_tabella
 * ---------------------------------
 *
 * cerca un elemento nella tabella hash tramite la chiave specificata
 *
 * Implementazione:
 *    - Calcola l'indice del bucket associato alla chiave usando la funzione di hash.
 *    - Scorre la lista collegata a quel bucket.
 *    - Confronta ciascuna chiave con quella cercata.
 *    - Se trova la chiave, restituisce il valore associato.
 *    - Se non trova la chiave, restituisce NULL.
 *
 * Parametri:
 *    tabella_hash: puntatore alla tabella hash
 *    chiave: stringa contenente la chiave da cercare
 *
 * Pre-condizioni:
 *    tabella_hash: non deve essere NULL
 *    chiave: non deve essere NULL
 *
 * Post-condizioni:
 *    Se la chiave è presente, restituisce il puntatore al valore associato;
 *    altrimenti restituisce NULL
 */
void *cerca_in_tabella(TabellaHash tabella_hash, char *chiave){
	if(tabella_hash == NULL || chiave == NULL) return NULL;

	unsigned long indice = djb2_hash(chiave) % tabella_hash->grandezza;
	Nodo curr = tabella_hash->buckets[indice];

	while(!lista_vuota(curr)){
		struct item *item = (struct item *)ottieni_item(curr);
		if(strcmp(item->chiave, chiave) == 0){
			return item->valore;
		}
		curr = ottieni_prossimo(curr);
	}
	return NULL;
}

/*
 * Funzione: ottieni_vettore
 * -------------------------
 *
 * estrae tutti i valori contenuti nella tabella hash e li restituisce in un array.
 *
 * Implementazione:
 *    - Alloca un array di puntatori void* con dimensione pari al numero di elementi presenti.
 *    - Scorre ogni bucket della tabella hash.
 *    - Per ogni nodo nella lista del bucket, estrae il valore e lo inserisce nel vettore.
 *    - Al termine, assegna al parametro dimensione il numero di elementi raccolti.
 *    - Restituisce il puntatore al vettore popolato.
 *
 * Parametri:
 *    tabella_hash: puntatore alla tabella hash
 *    dimensione: puntatore ad un intero dove verrà memorizzata la dimensione del vettore restituito
 *
 * Pre-condizioni:
 *    tabella_hash: non deve essere NULL
 *    dimensione: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce un array di puntatori ai valori presenti nella tabella hash,
 *    oppure NULL se ci sono errori o la tabella è vuota.
 *
 * Side-effect:
 *    alloca dinamicamente memoria per il vettore risultante
 */
void **ottieni_vettore(TabellaHash tabella_hash, unsigned int *dimensione){
    if(tabella_hash == NULL || dimensione == NULL) return NULL;

    void **vettore = malloc(sizeof(void *) * tabella_hash->numero_buckets);
    if(vettore == NULL){
        return NULL;
    }

    unsigned int n = 0;

    for(unsigned int i = 0; i < tabella_hash->grandezza; i++){
        Nodo curr = tabella_hash->buckets[i];
        while(!lista_vuota(curr)){
            struct item *item = (struct item *)ottieni_item(curr);
            vettore[n++] = item->valore;
            curr = ottieni_prossimo(curr);
        }
    }

    *dimensione = n;
    return vettore;
}
