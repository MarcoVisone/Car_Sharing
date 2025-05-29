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

static void intest_noleggi();
static void sep_noleggi();

/*
 * Autore: Marco Visone
 * Data: 26/05/2025
 *
 * Funzione: storico_noleggi
 * -------------------------
 * Interfaccia che permette all'amministratore di visualizzare lo storico dei noleggi
 * per un utente specifico selezionato dalla lista degli utenti registrati
 *
 * Implementazione:
 *   La funzione recupera tutti gli utenti dalla tabella e mostra solo quelli non amministratori.
 *   L'utente può inserire l'email di un utente per visualizzarne lo storico oppure 'E' per uscire.
 *   Se l'utente non viene trovato, viene chiesta conferma per continuare o uscire.
 *   Il ciclo continua finché l'utente non decide di uscire.
 *
 * Parametri:
 *    - tabella_utenti: tabella contenente tutti gli utenti registrati
 *    - tabella_veicoli: tabella contenente tutti i veicoli per recuperare le informazioni complete
 *
 * Pre-condizioni:
 *    - tabella_utenti: non deve essere NULL
 *    - tabella_veicoli: non deve essere NULL
 *
 * Post-condizioni:
 *    Restituisce 0 in caso di successo, -1 se non ci sono utenti o in caso di errore
 *
 * Side-effects:
 *    - Input/output su console
 *    - Allocazione e deallocazione dinamica della memoria
 */
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
        if(uscita(email)) break;

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

/*
 * Autore: Marco Visone
 * Data: 26/05/2025
 *
 * Funzione: intest_noleggi
 * ------------------------
 * Funzione di utilità che stampa l'intestazione della tabella per la visualizzazione dei noleggi
 *
 * Implementazione:
 *   Stampa una tabella formattata con tre colonne: Cliente, Periodo e Costo
 *
 * Parametri: nessuno
 *
 * Pre-condizioni: nessuna
 *
 * Post-condizioni: nessuna
 *
 * Side-effects:
 *    - Output formattato su console
 */
static void intest_noleggi() {
    printf("+---------------------------+---------------------------------------+------------+\n");
    printf("| Cliente                   | Periodo                               | Costo (€)  |\n");
    printf("+---------------------------+---------------------------------------+------------+\n");
}

/*
 * Autore: Marco Visone
 * Data: 26/05/2025
 *
 * Funzione: sep_noleggi
 * ---------------------
 * Funzione di utilità che stampa il separatore finale della tabella dei noleggi
 *
 * Implementazione:
 *   Stampa una linea di separazione per chiudere la tabella formattata
 *
 * Parametri: nessuno
 *
 * Pre-condizioni: nessuna
 *
 * Post-condizioni: nessuna
 *
 * Side-effects:
 *    - Output formattato su console
 */
static void sep_noleggi() {
    printf("+---------------------------+---------------------------------------+------------+\n");
}

/*
 * Autore: Marco Visone
 * Data: 26/05/2025
 *
 * Funzione: gestione_noleggi
 * --------------------------
 * Visualizza tutti i veicoli e le relative prenotazioni in formato tabellare
 *
 * Implementazione:
 *   Per ogni veicolo nella tabella, mostra targa e modello.
 *   Se il veicolo ha prenotazioni, le visualizza in una tabella formattata
 *   con cliente, periodo e costo. Se non ha prenotazioni, mostra un messaggio appropriato.
 *
 * Parametri:
 *    - tabella_veicoli: tabella contenente tutti i veicoli
 *
 * Pre-condizioni:
 *    - tabella_veicoli: non deve essere NULL
 *
 * Post-condizioni:
 *    Restituisce 1 in caso di successo, -1 in caso di errore
 *
 * Side-effects:
 *    - Output formattato su console
 *    - Allocazione e deallocazione dinamica della memoria
 */
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
                char *periodo = intervallo_in_stringa(ottieni_intervallo_prenotazione(p[j]));
                double costo = ottieni_costo_prenotazione(p[j]);
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

/*
 * Autore: Marco Visone
 * Data: 26/05/2025
 *
 * Funzione: interfaccia_aggiungi_veicolo
 * --------------------------------------
 * Interfaccia interattiva per l'aggiunta di un nuovo veicolo alla tabella
 *
 * Implementazione:
 *   La funzione richiede all'utente di inserire tutti i dati necessari per creare un veicolo:
 *   targa (con validazione lunghezza e unicità), tipo, modello, posizione e tariffa.
 *   L'utente può digitare 'E' in qualsiasi momento per uscire senza salvare.
 *   Prima del salvataggio definitivo viene richiesta una conferma.
 *   Se confermato, crea il veicolo con una struttura prenotazioni vuota.
 *
 * Parametri:
 *    - tabella_veicoli: tabella in cui verificare l'unicità della targa
 *
 * Pre-condizioni:
 *    - tabella_veicoli: non deve essere NULL
 *
 * Post-condizioni:
 *    Restituisce il nuovo veicolo creato se l'operazione ha successo, NULL altrimenti
 *
 * Side-effects:
 *    - Input/output su console
 *    - Allocazione dinamica della memoria per il nuovo veicolo
 *    - Creazione di una nuova struttura prenotazioni
 */
Veicolo interfaccia_aggiungi_veicolo(TabellaVeicoli tabella_veicoli){
    Veicolo v = NULL;

    char targa[NUM_CARATTERI_TARGA] = {0};
    char tipo[MAX_LUNGHEZZA_TIPO] = {0};
    char modello[MAX_LUNGHEZZA_MODELLO] = {0};
    char posizione[MAX_LUNGHEZZA_POSIZIONE] = {0};

    double tariffa;
    Byte codice;
    size_t lun;
    printf("Digita <E> per uscire senza salvare\n\n");
    do{
        printf("Inserisci targa: ");
        ottieni_parola(targa, NUM_CARATTERI_TARGA);
        if(uscita(targa)) return NULL;
        lun = strlen(targa);

        if(lun != (NUM_CARATTERI_TARGA-2)){
            printf("Targa non valida!\n");
        }
        codice = cerca_veicolo_in_tabella(tabella_veicoli, targa) != NULL;
        if(codice){
            printf("Targa già in uso\n");
        }
    }while(codice || lun != (NUM_CARATTERI_TARGA-2));

    printf("Inserisci tipo: ");
    inserisci_stringa(tipo, MAX_LUNGHEZZA_TIPO);
    if(uscita(tipo)) return NULL;

    printf("Inserisci modello: ");
    inserisci_stringa(modello, MAX_LUNGHEZZA_MODELLO);
    if(uscita(modello)) return NULL;

    printf("Inserisci posizione: ");
    inserisci_stringa(posizione, MAX_LUNGHEZZA_POSIZIONE);
    if(uscita(posizione)) return NULL;

    printf("Inserisci la tariffa al minuto: ");
    scanf("%lf", &tariffa);

    printf("Vuoi salvare questo veicolo (S/N)? ");
    char c = getchar();

    while(c == '\n') c = getchar();

    //stdin_fflush();

    if((c != 's') && (c != 'S')){
        return NULL;
    }

    Prenotazioni pre = crea_prenotazioni();
    v = crea_veicolo(tipo, targa, modello, posizione, tariffa, pre);

    if(v == NULL){
        printf("Errore inserimento veicolo!\n");
        distruggi_prenotazioni(pre);
        return NULL;
    }

    return v;
}

/*
 * Autore: Russo Nello Manuel
 * Data: 26/05/2025
 *
 * Funzione: interfaccia_rimuovi_veicolo
 * -------------------------------------
 * Interfaccia testuale che consente all’utente di rimuovere un veicolo dalla tabella
 *
 * Implementazione:
 *   La funzione mostra a schermo l’elenco dei veicoli presenti nella tabella.
 *   L’utente può inserire la targa del veicolo da rimuovere oppure digitare 'E' per uscire.
 *   Dopo aver ricevuto la targa, la funzione richiede una conferma ('S') prima di procedere alla rimozione.
 *   Se confermata, rimuove il veicolo tramite la funzione rimuovi_veicolo_in_tabella.
 *   Il ciclo si ripete finché l’utente non decide di uscire.
 *
 * Parametri:
 *    - tabella_veicoli: la tabella veicoli
 *
 * Pre-condizioni:
 *    tabella_veicoli: non deve essere NULL
 *
 * Post-condizioni:
 * 	  restituisce 0 in caso di uscita o fallimento nella rimozione.
 *
 * Ritorna:
 *    un valore di tipo Byte(0)
 *
 * Side-effects:
 *    - Input/output su console
 *    - Allocazione e deallocazione dinamica della memoria
 *    - Il veicolo selezionato, se presente e confermato, viene rimosso dalla tabella.
 */
Byte interfaccia_rimuovi_veicolo(TabellaVeicoli tabella_veicoli){
	unsigned int dimensione;
    char targa[NUM_CARATTERI_TARGA];
	char scelta;

	do{
	    Veicolo *vettore_veicoli = (Veicolo*) ottieni_vettore(tabella_veicoli, &dimensione);
		if(vettore_veicoli == NULL){
			printf("Nessun veicolo presente\n");
			return 0;
		}

		system("clear || cls");

		printf("\n========================================\n");
        printf("         TABELLA VEICOLI DISPONIBILI    \n");
        printf("========================================\n");

		for(unsigned int i = 0; i < dimensione; i++){
			char *str = veicolo_in_stringa(vettore_veicoli[i]);
			if (str) {
                printf("%s\n", str);
                free(str);
                printf("----------------------------------------\n");
            }
		}

		printf("Inserisci la targa del veicolo che vuoi eliminare (per uscire digita E): ");
        ottieni_parola(targa, NUM_CARATTERI_TARGA);

		 if (strcmp(targa, "E") == 0 || strcmp(targa, "e") == 0) {
            free(vettore_veicoli);
            return 0;
        }

        printf("Sei sicuro di voler eliminare questo veicolo? (S/N): ");
        scelta = getchar();
        stdin_fflush();

        if(scelta == 's' || scelta == 'S'){
            Byte rim = rimuovi_veicolo_in_tabella(tabella_veicoli, targa);

			if(rim == 0) printf("\nErrore durante la rimozione del veicolo\n");

			else printf("\nVeicolo eliminato correttamente\n");

			printf("Premi INVIO per continuare...");
            getchar();
		}

		free(vettore_veicoli);
	}while(1);
}
