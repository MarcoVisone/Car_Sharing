/*
 * Autore: Russo Nello Manuel
 * Data: 09/05/2025
 */
 #define _POSIX_C_SOURCE 200809L  // Per usare strdup

#include "strutture_dati/tabella_hash.h"
#include <stdlib.h>
#include <string.h>

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

static unsigned long djb2_hash(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {  // Aggiunto parentesi extra
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

TabellaHash nuova_tabella_hash(unsigned int grandezza){
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

void distruggi_tabella(TabellaHash tabella_hash, void (*funzione_distruggi_valore)(void *)){
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

static void ridimensiona_tabella_hash(TabellaHash tabella_hash){
    // Raddoppiare la grandezza serve a mantenere bassa la possibilità di avere collisioni
	unsigned int nuova_grandezza = tabella_hash->grandezza * 2;
	Nodo *nuovi_buckets = calloc(nuova_grandezza, sizeof(Nodo));
	unsigned int i = 0;

	// Si spostano gli elementi dalla tabella hash ai nuovi bucket
	for(i = 0; i < tabella_hash->grandezza; i++){
		Nodo curr = tabella_hash->buckets[i];
		while(!lista_vuota(curr)){
			struct item *item = (struct item *)ottieni_item(curr);
			unsigned long nuovo_indice = djb2_hash(item->chiave) % nuova_grandezza;
			nuovi_buckets[nuovo_indice] = crea_lista();
			nuovi_buckets[nuovo_indice] = aggiungi_nodo(item, nuovi_buckets[nuovo_indice]);
			Nodo temp = curr;
			curr = ottieni_prossimo(curr);

			/* Libera solo la memoria occupata dal nodo, ma non dall'item
			 * così non c'è bisogno di fare l'operazione di allocare nuova memoria
			 */
			distruggi_nodo(temp, NULL);
		}
	}

	free(tabella_hash->buckets);
	tabella_hash->buckets = nuovi_buckets;
	tabella_hash->grandezza = nuova_grandezza;
}

Byte inserisci_in_tabella(TabellaHash tabella_hash, char *chiave, void *valore){
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

	nuovo_item->chiave = strdup(chiave); //alloca una nuova stringa chiave dentro alla chiave
	nuovo_item->valore = valore;
	tabella_hash->buckets[indice] = aggiungi_nodo(nuovo_item, lista);
	tabella_hash->numero_buckets++;
	return 1;
}

Byte cancella_dalla_tabella(TabellaHash tabella_hash, char *chiave, void (*funzione_distruggi_valore)(void *)){
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

void *cerca_in_tabella(TabellaHash tabella_hash, char *chiave){
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
