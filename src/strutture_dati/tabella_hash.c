/*
* Autore: Russo Nello Manuel
 * Data: 09/05/2025
 */

#include <stdio.h>
#include "strutture_dati/tabella_hash.h"
#include <stdlib.h>
#include <string.h>

#define MAX_LUNGHEZZA_CHIAVE 255 + 1
#define BLOCCO 10

struct item{
    char chiave[MAX_LUNGHEZZA_CHIAVE];
	void *valore;
};

struct tabella_hash{
	unsigned int grandezza;
	Nodo *buckets;
};

static unsigned long djb2_hash(const char str) {
    unsigned long hash = 5381;
    int c;
    while ((c =str++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    return hash;
}

TabellaHash nuova_tabella_hash(int grandezza){
	TabellaHash tabella_hash = malloc(sizeof(struct tabella_hash));
	if(tabella_hash == NULL){
		return NULL;
	}

	tabella_hash->grandezza = grandezza;
	tabella_hash->buckets = calloc(grandezza, sizeof(Nodo));
	if(tabella_hash->buckets == NULL){
		free(tabella_hash);
		return NULL;
	}

	int i = 0;
	for(i = 0; i < grandezza; i++){
		tabella_hash->buckets[i] = crea_lista();
	}

	return tabella_hash;
}

static TabellaHash ridimensiona_tabella_hash(TabellaHash tabella_hash){
	unsigned int nuova_grandezza = tabella_hash->grandezza + BLOCCO;
	Nodo *nuovi_buckets = calloc(nuova_grandezza, sizeof(Nodo));
	int i = 0;
	for(i = 0; i < nuova_grandezza; i++){
		nuovi_buckets[i] = crea_lista();
	}
	for(i = 0; i < tabella_hash->grandezza; i++){
		Nodo curr = tabella_hash->buckets[i];
		while(!lista_vuota(curr)){
			struct item *item = ottieni_item(curr);
		}
	}
}

Byte inserisci_in_tabella(TabellaHash tabella_hash, char *chiave, void *valore){
	unsigned long indice = djb2_hash(chiave) % tabella_hash->grandezza;

	Nodo lista = tabella_hash->buckets[indice];
	Nodo i;
	for(i = tabella_hash->buckets[indice]; !lista_vuota(i); i = ottieni_prossimo(i)){
		struct item *nuovo_item = ottieni_item(i);
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

	return 1;
}

Byte cancella_dalla_tabella(TabellaHash tabella_hash, char *chiave){
	unsigned long indice = djb2_hash(chiave) % tabella_hash->grandezza;

}