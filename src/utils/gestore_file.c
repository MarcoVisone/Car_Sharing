#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils/gestore_file.h"
#include "modelli/intervallo.h"
#include "modelli/prenotazione.h"
#include "strutture_dati/prenotazioni.h"
#include "modelli/veicolo.h"
#include "modelli/data.h"
#include "modelli/utente.h"

static void salva_prenotazione(FILE *fp, Prenotazione prenotazione);
static Prenotazione carica_prenotazione(FILE *fp);
static void salva_prenotazioni(FILE *fp, Prenotazioni prenotazioni);
static Prenotazioni carica_prenotazioni(FILE *fp);

/*
    Scrivere nel file la grandezza del vettore (funzione fwrite)
    poi iterare il vettore e fare fwrite di ogni campo del veicolo e per prenotazioni usare
    la funzione salva_prenotazioni passando il file_prenotazioni
*/
static void salva_veicolo(FILE *file_veicolo, FILE *file_prenotazioni, Veicolo v);

/*
    Prendere dal file la grandezza del veicolo con fread,
    leggere ogni campo del veicolo e alla fine creare un veicolo con
    quei campi (usare carica_prenotazioni quando si devono prendere le prenotazioni)
    e restituirlo
*/
static Veicolo carica_veicolo(FILE *file_veicolo, FILE *file_prenotazioni);

static void salva_data(FILE *file_data, Data d);

static Data carica_data(FILE *file_data);

static void salva_utente(FILE *file_utente, FILE *file_data, Utente u);

static Utente carica_utente(FILE *file_utente, FILE *file_data);

static void salva_prenotazione(FILE *fp, Prenotazione prenotazione){
    if(fp == NULL || prenotazione == NULL) return;

    char *cliente = ottieni_cliente_prenotazione(prenotazione);
    unsigned int len = (unsigned int)strlen(cliente) + 1;
    fwrite(&len, sizeof(len), 1, fp);
    fwrite(cliente, sizeof(char), len, fp);

    double costo = ottieni_costo_prenotazione(prenotazione);
    fwrite(&costo, sizeof(costo), 1, fp);

    Intervallo iv = ottieni_intervallo_prenotazione(prenotazione);
    time_t inizio = inizio_intervallo(iv);
    time_t fine   = fine_intervallo(iv);
    fwrite(&inizio, sizeof(inizio), 1, fp);
    fwrite(&fine, sizeof(fine), 1, fp);
}

static Prenotazione carica_prenotazione(FILE *fp){
    if(fp == NULL) return NULL;

    unsigned int len;
    fread(&len, sizeof(len), 1, fp);
    char *cliente = malloc(sizeof(char) * len);
    fread(cliente, sizeof(char), len, fp);

    double costo;
    fread(&costo, sizeof(costo), 1, fp);

    time_t inizio;
    time_t fine;
    fread(&inizio, sizeof(inizio), 1, fp);
    fread(&fine, sizeof(fine), 1, fp);
    Intervallo i = crea_intervallo(inizio, fine);

    Prenotazione p = crea_prenotazione(cliente, i, costo);

    free(cliente);

    return p;
}

static void salva_prenotazioni(FILE *fp, Prenotazioni prenotazioni) {
    if (fp == NULL || prenotazioni == NULL) return;
    unsigned int size = 0, i;
    Prenotazione *p = ottieni_vettore_prenotazioni_per_file(prenotazioni, &size);
    if (p == NULL) return;

    fwrite(&size, sizeof(size), 1, fp);

    for (i = 0; i < size; i++) {
        salva_prenotazione(fp, p[i]);
    }
}

static Prenotazioni carica_prenotazioni(FILE *fp) {
    if (fp == NULL) return NULL;
    unsigned int size = 0, i;
    if (fread(&size, sizeof size, 1, fp) != 1) return NULL;

    Prenotazioni pren = crea_prenotazioni();

    for (i = 0; i < size; i++) {
        if(!aggiungi_prenotazione(pren, carica_prenotazione(fp)))
            continue;
    }
    return pren;
}

/*
    Iterare il vettore e usare per ogni cella la funzione salva_veicolo
*/
void salva_vettore_veicoli(const char *nome_file, Veicolo vettore[], int num_veicoli){
    return;
}

int carica_vettore_veicoli(const char *nome_file, Veicolo vettore[], int max_veicoli){
    return 0;
}

/*
 * Funzione: salva_data
 * --------------------
 *
 * Salva su file le informazioni della struttura Data.
 *
 * Implementazione:
 * Scrive su file il numero di prenotazioni, la frequenza e l'intero storico
 * delle prenotazioni contenuto nella struttura Data.
 *
 * Parametri:
 *    file_data: puntatore al file su cui salvare i dati
 *    d: struttura Data da salvare
 *
 * Pre-condizione:
 *    file_data e d devono essere validi
 *
 * Post-condizione:
 *    i dati della struttura sono scritti nel file
 *
 * Ritorna:
 *    nessun valore
 *
 * Side-effect:
 *    scrittura su file
 */
static void salva_data(FILE *file_data, Data d){
    if(file_data == NULL || d == NULL){
      return;
    }
    unsigned int dimensione;
    Prenotazione *lista_prenotazioni;
    lista_prenotazioni = ottieni_vettore_storico(d, &dimensione);
    int numero_prenotazioni = ottieni_numero_prenotazioni(d);
    int frequenza = ottieni_frequenza_lista(d);
    fwrite(&frequenza, sizeof(int), 1, file_data);
    fwrite(&numero_prenotazioni, sizeof(int), 1, file_data);
    for(int i = 0; i < numero_prenotazioni; i++){
        salva_prenotazione(file_data, lista_prenotazioni[i]);
    }
}

/*
 * Funzione: carica_data
 * ---------------------
 *
 * Carica da file le informazioni per ricostruire una struttura Data.
 *
 * Implementazione:
 * Legge da file il numero di prenotazioni, la frequenza e ricostruisce
 * lo storico delle prenotazioni. Restituisce una nuova struttura Data.
 *
 * Parametri:
 *    file_data: puntatore al file da cui leggere i dati
 *
 * Pre-condizione:
 *    file_data deve essere un file aperto in lettura e valido
 *
 * Post-condizione:
 *    viene restituita una nuova struttura Data con i dati caricati
 *
 * Ritorna:
 *    un nuovo oggetto Data, oppure NULL in caso di errore
 *
 * Side-effect:
 *    lettura da file, allocazione dinamica
 */
static Data carica_data(FILE *file_data){
    if(file_data == NULL){
        return NULL;
    }
    int numero_prenotazioni;
    int frequenza;

    fread(&numero_prenotazioni, sizeof(int), 1, file_data);
    fread(&frequenza, sizeof(int), 1, file_data);

    Data d = crea_data();
    for(int i = 0; i < numero_prenotazioni; i++){
        imposta_storico_lista(d, aggiungi_a_storico_lista(d, carica_prenotazione(file_data)));
    }
    return d;
}

/*
 * Funzione: salva_utente
 * ----------------------
 *
 * Salva le informazioni di un utente su due file distinti: uno per l'anagrafica,
 * uno per i dati associati.
 *
 * Implementazione:
 * Scrive nome, cognome, email, password, permesso e chiama salva_data
 * per salvare la struttura Data.
 *
 * Parametri:
 *    file_utente: file su cui scrivere i dati dell'utente
 *    file_data: file su cui scrivere i dati storici dell'utente
 *    u: utente da salvare
 *
 * Pre-condizione:
 *    file_utente e u devono essere validi
 *
 * Post-condizione:
 *    i dati dell'utente sono salvati nei file
 *
 * Ritorna:
 *    nessun valore
 *
 * Side-effect:
 *    scrittura su file
 */
static void salva_utente(FILE *file_utente, FILE *file_data, Utente u){
    if (file_utente == NULL || u == NULL) return;

    unsigned int len = strlen(ottieni_nome(u))+1;
    fwrite(&len, sizeof(unsigned int), 1, file_utente);
    fwrite(ottieni_nome(u), sizeof(char), len, file_utente);

    len = strlen(ottieni_cognome(u))+1;
    fwrite(&len, sizeof(unsigned int), 1, file_utente);
    fwrite(ottieni_cognome(u), sizeof(char), len, file_utente);

    len = strlen(ottieni_email(u)+1);
    fwrite(&len, sizeof(unsigned int), 1, file_utente);
    fwrite(ottieni_email(u), sizeof(char), len, file_utente);

    fwrite(ottieni_password(u), sizeof(uint8_t), DIMENSIONE_PASSWORD, file_utente);

    Byte permesso = ottieni_permesso(u);
    fwrite(&permesso, sizeof(Byte), 1, file_utente);

    salva_data(file_data, ottieni_data(u));
}

/*
 * Funzione: carica_utente
 * -----------------------
 *
 * Carica da due file le informazioni necessarie per ricostruire un utente.
 *
 * Implementazione:
 * Legge nome, cognome, email, password, permesso e, se CLIENTE, carica
 * anche la struttura Data associata.
 *
 * Parametri:
 *    file_utente: file da cui leggere i dati dell'utente
 *    file_data: file da cui leggere i dati storici
 *
 * Pre-condizione:
 *    file_utente deve essere valido
 *
 * Post-condizione:
 *    restituisce un utente ricostruito dai file
 *
 * Ritorna:
 *    un nuovo oggetto Utente, o NULL in caso di errore
 *
 * Side-effect:
 *    lettura da file, allocazione dinamica di memoria
 */
static Utente carica_utente(FILE *file_utente, FILE *file_data){
    if (file_utente == NULL) return NULL;

    unsigned int len = 0;
    fread(&len, sizeof(unsigned int), 1, file_utente);
    char *nome = malloc(len*sizeof(char));
    fread(nome, sizeof(char), len, file_utente);

    fread(&len, sizeof(unsigned int), 1, file_utente);
    char *cognome = malloc(len*sizeof(char));
    fread(cognome, sizeof(char), len, file_utente);

    fread(&len, sizeof(unsigned int), 1, file_utente);
    char *email = malloc(len*sizeof(char));
    fread(email, sizeof(char), len, file_utente);

    uint8_t *password = malloc(sizeof(uint8_t)*DIMENSIONE_PASSWORD);
    fread(password, sizeof(uint8_t), DIMENSIONE_PASSWORD, file_utente);

    Byte permesso;
    fread(&permesso, sizeof(Byte), 1, file_utente);

    Data data = NULL;
    if(permesso == CLIENTE){
      data = carica_data(file_data);
    }

    Utente u;
    u=crea_utente(email, password,  nome, cognome, permesso);
    imposta_data(u, data);
    free(nome);
    free(cognome);
    free(email);
    free(password);
    return u;
}

/*
 * Funzione: salva_vettore_utenti
 * ------------------------------
 *
 * Salva un array di utenti su due file: uno per l'anagrafica, uno per i dati.
 *
 * Implementazione:
 * Apre due file, scrive il numero di utenti e salva ciascun utente.
 *
 * Parametri:
 *    nome_file_utente: nome del file per l'anagrafica
 *    nome_file_data: nome del file per i dati storici
 *    vettore: array di puntatori a Utente
 *    num_utenti: numero di utenti nell'array
 *
 * Pre-condizione:
 *    vettore e nomi file devono essere validi
 *
 * Post-condizione:
 *    i dati degli utenti sono scritti nei file
 *
 * Ritorna:
 *    nessun valore
 *
 * Side-effect:
 *    apertura e scrittura su file
 */
void salva_vettore_utenti(const char *nome_file_utente, const char *nome_file_data, Utente vettore[], int num_utenti){
    FILE *file_utente = fopen(nome_file_utente, "w");
    if (file_utente == NULL) return;
    FILE *file_data = fopen(nome_file_data, "w");
    if (file_data == NULL) return;

    fwrite(&num_utenti, sizeof(unsigned int), 1, file_utente);

    for (int i = 0; i < num_utenti; i++){
      salva_utente(file_utente, file_data, vettore[i]);
    }

    fclose(file_utente);
    fclose(file_data);
}

/*
 * Funzione: carica_vettore_utenti
 * -------------------------------
 *
 * Carica da due file un array di utenti.
 *
 * Implementazione:
 * Apre i file, legge il numero di utenti e chiama carica_utente per ognuno.
 *
 * Parametri:
 *    nome_file_utente: nome del file contenente i dati anagrafici
 *    nome_file_data: nome del file contenente i dati storici
 *    vettore: array di puntatori a Utente da riempire
 *    num_utenti: puntatore a intero dove memorizzare il numero di utenti caricati
 *
 * Pre-condizione:
 *    nomi file devono essere validi; vettore e num_utenti devono essere allocati
 *
 * Post-condizione:
 *    il vettore contiene gli utenti caricati dai file
 *
 * Ritorna:
 *    1 se il caricamento ha successo, 0 altrimenti
 *
 * Side-effect:
 *    lettura da file, allocazione dinamica di memoria
 */
int carica_vettore_utenti(const char *nome_file_utente, const char *nome_file_data, Utente vettore[], int *num_utenti){
    FILE *file_utente = fopen(nome_file_utente, "r");
    if (file_utente == NULL) return 0;
    FILE *file_data = fopen(nome_file_data, "r");
    if (file_data == NULL) return 0;

    fread(num_utenti, sizeof(unsigned int), 1, file_utente);

    for (int i = 0; i < *num_utenti; i++){
        vettore[i] = carica_utente(file_utente, file_data);
    }

    fclose(file_utente);
    fclose(file_data);

    return 1;
}
