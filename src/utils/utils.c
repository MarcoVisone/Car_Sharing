#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "utils/utils.h"
#include "modelli/veicolo.h"
#include "strutture_dati/prenotazioni.h"
#include "strutture_dati/tabella_veicoli.h"
#include <ctype.h>

static char *genera_targa();

/*
 * Funzione statica: genera_targa
 * ------------------------------
 * Genera una targa casuale nel formato: due lettere, tre cifre, due lettere.
 *
 * Ritorna:
 *    un puntatore statico a una stringa contenente la targa generata
 */
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
 * Implementazione:
 *    Viene creata una nuova tabella di veicoli con dimensione numero_veicoli
 *    tramite crea_tabella_veicoli. Per ogni veicolo, viene creato un nuovo
 *    oggetto Veicolo con tipo, modello e targa generati, quindi aggiunto alla tabella.
 *
 * Parametri:
 *    numero_veicoli: numero intero che rappresenta la dimensione della tabella
 *
 * Ritorna:
 *    una nuova tabella di veicoli allocata dinamicamente,
 *    NULL in caso di fallimento nell'allocazione
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
                                             "Macchina con 4 porte",
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
 * Implementazione:
 *    Calcola la lunghezza della stringa originale, alloca memoria
 *    sufficiente per la copia, quindi copia la stringa usando memcpy.
 *
 * Parametri:
 *    s: puntatore alla stringa originale da duplicare
 *
 * Ritorna:
 *    un nuovo puntatore a una copia della stringa s,
 *    NULL se l'allocazione della memoria fallisce
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
 * Funzione statica: controllo_lvl_2
 * ---------------------------------
 * Controlla se la password contiene almeno un carattere alfanumerico.
 *
 * Parametri:
 *    password: stringa da controllare
 *
 * Ritorna:
 *    1 se la password contiene almeno un carattere alfanumerico,
 *    0 altrimenti
 */
static Byte controllo_lvl_2(char *password) {
    int i=0;
    for(i=0;password[i];i++) {
        if(isalnum(password[i])) {
            return 1;
        }
    }
    return 0;
}

/*
 * Funzione statica: controllo_lunghezza_max
 * -----------------------------------------
 * Verifica se la lunghezza della password supera i 16 caratteri.
 *
 * Parametri:
 *    password: stringa da controllare
 *
 * Ritorna:
 *    1 se la lunghezza è maggiore di 16,
 *    0 altrimenti
 */
static Byte controllo_lunghezza_max(char *password) {
    if((int)strlen(password) > 16){
        return 1;
    }
    return 0;
}

/*
 * Funzione statica: controllo_lvl_0
 * ---------------------------------
 * Verifica che la password contenga almeno una lettera maiuscola e una minuscola.
 *
 * Parametri:
 *    password: stringa da controllare
 *
 * Ritorna:
 *    1 se contiene almeno una maiuscola e una minuscola,
 *    0 altrimenti
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
 * Funzione statica: controllo_lvl_1
 * ---------------------------------
 * Controlla se la password contiene almeno una cifra.
 *
 * Parametri:
 *    password: stringa da controllare
 *
 * Ritorna:
 *    1 se è presente almeno una cifra,
 *    0 altrimenti
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
 * Implementazione:
 *    Controlla la lunghezza minima (>=8), quindi verifica progressivamente la presenza
 *    di lettere maiuscole e minuscole, numeri, caratteri alfanumerici e lunghezza massima
 *    per assegnare un livello di sicurezza da -1 (non valida) a 4 (molto valida).
 *
 * Parametri:
 *    password: stringa che rappresenta la password da controllare
 *
 * Ritorna:
 *    -1 se la password è troppo corta o non rispetta i requisiti base,
 *    un valore da 0 a 4 che indica il livello di robustezza della password
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