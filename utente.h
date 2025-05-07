#include <stdio.h>
#include "list.h"
#include "data.h"

typedef char Byte;

typedef struct{
  char* email;
  char* password;
  char* name;
  char* surname;
  Byte permission;
  Data data;
}Utente;

Utente add_User(Utente* utente);
Utente remove_User(Utente* utente);
Utente get_User(Utente* utente);

