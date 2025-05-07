#include <stdio.h>

typedef struct{
  int value;
  struct BTree* left;
  struct BTree* right;
  }BTree;

typedef struct {
  char* targa;
  char* modello;
  char* descrizione;
  double tariffa;
  BTree prenotazioni;
  }Veicoli;

Veicoli add_Vehicle(Veicoli* veicoli);
Veicoli remove_Vehicle(Veicoli* veicoli);
Veicoli get_Vehicle(Veicoli* veicoli);