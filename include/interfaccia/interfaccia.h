//
// Created by sicig on 21/05/2025.
//

#ifndef INTERFACCIA_H
#define INTERFACCIA_H

#include <time.h>
#include "modelli/byte.h"

typedef struct prenotazione *Prenotazione;
typedef struct veicolo *Veicolo;
typedef struct tabella_hash *TabellaUtenti;
typedef struct tabella_hash *TabellaVeicoli;
typedef struct intervallo *Intervallo;
typedef struct utente* Utente;

/*
 * Funzione: stampa_errore
 * -----------------------
 *
 * Stampa un messaggio di errore formattato con prefisso identificativo.
 *
 * Parametri:
 *    msg: stringa contenente il messaggio di errore da visualizzare
 *
 * Pre-condizione:
 *    msg deve essere un puntatore a stringa valido (non NULL)
 *
 * Post-condizione:
 *    Il messaggio viene stampato su stdout con formattazione di errore
 *
 * Side-effect:
 *    Output su console
 */
void stampa_errore(const char *msg);

/*
 * Funzione: stampa_successo
 * -------------------------
 *
 * Stampa un messaggio di successo formattato con prefisso identificativo.
 *
 * Parametri:
 *    msg: stringa contenente il messaggio di successo da visualizzare
 *
 * Pre-condizione:
 *    msg deve essere un puntatore a stringa valido (non NULL)
 *
 * Post-condizione:
 *    Il messaggio viene stampato su stdout con formattazione di successo
 *
 * Side-effect:
 *    Output su console
 */
void stampa_successo(const char *msg);

/*
 * Funzione: stampa_info
 * ---------------------
 *
 * Stampa un messaggio informativo formattato con prefisso identificativo.
 *
 * Parametri:
 *    msg: stringa contenente il messaggio informativo da visualizzare
 *
 * Pre-condizione:
 *    msg deve essere un puntatore a stringa valido (non NULL)
 *
 * Post-condizione:
 *    Il messaggio viene stampato su stdout con formattazione informativa
 *
 * Side-effect:
 *    Output su console
 */
void stampa_info(const char *msg);

/*
 * Funzione: uscita
 * ----------------
 *
 * Verifica se una stringa rappresenta un comando di uscita.
 *
 * Parametri:
 *    str: stringa da verificare
 *
 * Pre-condizione:
 *    str deve essere un puntatore a stringa valido (non NULL)
 *
 * Post-condizione:
 *    Restituisce 1 se la stringa è "E" o "e", 0 altrimenti
 *
 * Side-effect:
 *    Nessuno
 */
Byte uscita(char *str);

/*
 * Funzione: inserisci_stringa
 * ---------------------------
 *
 * Legge una stringa da input standard gestendo l'overflow del buffer.
 *
 * Parametri:
 *    stringa: buffer in cui memorizzare la stringa letta
 *    lunghezza: dimensione massima del buffer
 *
 * Pre-condizione:
 *    stringa deve essere un puntatore a buffer valido
 *    lunghezza deve essere maggiore di 0
 *
 * Post-condizione:
 *    La stringa letta è memorizzata nel buffer senza carattere newline
 *    Il buffer stdin è pulito in caso di overflow
 *
 * Side-effect:
 *    Lettura da stdin, possibile pulizia del buffer di input
 */
void inserisci_stringa(char *stringa, unsigned int lunghezza);

/*
 * Funzione: benvenuto
 * -------------------
 *
 * Mostra il menu principale dell'applicazione e acquisisce la scelta dell'utente.
 *
 * Parametri:
 *    nessuno
 *
 * Pre-condizione:
 *    nessuna
 *
 * Post-condizione:
 *    Restituisce il carattere corrispondente alla scelta dell'utente
 *
 * Side-effect:
 *    Pulizia console, stampa del menu, lettura da stdin, pulizia buffer
 */
Byte benvenuto();

/*
 * Funzione: ottieni_parola
 * -------------------------
 *
 * Legge una stringa da input standard, rimuovendo newline e spazi finali.
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
void ottieni_parola(char *stringa, int dimensione);

/*
 * Funzione: stampa_header
 * -----------------------
 *
 * Stampa un'intestazione formattata per sezioni dell'interfaccia utente.
 *
 * Parametri:
 *    titolo: stringa contenente il titolo da visualizzare
 *
 * Pre-condizione:
 *    titolo deve essere un puntatore a stringa valido (non NULL)
 *
 * Post-condizione:
 *    Il titolo viene stampato con formattazione di intestazione
 *
 * Side-effect:
 *    Output su console
 */
void stampa_header(const char *titolo);

/*
 * Funzione: interfaccia_accesso
 * -----------------------------
 *
 * Gestisce l'interfaccia di accesso dell'utente, richiedendo l'inserimento
 * di email e password e verificandone la correttezza.
 *
 * Parametri:
 *    tabella_utenti: struttura contenente la lista di utenti registrati
 *
 * Pre-condizione:
 *    tabella_utenti deve essere inizializzata e non nullo
 *
 * Post-condizione:
 *    Se le credenziali sono corrette, restituisce il puntatore all'utente
 *    Se l'utente sceglie di uscire o supera i tentativi, restituisce NULL
 *
 * Side-effect:
 *    Lettura da stdin, possibili deallocazioni di memoria
 */
Utente interfaccia_accesso(TabellaUtenti tabella_utenti);

/*
 * Funzione: interfaccia_registrazione
 * -----------------------------------
 *
 * Gestisce l'interfaccia di registrazione di un nuovo utente.
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
 *    Ritorna 1 in caso di successo, 0 se l'utente esce, -1 in caso di fallimento
 *
 * Side-effect:
 *    Aggiunta di un nuovo utente alla tabella utenti
 */
Byte interfaccia_registrazione(TabellaUtenti tabella_utenti, Byte permesso);

/*
 * Funzione: menu_registrazione
 * ----------------------------
 *
 * Gestisce il menu di registrazione completo con feedback utente.
 *
 * Parametri:
 *    tabella_utenti: tabella contenente gli utenti registrati
 *
 * Pre-condizione:
 *    tabella_utenti deve essere inizializzata e non NULL
 *
 * Post-condizione:
 *    L'utente è stato registrato (se operazione riuscita) e informato del risultato
 *
 * Side-effect:
 *    Output su console, attesa input utente, possibile modifica tabella utenti
 */
void menu_registrazione(TabellaUtenti tabella_utenti);

/*
 * Funzione: menu_accesso
 * ----------------------
 *
 * Gestisce il menu di accesso completo con feedback utente.
 *
 * Parametri:
 *    tabella_utenti: tabella contenente gli utenti registrati
 *
 * Pre-condizione:
 *    tabella_utenti deve essere inizializzata e non NULL
 *
 * Post-condizione:
 *    Restituisce il puntatore all'utente se l'accesso è riuscito, NULL altrimenti
 *
 * Side-effect:
 *    Output su console, attesa input utente
 */
Utente menu_accesso(TabellaUtenti tabella_utenti);

/*
 * Autore: Russo Nello Manuel
 * Data: 22/05/2025
 *
 * Funzione: richiedi_intervallo_prenotazione
 * ------------------------------------------
 *
 * richiede all'utente di inserire un intervallo di tempo per una prenotazione
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
Intervallo richiedi_intervallo_prenotazione();

/*
 * Autore: Russo Nello Manuel
 * Data: 22/05/2025
 *
 * Funzione: interfaccia_seleziona_veicolo
 * ---------------------------------------
 *
 * permette all'utente di selezionare un veicolo mostrando quelli disponibili nell'intervallo specificato
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
Veicolo interfaccia_seleziona_veicolo(TabellaVeicoli tabella_veicoli, Intervallo i);

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
Byte prenota_veicolo(Veicolo v, Prenotazione p, double percentuale, const char *motivo);

/*
 * Autore: Marco Visone
 * Data: 24/05/2025
 *
 * Funzione: visualizza_veicoli_disponibili
 * -----------------------------------------
 *
 * Mostra in tempo reale una tabella formattata dei veicoli disponibili per il noleggio
 * con informazioni dettagliate su modello, targa, tipo, posizione, costo e disponibilità
 *
 * Parametri:
 *    tabella_veicoli: tabella contenente tutti i veicoli del sistema
 *    data_riferimento: timestamp di riferimento per il calcolo della disponibilità
 *
 * Pre-condizioni:
 *    tabella_veicoli: deve essere una tabella valida e inizializzata
 *    data_riferimento: deve essere un timestamp valido
 *
 * Post-condizione:
 *    visualizza l'interfaccia utente e termina quando l'utente sceglie di uscire
 *
 * Side-effect:
 *    stampa a video, pulizia schermo, acquisizione input utente,
 *    allocazione e deallocazione di memoria per le stringhe temporanee
 */
void visualizza_veicoli_disponibili(TabellaVeicoli tabella_veicoli, time_t data_riferimento);

/*
 * Autore: Antonio Sicignano
 * Data: 24/05/2025
 *
 * Funzione: visualizza_storico
 * -----------------------------
 *
 * Visualizza lo storico completo delle prenotazioni di un utente in formato tabellare
 * con dettagli su veicolo, modello, periodo di noleggio e costo totale
 *
 * Parametri:
 *    email_utente: stringa contenente l'email dell'utente di cui visualizzare lo storico
 *    tabella_utenti: tabella contenente tutti gli utenti registrati
 *    tabella_veicoli: tabella contenente tutti i veicoli del sistema
 *
 * Pre-condizioni:
 *    email_utente: deve essere diverso da NULL e contenere un'email valida
 *    tabella_utenti: deve essere una tabella valida e inizializzata
 *    tabella_veicoli: deve essere una tabella valida e inizializzata
 *
 * Post-condizione:
 *    restituisce 1 se l'operazione ha successo, -1 in caso di errore (utente non trovato o storico vuoto)
 *
 * Side-effect:
 *    stampa a video, acquisizione input utente per conferma uscita,
 *    allocazione e deallocazione di memoria per le stringhe temporanee
 */
Byte visualizza_storico(char *email_utente, TabellaUtenti tabella_utenti, TabellaVeicoli tabella_veicoli);

/*
 * Autore: Marco Visone
 * Data: 25/05/2025
 *
 * Funzione: gestisci_le_mie_prenotazioni
 * --------------------------------------
 * Gestisce l'interfaccia utente per visualizzare e cancellare le prenotazioni attive
 * di un utente, mostrandole in una tabella formattata.
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
Byte gestisci_le_mie_prenotazioni(char *email_utente, TabellaUtenti tabella_utenti, TabellaVeicoli tabella_veicoli);

#endif //INTERFACCIA_H
