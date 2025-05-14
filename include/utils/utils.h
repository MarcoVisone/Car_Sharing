#ifndef UTILS_H
#define UTILS_H

#include "strutture_dati/tabella_veicoli.h"


TabellaVeicoli genera_tabella_veicoli(unsigned int numero_veicoli);

char* mia_strdup(const char* s);

Byte controllo_password(char* password);

#endif //UTILS_H
