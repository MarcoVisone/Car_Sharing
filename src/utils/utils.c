#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "utils/utils.h"

#include "modelli/intervallo.h"
#include "modelli/veicolo.h"
#include "strutture_dati/prenotazioni.h"
#include "strutture_dati/tabella_veicoli.h"
#include <ctype.h>

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
char* mia_strdup(const char* s) {
    if (s == NULL) return NULL;
    size_t len = strlen(s) + 1;
    char* dup = malloc(len * sizeof(char));
    if (dup != NULL) {
        memcpy(dup, s, len);
    }
    return dup;
}


static Byte controllo_lvl_2(char *password) {
    int i=0;
    for(i=0;password[i];i++) {
        if(!isalnum(password[i])) {
            return 1;
        }
    }
    return 0;
}


static Byte controllo_lunghezza_max(char *password) {
    if((int)strlen(password) > 16){
        return 1;
    }
    return 0;
}


static Byte controllo_lvl_0(char *password) {
    int i=0;
    int maiuscolo = 0;
    int minuscolo = 0;
    for (i=0;password[i];i++) {
        if (islower(password[i])) {
            minuscolo=1;
		}
		if (isupper(password[i])) {
        	maiuscolo=1;
		}
	}
    return maiuscolo && minuscolo;
}


static Byte controllo_lvl_1(char *password) {
    for (int i=0; password[i]; i++) {
        if (isdigit(password[i])) {
            return 1;
        }
    }
    return 0;
}

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
Byte controllo_password(char *password) {
  	Byte lvl = -1;

    if (strlen(password) < 8) return lvl;

    if (!controllo_lvl_0(password)) return lvl;
    lvl++;

    if (!controllo_lvl_1(password)) return lvl;
    lvl++;

    if (!controllo_lvl_2(password)) return lvl;
    lvl++;

    if (!controllo_lunghezza_max(password)) return lvl;
    lvl++;

    return lvl;
}

double calcola_costo(double tariffa, Intervallo i){
    time_t inizio = inizio_intervallo(i);
    time_t fine = fine_intervallo(i);

    time_t totale = fine - inizio;

    totale = totale / 60;

    return totale * tariffa;
}
