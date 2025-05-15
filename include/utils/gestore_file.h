#ifndef GESTORE_FILE_H
#define GESTORE_FILE_H
typedef struct veicolo *Veicolo;

void salva_vettore_veicoli(const char *nome_file, Veicolo vettore[], int num_veicoli);

int carica_vettore_veicoli(const char *nome_file, Veicolo vettore[], int max_veicoli);

#endif //GESTORE_FILE_H
