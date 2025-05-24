#include "interfaccia/interfaccia.h"
#include "utils/utils.h"
#include "utils/md5.h"
#include "modelli/intervallo.h"
#include "modelli/utente.h"
#include "strutture_dati/tabella_utenti.h"
#include "modelli/veicolo.h"
#include "strutture_dati/tabella_veicoli.h"
#include <string.h>
#include <stdio.h>

#define stdin_fflush() while(getchar() != '\n')
#define DIMENSIONE_STRINGA_PASSWORD (64 + 2)
#define DIMENSIONE_INTERVALLO (16 + 2)

static void inserisci_stringa(char *stringa, unsigned int lunghezza);
static void ottieni_parola(char *stringa, int dimensione);
static void stampa_veicolo(const Veicolo v, Intervallo i);

static void inserisci_stringa(char *stringa, unsigned int lunghezza){
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
static void ottieni_parola(char *stringa, int dimensione){
    fgets(stringa, dimensione, stdin);
    int i = 0;
    while(i < (dimensione-1) && *stringa){
      if (*stringa == '\n'|| *stringa == ' '){
        *stringa = '\0';
        break;
      }
      stringa++;
      i++;
    }

    if(i >= (dimensione-1)){
        stdin_fflush();
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
Byte interfaccia_accesso(TabellaUtenti tabella_utenti){
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
                return -1;
            }
            distruggi_utente(utente);
            utente = NULL;
            tentativi++;
        }
        else break;
    }while(tentativi < 3);

    return tentativi;
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

static void stampa_riga_separatrice() {
    printf("+------------+--------------------------------+--------------------------------+--------------+------------------------+\n");
}

static void stampa_intestazione_tabella() {
    stampa_riga_separatrice();
    printf("| %-10s | %-30s | %-30s | %-12s | %-22s |\n",
           "Targa", "Modello", "Posizione", "Prezzo", "Tipo");
    stampa_riga_separatrice();
}

static void stampa_veicolo(const Veicolo v, Intervallo i) {
    printf("| %-10s | %-30s | %-30s | %-10.2f € | %-22s |\n",
           ottieni_targa(v),
           ottieni_modello(v),
           ottieni_posizione(v),
           calcola_costo(ottieni_tariffa(v), i),
           ottieni_tipo_veicolo(v));
}

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
        inserisci_stringa(targa, NUM_CARATTERI_TARGA);

        if(strcmp(targa, "E") == 0) return NULL;

        Veicolo trovato = cerca_veicolo_in_tabella(tabella_veicoli, targa);

        if(trovato != NULL){
            printf("Sei sicuro di voler selezionare questo veicolo? (S/N): ");
            scelta = getchar();

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
 * Autore: Marco Visone
 * Data: 24/05/2025
 */
void visualizza_veicoli_disponibili(TabellaVeicoli tabella_veicoli){
    unsigned int dimensione;
    Intervallo i = crea_intervallo(time(NULL), time(NULL));
}

void prenota_veicolo(Veicolo v, Prenotazione p, double percentuale, const char *motivo){
	if (!v || !p || percentuale < 0.0 || percentuale > 1.0 || !motivo) {
		printf("Errore di sistema\n");
		return;
	}

    double costo_totale = ottieni_costo_prenotazione(p);
    double costo_scontato = costo_totale * (1.0 - percentuale);
    char *desc_v   = veicolo_in_stringa(v);
    char *desc_pr  = prenotazione_in_stringa(p);

	printf("========================================\n");
    printf("         RICEVUTA DI NOLEGGIO          \n");
    printf("========================================\n");
    printf("%s\n", desc_v);
    printf("%s\n", desc_pr);
    printf("----------------------------------------\n");
    printf("Costo totale       : %8.2f EUR\n", costo_totale);
    printf("Sconto applicato   : %8.0f %%\n", percentuale * 100.0);
    printf("Motivo sconto      : %s\n", motivo);
    printf("Costo scontato     : %8.2f EUR\n", costo_scontato);
    printf("========================================\n\n");

    free(desc_v);
    free(desc_pr);
}