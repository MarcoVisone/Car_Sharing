#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "utils/utils.h"
#include "modelli/veicolo.h"
#include "strutture_dati/prenotazioni.h"
#include "strutture_dati/tabella_veicoli.h"

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

char* my_strdup(const char* s) {
    if (s == NULL) return NULL;
    size_t len = strlen(s) + 1;
    char* dup = malloc(len * sizeof(char));
    if (dup != NULL) {
        memcpy(dup, s, len);
    }
    return dup;
}
