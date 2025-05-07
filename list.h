#include <stdio.h>
#include "utente.h"
#include "veicoli.h"

struct node_users{
  Utente* user;
  struct node* next;
};

struct node_vehicles{
  Veicoli* veicoli;
  struct node* next;
  };

  Utente new_list_u();
  Veicoli new_list_v();
  Utente delete_list_u(Utente* utente);
  Veicoli delete_list_v(Veicoli* veicoli);