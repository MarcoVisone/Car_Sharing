#ifndef VEICOLO_H
#define VEICOLO_H

#include "adt/btree.h"
#include "strutture_dati/byte.h"

typedef struct veicolo *veicolo;

char* getTarga(veicolo *v);

void setTarga(veicolo *v, char *targa);

char* getModello(veicolo *v);

void setModello(veicolo *v, char *modello);

char* getDescrizione(veicolo *v);

void setDescrizione(veicolo *v, char *descrizione);

double getTariffa(veicolo *v);

void setTariffa(veicolo *v, double tariffa);

AVLIntervalTree getPrenotazione(veicolo *v);

void setPrenotazione(veicolo *v, AVLIntervalTree prenotazione);

Byte confrontaTarghe(veicolo *v, char *targa);

char* veicoloToString(veicolo *v);

#endif //VEICOLO_H
