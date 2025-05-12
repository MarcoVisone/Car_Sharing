/*
 * Autore: Marco Visone
 * Data: 09/05/2025
 */

#include "strutture_dati/lista_prenotazione.h"
#include "strutture_dati/lista.h"
#include "modelli/prenotazione.h"
#include "modelli/intervallo.h"

#include <stddef.h>

ListaPre aggiungi_prenotazione_lista(ListaPre l, Prenotazione p){
    return aggiungi_nodo(p, l);
}

static void distruggi_prenotazione_t(void *prenotazione){
	Prenotazione p = (Prenotazione)prenotazione;
	distruggi_prenotazione(p);
}

ListaPre rimuovi_prenotazione_lista(ListaPre l, Prenotazione p){
    ListaPre curr = l;
    ListaPre prev = NULL;
    while(!lista_vuota(curr)){
        Prenotazione pre = ottieni_item(curr);
        if(compara_intervalli(ottieni_intervallo_prenotazione(pre), ottieni_intervallo_prenotazione(p)) == 0){
            if(prev){
               imposta_prossimo(prev, ottieni_prossimo(curr));
            }
            else{
              return ottieni_prossimo(curr);
            }
			distruggi_nodo(curr, distruggi_prenotazione_t);
        }
		prev = curr;
		curr = ottieni_prossimo(curr);
    }
	return l;
}



Prenotazione ottieni_prenotazione_lista(ListaPre l){
    return ottieni_item(l);
}
