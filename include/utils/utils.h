#ifndef UTILS_H
#define UTILS_H

#include "strutture_dati/tabella_veicoli.h"

/*
 * Funzione: genera_tabella_veicoli
 * --------------------------------
 * Crea e inizializza una tabella di veicoli con il numero specificato di veicoli.
 *
 * Parametri:
 *    numero_veicoli: numero intero che rappresenta la dimensione della tabella
 *
 * Ritorna:
 *    una nuova tabella di veicoli allocata dinamicamente,
 *    NULL in caso di fallimento nell'allocazione
 */
TabellaVeicoli genera_tabella_veicoli(unsigned int numero_veicoli);

/*
 * Funzione: mia_strdup
 * -------------------
 * Duplica una stringa allocando nuova memoria.
 *
 * Parametri:
 *    s: puntatore alla stringa originale da duplicare
 *
 * Ritorna:
 *    un nuovo puntatore a una copia della stringa s,
 *    NULL se l'allocazione della memoria fallisce
 */
char* mia_strdup(const char* s);

/*
 * Funzione: controllo_password
 * ----------------------------
 * Controlla se la password soddisfa i criteri di sicurezza definiti.
 *
 * Parametri:
 *    password: stringa che rappresenta la password da controllare
 *
 * Ritorna:
 *    Byte 1 se la password è valida secondo i criteri,
 *    0 se la password non è valida
 */
Byte controllo_password(char* password);

#endif //UTILS_H
