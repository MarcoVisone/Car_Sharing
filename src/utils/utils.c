#include <stdlib.h>
#include <stdio.h>
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


/*
 * Funzione: stdin_fflush
 * ----------------------
 *
 * Pulisce il buffer di input standard scartando tutti i caratteri
 * rimanenti fino al newline o EOF
 *
 * Implementazione:
 *    Legge caratteri dal buffer stdin usando getchar() finché non
 *    incontra '\n' o EOF, scartando tutti i caratteri letti
 *
 * Pre-condizioni:
 *    nessuna
 *
 * Post-condizioni:
 *    il buffer stdin è vuoto e pronto per la prossima operazione di input
 *
 * Side-effect:
 *    modifica lo stato del buffer stdin
 */
void stdin_fflush(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Scarta il carattere letto
    }
}

/*
 * Funzione: controllo_lvl_2
 * -------------------------
 *
 * Verifica che la password contenga solo caratteri alfanumerici
 *
 * Implementazione:
 *    Scorre la stringa `password` carattere per carattere. Se trova un
 *    carattere non alfanumerico (controllato con isalnum), restituisce 1.
 *    Se tutti i caratteri sono alfanumerici, restituisce 0.
 *
 * Pre-condizioni:
 *    `password` è una stringa valida e terminata da '\0'
 *
 * Post-condizioni:
 *    Restituisce 1 se la password contiene almeno un carattere non alfanumerico,
 *    altrimenti restituisce 0
 *
 * Side-effect:
 *    nessuno
 */
static Byte controllo_lvl_2(char *password) {
    int i=0;
    for(i=0;password[i];i++) {
        if(!isalnum(password[i])) {
            return 1;
        }
    }
    return 0;
}

/*
 * Funzione: controllo_lunghezza_max
 * ---------------------------------
 *
 * Verifica che la lunghezza della password non superi il limite massimo consentito
 *
 * Implementazione:
 *    Calcola la lunghezza della stringa `password` usando `strlen`. Se la lunghezza
 *    è maggiore di 16, restituisce 1; altrimenti restituisce 0.
 *
 * Pre-condizioni:
 *    `password` è una stringa valida e terminata da '\0'
 *
 * Post-condizioni:
 *    Restituisce 1 se la password supera i 16 caratteri, altrimenti 0
 *
 * Side-effect:
 *    nessuno
 */
static Byte controllo_lunghezza_max(char *password) {
    if((int)strlen(password) > 16){
        return 1;
    }
    return 0;
}

/*
 * Funzione: controllo_lvl_0
 * -------------------------
 *
 * Verifica che la password contenga almeno una lettera maiuscola e una minuscola
 *
 * Implementazione:
 *    Scorre la stringa `password` carattere per carattere. Se trova almeno un
 *    carattere minuscolo (controllato con `islower`) imposta il flag `minuscolo` a 1.
 *    Se trova almeno un carattere maiuscolo (controllato con `isupper`) imposta il
 *    flag `maiuscolo` a 1. Alla fine restituisce l'AND logico dei due flag.
 *
 * Pre-condizioni:
 *    `password` è una stringa valida e terminata da '\0'
 *
 * Post-condizioni:
 *    Restituisce 1 se la password contiene almeno una maiuscola e una minuscola,
 *    altrimenti 0
 *
 * Side-effect:
 *    nessuno
 */
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

/*
 * Funzione: controllo_lvl_1
 * -------------------------
 *
 * Verifica che la password contenga almeno una cifra numerica
 *
 * Implementazione:
 *    Scorre la stringa `password` carattere per carattere. Se trova un
 *    carattere numerico (controllato con `isdigit`), restituisce 1.
 *    Se non trova cifre, restituisce 0.
 *
 * Pre-condizioni:
 *    `password` è una stringa valida e terminata da '\0'
 *
 * Post-condizioni:
 *    Restituisce 1 se la password contiene almeno una cifra, altrimenti 0
 *
 * Side-effect:
 *    nessuno
 */
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

/*
 * Funzione: calcola_costo
 * -----------------------
 *
 * Calcola il costo totale di un intervallo temporale dato, in base a una tariffa al minuto
 *
 * Implementazione:
 *    Ottiene l'inizio e la fine dell'intervallo `i` utilizzando le funzioni
 *    `inizio_intervallo` e `fine_intervallo`. Calcola la durata totale in secondi
 *    e la converte in minuti dividendo per 60. Infine, moltiplica i minuti per
 *    la `tariffa` e restituisce il risultato come costo totale.
 *
 * Pre-condizioni:
 *    `tariffa` è un valore positivo che rappresenta il costo per minuto
 *    `i` è un intervallo valido con inizio e fine correttamente impostati
 *
 * Post-condizioni:
 *    Restituisce il costo calcolato come (durata in minuti) * tariffa
 *
 * Side-effect:
 *    nessuno
 */
double calcola_costo(double tariffa, Intervallo i){
    time_t inizio = inizio_intervallo(i);
    time_t fine = fine_intervallo(i);

    time_t totale = fine - inizio;

    totale = totale / 60;

    return totale * tariffa;
}
