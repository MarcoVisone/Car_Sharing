#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils/gestore_file.h"
#include "modelli/intervallo.h"
#include "modelli/prenotazione.h"
#include "strutture_dati/lista.h"
#include "strutture_dati/prenotazioni.h"
#include "modelli/veicolo.h"
#include "modelli/data.h"
#include "modelli/utente.h"

#define DIMENSIONE_BUFFER 1024

static char buffer[DIMENSIONE_BUFFER];
static uint8_t password[DIMENSIONE_PASSWORD];

static void salva_prenotazione(FILE *fp, Prenotazione prenotazione);

static Prenotazione carica_prenotazione(FILE *fp);

static void salva_prenotazioni(FILE *fp, Prenotazioni prenotazioni);

static Prenotazioni carica_prenotazioni(FILE *fp);

static void salva_veicolo(FILE *file_veicolo, FILE *file_prenotazioni, Veicolo v);

static Veicolo carica_veicolo(FILE *file_veicolo, FILE *file_prenotazioni);

static void salva_data(FILE *file_data, Data d);

static Data carica_data(FILE *file_data);

static void salva_utente(FILE *file_utente, FILE *file_data, Utente u);

static Utente carica_utente(FILE *file_utente, FILE *file_data);

/*
 * Autore: Marco Visone
 * Data: 15/05/2025
 */
static void salva_prenotazione(FILE *fp, Prenotazione prenotazione){
    if(fp == NULL || prenotazione == NULL) return;

    char *cliente = ottieni_cliente_prenotazione(prenotazione);
    if(cliente == NULL) return;

    unsigned int len = (unsigned int)strlen(cliente) + 1;
    fwrite(&len, sizeof(len), 1, fp);

    fwrite(cliente, sizeof(char), len, fp);

    double costo = ottieni_costo_prenotazione(prenotazione);
    fwrite(&costo, sizeof(costo), 1, fp);

    Intervallo iv = ottieni_intervallo_prenotazione(prenotazione);
    if(iv == NULL) return;

    time_t inizio = inizio_intervallo(iv);
    time_t fine = fine_intervallo(iv);
    fwrite(&inizio, sizeof(inizio), 1, fp);
    fwrite(&fine, sizeof(fine), 1, fp);
}

/*
 * Autore: Marco Visone
 * Data: 15/05/2025
 */
static Prenotazione carica_prenotazione(FILE *fp){
    if(fp == NULL) return NULL;

    unsigned int len;
    if(fread(&len, sizeof(len), 1, fp) != 1) return NULL;

    if (len >= DIMENSIONE_BUFFER) {
        return NULL;
    }
    if (fread(buffer, sizeof(char), len, fp) != len) {
        return NULL;
    }

    double costo;
    if(fread(&costo, sizeof(costo), 1, fp) != 1){
        return NULL;
    }

    time_t inizio, fine;
    if(fread(&inizio, sizeof(inizio), 1, fp) != 1 ||
       fread(&fine, sizeof(fine), 1, fp) != 1){
        return NULL;
    }

    Intervallo i = crea_intervallo(inizio, fine);
    if(i == NULL){
        return NULL;
    }

    Prenotazione p = crea_prenotazione(buffer, i, costo);
    return p;
}

/*
 * Autore: Marco Visone
 * Data: 15/05/2025
 */
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

/*
 * Autore: Marco Visone
 * Data: 15/05/2025
 */
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
 * Autore: Russo Nello Manuel
 * Data: 18/05/2025
 *
 * Funzione: salva_veicolo
 * -----------------------
 *
 * salva le informazioni di un singolo veicolo su un file binario, includendo anche le sue prenotazioni
 *
 * Implementazione:
 *    - Scrive nel file file_veicolo i seguenti campi, ciascuno preceduto dalla sua lunghezza:
 *        - tipo del veicolo, targa, modello, posizione, tariffa
 *    - Le prenotazioni associate vengono salvate nel file file_prenotazioni tramite la funzione salva_prenotazioni
 *
 * Parametri:
 *    file_veicolo: puntatore a FILE aperto in modalità scrittura binaria, destinato ai dati del veicolo
 *    file_prenotazioni: puntatore a FILE aperto in modalità scrittura binaria, destinato alle prenotazioni
 *    v: veicolo da salvare
 *
 * Pre-condizioni:
 *    file_veicolo: deve essere diverso da NULL
 *    file_prenotazioni: deve essere diverso da NULL
 *    v: deve essere diverso da NULL
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    - I dati del veicolo vengono scritti nel file file_veicolo
 *    - Le prenotazioni vengono scritte nel file file_prenotazioni
 */
static void salva_veicolo(FILE *file_veicolo, FILE *file_prenotazioni, Veicolo v){
	if (file_veicolo == NULL || v == NULL || file_prenotazioni == NULL) return;

	unsigned int len = strlen(ottieni_tipo_veicolo(v))+1;
    fwrite(&len, sizeof(unsigned int), 1, file_veicolo);
    fwrite(ottieni_tipo_veicolo(v), sizeof(char), len, file_veicolo);

    len = strlen(ottieni_targa(v))+1;
    fwrite(&len, sizeof(unsigned int), 1, file_veicolo);
    fwrite(ottieni_targa(v), sizeof(char), len, file_veicolo);

    len = strlen(ottieni_modello(v))+1;
    fwrite(&len, sizeof(unsigned int), 1, file_veicolo);
    fwrite(ottieni_modello(v), sizeof(char), len, file_veicolo);

    len = strlen(ottieni_posizione(v)) + 1;
    fwrite(&len, sizeof(unsigned int), 1, file_veicolo);
    fwrite(ottieni_posizione(v), sizeof(char), len, file_veicolo);

	double tariffa = ottieni_tariffa(v);
	fwrite(&tariffa, sizeof(tariffa), 1, file_veicolo);

	salva_prenotazioni(file_prenotazioni, ottieni_prenotazioni(v));
}

/*
 * Autore: Russo Nello Manuel
 * Data: 18/05/2025
 *
 * Funzione: carica_veicolo
 * ------------------------
 *
 * carica un veicolo da un file binario e le relative prenotazioni da un secondo file binario
 *
 * Implementazione:
 *    - Legge dal file file_veicolo i campi stringa tipo, targa, modello, posizione
 *      preceduti dalla loro lunghezza, e un double tariffa
 *    - Carica le prenotazioni associate dal file file_prenotazioni usando la funzione carica_prenotazioni
 *    - Crea il veicolo con i dati letti e lo restituisce.
 *
 * Parametri:
 *    file_veicolo: file binario da cui leggere i dati del veicolo
 *    file_prenotazioni: file binario da cui leggere le prenotazioni associate al veicolo
 *
 * Pre-condizioni:
 *    file_veicolo: deve essere diverso da NULL
 *    file_prenotazioni: deve essere diverso da NULL e
 *    deve avere il formato previsto (lunghezza stringa seguita dalla stringa)
 *
 * Post-condizioni:
 *    restituisce NULL se uno dei file è NULL, altrimenti restituisce un nuovo oggetto Veicolo
 *
 * Side-effect:
 *    Alloca memoria dinamicamente per le stringhe temporanee (poi liberate), e per un nuovo oggetto Veicolo
 */
static Veicolo carica_veicolo(FILE *file_veicolo, FILE *file_prenotazioni){
	if (file_veicolo == NULL || file_prenotazioni == NULL) return NULL;

	unsigned int len;
    fread(&len, sizeof(unsigned int), 1, file_veicolo);
	char *tipo_veicolo = malloc(sizeof(char) * len);
    fread(tipo_veicolo, sizeof(char), len, file_veicolo);

    fread(&len, sizeof(unsigned int), 1, file_veicolo);
	char *targa_veicolo = malloc(sizeof(char) * len);
    fread(targa_veicolo, sizeof(char), len, file_veicolo);

    fread(&len, sizeof(unsigned int), 1, file_veicolo);
	char *modello_veicolo = malloc(sizeof(char) * len);
    fread(modello_veicolo, sizeof(char), len, file_veicolo);

    fread(&len, sizeof(unsigned int), 1, file_veicolo);
	char *posizione_veicolo = malloc(sizeof(char) * len);
    fread(posizione_veicolo, sizeof(char), len, file_veicolo);

	double tariffa;
	fread(&tariffa, sizeof(tariffa), 1, file_veicolo);

	Prenotazioni p = carica_prenotazioni(file_prenotazioni);

	Veicolo v = crea_veicolo(tipo_veicolo, targa_veicolo, modello_veicolo, posizione_veicolo, tariffa, p);

	free(tipo_veicolo);
	free(targa_veicolo);
	free(modello_veicolo);
	free(posizione_veicolo);

	return v;
}

/*
 * Autore: Russo Nello Manuel
 * Data: 18/05/2025
 *
 * Funzione: salva_vettore_veicoli
 * -------------------------------
 *
 * salva su un file binario un vettore di veicoli e su un altro le relative prenotazioni
 *
 * Implementazione:
 *    - Apre due file binari in modalità scrittura:
 *        - uno per i dati dei veicoli, nome_file_veicolo
 *        - uno per le prenotazioni associate, nome_file_prenotazioni
 *    - Scrive nel file dei veicoli il numero totale di veicoli da salvare
 *    - Per ogni veicolo nel vettore, chiama la funzione salva_veicolo
 *      che scrive i dati nei rispettivi file
 *    - Chiude entrambi i file al termine
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
 *    num_veicoli: deve essere diverso di 0
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    i dati dei veicoli e delle relative prenotazioni vengono scritti
 *    nei file specificati in formato binario
 */
void salva_vettore_veicoli(const char *nome_file_veicolo, const char *nome_file_prenotazioni, Veicolo vettore[], unsigned int num_veicoli){
	if(nome_file_veicolo == NULL || nome_file_prenotazioni == NULL || vettore == NULL || !num_veicoli) return;

	FILE *file_veicolo = fopen(nome_file_veicolo, "wb");
    if (file_veicolo == NULL) return;

    FILE *file_prenotazioni = fopen(nome_file_prenotazioni, "wb");
    if (file_prenotazioni == NULL) return;

    fwrite(&num_veicoli, sizeof(unsigned int), 1, file_veicolo);

    for (unsigned i = 0; i < num_veicoli; i++){
      salva_veicolo(file_veicolo, file_prenotazioni, vettore[i]);
    }

    fclose(file_veicolo);
    fclose(file_prenotazioni);
}

/*
 * Autore: Russo Nello Manuel
 * Data: 18/05/2025
 *
 * Funzione: carica_vettore_veicoli
 * --------------------------------
 *
 * carica un insieme di veicoli da un file binario e le relative prenotazioni da un secondo file binario
 *
 * Implementazione:
 *    - Apre due file binari in lettura: uno per i veicoli e uno per le prenotazioni
 *    - Legge il numero totale di veicoli da caricare dal file dei veicoli
 *    - Alloca dinamicamente un array di puntatori a Veicolo
 *    - Per ogni veicolo, richiama la funzione carica_veicolo per leggere i dati e le prenotazioni
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
Veicolo *carica_vettore_veicoli(const char *nome_file_veicolo, const char *nome_file_prenotazioni, unsigned int *num_veicoli){
	if(nome_file_veicolo == NULL || nome_file_prenotazioni == NULL || num_veicoli == NULL) return NULL;

	FILE *file_veicolo = fopen(nome_file_veicolo, "rb");
    if (file_veicolo == NULL) return NULL;

    FILE *file_prenotazioni = fopen(nome_file_prenotazioni, "rb");
    if (file_prenotazioni == NULL) return NULL;
    fread(num_veicoli, sizeof(unsigned int), 1, file_veicolo);

    Veicolo *vettore = malloc(sizeof(Veicolo) * (*num_veicoli));

    for (unsigned i = 0; i < *num_veicoli; i++){
        vettore[i] = carica_veicolo(file_veicolo, file_prenotazioni);
    }

    fclose(file_veicolo);
    fclose(file_prenotazioni);

    return vettore;
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

    ListaPre lista_prenotazioni = ottieni_storico_lista(d);
    if(lista_prenotazioni == NULL) return;

    int frequenza = ottieni_frequenza_lista(d);
    fwrite(&frequenza, sizeof(int), 1, file_data);

    int numero_prenotazioni = ottieni_numero_prenotazioni(d);
    fwrite(&numero_prenotazioni, sizeof(int), 1, file_data);

    for(int i = 0; i < numero_prenotazioni; i++){
        salva_prenotazione(file_data, (Prenotazione)ottieni_item(lista_prenotazioni));
        lista_prenotazioni = ottieni_prossimo(lista_prenotazioni);
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

    fread(&frequenza, sizeof(int), 1, file_data);
    fread(&numero_prenotazioni, sizeof(int), 1, file_data);
    Data d = crea_data();
    imposta_frequenza(d, frequenza);
    for(int i = 0; i < numero_prenotazioni; i++){
        imposta_storico_lista(d, aggiungi_a_storico_lista(d, carica_prenotazione(file_data)));
    }
    imposta_numero_prenotazioni(d, numero_prenotazioni);
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

    len = strlen(ottieni_email(u)) + 1;
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
static Utente carica_utente(FILE *file_utente, FILE *file_data) {
    if (file_utente == NULL)
        return NULL;
    Utente u = crea_utente(NULL, NULL, NULL, NULL, 0);
    if (u == NULL)
        return NULL;

    unsigned int len;
    Byte permesso;
    Data data = NULL;
    size_t n;

    if (fread(&len, sizeof(len), 1, file_utente) != 1 || len == 0 || len > DIMENSIONE_NOME) {
        distruggi_utente(u);
        return NULL;
    }
    n = fread(buffer, sizeof(char), len, file_utente);
    if (n != len) {
        distruggi_utente(u);
        return NULL;
    }
    imposta_nome(u, buffer);

    if (fread(&len, sizeof(len), 1, file_utente) != 1 || len == 0 || len > DIMENSIONE_COGNOME) {
         distruggi_utente(u);
         return NULL;
    }
    n = fread(buffer, sizeof(char), len, file_utente);
    if (n != len) {
        distruggi_utente(u);
        return NULL;
    }
    imposta_cognome(u, buffer);

    if (fread(&len, sizeof(len), 1, file_utente) != 1 || len == 0 || len > DIMENSIONE_EMAIL) {
        distruggi_utente(u);
        return NULL;
    }
    n = fread(buffer, sizeof(char), len, file_utente);
    if (n != len) {
        distruggi_utente(u);
        return NULL;
    }
    imposta_email(u, buffer);

    if (fread(password, sizeof(uint8_t), DIMENSIONE_PASSWORD, file_utente) != DIMENSIONE_PASSWORD) {
        distruggi_utente(u);
        return NULL;
    }
    imposta_password(u, password);

    if (fread(&permesso, sizeof(permesso), 1, file_utente) != 1) {
        distruggi_utente(u);
        return NULL;
    }
    imposta_permesso(u, permesso);

    if (permesso == CLIENTE) {
        data = carica_data(file_data);
        if (data == NULL) {
            distruggi_utente(u);
            return NULL;
        }
    }
    imposta_data(u, data);

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
void salva_vettore_utenti(const char *nome_file_utente, const char *nome_file_data, Utente vettore[], unsigned int num_utenti){
    FILE *file_utente = fopen(nome_file_utente, "wb");
    if (file_utente == NULL) return;

    FILE *file_data = fopen(nome_file_data, "wb");
    if (file_data == NULL) return;

    fwrite(&num_utenti, sizeof(unsigned int), 1, file_utente);

    for (unsigned int i = 0; i < num_utenti; i++){
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
Utente *carica_vettore_utenti(const char *nome_file_utente, const char *nome_file_data, unsigned int *num_utenti){
    FILE *file_utente = fopen(nome_file_utente, "rb");
    if (file_utente == NULL) return NULL;

    FILE *file_data = fopen(nome_file_data, "rb");
    if (file_data == NULL) return NULL;

    fread(num_utenti, sizeof(unsigned int), 1, file_utente);
    Utente *vettore = malloc(sizeof(Utente) * (*num_utenti));

    if(vettore == NULL) return NULL;

    for (unsigned int i = 0; i < *num_utenti; i++){
        vettore[i] = carica_utente(file_utente, file_data);
    }

    fclose(file_utente);
    fclose(file_data);

    return vettore;
}
