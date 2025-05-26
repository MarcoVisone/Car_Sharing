#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "interfaccia/interfaccia_amministratore.h"
#include "interfaccia/interfaccia.h"
#include "modelli/byte.h"
#include "modelli/intervallo.h"
#include "modelli/prenotazione.h"
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

        Byte codice = visualizza_storico(email, tabella_utenti, tabella_veicoli);

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

void intest_noleggi() {
    printf("+---------------------------+---------------------------------------+------------+\n");
    printf("| Cliente                   | Periodo                               | Costo (€)  |\n");
    printf("+---------------------------+---------------------------------------+------------+\n");
}

void sep_noleggi() {
    printf("+---------------------------+---------------------------------------+------------+\n");
}

Byte gestione_noleggi(TabellaVeicoli tabella_veicoli) {
    if (!tabella_veicoli) return -1;
    unsigned int nv = 0;
    Veicolo *vettore = (Veicolo*) ottieni_vettore(tabella_veicoli, &nv);
    if (!vettore) return -1;

    for (unsigned int i = 0; i < nv; i++) {
        const char *targa   = ottieni_targa(vettore[i]);
        const char *modello = ottieni_modello(vettore[i]);
        printf("\nVeicolo: %s  —  %s\n", targa, modello);

        Prenotazioni pre = ottieni_prenotazioni(vettore[i]);
        unsigned int np = 0;
        Prenotazione *p = pre? ottieni_vettore_prenotazioni_ordinate(pre, &np): NULL;

        if (p && np > 0) {
            intest_noleggi();
            for (unsigned int j = 0; j < np; j++) {
                const char *cliente = ottieni_cliente_prenotazione(p[j]);
                char *periodo       = intervallo_in_stringa(
                                         ottieni_intervallo_prenotazione(p[j]));
                double costo        = ottieni_costo_prenotazione(p[j]);

                // Correzione: allineamento corretto delle colonne
                printf("| %-25s | %-37s | %10.2f |\n",
                       cliente, periodo, costo);
                free(periodo);
            }
            sep_noleggi();
        }
        else {
            printf("  (Nessuna prenotazione per questo veicolo)\n");
        }
        if (p) free(p);
    }
    free(vettore);
    return 1;
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

    }while(lun != (NUM_CARATTERI_TARGA-2));

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
