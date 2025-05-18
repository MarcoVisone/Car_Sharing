#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "utils/utils.h"
#include "modelli/veicolo.h"
#include "strutture_dati/prenotazioni.h"
#include "strutture_dati/tabella_veicoli.h"
#include <ctype.h>

static char *genera_targa();

static char *genera_targa() {
    static char targa[8];
    const char lettere[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    static int inizializzato = 0;
    if (!inizializzato) {
        srand((unsigned int)time(NULL));
        inizializzato = 1;
    }

    targa[0] = lettere[rand() % 26];
    targa[1] = lettere[rand() % 26];
    targa[2] = '0' + rand() % 10;
    targa[3] = '0' + rand() % 10;
    targa[4] = '0' + rand() % 10;
    targa[5] = lettere[rand() % 26];
    targa[6] = lettere[rand() % 26];
    targa[7] = '\0';

    return targa;
}

/*
 * Funzione: genera_tabella_veicoli
 * --------------------------------
 * Crea e inizializza una tabella di veicoli con il numero specificato di veicoli.
 *
 * Parametri:
 *    numero_veicoli: numero intero che rappresenta la dimensione della tabella
 *
 * Pre-condizioni:
 *    numero_veicoli deve essere un valore positivo
 *
 * Post-condizione:
 *    ritorna una nuova tabella di veicoli allocata dinamicamente, oppure NULL in caso di errore
 *
 * Ritorna:
 *    una nuova tabella di veicoli allocata dinamicamente,
 *    NULL in caso di fallimento nell'allocazione
 *
 * Side effects:
 *    Allocazione dinamica di memoria per la tabella di veicoli
 */
TabellaVeicoli genera_tabella_veicoli(unsigned int numero_veicoli){
    char *tipi[] = {
        "City car",
        "Auto elettrica",
        "SUV",
        "Monovolume",
        "Auto ibrida",
        "Station wagon",
        "Furgoncino",
        "Cabriolet",
        "Pick-up",
        "Scooter elettrico"
    };

    char *modelli[] = {
        "Fiat Panda",
        "Toyota Yaris",
        "Volkswagen Golf",
        "Renault Clio",
        "Ford Fiesta",
        "Peugeot 208",
        "Opel Corsa",
        "Hyundai i20",
        "Citroen C3",
        "Kia Picanto"
    };
    int num_tipi = sizeof(tipi) / sizeof(tipi[0]);
    int num_modelli = sizeof(modelli) / sizeof(modelli[0]);

    TabellaVeicoli tabella = crea_tabella_veicoli(numero_veicoli);

    unsigned int i;
    for(i = 0; i < numero_veicoli; i++){
        Veicolo nuovo_veicolo = crea_veicolo(tipi[i%num_tipi],
                                             genera_targa(),
                                             modelli[i%(num_modelli)],
                                             "Napoli Centro",
                                             0.012,
                                             crea_prenotazioni());
        aggiungi_veicolo_in_tabella(tabella, nuovo_veicolo);
    }

    return tabella;
}

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
        if(isalnum(password[i])) {
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
