/*
 * Autore: Antonio Sicignano
 * Data: 15/05/2025
 */

#ifndef UTILS_H
#define UTILS_H

#include "modelli/byte.h"
typedef struct tabella_hash *TabellaVeicoli;
typedef struct intervallo *Intervallo;


/*
 * Funzione: mia_strdup
 * -------------------
 * Duplica una stringa allocando nuova memoria.
 *
 * Parametri:
 *    s: puntatore alla stringa originale da duplicare
 *
 * Pre-condizioni:
 *    s non deve essere NULL
 *
 * Post-condizione:
 *    ritorna un nuovo puntatore a una copia della stringa s,
 *    oppure NULL se l'allocazione della memoria fallisce
 *
 * Ritorna:
 *    un nuovo puntatore a una copia della stringa s,
 *    NULL se l'allocazione della memoria fallisce
 *
 * Side effects:
 *    Allocazione dinamica di memoria per la nuova stringa duplicata
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
 * Pre-condizioni:
 *    password non deve essere NULL
 *
 * Post-condizione:
 *    ritorna 1 (Byte) se la password è valida,
 *    0 (Byte) se la password non è valida
 *
 * Ritorna:
 *    Byte 1 se la password è valida secondo i criteri,
 *    0 se la password non è valida
 *
 * Side effects:
 *    Nessuno
 */
Byte controllo_password(char* password);

double calcola_costo(double tariffa, Intervallo i);

#endif //UTILS_H
