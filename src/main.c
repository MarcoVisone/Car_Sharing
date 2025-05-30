#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>   // Per time(NULL)

#include "interfaccia/interfaccia.h"
#include "interfaccia/interfaccia_amministratore.h"
#include "modelli/byte.h"
#include "modelli/data.h"
#include "modelli/intervallo.h"
#include "modelli/prenotazione.h"
#include "modelli/utente.h"
#include "modelli/veicolo.h"
#include "strutture_dati/prenotazioni.h"
#include "strutture_dati/tabella_hash.h"
#include "strutture_dati/tabella_utenti.h"
#include "strutture_dati/tabella_veicoli.h"
#include "utils/md5.h"
#include "utils/utils.h"
#include "utils/gestore_file.h"

#define TABELLA_GRANDEZZA 20
#define MOTIVO_SCONTO 30
#define FILE_UTENTI "archivio/utenti.bin"
#define FILE_DATI_UTENTI "archivio/dati_utenti.bin"
#define FILE_VEICOLI "archivio/veicoli.bin"
#define FILE_PRENOTAZIONI_VEICOLI "archivio/prenotazioni_veicoli.bin"

typedef enum {
    FASCIA_NORMALE,      // Orari di punta - nessuno sconto
    FASCIA_NOTTURNA,     // 00:00-06:00 e 22:00-23:59 - sconto per bassa domanda
    FASCIA_MATTUTINA,    // 06:00-08:00  - sconto leggero
} TipoFascia;

// Dichiarazioni delle funzioni di utilità per il main
/*
 * Funzione: invio
 * ---------------
 *
 * Attende che l'utente prema INVIO prima di continuare
 *
 * Implementazione:
 *    - Stampa un messaggio che invita a premere INVIO
 *    - Legge caratteri dall'input fino a quando non viene rilevato '\n'
 *
 * Pre-condizioni:
 *    nessuna
 *
 * Post-condizione:
 *    non restituisce niente
 *
 * Side-effect:
 *    consuma tutti i caratteri nel buffer di input fino al newline
 */
void invio();

/*
 * Funzione: carica_tabella_utenti
 * -------------------------------
 *
 * Carica una tabella hash di utenti da file
 *
 * Implementazione:
 *    - Tenta di caricare un vettore di utenti dai file specificati
 *    - Se il caricamento fallisce, crea una tabella vuota
 *    - Calcola una dimensione appropriata per la tabella
 *    - Inserisce tutti gli utenti caricati nella tabella
 *    - Libera la memoria del vettore temporaneo
 *
 * Parametri:
 *    grandezza: dimensione minima della tabella hash
 *    file_utente: percorso del file contenente i dati degli utenti
 *    file_dati: percorso del file contenente i dati aggiuntivi degli utenti
 *
 * Pre-condizioni:
 *    file_utente: non deve essere NULL
 *    file_dati: non deve essere NULL
 *
 * Post-condizione:
 *    restituisce una tabella hash contenente gli utenti caricati
 *    oppure una tabella vuota se il caricamento fallisce
 *
 * Ritorna:
 *    Una tabella hash di utenti (TabellaUtenti) oppure NULL in caso di errore
 *
 * Side-effect:
 *    alloca memoria per la tabella hash e per gli utenti
 */
TabellaUtenti carica_tabella_utenti(unsigned int grandezza, const char *file_utente, const char *file_dati);

/*
 * Funzione: carica_tabella_veicoli
 * --------------------------------
 *
 * Carica una tabella hash di veicoli da file
 *
 * Implementazione:
 *    - Tenta di caricare un vettore di veicoli dai file specificati
 *    - Se il caricamento fallisce, crea una tabella vuota
 *    - Calcola una dimensione appropriata per la tabella
 *    - Inserisce tutti i veicoli caricati nella tabella
 *    - Libera la memoria del vettore temporaneo
 *
 * Parametri:
 *    grandezza: dimensione minima della tabella hash
 *    file_veicolo: percorso del file contenente i dati dei veicoli
 *    file_prenotazioni: percorso del file contenente le prenotazioni
 *
 * Pre-condizioni:
 *    file_veicolo: non deve essere NULL
 *    file_prenotazioni: non deve essere NULL
 *
 * Post-condizione:
 *    restituisce una tabella hash contenente i veicoli caricati
 *    oppure una tabella vuota se il caricamento fallisce
 *
 * Ritorna:
 *    Una tabella hash di veicoli (TabellaVeicoli) oppure NULL in caso di errore
 *
 * Side-effect:
 *    alloca memoria per la tabella hash e per i veicoli
 */
TabellaVeicoli carica_tabella_veicoli(unsigned int grandezza, const char *file_veicolo, const char *file_prenotazioni);

/*
 * Funzione: determina_fascia_oraria
 * ---------------------------------
 *
 * Determina la fascia oraria di un timestamp
 *
 * Implementazione:
 *    - Analizza l'ora e il giorno della settimana
 *    - Classifica il timestamp in una delle fasce disponibili
 *    - Gestisce eventuali errori nella conversione del tempo
 *
 * Parametri:
 *    timestamp: valore time_t rappresentante il tempo da analizzare
 *
 * Pre-condizioni:
 *    timestamp: deve essere un valore valido
 *
 * Post-condizione:
 *    restituisce la fascia oraria corrispondente
 *
 * Ritorna:
 *    Un valore dell'enum TipoFascia
 */
TipoFascia determina_fascia_oraria(time_t timestamp);

/*
 * Funzione: calcola_sconto_percentuale
 * ------------------------------------
 *
 * Calcola lo sconto percentuale in base alla fascia oraria
 *
 * Implementazione:
 *    - Utilizza uno switch per selezionare la percentuale di sconto
 *    - Restituisce valori predefiniti per ogni fascia
 *
 * Parametri:
 *    fascia: tipo di fascia oraria
 *
 * Pre-condizioni:
 *    fascia: deve essere un valore valido dell'enum TipoFascia
 *
 * Post-condizione:
 *    restituisce la percentuale di sconto corrispondente
 *
 * Ritorna:
 *    Un double rappresentante la percentuale di sconto (es. 0.15 per 15%)
 */
double calcola_sconto_percentuale(TipoFascia fascia);

/*
 * Funzione: ottieni_descrizione_fascia
 * ------------------------------------
 *
 * Restituisce una descrizione testuale della fascia oraria
 *
 * Implementazione:
 *    - Utilizza uno switch per selezionare la stringa descrittiva
 *    - Restituisce stringhe costanti predefinite
 *
 * Parametri:
 *    fascia: tipo di fascia oraria
 *
 * Pre-condizioni:
 *    fascia: deve essere un valore valido dell'enum TipoFascia
 *
 * Post-condizione:
 *    restituisce la descrizione corrispondente
 *
 * Ritorna:
 *    Una stringa costante costante
 */
const char* ottieni_descrizione_fascia(TipoFascia fascia);

/*
 * Funzione: menu_utente
 * ---------------------
 *
 * Gestisce il menu principale per gli utenti clienti
 *
 * Implementazione:
 *    - Mostra un menu con diverse opzioni
 *    - Gestisce l'interazione con l'utente
 *    - Chiama le funzioni appropriate in base alla scelta
 *
 * Parametri:
 *    utente: l'utente loggato
 *    tabella_veicoli: tabella hash dei veicoli disponibili
 *    tabella_utenti: tabella hash degli utenti registrati
 *
 * Pre-condizioni:
 *    utente: deve essere un utente valido con permesso CLIENTE
 *    tabella_veicoli: non deve essere NULL
 *    tabella_utenti: non deve essere NULL
 *
 * Post-condizione:
 *    non restituisce niente
 *
 * Side-effect:
 *    esegue le operazioni richieste dall'utente fino al logout
 *    modifica lo stato delle prenotazioni e dello storico utente
 */
void menu_utente(Utente utente, TabellaVeicoli tabella_veicoli, TabellaUtenti tabella_utenti);

/*
 * Funzione: menu_amministratore
 * -----------------------------
 *
 * Gestisce il menu principale per gli utenti amministratori
 *
 * Implementazione:
 *    - Mostra un menu con opzioni di amministrazione
 *    - Gestisce l'interazione con l'utente
 *    - Chiama le funzioni appropriate in base alla scelta
 *
 * Parametri:
 *    amministratore: l'utente loggato
 *    tabella_veicoli: tabella hash dei veicoli disponibili
 *    tabella_utenti: tabella hash degli utenti registrati
 *
 * Pre-condizioni:
 *    amministratore: deve essere un utente valido con permesso ADMIN
 *    tabella_veicoli: non deve essere NULL
 *    tabella_utenti: non deve essere NULL
 *
 * Post-condizione:
 *    non restituisce niente
 *
 * Side-effect:
 *    esegue le operazioni di amministrazione fino al logout
 *    modifica lo stato dei veicoli e delle prenotazioni
 */
void menu_amministratore(Utente amministratore, TabellaVeicoli tabella_veicoli, TabellaUtenti tabella_utenti);

/*
 * Funzione: menu_utente
 * ---------------------
 * Gestisce il menu principale per gli utenti clienti con tutte le operazioni disponibili
 *
 * Implementazione:
 *    - Mostra un'interfaccia testuale con 5 opzioni principali
 *    - Gestisce la selezione e l'input dell'utente
 *    - Per ogni opzione:
 *        * '1': Visualizza veicoli disponibili in tempo reale
 *        * '2': Gestisce il processo completo di prenotazione:
 *            - Richiede intervallo di prenotazione
 *            - Seleziona veicolo disponibile
 *            - Calcola costi e sconti (fedeltà e fascia oraria)
 *            - Conferma e salva la prenotazione
 *        * '3': Gestione prenotazioni esistenti (visualizza/cancella)
 *        * '4': Visualizza storico noleggi precedenti
 *        * '5': Logout e uscita dal menu
 *    - Gestisce errori e casi limite con messaggi appropriati
 *    - Pulisce lo schermo tra le operazioni
 *
 * Parametri:
 *    utente: puntatore all'utente loggato (non NULL, già validato)
 *    tabella_veicoli: tabella hash contenente tutti i veicoli disponibili
 *    tabella_utenti: tabella hash contenente tutti gli utenti registrati
 *
 * Pre-condizioni:
 *    utente:; deve essere un puntatore valido a un Utente con permesso CLIENTE
 *    tabella_veicoli: non deve essere NULL
 *    tabella_utenti: non deve essere NULL
 *
 * Post-condizione:
 *    non restituisce niente
 *
 * Side-effect:
 *    Modifica lo stato delle prenotazioni nei veicoli
 *    Aggiorna lo storico dell'utente
 *    Può allocare/distruggere oggetti Prenotazione e Intervallo
 *    Interagisce con stdin/stdout per l'I/O
 */
void scelta_menu(Utente utente, TabellaVeicoli tabella_veicoli, TabellaUtenti);

/*
 * Funzione: salva_tabella_utenti
 * ------------------------------
 *
 * Salva la tabella hash degli utenti su file
 *
 * Implementazione:
 *    - Estrae un vettore di utenti dalla tabella hash
 *    - Chiama la funzione di salvataggio su file
 *    - Gestisce eventuali errori nei parametri
 *
 * Parametri:
 *    tabella_utenti: tabella hash da salvare
 *    file_utente: percorso del file per i dati principali
 *    file_dati: percorso del file per i dati aggiuntivi
 *
 * Pre-condizioni:
 *    tabella_utenti: non deve essere NULL
 *    file_utente: non deve essere NULL
 *    file_dati: non deve essere NULL
 *
 * Post-condizione:
 *    non restituisce niente
 *
 * Side-effect:
 *    i dati degli utenti sono salvati sui file specificati e alloca memoria temporanea per il vettore
 */
void salva_tabella_utenti(TabellaUtenti tabella_utenti, const char *file_utente, const char *file_dati);

/*
 * Funzione: salva_tabella_veicoli
 * -------------------------------
 *
 * Salva la tabella hash dei veicoli su file
 *
 * Implementazione:
 *    - Estrae un vettore di veicoli dalla tabella hash
 *    - Chiama la funzione di salvataggio su file
 *    - Gestisce eventuali errori nei parametri
 *
 * Parametri:
 *    tabella_veicoli: tabella hash da salvare
 *    file_veicoli: percorso del file per i dati dei veicoli
 *    file_prenotazioni: percorso del file per le prenotazioni
 *
 * Pre-condizioni:
 *    tabella_veicoli: non deve essere NULL
 *    file_veicoli e file_prenotazioni devono essere percorsi validi
 *
 * Post-condizione:
 *    non restituisce niente
 *
 * Side-effect:
 *    i dati dei veicoli sono salvati sui file specificati e alloca memoria temporanea per il vettore
 */
void salva_tabella_veicoli(TabellaVeicoli tabella_veicoli, const char *file_veicoli, const char *file_prenotazioni);

/*
 * Funzione: main
 * ----------------------
 * Punto di ingresso principale del programma
 *
 * Implementazione:
 *    - Carica le tabelle hash da file
 *    - Crea l'amministratore di default se necessario
 *    - Gestisce il ciclo principale di accesso/registrazione
 *    - Mostra i menu appropriati in base al tipo di utente
 *    - Salva i dati prima di terminare
 *
 * Pre-condizioni:
 *    nessuna
 *
 * Post-condizione:
 *    il programma è eseguito fino alla scelta di uscita
 *    tutti i dati sono salvati correttamente prima di terminare
 *
 * Ritorna:
 *    0 in caso di successo, -1 in caso di errore critico
 *
 * Side-effect:
 *    gestisce tutte le risorse di memoria e file del programma
 */
int main() {
    TabellaUtenti tabella_utenti = carica_tabella_utenti(TABELLA_GRANDEZZA, FILE_UTENTI, FILE_DATI_UTENTI);
    TabellaVeicoli tabella_veicoli = carica_tabella_veicoli(TABELLA_GRANDEZZA, FILE_VEICOLI, FILE_PRENOTAZIONI_VEICOLI);
    uint8_t password[DIMENSIONE_PASSWORD];

    if(tabella_utenti == NULL || tabella_veicoli == NULL){
        printf("Errore del sistema!\n");
        // Pulizia delle risorse parzialmente allocate
        if(tabella_utenti != NULL) {
            distruggi_tabella_utenti(tabella_utenti);
        }
        if(tabella_veicoli != NULL) {
            distruggi_tabella_veicoli(tabella_veicoli);
        }
        return -1;
    }

    // Creazione admin in caso non è stato già caricato (primo avvio)
    Utente admin_presente = cerca_utente_in_tabella(tabella_utenti, "admin@email.com");
    if (admin_presente == NULL) {
        const char *password_str = "Admin_123&";
        // Inizializzazione sicura dell'array password
        memset(password, 0, DIMENSIONE_PASSWORD);
        md5(password_str, strlen(password_str), password);
        admin_presente = crea_utente("admin@email.com", password, "Manuel Nello", "Russo", ADMIN);

        if(admin_presente == NULL){
            printf("Errore: Impossibile creare l'amministratore di default.\n");
            // Pulizia delle risorse prima di uscire
            distruggi_tabella_utenti(tabella_utenti);
            distruggi_tabella_veicoli(tabella_veicoli);
            return -1;
        }

        if (!aggiungi_utente_in_tabella(tabella_utenti, admin_presente)) {
            distruggi_utente(admin_presente);
            printf("Errore: Impossibile aggiungere l'amministratore\n");
            //  Pulizia delle risorse prima di uscire
            distruggi_tabella_utenti(tabella_utenti);
            distruggi_tabella_veicoli(tabella_veicoli);
            return -1;
        }
    }

    // --- CICLO PRINCIPALE DI ACCESSO/REGISTRAZIONE ---
    Byte scelta;
    do {
        scelta = benvenuto();

        switch (scelta) {
            case '1': {
                menu_registrazione(tabella_utenti);
                break;
            }
            case '2': {
                Utente utente_loggato = menu_accesso(tabella_utenti);

                if(utente_loggato == NULL) break;

                Byte permesso = ottieni_permesso(utente_loggato);

                if(permesso == CLIENTE){
                    menu_utente(utente_loggato, tabella_veicoli, tabella_utenti);
                }else menu_amministratore(utente_loggato, tabella_veicoli, tabella_utenti);

                break;
            }
            case '3': { // Esci
                printf("Uscita dal programma.\n");
                break;
            }
            default: {
                stampa_errore("Opzione non valida. Riprova.");
                printf("Premi INVIO per continuare...");
                getchar();
                break;
            }
        }
    } while (scelta != '3');

    // Salvataggio PRIMA della distruzione delle tabelle
    // Questo evita l'accesso a memoria già liberata durante il salvataggio
    printf("Salvataggio dei dati in corso...\n");
    salva_tabella_utenti(tabella_utenti, FILE_UTENTI, FILE_DATI_UTENTI);
    salva_tabella_veicoli(tabella_veicoli, FILE_VEICOLI, FILE_PRENOTAZIONI_VEICOLI);
    printf("Salvataggio completato.\n");

    // Pulizia finale con controlli di validità
    // Distrugge le tabelle hash e tutti gli elementi al loro interno
    if(tabella_utenti != NULL) {
        distruggi_tabella_utenti(tabella_utenti);
        tabella_utenti = NULL; // Prevenire accessi accidentali
    }

    if(tabella_veicoli != NULL) {
        distruggi_tabella_veicoli(tabella_veicoli);
        tabella_veicoli = NULL; // Prevenire accessi accidentali
    }

    printf("\n>> Programma terminato e memoria liberata correttamente.\n");
    return 0;
}

void invio(){
    puts("Premi invio per continuare...");
    char c = getchar();
    while(c != '\n') c = getchar();
}

TabellaUtenti carica_tabella_utenti(unsigned int grandezza, const char *file_utente, const char *file_dati){
    TabellaUtenti tabella_utenti = NULL;

    unsigned int num_utenti_caricati = 0;
    Utente *utenti_caricati = carica_vettore_utenti(file_utente, file_dati, &num_utenti_caricati);

    if(utenti_caricati == NULL){
        tabella_utenti = crea_tabella_utenti(grandezza);
        return tabella_utenti;
    }

    unsigned int dimensione_tabella = (num_utenti_caricati * 2 > grandezza) ?
                                      num_utenti_caricati * 2 : grandezza;
    tabella_utenti = crea_tabella_utenti(dimensione_tabella);

    if(tabella_utenti == NULL){
        printf("Errore caricamento utenti!\n");
        // Pulizia sicura degli utenti caricati
        for(unsigned i = 0; i < num_utenti_caricati; i++) {
            if(utenti_caricati[i] != NULL) {
                distruggi_utente(utenti_caricati[i]);
            }
        }
        free(utenti_caricati);
        return NULL;
    }

    carica_utenti(tabella_utenti, utenti_caricati, num_utenti_caricati);

    // Pulizia sicura del vettore
    free(utenti_caricati);
    utenti_caricati = NULL;

    return tabella_utenti;
}

TabellaVeicoli carica_tabella_veicoli(unsigned int grandezza, const char *file_veicolo, const char *file_prenotazioni){
    TabellaVeicoli tabella_veicoli = NULL;

    unsigned int num_veicoli_caricati = 0;
    Veicolo *veicoli_caricati = carica_vettore_veicoli(file_veicolo, file_prenotazioni, &num_veicoli_caricati);

    if(veicoli_caricati == NULL){
        tabella_veicoli = crea_tabella_veicoli(grandezza);
        return tabella_veicoli;
    }

    unsigned int dimensione_tabella = (num_veicoli_caricati * 2 > grandezza) ?
                                      num_veicoli_caricati * 2 : grandezza;
    tabella_veicoli = crea_tabella_veicoli(dimensione_tabella);

    if(tabella_veicoli == NULL){
        printf("Errore caricamento veicoli!\n");
        for(unsigned i = 0; i < num_veicoli_caricati; i++) {
            if(veicoli_caricati[i] != NULL) {
                distruggi_veicolo(veicoli_caricati[i]);
            }
        }
        free(veicoli_caricati);
        return NULL;
    }

    carica_veicoli(tabella_veicoli, veicoli_caricati, num_veicoli_caricati);

    free(veicoli_caricati);
    veicoli_caricati = NULL;

    return tabella_veicoli;
}

TipoFascia determina_fascia_oraria(time_t timestamp) {
    struct tm *tm_info = localtime(&timestamp);
    if(tm_info == NULL) {
        // Gestione errore localtime
        return FASCIA_NORMALE;
    }

    int ora = tm_info->tm_hour;
    int giorno_settimana = tm_info->tm_wday;

    // Weekend = nessuno sconto (alta domanda per tempo libero)
    if (giorno_settimana == 0 || giorno_settimana == 6) {
        return FASCIA_NORMALE;
    }

    if (ora >= 22 || ora < 6) {
        return FASCIA_NOTTURNA;     // Notte: poca domanda
    }

    if (ora >= 6 && ora < 8) {
        return FASCIA_MATTUTINA;    // Prima mattina: incentivo per partenze precoci
    }

    //orari di punta = prezzo pieno
    return FASCIA_NORMALE;
}

double calcola_sconto_percentuale(TipoFascia fascia) {
    switch (fascia) {
        case FASCIA_NOTTURNA:     return 0.15;  // 15% sconto - molto meno richiesta
        case FASCIA_MATTUTINA:    return 0.10;  // 10% sconto - incentivo mattutino
        case FASCIA_NORMALE:
        default:                  return 0.0;   // Nessuno sconto - orari normali/di punta
    }
}

const char* ottieni_descrizione_fascia(TipoFascia fascia) {
    switch (fascia) {
        case FASCIA_NOTTURNA:     return "Sconto notturno";
        case FASCIA_MATTUTINA:    return "Sconto mattutino";
        case FASCIA_NORMALE:
        default:                  return "Nessuno";
    }
}

// --- Menu per Utente Normale (Cliente) ---
void menu_utente(Utente utente, TabellaVeicoli tabella_veicoli, TabellaUtenti tabella_utenti) {
    char scelta_menu_utente;
    do {
        system("clear || cls");
        stampa_header("MENU UTENTE");
        printf("Benvenuto, %s %s!\n", ottieni_nome(utente), ottieni_cognome(utente));
        printf("1. Visualizza veicoli disponibili\n");
        printf("2. Prenota un veicolo\n");
        printf("3. Gestisci le mie prenotazioni (visualizza/cancella)\n");
        printf("4. Visualizza storico noleggi\n");
        printf("5. Logout\n");
        printf("Scegli un'opzione: ");
        scelta_menu_utente = getchar();
        while(scelta_menu_utente == '\n'){
            scelta_menu_utente = getchar();
        }
        stdin_fflush();

        switch (scelta_menu_utente) {
            case '1': { // Visualizza veicoli disponibili (Tempo reale)
                visualizza_veicoli_disponibili(tabella_veicoli, time(NULL));
                break;
            }
            case '2': { // Prenota un veicolo
                stampa_header("PRENOTA UN VEICOLO");

                Intervallo intervallo_prenotazione = richiedi_intervallo_prenotazione();
                if (intervallo_prenotazione == NULL) {
                    stampa_errore("Prenotazione annullata o intervallo non valido.");
                    invio();
                    break;
                }

                Veicolo veicolo_selezionato = interfaccia_seleziona_veicolo(tabella_veicoli, intervallo_prenotazione);
                if (veicolo_selezionato == NULL) {
                    stampa_errore("Nessun veicolo selezionato o disponibile per l'intervallo.");
                    distruggi_intervallo(intervallo_prenotazione);
                    invio();
                    break;
                }

                Prenotazione nuova_prenotazione = crea_prenotazione(
                    ottieni_email(utente),
                    ottieni_targa(veicolo_selezionato),
                    intervallo_prenotazione,
                    calcola_costo(ottieni_tariffa(veicolo_selezionato), intervallo_prenotazione)
                );

                if (nuova_prenotazione == NULL) {
                    stampa_errore("Errore nella creazione della prenotazione.");
                    distruggi_intervallo(intervallo_prenotazione);
                    invio();
                    break;
                }

                double sconto_totale = 0;
                char motivo_sconto[MOTIVO_SCONTO * 2];
                //  Inizializzazione sicura della stringa
                memset(motivo_sconto, 0, sizeof(motivo_sconto));

                /*Se il numero di prenotazioni è 0 allora nessun premio frequenza!*/
                Byte molto_frequente = 0;
                unsigned int num_prenotazioni = ottieni_numero_prenotazioni_utente(utente);
                getchar();
                if(num_prenotazioni > 0)
                    molto_frequente = (num_prenotazioni % 5) == 0;

                TipoFascia fascia_oraria = determina_fascia_oraria(inizio_intervallo(intervallo_prenotazione));
                distruggi_intervallo(intervallo_prenotazione);

                if(molto_frequente){
                    sconto_totale += 0.20; // 20% di sconto
                    strncpy(motivo_sconto, "Premio fedeltà (20%)", sizeof(motivo_sconto) - 1);
                }

                if (fascia_oraria != FASCIA_NORMALE) {
                    double sconto_fascia = calcola_sconto_percentuale(fascia_oraria);
                    sconto_totale += sconto_fascia;

                    if (strlen(motivo_sconto) > 0) {
                        strncat(motivo_sconto, " + ", sizeof(motivo_sconto) - strlen(motivo_sconto) - 1);
                    }
                    char temp[MOTIVO_SCONTO];
                    snprintf(temp, sizeof(temp), "%s (%.0f%%)",
                             ottieni_descrizione_fascia(fascia_oraria), sconto_fascia * 100);
                    strncat(motivo_sconto, temp, sizeof(motivo_sconto) - strlen(motivo_sconto) - 1);
                }

                if (!prenota_veicolo(veicolo_selezionato, nuova_prenotazione, sconto_totale, motivo_sconto)) {
                    stampa_errore("Prenotazione annullata dall'utente o errore.");
                    distruggi_prenotazione(nuova_prenotazione);
                    invio();
                    break;
                }

                aggiungi_a_storico_utente(utente, nuova_prenotazione);
                aggiungi_prenotazione_veicolo(veicolo_selezionato, nuova_prenotazione);
                stampa_successo("Veicolo prenotato con successo!");
                invio();
                break;
            }
            case '3': { // Gestisci le mie prenotazioni
                Byte codice = gestisci_le_mie_prenotazioni(ottieni_email(utente), tabella_utenti, tabella_veicoli);
                if (codice < 0) {
                    stampa_errore("Errore sconosciuto!");
                    invio();
                }
                break;
            }
            case '4': { // Visualizza storico noleggi
                Byte codice = visualizza_storico(ottieni_email(utente), tabella_utenti, tabella_veicoli);
                if (codice < 0) {
                    stampa_info("Al momento non hai ancora fatto prenotazioni!");
                    invio();
                }
                break;
            }
            case '5': { // Logout
                printf("Effettuato il logout.\n");
                break;
            }
            default: {
                stampa_errore("Opzione non valida. Riprova.");
                invio();
                break;
            }
        }
    } while (scelta_menu_utente != '5');
}

//Menu per Amministratore
void menu_amministratore(Utente amministratore, TabellaVeicoli tabella_veicoli, TabellaUtenti tabella_utenti) {
    char scelta_menu_admin;
    do {
        system("clear || cls");
        stampa_header("MENU AMMINISTRATORE");
        printf("Benvenuto, %s %s (Amministratore)!\n", ottieni_nome(amministratore), ottieni_cognome(amministratore));
        printf("1. Aggiungi un veicolo\n");
        printf("2. Rimuovi un veicolo\n");
        printf("3. Gestione Noleggi\n");
        printf("4. Storico Noleggi\n");
        printf("5. Logout\n");
        printf("Scegli un'opzione: ");
        scelta_menu_admin = getchar();
        stdin_fflush();

        switch (scelta_menu_admin) {
            case '1': { // Aggiungi un veicolo
                stampa_header("AGGIUNGI NUOVO VEICOLO");
                Veicolo v = interfaccia_aggiungi_veicolo(tabella_veicoli); // Questa funzione crea e alloca un veicolo
                if(v == NULL){
                    stampa_info("Il veicolo non è stato salvato");
                } else {
                    Byte codice = aggiungi_veicolo_in_tabella(tabella_veicoli, v);
                    if(codice){
                        stampa_successo("Veicolo aggiunto con successo!");
                    }else{
                        stampa_errore("Veicolo non aggiunto! La targa potrebbe essere già in uso.");
                        distruggi_veicolo(v);
                    }
                }
                stdin_fflush();
                invio();
                break;
            }
            case '2': { // Rimuovi un veicolo
                stampa_header("RIMUOVI VEICOLO");
                interfaccia_rimuovi_veicolo(tabella_veicoli);
                invio();
                break;
            }
            case '3': { // Visualizza tutti i veicoli con le prenotazioni
                stampa_header("Gestione Noleggi");
                gestione_noleggi(tabella_veicoli);
                invio();
                break;
            }
            case '4': { // Visualizza storico noleggi di un utente specifico
                Byte result = storico_noleggi(tabella_utenti, tabella_veicoli);

                if (result == -1) {
                    stampa_errore("Al momento non ci sono utenti registrati!\n");
                }

                invio();
                break;
            }
            case '5': { // Logout
                printf("Effettuato il logout.\n");
                break;
            }
            default: {
                stampa_errore("Opzione non valida. Riprova.");
                invio();
                break;
            }
        }
    } while (scelta_menu_admin != '5');
}

void salva_tabella_utenti(TabellaUtenti tabella_utenti, const char *file_utente, const char *file_dati){
    //  Controlli di validità prima dell'accesso
    if(tabella_utenti == NULL || file_utente == NULL || file_dati == NULL) {
        printf("Errore: parametri non validi per il salvataggio utenti\n");
        return;
    }

    unsigned int numero_utenti = 0;
    Utente *vettore_utenti = (Utente*)ottieni_vettore(tabella_utenti, &numero_utenti);

    if (vettore_utenti == NULL || numero_utenti == 0) {
        printf("Nessun utente da salvare\n");
        return;
    }

    // IMPORTANTE: salva_vettore_utenti deve essere chiamata PRIMA che le strutture Utente
    // vengano distrutte, perché le funzioni ottieni_* restituiscono const char* che puntano
    // direttamente ai dati interni degli oggetti Utente
    salva_vettore_utenti(file_utente, file_dati, vettore_utenti, numero_utenti);

    //  Libera solo il vettore di puntatori, NON gli oggetti Utente
    // Gli oggetti Utente saranno liberati da distruggi_tabella_utenti()
    free(vettore_utenti);
    vettore_utenti = NULL;
}

void salva_tabella_veicoli(TabellaVeicoli tabella_veicoli, const char *file_veicoli, const char *file_prenotazioni){
    //  Controlli di validità prima dell'accesso
    if(tabella_veicoli == NULL || file_veicoli == NULL || file_prenotazioni == NULL) {
        printf("Errore: parametri non validi per il salvataggio veicoli\n");
        return;
    }

    unsigned int numero_veicoli = 0;
    Veicolo *vettore_veicoli = (Veicolo*)ottieni_vettore(tabella_veicoli, &numero_veicoli);

    if (vettore_veicoli == NULL) {
        printf("Nessun veicolo da salvare\n");
        return;
    }

    // IMPORTANTE: salva_vettore_veicoli deve essere chiamata PRIMA che le strutture Veicolo
    // vengano distrutte, perché le funzioni ottieni_* restituiscono const char* che puntano
    // direttamente ai dati interni degli oggetti Veicolo
    salva_vettore_veicoli(file_veicoli, file_prenotazioni, vettore_veicoli, numero_veicoli);

    // Gli oggetti Veicolo saranno liberati da distruggi_tabella_veicoli()
    free(vettore_veicoli);
    vettore_veicoli = NULL;
}
