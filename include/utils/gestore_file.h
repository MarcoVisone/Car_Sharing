#ifndef GESTORE_FILE_H
#define GESTORE_FILE_H
typedef struct veicolo *Veicolo;
typedef struct utente *Utente;

void salva_vettore_veicoli(const char *nome_file, Veicolo vettore[], int num_veicoli);

int carica_vettore_veicoli(const char *nome_file, Veicolo vettore[], int max_veicoli);

void salva_vettore_utenti(const char *nome_file, Utente vettore[], int num_utenti);

int carica_vettore_utenti(const char *nome_file, Utente vettore[], int max_utenti);

#endif //GESTORE_FILE_H
