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

// Dichiarazioni statiche delle funzioni interne (con buffer passato come parametro dove serve)
static void salva_prenotazione(FILE *fp, Prenotazione prenotazione);
static Prenotazione carica_prenotazione(FILE *fp, char *buffer_str);
static void salva_prenotazioni(FILE *fp, Prenotazioni prenotazioni);
static Prenotazioni carica_prenotazioni(FILE *fp, char *buffer_str);
static void salva_veicolo(FILE *file_veicolo, FILE *file_prenotazioni, Veicolo v);
static Veicolo carica_veicolo(FILE *file_veicolo, FILE *file_prenotazioni, char *buffer_str);
static void salva_data(FILE *file_data, Data d);
static Data carica_data(FILE *file_data, char *buffer_str);
static void salva_utente(FILE *file_utente, FILE *file_data, Utente u);
static Utente carica_utente(FILE *file_utente, FILE *file_data, char *buffer_str);

static uint8_t password_buffer[DIMENSIONE_PASSWORD];


/*
 * Autore: Marco Visone
 * Data: 15/05/2025
 *
 * Funzione: salva_prenotazione
 * ----------------------------
 * Salva una singola prenotazione su un file binario.
 *
 * Implementazione:
 * Scrive nel file la lunghezza e il contenuto delle stringhe 'cliente' e 'targa',
 * il costo della prenotazione e gli orari di inizio e fine dell'intervallo.
 *
 * Parametri:
 * fp: puntatore al file su cui salvare la prenotazione
 * prenotazione: la prenotazione da salvare
 *
 * Pre-condizioni:
 * fp e prenotazione non devono essere NULL.
 *
 * Post-condizioni:
 * La prenotazione viene scritta nel file.
 */
static void salva_prenotazione(FILE *fp, Prenotazione prenotazione){
    if(fp == NULL || prenotazione == NULL) return;

    const char *cliente = ottieni_cliente_prenotazione(prenotazione);
    if(cliente == NULL) return;
    unsigned int len = (unsigned int)strlen(cliente) + 1;
    fwrite(&len, sizeof(len), 1, fp);
    fwrite(cliente, sizeof(char), len, fp);

    const char *targa = ottieni_veicolo_prenotazione(prenotazione);
    if(targa == NULL) return;
    len = strlen(targa) + 1;
    fwrite(&len, sizeof(len), 1, fp);
    fwrite(targa, sizeof(char), len, fp);

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
 *
 * Funzione: carica_prenotazione
 * -----------------------------
 * Carica una singola prenotazione da un file binario.
 *
 * Implementazione:
 * Legge dal file la lunghezza e il contenuto delle stringhe 'cliente' e 'targa',
 * il costo della prenotazione e gli orari di inizio e fine dell'intervallo,
 * ricostruendo l'oggetto Prenotazione.
 *
 * Parametri:
 * fp: puntatore al file da cui caricare la prenotazione
 * buffer_str: buffer temporaneo per le stringhe
 *
 * Pre-condizioni:
 * fp e buffer_str non devono essere NULL.
 *
 * Post-condizioni:
 * Restituisce un oggetto Prenotazione caricato dal file, o NULL in caso di errore.
 */
static Prenotazione carica_prenotazione(FILE *fp, char *buffer_str){
    if(fp == NULL || buffer_str == NULL) return NULL;

    Prenotazione p = crea_prenotazione(NULL, NULL, NULL, 0);
    if (p == NULL) return NULL; // Controllo allocazione

    unsigned int len;
    size_t n_read;
    Intervallo i = NULL; // Inizializza per la goto

    // Leggi cliente
    if(fread(&len, sizeof(len), 1, fp) != 1) goto errore;
    if (len == 0 || len > DIMENSIONE_BUFFER) goto errore; // Controllo dimensione
    n_read = fread(buffer_str, sizeof(char), len, fp);
    if (n_read != len) goto errore;
    imposta_cliente_prenotazione(p, buffer_str);

    // Leggi targa
    if(fread(&len, sizeof(len), 1, fp) != 1) goto errore;
    if (len == 0 || len > DIMENSIONE_BUFFER) goto errore; // Controllo dimensione
    n_read = fread(buffer_str, sizeof(char), len, fp);
    if (n_read != len) goto errore;
    imposta_veicolo_prenotazione(p, buffer_str);

    // Leggi costo
    double costo;
    if(fread(&costo, sizeof(costo), 1, fp) != 1) goto errore;
    imposta_costo_prenotazione(p, costo);

    // Leggi intervallo
    time_t inizio, fine;
    if(fread(&inizio, sizeof(inizio), 1, fp) != 1 ||
       fread(&fine, sizeof(fine), 1, fp) != 1) goto errore;

    i = crea_intervallo(inizio, fine);
    if(i == NULL) goto errore;
    imposta_intervallo_prenotazione(p, i);

    return p;

errore:
    distruggi_prenotazione(p); // La funzione distruggi_prenotazione dovrebbe anche distruggere l'intervallo e le stringhe interne.
    return NULL;
}

/*
 * Autore: Marco Visone
 * Data: 15/05/2025
 *
 * Funzione: salva_prenotazioni
 * ----------------------------
 * Salva tutte le prenotazioni di una struttura Prenotazioni su un file binario.
 *
 * Implementazione:
 * Ottiene un vettore delle prenotazioni dall'albero, scrive la dimensione del vettore,
 * e poi cicla salvando ogni singola prenotazione.
 *
 * Parametri:
 * fp: puntatore al file su cui salvare le prenotazioni
 * prenotazioni: la struttura Prenotazioni da salvare
 *
 * Pre-condizioni:
 * fp e prenotazioni non devono essere NULL.
 *
 * Post-condizioni:
 * Tutte le prenotazioni vengono scritte nel file.
 */
static void salva_prenotazioni(FILE *fp, Prenotazioni prenotazioni) {
    if (fp == NULL || prenotazioni == NULL) return;
    unsigned int size = 0, i;
    Prenotazione *p = ottieni_vettore_prenotazioni_per_file(prenotazioni, &size);
    if (p == NULL) {
        // Se non ci sono prenotazioni, scrivi 0 per mantenere la consistenza del formato
        fwrite(&size, sizeof(size), 1, fp);
        return;
    }

    fwrite(&size, sizeof(size), 1, fp);

    for (i = 0; i < size; i++) {
        salva_prenotazione(fp, p[i]);
    }
    // E' responsabilità di chi crea il vettore (ottieni_vettore_prenotazioni_per_file)
    // garantire che sia liberato, ma se qui lo liberi è meglio, assumendo che sia una copia
    free(p);
}

/*
 * Autore: Marco Visone
 * Data: 15/05/2025
 *
 * Funzione: carica_prenotazioni
 * -----------------------------
 * Carica tutte le prenotazioni da un file binario e le inserisce in una nuova struttura Prenotazioni.
 *
 * Implementazione:
 * Legge la dimensione del set di prenotazioni, crea una nuova struttura Prenotazioni,
 * e poi cicla caricando ogni singola prenotazione e aggiungendola alla struttura.
 *
 * Parametri:
 * fp: puntatore al file da cui caricare le prenotazioni
 * buffer_str: buffer temporaneo per le stringhe
 *
 * Pre-condizioni:
 * fp e buffer_str non devono essere NULL.
 *
 * Post-condizioni:
 * Restituisce una nuova struttura Prenotazioni con i dati caricati, o NULL in caso di errore.
 */
static Prenotazioni carica_prenotazioni(FILE *fp, char *buffer_str) {
    if (fp == NULL || buffer_str == NULL) return NULL;
    unsigned int size = 0, i;
    if (fread(&size, sizeof size, 1, fp) != 1) return NULL;

    Prenotazioni pren = crea_prenotazioni();
    if (pren == NULL) return NULL; // Controllo allocazione

    for (i = 0; i < size; i++) {
        Prenotazione p_caricata = carica_prenotazione(fp, buffer_str);
        if (p_caricata == NULL) {
            distruggi_prenotazioni(pren); // Libera le prenotazioni già aggiunte
            return NULL;
        }
        if(!aggiungi_prenotazione(pren, p_caricata)) {
            distruggi_prenotazione(p_caricata);
            distruggi_prenotazioni(pren);
            return NULL;
        }
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
 * - Scrive nel file file_veicolo i seguenti campi, ciascuno preceduto dalla sua lunghezza:
 * - tipo del veicolo, targa, modello, posizione, tariffa
 * - Le prenotazioni associate vengono salvate nel file file_prenotazioni tramite la funzione salva_prenotazioni
 *
 * Parametri:
 * file_veicolo: puntatore a FILE aperto in modalità scrittura binaria, destinato ai dati del veicolo
 * file_prenotazioni: puntatore a FILE aperto in modalità scrittura binaria, destinato alle prenotazioni
 * v: veicolo da salvare
 *
 * Pre-condizioni:
 * file_veicolo: deve essere diverso da NULL
 * file_prenotazioni: deve essere diverso da NULL
 * v: deve essere diverso da NULL
 *
 * Post-condizioni:
 * non restituisce niente
 *
 * Side-effect:
 * - I dati del veicolo vengono scritti nel file file_veicolo
 * - Le prenotazioni vengono scritte nel file file_prenotazioni
 */
static void salva_veicolo(FILE *file_veicolo, FILE *file_prenotazioni, Veicolo v){
	if (file_veicolo == NULL || v == NULL || file_prenotazioni == NULL) return;

    // Utilizzo di const char* per i getter
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
 * - Legge dal file file_veicolo i campi stringa tipo, targa, modello, posizione
 * preceduti dalla loro lunghezza, e un double tariffa
 * - Carica le prenotazioni associate dal file file_prenotazioni usando la funzione carica_prenotazioni
 * - Crea il veicolo con i dati letti e lo restituisce.
 *
 * Parametri:
 * file_veicolo: file binario da cui leggere i dati del veicolo
 * file_prenotazioni: file binario da cui leggere le prenotazioni associate al veicolo
 * buffer_str: buffer temporaneo per le stringhe
 *
 * Pre-condizioni:
 * file_veicolo: deve essere diverso da NULL
 * file_prenotazioni: deve essere diverso da NULL
 * buffer_str: non deve essere NULL
 *
 * Post-condizioni:
 * restituisce NULL se uno dei file è NULL o in caso di errore, altrimenti restituisce un nuovo oggetto Veicolo
 *
 * Side-effect:
 * Alloca memoria dinamicamente per le stringhe temporanee (poi liberate), e per un nuovo oggetto Veicolo
 */
static Veicolo carica_veicolo(FILE *file_veicolo, FILE *file_prenotazioni, char *buffer_str){
	if (file_veicolo == NULL || file_prenotazioni == NULL || buffer_str == NULL) return NULL;

    char *tipo_veicolo = NULL;
    char *targa_veicolo = NULL;
    char *modello_veicolo = NULL;
    char *posizione_veicolo = NULL;
    Prenotazioni p_veicolo = NULL;
    Veicolo v = NULL;

    unsigned int len;
    size_t n_read;

    // Leggi tipo veicolo
    if (fread(&len, sizeof(unsigned int), 1, file_veicolo) != 1 || len == 0 || len > DIMENSIONE_BUFFER) goto errore;
    tipo_veicolo = malloc(sizeof(char) * len);
    if (tipo_veicolo == NULL) goto errore;
    n_read = fread(tipo_veicolo, sizeof(char), len, file_veicolo);
    if (n_read != len) goto errore;

    // Leggi targa veicolo
    if (fread(&len, sizeof(unsigned int), 1, file_veicolo) != 1 || len == 0 || len > DIMENSIONE_BUFFER) goto errore;
    targa_veicolo = malloc(sizeof(char) * len);
    if (targa_veicolo == NULL) goto errore;
    n_read = fread(targa_veicolo, sizeof(char), len, file_veicolo);
    if (n_read != len) goto errore;

    // Leggi modello veicolo
    if (fread(&len, sizeof(unsigned int), 1, file_veicolo) != 1 || len == 0 || len > DIMENSIONE_BUFFER) goto errore;
    modello_veicolo = malloc(sizeof(char) * len);
    if (modello_veicolo == NULL) goto errore;
    n_read = fread(modello_veicolo, sizeof(char), len, file_veicolo);
    if (n_read != len) goto errore;

    // Leggi posizione veicolo
    if (fread(&len, sizeof(unsigned int), 1, file_veicolo) != 1 || len == 0 || len > DIMENSIONE_BUFFER) goto errore;
    posizione_veicolo = malloc(sizeof(char) * len);
    if (posizione_veicolo == NULL) goto errore;
    n_read = fread(posizione_veicolo, sizeof(char), len, file_veicolo);
    if (n_read != len) goto errore;

    // Leggi tariffa
	double tariffa;
	if (fread(&tariffa, sizeof(tariffa), 1, file_veicolo) != 1) goto errore;

    // Carica prenotazioni
	p_veicolo = carica_prenotazioni(file_prenotazioni, buffer_str);
    if (p_veicolo == NULL) goto errore;

    // Crea veicolo
	v = crea_veicolo(tipo_veicolo, targa_veicolo, modello_veicolo, posizione_veicolo, tariffa, p_veicolo);
    if (v == NULL) goto errore;

    // Libera i buffer temporanei usati per le stringhe
	free(tipo_veicolo);
	free(targa_veicolo);
	free(modello_veicolo);
	free(posizione_veicolo);

	return v;

errore:
    free(tipo_veicolo);
    free(targa_veicolo);
    free(modello_veicolo);
    free(posizione_veicolo);
    distruggi_veicolo(v);
    return NULL;
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
 * - Apre due file binari in modalità scrittura:
 * - uno per i dati dei veicoli, nome_file_veicolo
 * - uno per le prenotazioni associate, nome_file_prenotazioni
 * - Scrive nel file dei veicoli il numero totale di veicoli da salvare
 * - Per ogni veicolo nel vettore, chiama la funzione salva_veicolo
 * che scrive i dati nei rispettivi file
 * - Chiude entrambi i file al termine
 *
 * Parametri:
 * nome_file_veicolo: file in cui salvare i dati dei veicoli
 * nome_file_prenotazioni: file in cui salvare le prenotazioni
 * vettore: array di veicoli da salvare
 * num_veicoli: numero di elementi nel vettore
 *
 * Pre-condizioni:
 * nome_file_veicolo: deve essere diverso da NULL
 * nome_file_prenotazioni: deve essere diverso da NULL
 * vettore: deve essere diverso da NULL
 * num_veicoli: deve essere diverso di 0
 *
 * Post-condizioni:
 * non restituisce niente
 *
 * Side-effect:
 * i dati dei veicoli e delle relative prenotazioni vengono scritti
 * nei file specificati in formato binario
 */
void salva_vettore_veicoli(const char *nome_file_veicolo, const char *nome_file_prenotazioni, Veicolo vettore[], unsigned int num_veicoli){
	if(nome_file_veicolo == NULL || nome_file_prenotazioni == NULL || vettore == NULL || num_veicoli == 0) return; // !num_veicoli è corretto, ma num_veicoli == 0 è più esplicito

	FILE *file_veicolo = fopen(nome_file_veicolo, "wb");
    if (file_veicolo == NULL) return;

    FILE *file_prenotazioni = fopen(nome_file_prenotazioni, "wb");
    if (file_prenotazioni == NULL){
        fclose(file_veicolo);
        return;
    }

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
 * - Apre due file binari in lettura: uno per i veicoli e uno per le prenotazioni
 * - Legge il numero totale di veicoli da caricare dal file dei veicoli
 * - Alloca dinamicamente un array di puntatori a Veicolo
 * - Per ogni veicolo, richiama la funzione carica_veicolo per leggere i dati e le prenotazioni
 *
 * Parametri:
 * nome_file_veicolo: nome del file contenente i dati dei veicoli
 * nome_file_prenotazioni: nome del file contenente le prenotazioni associate
 * num_veicoli: puntatore a variabile dove verrà salvato il numero di veicoli caricati
 *
 * Pre-condizioni:
 * nome_file_veicolo: deve essere diverso da NULL
 * nome_file_prenotazioni: deve essere diverso da NULL
 * num_veicoli: non deve essere NULL
 *
 * Post-condizioni:
 * - Restituisce un array di Veicolo e ne imposta la dimensione in num_veicoli, restituisce NULL in caso di errore
 *
 * Side-effect:
 * - Alloca memoria dinamicamente per il vettore restituito (va liberata dal chiamante)
 */
Veicolo *carica_vettore_veicoli(const char *nome_file_veicolo, const char *nome_file_prenotazioni, unsigned int *num_veicoli){
	if(nome_file_veicolo == NULL || nome_file_prenotazioni == NULL || num_veicoli == NULL) return NULL;

	FILE *file_veicolo = fopen(nome_file_veicolo, "rb");
    if (file_veicolo == NULL) return NULL;

    char *buffer_local = calloc(DIMENSIONE_BUFFER, sizeof(char)); // Buffer locale
    if(buffer_local == NULL){
        fclose(file_veicolo);
        return NULL;
    }

    FILE *file_prenotazioni = fopen(nome_file_prenotazioni, "rb");
    if (file_prenotazioni == NULL){
        fclose(file_veicolo);
        free(buffer_local); // Libera il buffer locale in caso di fallimento
        return NULL;
    }

    // Leggi il numero di veicoli
    if (fread(num_veicoli, sizeof(unsigned int), 1, file_veicolo) != 1) {
        fclose(file_veicolo);
        fclose(file_prenotazioni);
        free(buffer_local);
        return NULL;
    }

    Veicolo *vettore = malloc(sizeof(Veicolo) * (*num_veicoli));
    if(vettore == NULL) {
        fclose(file_veicolo);
        fclose(file_prenotazioni);
        free(buffer_local);
        return NULL;
    }

    for (unsigned i = 0; i < *num_veicoli; i++){
        vettore[i] = carica_veicolo(file_veicolo, file_prenotazioni, buffer_local); // Passa il buffer
        if (vettore[i] == NULL) {
            // Se un caricamento fallisce, libera gli oggetti già caricati
            for (unsigned j = 0; j < i; j++) {
                distruggi_veicolo(vettore[j]);
            }
            free(vettore);
            fclose(file_veicolo);
            fclose(file_prenotazioni);
            free(buffer_local);
            *num_veicoli = 0;
            return NULL;
        }
    }

    fclose(file_veicolo);
    fclose(file_prenotazioni);
    free(buffer_local); // Libera il buffer locale

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
 * file_data: puntatore al file su cui salvare i dati
 * d: struttura Data da salvare
 *
 * Pre-condizione:
 * file_data e d devono essere validi
 *
 * Post-condizione:
 * i dati della struttura sono scritti nel file
 *
 * Ritorna:
 * nessun valore
 *
 * Side-effect:
 * scrittura su file
 */
static void salva_data(FILE *file_data, Data d){
    if(file_data == NULL || d == NULL){
        return;
    }

    // Ottieni la lista e il numero di prenotazioni prima di scriverli
    ListaPre lista_prenotazioni = ottieni_storico_lista(d);
    int numero_prenotazioni = ottieni_numero_prenotazioni(d);

    int frequenza = ottieni_frequenza_lista(d);
    fwrite(&frequenza, sizeof(int), 1, file_data);
    fwrite(&numero_prenotazioni, sizeof(int), 1, file_data);

    // Iterare sulla lista originale senza modificarla
    ListaPre curr = lista_prenotazioni;
    for(int i = 0; curr && (i < numero_prenotazioni); i++){
        salva_prenotazione(file_data, (Prenotazione)ottieni_item(curr));
        curr = ottieni_prossimo(curr);
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
 * file_data: puntatore al file da cui leggere i dati
 * buffer_str: buffer temporaneo per le stringhe
 *
 * Pre-condizione:
 * file_data e buffer_str devono essere validi
 *
 * Post-condizione:
 * viene restituita una nuova struttura Data con i dati caricati
 *
 * Ritorna:
 * un nuovo oggetto Data, oppure NULL in caso di errore
 *
 * Side-effect:
 * lettura da file, allocazione dinamica
 */
static Data carica_data(FILE *file_data, char *buffer_str){
    if(file_data == NULL || buffer_str == NULL){
        return NULL;
    }
    int numero_prenotazioni;
    int frequenza;

    Data d = NULL; // Inizializza per la goto

    if (fread(&frequenza, sizeof(int), 1, file_data) != 1) goto errore;
    if (fread(&numero_prenotazioni, sizeof(int), 1, file_data) != 1) goto errore;

    d = crea_data();
    if (d == NULL) goto errore;

    imposta_frequenza(d, frequenza);

    for(int i = 0; i < numero_prenotazioni; i++){
        Prenotazione p_caricata = carica_prenotazione(file_data, buffer_str); // Passa il buffer
        if (p_caricata == NULL) {
            goto errore; // Se una prenotazione fallisce, fallisce l'intera data
        }

        if (aggiungi_a_storico_lista(d, p_caricata) == NULL) {
            distruggi_prenotazione(p_caricata); // Libera la prenotazione se non può essere aggiunta
            goto errore;
        }
    }
    imposta_numero_prenotazioni(d, numero_prenotazioni);
    return d;

errore:
    distruggi_data(d);
    return NULL;
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
 * file_utente: file su cui scrivere i dati dell'utente
 * file_data: file su cui scrivere i dati storici dell'utente
 * u: utente da salvare
 *
 * Pre-condizione:
 * file_utente e u devono essere validi
 *
 * Post-condizione:
 * i dati dell'utente sono salvati nei file
 *
 * Ritorna:
 * nessun valore
 *
 * Side-effect:
 * scrittura su file
 */
static void salva_utente(FILE *file_utente, FILE *file_data, Utente u){
    if (file_utente == NULL || u == NULL) return;

    // Utilizzo di const char* per i getter
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

    if (permesso == CLIENTE) { // Salva lo storico e frequenza solo se l'utente è un CLIENTE
        salva_data(file_data, ottieni_data(u));
    }
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
 * file_utente: file da cui leggere i dati dell'utente
 * file_data: file da cui leggere i dati storici
 * buffer_str: buffer temporaneo per le stringhe
 *
 * Pre-condizione:
 * file_utente e buffer_str devono essere validi
 *
 * Post-condizione:
 * restituisce un utente ricostruito dai file
 *
 * Ritorna:
 * un nuovo oggetto Utente, o NULL in caso di errore
 *
 * Side-effect:
 * lettura da file, allocazione dinamica di memoria
 */
static Utente carica_utente(FILE *file_utente, FILE *file_data, char *buffer_str) {
    if (file_utente == NULL || buffer_str == NULL)
        return NULL;

    Utente u = crea_utente(NULL, NULL, NULL, NULL, 0);
    if (u == NULL)
        return NULL;

    unsigned int len;
    Byte permesso;
    Data data = NULL;
    size_t n;

    // Leggi nome
    if (fread(&len, sizeof(len), 1, file_utente) != 1 || len == 0 || len > DIMENSIONE_BUFFER) { // Controllo DIMENSIONE_BUFFER
        goto errore;
    }
    n = fread(buffer_str, sizeof(char), len, file_utente);
    if (n != len) {
        goto errore;
    }
    imposta_nome(u, buffer_str);

    // Leggi cognome
    if (fread(&len, sizeof(len), 1, file_utente) != 1 || len == 0 || len > DIMENSIONE_BUFFER) { // Controllo DIMENSIONE_BUFFER
        goto errore;
    }
    n = fread(buffer_str, sizeof(char), len, file_utente);
    if (n != len) {
        goto errore;
    }
    imposta_cognome(u, buffer_str);

    // Leggi email
    if (fread(&len, sizeof(len), 1, file_utente) != 1 || len == 0 || len > DIMENSIONE_BUFFER) { // Controllo DIMENSIONE_BUFFER
        goto errore;
    }
    n = fread(buffer_str, sizeof(char), len, file_utente);
    if (n != len) {
        goto errore;
    }
    imposta_email(u, buffer_str);

    // Leggi password
    if (fread(password_buffer, sizeof(uint8_t), DIMENSIONE_PASSWORD, file_utente) != DIMENSIONE_PASSWORD) {
        goto errore;
    }
    imposta_password(u, password_buffer); // Usa il buffer locale statico per la password

    // Leggi permesso
    if (fread(&permesso, sizeof(permesso), 1, file_utente) != 1) {
        goto errore;
    }
    imposta_permesso(u, permesso);

    if (permesso == CLIENTE) {
        data = carica_data(file_data, buffer_str); // Passa il buffer
        if (data == NULL) {
            goto errore;
        }
    }
    imposta_data(u, data);

    return u;

errore:
    distruggi_utente(u); //Libera la memoria dell'utente (con anche Data)
    return NULL;
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
void salva_vettore_utenti(const char *nome_file_utente, const char *nome_file_data, Utente vettore[], unsigned int num_utenti){
    if(nome_file_utente == NULL || nome_file_data == NULL || vettore == NULL || num_utenti == 0) return;

    FILE *file_utente = fopen(nome_file_utente, "wb");
    if (file_utente == NULL) return;

    FILE *file_data = fopen(nome_file_data, "wb");
    if (file_data == NULL){
        fclose(file_utente);
        return;
    }

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
Utente *carica_vettore_utenti(const char *nome_file_utente, const char *nome_file_data, unsigned int *num_utenti){
    if(nome_file_utente == NULL || nome_file_data == NULL || num_utenti == NULL) return NULL;

    FILE *file_utente = fopen(nome_file_utente, "rb");
    if (file_utente == NULL) return NULL;

    char *buffer_local = calloc(DIMENSIONE_BUFFER, sizeof(char)); // Buffer locale
    if(buffer_local == NULL){
        fclose(file_utente);
        return NULL;
    }

    FILE *file_data = fopen(nome_file_data, "rb");
    if (file_data == NULL){
        fclose(file_utente);
        free(buffer_local); // Libera il buffer locale
        return NULL;
    }

    // Leggi il numero di utenti
    if (fread(num_utenti, sizeof(unsigned int), 1, file_utente) != 1) {
        fclose(file_utente);
        fclose(file_data);
        free(buffer_local);
        return NULL;
    }

    Utente *vettore = malloc(sizeof(Utente) * (*num_utenti));
    if(vettore == NULL) {
        fclose(file_utente);
        fclose(file_data);
        free(buffer_local);
        return NULL;
    }

    for (unsigned int i = 0; i < *num_utenti; i++){
        vettore[i] = carica_utente(file_utente, file_data, buffer_local); // Passa il buffer
        if (vettore[i] == NULL) {
            // Se un caricamento fallisce, libera gli oggetti già caricati
            for (unsigned int j = 0; j < i; j++) {
                distruggi_utente(vettore[j]);
            }
            free(vettore);
            fclose(file_utente);
            fclose(file_data);
            free(buffer_local);
            *num_utenti = 0;
            return NULL;
        }
    }

    fclose(file_utente);
    fclose(file_data);
    free(buffer_local);

    return vettore;
}
