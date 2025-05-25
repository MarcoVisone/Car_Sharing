#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "interfaccia/interfaccia_amministratore.h"
#include "interfaccia/interfaccia.h"
#include "modelli/byte.h"
#include "modelli/utente.h"
#include "strutture_dati/tabella_hash.h"
#include "strutture_dati/tabella_utenti.h"
#include "modelli/veicolo.h"
#include "strutture_dati/tabella_veicoli.h"
#include "utils/utils.h"


Byte storico_noleggi(TabellaUtenti tabella_utenti, TabellaVeicoli tabella_veicoli){
    unsigned int dimensione = 0;
    char email[DIMENSIONE_EMAIL];
    char scelta;

    Utente *utenti = (Utente *)ottieni_vettore(tabella_utenti, &dimensione);
    if (utenti == NULL) {
        return -1;
    }

    printf("\n========================================\n");
    printf("         UTENTI REGISTRATI              \n");
    printf("========================================\n");

    for(unsigned int i = 0; i < dimensione; i++){
        Utente u = utenti[i];
        if(u != NULL && ottieni_permesso(u) != ADMIN){
            char *str = utente_in_stringa(u);
            printf("%s\n", str);
            free(str);
            printf("----------------------------------------\n");
        }
    }
    while(1){
        printf("\nEmail dell'utente da visualizzare (E per uscire): ");
        ottieni_parola(email, DIMENSIONE_EMAIL);
        if(strcmp(email, "E") == 0) break;;

        Byte codice = visualizza_storico(email, tabella_utenti);

        if(codice < 0){
            printf("\nUtente non trovato\n");

            printf("Vuoi uscire? (S/N): ");
            scelta = getchar();
            stdin_fflush();

            if(scelta == 's' || scelta == 'S'){
                break;
            }
        }
    }

    free(utenti);

    printf("\nUscita dal visualizzatore storico completata.\n");
    return 0;
}
