#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "interfaccia/interfaccia_amministratore.h"
#include "interfaccia/interfaccia.h"
#include "modelli/byte.h"
#include "modelli/utente.h"
#include "strutture_dati/prenotazioni.h"
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

    unsigned j = 0;
    for(unsigned int i = 0; i < dimensione; i++){
        Utente u = utenti[i];
        if(u != NULL && ottieni_permesso(u) != ADMIN){
            char *str = utente_in_stringa(u);
            printf("%s\n", str);
            free(str);
            printf("----------------------------------------\n");
            j++;
        }
    }

    if(j == 0){
        return -1;
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

Veicolo interfaccia_aggiungi_veicolo(){
    Veicolo v = NULL;

    char targa[NUM_CARATTERI_TARGA] = {0};
    char tipo[MAX_LUNGHEZZA_TIPO] = {0};
    char modello[MAX_LUNGHEZZA_MODELLO] = {0};
    char posizione[MAX_LUNGHEZZA_POSIZIONE] = {0};
    double tariffa;
    size_t lun;

    do{
        printf("Inserisci targa: ");
        ottieni_parola(targa, NUM_CARATTERI_TARGA);

        lun = strlen(targa);

        if(lun != (NUM_CARATTERI_TARGA-2)){
            printf("Targa non valida!\n");
        }

    }while(lun != NUM_CARATTERI_TARGA);

    printf("Inserisci tipo: ");
    inserisci_stringa(tipo, MAX_LUNGHEZZA_TIPO);

    printf("Inserisci modello: ");
    inserisci_stringa(modello, MAX_LUNGHEZZA_MODELLO);

    printf("Inserisci posizione: ");
    inserisci_stringa(posizione, MAX_LUNGHEZZA_POSIZIONE);

    printf("Inserisci la tariffa al minuto: ");
    scanf("%lf", &tariffa);

    Prenotazioni pre = crea_prenotazioni();
    v = crea_veicolo(tipo, targa, modello, posizione, tariffa, pre);

    if(v == NULL){
        printf("Errore inserimento veicolo!\n");
        distruggi_prenotazioni(pre);
        return NULL;
    }

    return v;
}
