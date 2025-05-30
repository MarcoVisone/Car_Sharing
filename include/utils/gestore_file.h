#ifndef GESTORE_FILE_H
#define GESTORE_FILE_H

typedef struct veicolo *Veicolo;
typedef struct utente *Utente;

/*
 * Autore: Russo Nello Manuel
 * Data: 18/05/2025
 *
 * Funzione: salva_vettore_veicoli
 * -------------------------------
 *
 * salva su un file binario un vettore di veicoli e su un altro le relative prenotazioni
 *
 * Parametri:
 *    nome_file_veicolo: file in cui salvare i dati dei veicoli
 *    nome_file_prenotazioni: file in cui salvare le prenotazioni
 *    vettore: array di veicoli da salvare
 *    num_veicoli: numero di elementi nel vettore
 *
 * Pre-condizioni:
 *    nome_file_veicolo: deve essere diverso da NULL
 *    nome_file_prenotazioni: deve essere diverso da NULL
 *    vettore: deve essere diverso da NULL
 *    num_veicoli: deve essere maggiore di 0
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    i dati dei veicoli e delle relative prenotazioni vengono scritti
 *    nei file specificati in formato binario
 */
void salva_vettore_veicoli(const char *nome_file_veicolo, const char *nome_file_prenotazioni, Veicolo vettore[], unsigned int num_veicoli);

/*
 * Autore: Russo Nello Manuel
 * Data: 18/05/2025
 *
 * Funzione: carica_vettore_veicoli
 * --------------------------------
 *
 * carica un insieme di veicoli da un file binario e le relative prenotazioni da un secondo file binario
 *
 * Parametri:
 *    nome_file_veicolo: nome del file contenente i dati dei veicoli
 *    nome_file_prenotazioni: nome del file contenente le prenotazioni associate
 *    num_veicoli: puntatore a variabile dove verrà salvato il numero di veicoli caricati
 *
 * Pre-condizioni:
 *    nome_file_veicolo: deve essere diverso da NULL
 *    nome_file_prenotazioni: deve essere diverso da NULL
 *    num_veicoli: non deve essere NULL
 *
 * Post-condizioni:
 *    - Restituisce un array di Veicolo e ne imposta la dimensione in num_veicoli, restituisce NULL in caso di errore
 *
 * Side-effect:
 *    - Alloca memoria dinamicamente per il vettore restituito (va liberata dal chiamante)
 */
Veicolo *carica_vettore_veicoli(const char *nome_file_veicolo, const char *nome_file_prenotazioni, unsigned int *num_veicoli);

/*
 * Funzione: salva_vettore_utenti
 * ------------------------------
 *
 * Salva un array di utenti su due file: uno per l'anagrafica, uno per i dati.
 *
 * Parametri:
 * nome_file_utente: nome del file per l'anagrafica
 * nome_file_data: nome del file per i dati storici
 * vettore: array di puntatori a Utente
 * num_utenti: numero di utenti nell'array
 *
 * Pre-condizione:
 * vettore e nomi file devono essere validi
 *
 * Post-condizione:
 * i dati degli utenti sono scritti nei file
 *
 * Ritorna:
 * nessun valore
 *
 * Side-effect:
 * apertura e scrittura su file
 */
void salva_vettore_utenti(const char *nome_file_utente, const char *nome_file_data, Utente vettore[], unsigned int num_utenti);

/*
 * Funzione: carica_vettore_utenti
 * -------------------------------
 *
 * Carica da due file un array di utenti.
 *
 * Parametri:
 * nome_file_utente: nome del file contenente i dati anagrafici
 * nome_file_data: nome del file contenente i dati storici
 * num_utenti: puntatore a intero dove memorizzare il numero di utenti caricati
 *
 * Pre-condizione:
 * nomi file devono essere validi; num_utenti deve essere allocato
 *
 * Post-condizione:
 * il vettore contiene gli utenti caricati dai file
 *
 * Ritorna:
 * un array di Utente, o NULL in caso di errore
 *
 * Side-effect:
 * lettura da file, allocazione dinamica di memoria
 */
Utente *carica_vettore_utenti(const char *nome_file_utente, const char *nome_file_data, unsigned int *num_utenti);

#endif //GESTORE_FILE_H
