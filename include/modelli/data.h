/*
 * Autore: Antonio Sicignano
 * Data: 09/05/2025
 */

#ifndef DATA_H
#define DATA_H
#define ERRORE_FREQUENZA -2
typedef struct data *Data;
typedef struct nodo *ListaPre;
typedef struct prenotazione *Prenotazione;

Data crea_data();
void distruggi_data(Data data);
ListaPre ottieni_storico_lista(Data data);
ListaPre aggiungi_a_storico_lista(Data data, Prenotazione prenotazione);
ListaPre rimuovi_da_storico_lista(Data data, Prenotazione prenotazione);
int ottieni_frequenza_lista(Data data);
void azzera_frequenza(Data data);
#endif //DATA_H
