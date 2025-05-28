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
    FASCIA_MATTUTINA,    // 06:00-08:00 giorni feriali - sconto leggero
    FASCIA_POMERIDIANA   // 14:00-17:00 giorni feriali - sconto leggero
} TipoFascia;

// Dichiarazioni delle funzioni di utilità per il main
void invio();
TabellaUtenti carica_tabella_utenti(unsigned int grandezza, const char *file_utente, const char *file_dati);
TabellaVeicoli carica_tabella_veicoli(unsigned int grandezza, const char *file_veicolo, const char *file_prenotazioni);
TipoFascia determina_fascia_oraria(time_t timestamp);
double calcola_sconto_percentuale(TipoFascia fascia);
const char* ottieni_descrizione_fascia(TipoFascia fascia);
void menu_utente(Utente utente, TabellaVeicoli tabella_veicoli, TabellaUtenti tabella_utenti);
void menu_amministratore(Utente amministratore, TabellaVeicoli tabella_veicoli, TabellaUtenti tabella_utenti);
void scelta_menu(Utente utente, TabellaVeicoli tabella_veicoli, TabellaUtenti);
void salva_tabella_utenti(TabellaUtenti tabella_utenti, const char *file_utente, const char *file_dati);
void salva_tabella_veicoli(TabellaVeicoli tabella_veicoli, const char *file_veicoli, const char *file_prenotazioni);

int main() {
    TabellaUtenti tabella_utenti = carica_tabella_utenti(TABELLA_GRANDEZZA, FILE_UTENTI, FILE_DATI_UTENTI);
    TabellaVeicoli tabella_veicoli = carica_tabella_veicoli(TABELLA_GRANDEZZA, FILE_VEICOLI, FILE_PRENOTAZIONI_VEICOLI);
    uint8_t password[DIMENSIONE_PASSWORD];

    if(tabella_utenti == NULL || tabella_veicoli == NULL){
        printf("Errore del sistema!\n");
        return -1;
    }

    // Creazione admin in caso non è stato già caricato (primo avvio)
    Utente admin_presente = cerca_utente_in_tabella(tabella_utenti, "admin@email.com");
    if (admin_presente == NULL) {
        const char *password_str = "Admin_123&";
        md5(password_str, strlen(password_str), password);
        admin_presente = crea_utente("admin@email.com", password, "Manuel Nello", "Russo", ADMIN);

        if(admin_presente == NULL){
            printf("Errore: Impossibile creare l'amministratore di default.\n");
            return -1;
        }

        if (!aggiungi_utente_in_tabella(tabella_utenti, admin_presente)) {
            distruggi_utente(admin_presente);
            printf("Errore: Impossibile aggiungere l'amministratore\n");
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


    salva_tabella_utenti(tabella_utenti, FILE_UTENTI, FILE_DATI_UTENTI);
    salva_tabella_veicoli(tabella_veicoli, FILE_VEICOLI, FILE_PRENOTAZIONI_VEICOLI);

    // Pulizia finale: distrugge le tabelle hash e tutti gli elementi al loro interno
    distruggi_tabella_utenti(tabella_utenti);
    distruggi_tabella_veicoli(tabella_veicoli);
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

    //Metto il doppio degli utenti caricati per evitare collisioni
    tabella_utenti = crea_tabella_utenti(num_utenti_caricati * 2);

    if(tabella_utenti == NULL){
        printf("Errore caricamento utenti!\n");
        for(unsigned i = 0; i < num_utenti_caricati; i++) distruggi_utente(utenti_caricati[i]);
        free(utenti_caricati);
        return NULL;
    }

    carica_utenti(tabella_utenti, utenti_caricati, num_utenti_caricati);

    free(utenti_caricati);

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

    //Metto il doppio degli utenti caricati per evitare collisioni
    tabella_veicoli = crea_tabella_veicoli(num_veicoli_caricati * 2);

    if(tabella_veicoli == NULL){
        printf("Errore caricamento veicoli!\n");
        for(unsigned i = 0; i < num_veicoli_caricati; i++) distruggi_veicolo(veicoli_caricati[i]);
        free(veicoli_caricati);
        return NULL;
    }

    carica_veicoli(tabella_veicoli, veicoli_caricati, num_veicoli_caricati);

    free(veicoli_caricati);

    return tabella_veicoli;
}

TipoFascia determina_fascia_oraria(time_t timestamp) {
    struct tm *tm_info = localtime(&timestamp);
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

    if (ora >= 14 && ora < 17) {
        return FASCIA_POMERIDIANA;  // Primo pomeriggio: dopo pranzo, meno richiesto
    }

    // Orari 8:00-14:00 e 17:00-22:00 = orari di punta = prezzo pieno
    return FASCIA_NORMALE;
}

double calcola_sconto_percentuale(TipoFascia fascia) {
    switch (fascia) {
        case FASCIA_NOTTURNA:     return 0.15;  // 15% sconto - molto meno richiesta
        case FASCIA_MATTUTINA:    return 0.10;  // 10% sconto - incentivo mattutino
        case FASCIA_POMERIDIANA:  return 0.05;  // 5% sconto - pomeriggio tranquillo
        case FASCIA_NORMALE:
        default:                  return 0.0;   // Nessuno sconto - orari normali/di punta
    }
}

const char* ottieni_descrizione_fascia(TipoFascia fascia) {
    switch (fascia) {
        case FASCIA_NOTTURNA:     return "Sconto notturno";
        case FASCIA_MATTUTINA:    return "Sconto mattutino";
        case FASCIA_POMERIDIANA:  return "Sconto pomeridiano";
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
                    invio();
                    break;
                }

                double sconto_totale = 0;
                char motivo_sconto[MOTIVO_SCONTO * 2] = "";
                Byte molto_frequente = (ottieni_frequenza_cliente(utente) % 5) == 0;
                Byte fascia_oraria = determina_fascia_oraria(inizio_intervallo(intervallo_prenotazione));

                if(molto_frequente){
                    sconto_totale += 0.20; // 20% di sconto
                    strcpy(motivo_sconto, "Premio fedeltà (20%)");
                    azzera_frequenza(ottieni_data(utente)); //Lo azzero solo per evitare che raggiunga numeri enormi
                }

                if (fascia_oraria != FASCIA_NORMALE) {
                    float sconto_fascia = calcola_sconto_percentuale(fascia_oraria);
                    sconto_totale += sconto_fascia;

                    if (strlen(motivo_sconto) > 0) {
                        strcat(motivo_sconto, " + ");
                    }
                    char temp[MOTIVO_SCONTO];
                    snprintf(temp, sizeof(temp), "%s (%.0f%%)",
                             ottieni_descrizione_fascia(fascia_oraria), sconto_fascia * 100);
                    strcat(motivo_sconto, temp);
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
                    stampa_errore("Al momento non hai ancora fatto prenotazioni!");
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
    unsigned int numero_utenti = 0;
    Utente *vettore_utenti = (Utente*)ottieni_vettore(tabella_utenti, &numero_utenti);

    if (vettore_utenti == NULL || numero_utenti == 0) return;

    salva_vettore_utenti(file_utente, file_dati, vettore_utenti, numero_utenti);

    free(vettore_utenti);
}

void salva_tabella_veicoli(TabellaVeicoli tabella_veicoli, const char *file_veicoli, const char *file_prenotazioni){
    unsigned int numero_veicoli = 0;
    Veicolo *vettore_veicoli = (Veicolo*)ottieni_vettore(tabella_veicoli, &numero_veicoli);

    if (vettore_veicoli == NULL || numero_veicoli == 0) return;

    salva_vettore_veicoli(file_veicoli, file_prenotazioni, vettore_veicoli, numero_veicoli);

    free(vettore_veicoli);
}
