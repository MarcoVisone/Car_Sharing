#include <complex.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "interfaccia/interfaccia.h"
#include "modelli/data.h"
#include "strutture_dati/prenotazioni.h"
#include "strutture_dati/tabella_hash.h"
#include "utils/utils.h"
#include "utils/md5.h"
#include "modelli/intervallo.h"
#include "modelli/prenotazione.h"
#include "modelli/utente.h"
#include "strutture_dati/tabella_utenti.h"
#include "modelli/veicolo.h"
#include "strutture_dati/tabella_veicoli.h"
#include "strutture_dati/lista.h"
#include "strutture_dati/lista_prenotazione.h"

#define DIMENSIONE_STRINGA_PASSWORD (64 + 2)
#define DIMENSIONE_INTERVALLO (16 + 2)

static void stampa_veicolo(const Veicolo v, Intervallo i);
static char *formatta_data(time_t timestamp);
static char *ottieni_orario(time_t timestamp);
static time_t fine_giornata(time_t inizio);


void inserisci_stringa(char *stringa, unsigned int lunghezza){
    fgets(stringa, lunghezza, stdin);

    unsigned long indice = strcspn(stringa, "\n");
    if(indice >= (DIMENSIONE_INTERVALLO-1)){
        stdin_fflush(); //PULIZIA BUFFER IN CASO DI OVERFLOW
    }

    stringa[indice] = '\0';

}

/*
 * Funzione: risposta_password
 * ---------------------------
 *
 * Fornisce un messaggio all'utente in base al livello di sicurezza della password.
 *
 * Implementazione:
 *    In base al valore di 'lvl', stampa un messaggio che spiega cosa manca
 *    nella password inserita. Se il livello è sufficiente (valore diverso dai casi),
 *    conferma che la password è valida e restituisce 1. Altrimenti restituisce -1.
 *
 * Parametri:
 *    lvl: livello di sicurezza della password, determinato da controlli precedenti
 *
 * Pre-condizione:
 *    lvl deve essere un valore intero compreso tra -1 e un massimo coerente con il sistema
 *
 * Post-condizione:
 *    Stampa un messaggio a video in base al livello ricevuto
 *    Ritorna 1 se la password è considerata valida, -1 altrimenti
 *
 * Side-effect:
 *    Output su console
 */
static Byte risposta_password(Byte lvl){
    switch (lvl){
      case -1:
        printf("La password deve avere:\n Almeno 8 caratteri\n Almeno una lettera minuscola ed una minuscola\n");
        printf(" Almeno un numero\n Almeno un carattere speciale\n");
        break;

      case 0:
        printf("Inserisci almeno un carattere speciale o un numero\n");
        break;

      case 1:
        printf("Inserisci almeno un carattere speciale\n");
        break;

      default:
        return 1;
    }

    return -1;
}

/*
 * Funzione: ottieni_parola
 * -------------------------
 *
 * Legge una stringa da input standard, rimuovendo newline e spazi finali.
 *
 * Implementazione:
 *    Utilizza fgets per leggere la stringa da stdin fino alla dimensione specificata.
 *    Scorre la stringa e termina al primo carattere di newline ('\n') o spazio (' '),
 *    sostituendolo con il terminatore di stringa '\0'.
 *
 * Parametri:
 *    stringa: puntatore al buffer in cui memorizzare la stringa letta
 *    dimensione: dimensione massima del buffer (in caratteri)
 *
 * Pre-condizione:
 *    stringa deve essere un puntatore valido a un buffer allocato
 *    dimensione deve essere maggiore di 0
 *
 * Post-condizione:
 *    La stringa letta da input è memorizzata in 'stringa'
 *    I caratteri '\n' o ' ' vengono rimossi se presenti
 *
 * Side-effect:
 *    Lettura da stdin
 */
void ottieni_parola(char *stringa, int dimensione) {
    if (fgets(stringa, dimensione, stdin) == NULL) {
        // Errore in input
        stringa[0] = '\0';
        return;
    }

     // Rimuove il newline, se presente
    char *newline = strchr(stringa, '\n');
    if (newline) {
        *newline = '\0';
    } else {
        stdin_fflush();
    }

    // Tronca la stringa al primo spazio, se presente
    char *spazio = strchr(stringa, ' ');
    if (spazio) {
        *spazio = '\0';
    }
}

/*
 * Funzione: interfaccia_accesso
 * -----------------------------
 *
 * Gestisce l'interfaccia di accesso dell'utente, richiedendo l'inserimento
 * di email e password e verificandone la correttezza.
 *
 * Implementazione:
 *    Richiede all'utente l'inserimento di email e password.
 *    La password inserita viene cifrata con MD5 e confrontata con quella memorizzata.
 *    Se l'accesso fallisce, l'utente può ritentare fino a 3 volte o scegliere di uscire.
 *    Restituisce 1 se l'accesso ha successo, -1 se l'utente sceglie di uscire e un numero
 *    maggiore o uguale a 3 in caso di troppi tentativi.
 *
 * Parametri:
 *    tabella_utenti: struttura contenente la lista di utenti registrati
 *
 * Pre-condizione:
 *    tabella_utenti deve essere inizializzata e non nullo
 *
 * Post-condizione:
 *    Se le credenziali sono corrette, restituisce 1
 *    Se l'utente sceglie di uscire, restituisce -1
 *    Se l'utente supera il numero di tentativi, restituisce il numero dei tentativi fatti.
 *
 * Side-effect:
 *    Nessuno
 */
Utente interfaccia_accesso(TabellaUtenti tabella_utenti){
    Byte tentativi = 0;
    char scelta;

    Utente utente = NULL;

    do{
        char email[DIMENSIONE_EMAIL] = {0};
        char password[DIMENSIONE_STRINGA_PASSWORD] = {0};
        uint8_t password_mod[DIMENSIONE_PASSWORD] = {0};

        printf("Inserisci l'email: ");
        ottieni_parola(email, DIMENSIONE_EMAIL);

        printf("Inserisci la password: ");
        ottieni_parola(password, DIMENSIONE_STRINGA_PASSWORD);
        if(controllo_password(password) >= 0){
            md5(password, strlen(password), password_mod);
            utente = cerca_utente_in_tabella(tabella_utenti, email);
        }
        if((utente == NULL )|| !hash_equals(ottieni_password(utente), password_mod, DIMENSIONE_PASSWORD)){
            printf("Email o password errati\n");

            printf("Vuoi uscire? (S/N): ");
            scelta = getchar();
            stdin_fflush();
            if(scelta == 's' || scelta == 'S'){
                return NULL;
            }
            distruggi_utente(utente);
            utente = NULL;
            tentativi++;
        }
        else break;
    }while(tentativi < 3);

    return utente;
}

/*
 * Funzione: interfaccia_registrazione
 * -----------------------------------
 *
 * Gestisce l'interfaccia di registrazione di un nuovo utente.
 *
 * Implementazione:
 *    Richiede l'inserimento di nome, cognome, email e password.
 *    Verifica la forza della password e chiede conferma.
 *    Se la conferma è corretta, la password viene cifrata con MD5.
 *    Viene creato un nuovo utente e aggiunto alla tabella.
 *    Restituisce 1 se la registrazione ha successo, 0 altrimenti.
 *
 * Parametri:
 *    tabella_utenti: struttura contenente la lista di utenti registrati
 *    permesso: livello di permesso da assegnare al nuovo utente
 *
 * Pre-condizione:
 *    tabella_utenti deve essere inizializzata e non nullo
 *    permesso deve essere un valore valido
 *
 * Post-condizione:
 *    Se la registrazione va a buon fine, l'utente è inserito in tabella
 *    Ritorna 1 in caso di successo, 0 in caso di fallimento
 *
 * Side-effect:
 *    Aggiunta di un nuovo utente alla tabella utenti
 */
Byte interfaccia_registrazione(TabellaUtenti tabella_utenti, Byte permesso){
    char nome[DIMENSIONE_NOME];
    char cognome[DIMENSIONE_COGNOME];
    char email[DIMENSIONE_EMAIL];
    char password[DIMENSIONE_STRINGA_PASSWORD];
    char password_2[DIMENSIONE_STRINGA_PASSWORD];
    uint8_t password_mod[DIMENSIONE_PASSWORD];
    Utente utente;
    Byte conferma;
    Byte lvl;

    printf("Inserisci il nome: ");
    ottieni_parola(nome, DIMENSIONE_NOME);

    printf("Inserisci il cognome: ");
    ottieni_parola(cognome, DIMENSIONE_COGNOME);

    printf("Inserisci l'email: ");
    ottieni_parola(email, DIMENSIONE_EMAIL);

    do{
      do{
        printf("Inserisci la password: ");
        ottieni_parola(password, DIMENSIONE_STRINGA_PASSWORD);

        lvl = controllo_password(password);
      }while(risposta_password(lvl) < 0);

      printf("Conferma Password: ");
      ottieni_parola(password_2, DIMENSIONE_PASSWORD);
      conferma = strcmp(password, password_2) != 0;
      if(conferma){
        printf("Le password non corrispondono\n");
      }
    }while(conferma);

    md5(password, strlen(password), password_mod);
    utente = crea_utente(email, password_mod, nome, cognome, permesso);

    if(aggiungi_utente_in_tabella(tabella_utenti, utente)){
        return 1;
    }

    return 0;
}

/*
 * Autore: Russo Nello Manuel
 * Data: 22/05/2025
 *
 * Funzione: richiedi_intervallo_prenotazione
 * ------------------------------------------
 *
 * richiede all'utente di inserire un intervallo di tempo per una prenotazione
 *
 * Implementazione:
 *    - Chiede in input le date e orari di inizio e fine in formato "gg/mm/aaaa HH:MM"
 *    - Converte le stringhe in un oggetto `Intervallo`
 *    - Verifica che l’intervallo sia valido (non NULL e con inizio maggiore all’orario corrente)
 *    - Se l’intervallo è invalido, permette all’utente di riprovare o annullare l’operazione
 *
 * Parametri:
 *    nessuno
 *
 * Pre-condizioni:
 *    nessuna
 *
 * Post-condizioni:
 *    - Restituisce un puntatore a Intervallo se l’input è corretto
 *    - Restituisce NULL se l’utente decide di uscire o se non è stato possibile creare un intervallo valido
 *
 * Side-effect:
 *    - Legge input da tastiera
 *    - Stampa messaggi
 *    - Alloca memoria dinamicamente per l’intervallo restituito (da liberare)
 */
Intervallo richiedi_intervallo_prenotazione(){
    char inizio[DIMENSIONE_INTERVALLO];
    char fine[DIMENSIONE_INTERVALLO];
    char scelta;
    Intervallo i;

    do{
        printf("Inserisci la data e l'orario iniziali (formato: gg/mm/aaaa HH:MM): ");
        inserisci_stringa(inizio, DIMENSIONE_INTERVALLO);

        printf("Inserisci la data e l'orario finali (formato: gg/mm/aaaa HH:MM): ");
        inserisci_stringa(fine, DIMENSIONE_INTERVALLO);

        i = converti_data_in_intervallo(inizio, fine);

        if(i == NULL || inizio_intervallo(i) < time(NULL)){
            distruggi_intervallo(i);
            i = NULL;
            printf("Intervallo non valido\n");
            printf("Vuoi uscire? (S/N): ");
            scelta = getchar();
            stdin_fflush();

            if(scelta == 's' || scelta == 'S'){
                return NULL;
            }
        }
    }while(i == NULL);

    return i;
}

/*
 * Autore: Russo Nello Manuel
 * Data: 22/05/2025
 *
 * Funzione: stampa_riga_separatrice
 * ----------------------------------
 *
 * stampa una riga di separazione utilizzata per formattare tabelle testuali in output
 *
 * Implementazione:
 *    Utilizza printf per stampare una riga composta da caratteri '+' e '-' per delimitare visivamente le colonne
 *
 * Parametri:
 *    nessuno
 *
 * Pre-condizioni:
 *    nessuna
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    viene stampata una riga orizzontale sulla console per separare o delimitare sezioni di una tabella
 */
static void stampa_riga_separatrice() {
    printf("+------------+--------------------------------+--------------------------------+--------------+------------------------+\n");
}

/*
 * Autore: Russo Nello Manuel
 * Data: 22/05/2025
 *
 * Funzione: stampa_intestazione_tabella
 * --------------------------------------
 *
 * stampa l'intestazione di una tabella formattata, con nomi di colonna per i dati dei veicoli
 *
 * Implementazione:
 *    Utilizza printf per stampare i titoli delle colonne allineati e formattati, seguiti da righe separatrici
 *
 * Parametri:
 *    nessuno
 *
 * Pre-condizioni:
 *    nessuna
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    viene stampata su console l'intestazione della tabella con i nomi delle colonne
 */
static void stampa_intestazione_tabella() {
    stampa_riga_separatrice();
    printf("| %-10s | %-30s | %-30s | %-12s | %-22s |\n",
           "Targa", "Modello", "Posizione", "Prezzo", "Tipo");
    stampa_riga_separatrice();
}

/*
 * Autore: Russo Nello Manuel
 * Data: 22/05/2025
 *
 * Funzione: stampa_veicolo
 * ------------------------
 *
 * stampa su console le informazioni di un veicolo formattate come riga di una tabella
 *
 * Implementazione:
 *    Utilizza printf per stampare i dati del veicolo. Calcola il costo della prenotazione
 *    in base all'intervallo fornito.
 *
 * Parametri:
 *    v: puntatore ad un veicolo da stampare (non deve essere NULL)
 *    i: puntatore ad un intervallo
 *
 * Pre-condizioni:
 *    v: deve essere diverso da NULL
 *    i: deve essere diverso da NULL
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    i dati del veicolo vengono stampati in una riga formattata sullo standard output
 */
static void stampa_veicolo(const Veicolo v, Intervallo i) {
    printf("| %-10s | %-30s | %-30s | %-10.2f € | %-22s |\n",
           ottieni_targa(v),
           ottieni_modello(v),
           ottieni_posizione(v),
           calcola_costo(ottieni_tariffa(v), i),
           ottieni_tipo_veicolo(v));
}

/*
 * Autore: Russo Nello Manuel
 * Data: 22/05/2025
 *
 * Funzione: interfaccia_seleziona_veicolo
 * ---------------------------------------
 *
 * permette all'utente di selezionare un veicolo mostrando quelli disponibili nell'intervallo specificato
 *
 * Implementazione:
 *    Recupera i veicoli disponibili nell'intervallo, li stampa in una tabella
 *    e chiede all'utente di selezionarne uno inserendo la targa.
 *    Conferma la scelta prima di restituire il veicolo selezionato.
 *
 * Parametri:
 *    tabella_veicoli: tabella contenente i veicoli
 *    i: intervallo per cui si cerca un veicolo disponibile
 *
 * Pre-condizioni:
 *    tabella_veicoli: deve essere diversa da NULL
 *    i: deve essere diversa da NULL
 *
 * Post-condizioni:
 *    se l’utente seleziona un veicolo disponibile, restituisce un puntatore al veicolo selezionato.
 *    Se l’utente esce o non ci sono veicoli disponibili, restituisce NULL.
 *
 * Side-effect:
 *    Stampa a video, acquisizione input utente
 */
Veicolo interfaccia_seleziona_veicolo(TabellaVeicoli tabella_veicoli, Intervallo i){
    unsigned int dimensione;
    Veicolo *v = ottieni_veicoli_disponibili(tabella_veicoli, i, &dimensione);

    if(v == NULL){
        printf("Nessun veicolo disponibile\n");
        return NULL;
    }
    char targa[NUM_CARATTERI_TARGA];
    char scelta;

    printf("TABELLA VEICOLI DISPONIBILI:\n");

	stampa_intestazione_tabella();
    for (unsigned int j = 0; j < dimensione; j++) {
        if(v[j] == NULL) continue;
        stampa_veicolo(v[j], i);
    }
    stampa_riga_separatrice();

    while(1){
        printf("Inserisci la targa del veicolo che vuoi selezionare (per uscire digita E): ");
        ottieni_parola(targa, NUM_CARATTERI_TARGA);

        if(strcmp(targa, "E") == 0) return NULL;

        Veicolo trovato = cerca_veicolo_in_tabella(tabella_veicoli, targa);

        if(trovato != NULL){
            printf("Sei sicuro di voler selezionare questo veicolo? (S/N): ");
            scelta = getchar();
            stdin_fflush();

            if(scelta == 's' || scelta == 'S'){
                return trovato;
            }
        }
        else if(trovato == NULL){
            printf("Veicolo non trovato\n");
        }
    }
}

/*
 * Autore: Russo Nello Manuel
 * Data: 24/05/2025
 *
 * Funzione: prenota_veicolo
 * --------------------------
 *
 * gestisce la prenotazione di un veicolo, mostrando una ricevuta
 * con il dettaglio del costo, lo sconto applicato e il motivo dello sconto
 *
 * Implementazione:
 *    Calcola il costo scontato, stampa una ricevuta e chiede conferma all’utente.
 *    Se l’utente conferma la prenotazione restituisce 1, altrimenti 0.
 *
 * Parametri:
 *    v: veicolo da prenotare
 *    p: prenotazione da associare al veicolo
 *    percentuale: sconto da applicare (compreso tra 0.0 e 1.0)
 *    motivo: stringa che rappresenta la motivazione dello sconto
 *
 * Pre-condizioni:
 *    v: deve essere diverso da NULL
 *    p: deve essere diverso da NULL
 *    percentuale: deve essere compresa tra 0.0 e 1.0
 *    motivo: deve essere diverso da NULL
 *
 * Post-condizione:
 *    restituisce 1 se la prenotazione è confermata, altrimenti 0
 *
 * Side-effect:
 *    stampa a video, acquisizione input utente, allocazione e deallocazione di memoria
 */
Byte prenota_veicolo(Veicolo v, Prenotazione p, double percentuale, const char *motivo){
	if (!v || !p || percentuale < 0.0 || percentuale > 1.0 || !motivo) {
		return 0;
	}

	char scelta;
    double costo_totale = ottieni_costo_prenotazione(p);
    double costo_scontato = costo_totale * (1.0 - percentuale);
    char *desc_v   = veicolo_in_stringa(v);
    char *intervallo  =  intervallo_in_stringa(ottieni_intervallo_prenotazione(p));

	printf("========================================\n");
    printf("         RICEVUTA DI NOLEGGIO          \n");
    printf("========================================\n");
    printf("%s\n", desc_v);
    printf("Periodo: %s\n", intervallo);
    printf("----------------------------------------\n");
    printf("Costo totale       : %8.2f EUR\n", costo_totale);
    printf("Sconto applicato   : %8.0f %%\n", percentuale * 100.0);
    printf("Motivo sconto      : %s\n", motivo);
    printf("Costo scontato     : %8.2f EUR\n", costo_scontato);
    printf("========================================\n\n");

	printf("Prenota (S/N): ");
	scelta = getchar();
	stdin_fflush();

    free(desc_v);
    free(intervallo);

	if((scelta == 's') || (scelta == 'S')){
		return 1;
	}

    return 0;
}


static char *formatta_data(time_t timestamp) {
    char *buffer = malloc(DIMENSIONE_INTERVALLO);
    struct tm *tm_info = localtime(&timestamp);
    strftime(buffer, DIMENSIONE_INTERVALLO, "%d/%m/%Y %H:%M", tm_info);
    return buffer;
}

static char *ottieni_orario(time_t timestamp){
    char *buffer = malloc(DIMENSIONE_INTERVALLO);
    struct tm *tm_info = localtime(&timestamp);
    strftime(buffer, DIMENSIONE_INTERVALLO, "%H:%M", tm_info);
    return buffer;
}

static time_t fine_giornata(time_t inizio) {
    struct tm tm_info = *localtime(&inizio);

    tm_info.tm_hour = 0;
    tm_info.tm_min = 0;
    tm_info.tm_sec = 0;
    tm_info.tm_mday += 1;

    return mktime(&tm_info);
}

/*
 * Autore: Marco Visone
 * Data: 24/05/2025
 */
void visualizza_veicoli_disponibili(TabellaVeicoli tabella_veicoli, time_t data_riferimento) {
    unsigned int dimensione;
    char comando;

    do {
        system("clear || cls");

        time_t ora_corrente_aggiornata = data_riferimento; // Current time for this display cycle
        time_t fine_della_giornata = fine_giornata(ora_corrente_aggiornata);
        Intervallo resto_giornata = crea_intervallo(ora_corrente_aggiornata, fine_della_giornata);

        Veicolo *vettore_veicoli = (Veicolo*) ottieni_vettore(tabella_veicoli, &dimensione);

        printf("\n+-------------------------------------------------------------+\n");
        printf("|              VEICOLI DISPONIBILI - TEMPO REALE              |\n");
        printf("+-------------------------------------------------------------+\n");
        printf("Ultimo Aggiornamento: %s\n", formatta_data(ora_corrente_aggiornata));
        printf("---------------------------------------------------------------\n\n");

        printf("%-3s | %-20s | %-8s | %-11s | %-18s | %-8s | %-16s | %-15s\n",
                 "#", "Modello", "Targa", "Tipo", "Posizione", "Costo", "Disponibile fino", "Durata");
        printf("----+----------------------+----------+-------------+--------------------+----------+------------------+---------------\n");

        int j = 0;
        for (unsigned int i = 0; i < dimensione; i++) {
            Intervallo disponibile = ottieni_intervallo_disponibile(ottieni_prenotazioni(vettore_veicoli[i]), resto_giornata);

            if (disponibile != NULL) {
                char *modello = ottieni_modello(vettore_veicoli[i]);
                char *targa = ottieni_targa(vettore_veicoli[i]);
                char *tipo = ottieni_tipo_veicolo(vettore_veicoli[i]);
                char *posizione = ottieni_posizione(vettore_veicoli[i]);
                double prezzo_min = ottieni_tariffa(vettore_veicoli[i]);

                char costo_str[16];
                snprintf(costo_str, sizeof(costo_str), "%.2f EUR", calcola_costo(prezzo_min, disponibile)); // Changed to EUR for broad use

                time_t fine_disp = fine_intervallo(disponibile);
                char *disponibile_fino_str = ottieni_orario(fine_disp);

                double durata_secondi = difftime(fine_disp, ora_corrente_aggiornata);
                char durata_str[20];

                if (durata_secondi <= 0) {
                    strcpy(durata_str, "N/A"); // Not available now
                } else {
                    int hours = (int)(durata_secondi / 3600);
                    int minutes = (int)((durata_secondi - (hours * 3600)) / 60);
                    snprintf(durata_str, sizeof(durata_str), "%dh %02dm", hours, minutes);
                }

                printf("%-3d | %-20s | %-8s | %-11s | %-18s | %-8s | %-16s | %-15s\n",
                        j++, modello, targa, tipo, posizione, costo_str, disponibile_fino_str, durata_str);
             }
            if (disponibile){
                distruggi_intervallo(disponibile);
            }
        }

        printf("\n---------------------------------------------------------------\n");
        printf("Trovati/o %d veicoli disponibili.\n", j);
        printf("---------------------------------------------------------------\n\n");


        printf("Comandi:\n");
        printf("  [R] Aggiorna\n");
        printf("  [E] Esci\n");
        printf("---------------------------------------------------------------\n");
        printf("Commando: ");
        comando = getchar();
        stdin_fflush();

        if ((comando) == 'R' || comando == 'r') {
            data_riferimento = time(NULL);
        }

    }while (comando != 'E' && comando != 'e');
}

Byte visualizza_storico(char *email_utente, TabellaUtenti tabella_utenti){
    Utente u = cerca_utente_in_tabella(tabella_utenti, email_utente);
    if(u == NULL){
        return -1;
    }

    ListaPre l = ottieni_storico_utente(u);

    if(l == NULL) return -1;

    printf("\n+----------------------------------------------------------------------------+\n");
    printf("|                      STORICO PRENOTAZIONI UTENTE                           |\n");
    printf("+----------------------------------------------------------------------------+\n\n");
    printf("%-15s | %-30s | %-15s\n",
           "Veicolo (Targa)", "Periodo", "Costo Totale (€)");
    printf("-----------------+---------------------------+-----------------\n");

    while (l != NULL){
        Prenotazione p = ottieni_prenotazione_lista(l);
        if(p == NULL) {
            l = ottieni_prossimo(l);
            continue;
        }
        char *str = intervallo_in_stringa(ottieni_intervallo_prenotazione(p));

        printf("%-15s | %-30s | %-15.2f\n",
        ottieni_veicolo_prenotazione(p), str, ottieni_costo_prenotazione(p));

        free(str);
        l = ottieni_prossimo(l);
    }
    printf("-----------------+---------------------------+-----------------\n");

    printf("Digita un tasto per uscire...");
    getchar();
    return 1;
}

/*
 * Autore: Marco Visone
 * Data: 25/05/2025
 *
 * Funzione: gestisci_le_mie_prenotazioni
 * --------------------------------------
 * Gestisce l'interfaccia utente per visualizzare e cancellare le prenotazioni attive
 * di un utente, mostrandole in una tabella formattata.
 *
 * Implementazione:
 *    Recupera le prenotazioni attive dell'utente, le visualizza in una tabella formattata
 *    e permette all'utente di selezionarne una per la cancellazione.
 *    Gestisce tutti i casi edge (nessuna prenotazione, input non valido, conferma).
 *
 * Parametri:
 *    email_utente: stringa con l'email dell'utente (non NULL)
 *    tabella_utenti: tabella degli utenti (non NULL)
 *    tabella_veicoli: tabella dei veicoli (non NULL)
 *
 * Pre-condizioni:
 *    email_utente deve essere una stringa valida
 *    tabella_utenti e tabella_veicoli devono essere inizializzate
 *
 * Post-condizioni:
 *    Restituisce 1 se tutto ok, 0 se errore, -1 se utente non trovato
 *
 * Side-effect:
 *    Modifica lo storico prenotazioni se l'utente cancella una prenotazione
 *    Stampa a video l'interfaccia utente
 */
Byte gestisci_le_mie_prenotazioni(char *email_utente, TabellaUtenti tabella_utenti, TabellaVeicoli tabella_veicoli) {
    Utente u = cerca_utente_in_tabella(tabella_utenti, email_utente);
    if(u == NULL) {
        printf("Errore: utente non trovato\n");
        return -1;
    }

    time_t ora = time(NULL);
    unsigned int num_ele = ottieni_numero_prenotazioni(ottieni_data(u));
    Prenotazione vettore_prenotazione[num_ele];

    while(1) {
        //(system("clear || cls");

        printf("\n");
        printf("+-----------------------------------------------------------------------------------------+\n");
        printf("|                          LE TUE PRENOTAZIONI ATTIVE                                      |\n");
        printf("+----+------------------+-------------+---------------------------------------+-----------+\n");
        printf("| ID |     Modello      |    Targa    |               Periodo                 |   Costo   |\n");
        printf("+----+------------------+-------------+---------------------------------------+-----------+\n");

        unsigned int id = 0;
        for(ListaPre curr = ottieni_storico_utente(u); !lista_vuota(curr); curr = ottieni_prossimo(curr)) {
             Prenotazione p = ottieni_prenotazione_lista(curr);
             Intervallo i = ottieni_intervallo_prenotazione(p);
             if(fine_intervallo(i) > ora) {
                char *targa = ottieni_veicolo_prenotazione(p);
                Veicolo v = cerca_veicolo_in_tabella(tabella_veicoli, targa);
                char *modello = ottieni_modello(v);
                char *periodo = intervallo_in_stringa(i);
                double costo = ottieni_costo_prenotazione(p);
                vettore_prenotazione[id] = p;

                 /* STAMPA RIGA PRENOTAZIONE */
                printf("| %2u | %-16s | %-11s | %-37s | %9.2f |\n",
                        id, modello, targa, periodo, costo);
                printf("+----+------------------+-------------+---------------------------------------+-----------+\n");

                id++;
            }
        }

        if(id == 0) {
            printf("|                       Nessuna prenotazione attiva trovata                              |\n");
            printf("+-----------------------------------------------------------------------------------------+\n");
            printf("Premi un tasto per uscire...");
            getchar();
            return 0;
        }

        printf("\n[-1] Torna al menu principale\n\n");
        printf("Inserisci l'ID della prenotazione da cancellare (0-%u): ", id-1);

        int scelta;
        if(scanf("%d", &scelta) != 1) {
             printf("\nInput non valido. Premere INVIO per continuare...");
             stdin_fflush();
             continue;
         }

        if(scelta < 0) {
            return 1;
        }

        if((unsigned)scelta >= id) {
            printf("\nID non valido. Premere INVIO per continuare...");
            stdin_fflush();
            continue;
        }

        printf("\nSei sicuro di voler cancellare la prenotazione ID %u? (S/N): ", scelta);

        stdin_fflush();
        char conferma = getchar();
        stdin_fflush();

        if((conferma != 'S') && (conferma != 's')) {
            printf("%d %c\n", conferma, conferma);
            return 1;
            continue;
        }

        Prenotazione p = vettore_prenotazione[scelta];
        Veicolo v = cerca_veicolo_in_tabella(tabella_veicoli, ottieni_veicolo_prenotazione(p));
        ListaPre storico = ottieni_storico_utente(u);
        Byte code = rimuovi_prenotazione_veicolo(v, ottieni_intervallo_prenotazione(p));
        storico = rimuovi_prenotazione_lista(storico, vettore_prenotazione[scelta]);

        if((storico == NULL) || !code) {
            printf("\nErrore durante la cancellazione. Premere INVIO per continuare...");
            stdin_fflush();
            return 0;
        }

        imposta_storico_lista(ottieni_data(u), storico);
        printf("\nPrenotazione cancellata con successo! Premere INVIO per continuare...");
        stdin_fflush();
    }
}
