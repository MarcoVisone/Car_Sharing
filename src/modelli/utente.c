/*
 * Autore: Antonio Sicignano
 * Data: 09/05/2025
 */

#include <stdlib.h>
#include <stdio.h>
#include "modelli/utente.h"
#include "modelli/data.h"
#include "modelli/veicolo.h"
#include "utils/utils.h"
#include <string.h>
#include <sys/types.h>

struct utente {
    char nome[DIMENSIONE_NOME];
    char cognome[DIMENSIONE_COGNOME];
    char email[DIMENSIONE_EMAIL];
    uint8_t password[DIMENSIONE_PASSWORD];
    Byte permesso;
    Data data;
};

/*
 * Funzione: crea_utente
 * ---------------------
 * Crea e inizializza un nuovo utente con le informazioni fornite.
 *
 * Implementazione:
 *    - Alloca dinamicamente memoria per una nuova struttura `utente`.
 *    - Copia i valori di `nome`, `cognome` ed `email` nelle rispettive proprietà
 *    della struttura, rispettando le dimensioni massime definite.
 *    - Se la password è fornita, la copia nella struttura utente.
 *    - Imposta il campo `permesso` con il valore specificato.
 *    - Se il permesso è `CLIENTE`, crea una struttura dati associata tramite `crea_data`.
 *    Altrimenti, imposta il campo `data` a NULL.
 *
 * Parametri:
 *    email: stringa costante contenente l'email dell'utente.
 *    password: puntatore ai dati della password (array di byte).
 *    nome: stringa costante contenente il nome dell'utente.
 *    cognome: stringa costante contenente il cognome dell'utente.
 *    permesso: valore di tipo `Byte` che rappresenta il livello di permesso dell'utente.
 *
 * Pre-condizioni:
 *    email: non deve essere NULL
 *    nome: non deve essere NULL
 *    cognome: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce un nuovo utente, in caso di errore restituisce NULL
 *
 * Ritorna:
 *    un puntatore a utente o NULL
 *
 * Side-effect:
 *    - Alloca memoria dinamica per la struttura `utente` e, opzionalmente, per la struttura dati associata.
 *    La memoria deve essere liberata dal chiamante.
 */
Utente crea_utente(const char *email, const uint8_t *password,  const char *nome, const char *cognome, Byte permesso){
    Utente u = malloc(sizeof(struct utente));

    if(u == NULL){
        return NULL;
    }

    snprintf(u->nome, DIMENSIONE_NOME, "%s", nome);
    snprintf(u->cognome, DIMENSIONE_COGNOME, "%s", cognome);
    snprintf(u->email, DIMENSIONE_EMAIL, "%s", email);
    if(password != NULL)
        memcpy(u->password, password, DIMENSIONE_PASSWORD);
    u->permesso = permesso;
    if (permesso == CLIENTE) {
        u->data = crea_data();
        if(u->data == NULL){
            free(u);
            return NULL;
        }
    }
    else {
        u->data = NULL;
    }

    return u;
}

/*
 * Funzione: distruggi_utente
 * --------------------------
 * Dealloca la memoria associata a un oggetto `Utente`, liberando anche le
 * eventuali risorse interne collegate.
 *
 * Implementazione:
 *    - Verifica se il puntatore `utente` è NULL; se sì, esce immediatamente.
 *    - Chiama `distruggi_data` per liberare la memoria associata al campo `data`.
 *    - Libera la memoria allocata per la struttura `utente`.
 *
 * Parametri:
 *    utente: puntatore all'oggetto `Utente` da deallocare.
 *
 * Pre-condizioni:
 *    utente: non deve essere NULL
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    - Tutta la memoria associata all'utente e alle sue risorse interne è liberata.
 */
void distruggi_utente(Utente utente){
    if(utente == NULL) return;
    distruggi_data(utente->data);
    free(utente);
}

/*
 * Funzione: imposta_nome
 * ---------------------
 * Imposta il nome di un utente con la stringa fornita.
 *
 * Implementazione:
 *    - Verifica che i parametri `utente` e `nome` non siano NULL.
 *    - Copia la stringa `nome` nel campo `nome` della struttura `utente`
 *    utilizzando `snprintf` per evitare overflow.
 *
 * Parametri:
 *    utente: puntatore all'oggetto `Utente` da modificare.
 *    nome: stringa costante contenente il nuovo nome da assegnare.
 *
 * Pre-condizioni:
 *    utente: non deve essere NULL
 *    nome: non deve essere NULL
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    - Il campo `nome` dell'utente viene aggiornato con il nuovo valore.
 */
void imposta_nome(Utente utente, const char *nome) {
    if(utente == NULL || nome == NULL) {
        return;
    }

    snprintf(utente->nome, DIMENSIONE_NOME, "%s", nome);
 }

/*
 * Funzione: imposta_cognome
 * -------------------------
 * Imposta il cognome di un utente con la stringa fornita.
 *
 * Implementazione:
 *    - Verifica che il parametro `utente` non sia NULL.
 *    - Copia la stringa `cognome` nel campo `cognome` della struttura `utente`
 *    utilizzando `snprintf` per evitare overflow.
 *
 * Parametri:
 *    utente: puntatore all'oggetto `Utente` da modificare.
 *    cognome: stringa costante contenente il nuovo cognome da assegnare.
 *
 * Pre-condizioni:
 *    utente: non deve essere NULL
 *    cognome: non deve essere NULL
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    - Il campo `cognome` dell'utente viene aggiornato con il nuovo valore.
 */
void imposta_cognome(Utente utente, const char *cognome) {
    if(utente == NULL) {
        return;
    }

    snprintf(utente->cognome, DIMENSIONE_COGNOME, "%s", cognome);
}

/*
 * Funzione: imposta_email
 * ----------------------
 * Imposta l'email di un utente con la stringa fornita.
 *
 * Implementazione:
 *    - Verifica che il parametro `utente` non sia NULL.
 *    - Copia la stringa `email` nel campo `email` della struttura `utente`
 *    utilizzando `snprintf` per evitare overflow.
 *
 * Parametri:
 *    utente: puntatore all'oggetto `Utente` da modificare.
 *    email: stringa costante contenente la nuova email da assegnare.
 *
 * Pre-condizioni:
 *    utente: non deve essere NULL
 *    email: non deve essere NULL
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    - Il campo `email` dell'utente viene aggiornato con il nuovo valore.
 */
void imposta_email(Utente utente, const char *email) {
    if(utente == NULL) {
        return;
    }

    snprintf(utente->email, DIMENSIONE_EMAIL, "%s", email);
}

/*
 * Funzione: imposta_password
 * -------------------------
 * Imposta la password di un utente copiando i dati forniti.
 *
 * Implementazione:
 *    - Verifica che il parametro `utente` non sia NULL.
 *    - Copia i byte della password nel campo `password` della struttura `utente`
 *    utilizzando `memcpy` con la dimensione `DIMENSIONE_PASSWORD`.
 *
 * Parametri:
 *    utente: puntatore all'oggetto `Utente` da modificare.
 *    password: puntatore ai dati della nuova password (array di byte).
 *
 * Pre-condizioni:
 *    utente: non deve essere NULL
 *    password: deve puntare a un array di grandezza DIMENSIONE_PASSWORD
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    - Il campo `password` dell'utente viene aggiornato con i nuovi dati.
 */
void imposta_password(Utente utente, const uint8_t *password) {
    if(utente == NULL) {
        return;
    }

    memcpy(utente->password, password, DIMENSIONE_PASSWORD);
}

/*
 * Funzione: imposta_permesso
 * --------------------------
 * Imposta il livello di permesso di un utente.
 *
 * Implementazione:
 *    - Verifica che il parametro `utente` non sia NULL.
 *    - Aggiorna il campo `permesso` della struttura `utente` con il valore fornito.
 *
 * Parametri:
 *    utente: puntatore all'oggetto `Utente` da modificare.
 *    permesso: valore di tipo Byte che indica il nuovo livello di permesso.
 *
 * Pre-condizioni:
 *    utente: non deve essere NULL
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    - Il campo `permesso` dell'utente viene aggiornato con il nuovo valore.
 */
void imposta_permesso(Utente utente, Byte permesso) {
    if(utente == NULL) {
        return;
    }

    utente->permesso = permesso;
}

/*
 * Funzione: imposta_data
 * ----------------------
 * Imposta la data associata a un utente, a meno che l'utente sia un admin.
 *
 * Implementazione:
 *    - Verifica che `utente` non sia NULL.
 *    - Se il permesso è ADMIN, non modifica nulla e ritorna subito.
 *    - Se il campo `data` esiste, lo distrugge liberando memoria.
 *    - Assegna la nuova data fornita al campo `data`.
 *
 * Parametri:
 *    utente: puntatore all'oggetto `Utente` da modificare.
 *    data: oggetto `Data` da assegnare all'utente.
 *
 * Pre-condizioni:
 *    utente: non deve essere NULL.
 *
 * Post-condizioni:
 *    non restituisce niente
 *
 * Side-effect:
 *    - Il campo `data` dell'utente è aggiornato con il nuovo valore, tranne se è admin.
 */
void imposta_data(Utente utente, Data data) {
    if(utente == NULL) {
        return;
    }

    if (utente->permesso == ADMIN) {
        return;
    }

    if (utente->data != NULL) {
        distruggi_data(utente->data);
    }

    utente->data = data;
}

/*
 * Funzione: ottieni_cognome
 * -------------------------
 * Restituisce una copia dinamica della stringa cognome di un utente.
 *
 * Implementazione:
 *    - Se `utente` è NULL, ritorna NULL.
 *    - Usa `mia_strdup` per duplicare la stringa `cognome`.
 *
 * Parametri:
 *    utente: puntatore costante all'oggetto `Utente`.
 *
 * Pre-condizioni:
 *    utente: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce il cognome dell'utente oppure NULL in caso di errore
 *
 * Ritorna:
 *    una stringa costante o NULL
 *
 * Side-effect:
 *    - Alloca memoria dinamica che deve essere liberata dal chiamante.
 */
const char *ottieni_cognome(const Utente utente){
    if (utente == NULL) {
        return NULL;
    }
    return utente->cognome;
}


/*
 * Funzione: ottieni_nome
 * ----------------------
 * Restituisce una copia dinamica della stringa nome di un utente.
 *
 * Implementazione:
 *    - Se `utente` è NULL, ritorna NULL.
 *    - Usa `mia_strdup` per duplicare la stringa `nome`.
 *
 * Parametri:
 *    utente: puntatore costante all'oggetto `Utente`.
 *
 * Pre-condizioni:
 *    utente: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce il nome dell'utente oppure NULL in caso di errore
 *
 * Ritorna:
 *    una stringa costante o NULL
 *
 * Side-effect:
 *    - Alloca memoria dinamica che deve essere liberata dal chiamante.
 */
const char *ottieni_nome(const Utente utente){
    if (utente == NULL) {
        return NULL;
    }
    return utente->nome;
}

/*
 * Funzione: ottieni_email
 * -----------------------
 * Restituisce una copia dinamica della stringa email di un utente.
 *
 * Implementazione:
 *    - Se `utente` è NULL, ritorna NULL.
 *    - Restituisce la stringa `email`.
 *
 * Parametri:
 *    utente: puntatore costante all'oggetto `Utente`.
 *
 * Pre-condizioni:
 *    utente: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce l'email dell'utente oppure NULL in caso di errore
 *
 * Ritorna:
 *    una stringa costante o NULL
 *
 * Side-effect:
 *    - Alloca memoria dinamica che deve essere liberata dal chiamante.
 */
const char *ottieni_email(const Utente utente){
    if (utente == NULL) {
        return NULL;
    }
    return utente->email;
}

/*
 * Funzione: ottieni_password
 * --------------------------
 * Restituisce una copia dinamica della password di un utente.
 *
 * Implementazione:
 *    - Se `utente` è NULL, ritorna NULL.
 *    - Restituisce password utente
 *
 * Parametri:
 *    utente: puntatore costante all'oggetto `Utente`.
 *
 * Pre-condizioni:
 *    utente: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce la password dell'utente oppure NULL in caso di errore
 *
 * Ritorna:
 *    un puntatore o NULL
 *
 * Side-effect:
 *    - Alloca memoria dinamica che deve essere liberata dal chiamante.
 */
const uint8_t *ottieni_password(const Utente utente){
    if (utente == NULL) {
        return NULL;
    }

    return utente->password;
}

/*
 * Funzione: ottieni_permesso
 * --------------------------
 * Restituisce il livello di permesso di un utente.
 *
 * Implementazione:
 *    - Se `utente` è NULL, ritorna il valore speciale `ERRORE_PERMESSO`.
 *    - Altrimenti restituisce il campo `permesso` dell'utente.
 *
 * Parametri:
 *    utente: puntatore all'oggetto `Utente`.
 *
 * Pre-condizioni:
 *    utente: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce la costante ERRORE_PERMESSO se c'è un errore, altrimenti il permesso dell'utente
 *
 * Ritorna:
 *     un valore di tipo Byte
 */
Byte ottieni_permesso(Utente utente){
    if (utente == NULL) {
        return ERRORE_PERMESSO;
    }

    return utente->permesso;
}

/*
 * Funzione: ottieni_storico_utente
 * --------------------------------
 * Restituisce la lista storico delle prenotazioni di un utente.
 *
 * Implementazione:
 *    - Se `utente` è NULL, ritorna NULL.
 *    - Altrimenti chiama `ottieni_storico_lista` passando il campo `data`.
 *
 * Parametri:
 *    utente: puntatore all'oggetto `Utente`.
 *
 * Pre-condizioni:
 *    utente: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce la lista delle prenotazioni, oppure NULL se `utente` è NULL.
 *
 * Ritorna:
 *    una lista o NULL
 */
ListaPre ottieni_storico_utente(Utente utente) {
    if (utente == NULL) {
        return NULL;
    }

    return ottieni_storico_lista(utente->data);
}

/*
 * Funzione: aggiungi_a_storico_utente
 * -----------------------------------
 * Aggiunge una prenotazione allo storico di un utente.
 *
 * Implementazione:
 *    - Se `utente` è NULL, ritorna 0.
 *    - Chiama `aggiungi_a_storico_lista` con lo storico dati dell'utente e la prenotazione.
 *
 * Parametri:
 *    utente: puntatore all'oggetto `Utente`.
 *    prenotazione: prenotazione da aggiungere allo storico.
 *
 * Pre-condizioni:
 *    utente: non deve essere NULL
 *    prenotazione: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce 1 in caso di successo, 0 in caso di fallimento o utente NULL.
 *
 * Ritorna:
 *    un valore di tipo Byte(0 o 1)
 *
 * Side-effect:
 *    - Lo storico dati dell'utente è aggiornato con la nuova prenotazione.
 */
Byte aggiungi_a_storico_utente(Utente utente, Prenotazione prenotazione) {
    if (utente == NULL) {
        return 0;
    }

    return aggiungi_a_storico_lista(utente->data, prenotazione);
}

/*
 * Funzione: rimuovi_da_storico_utente
 * -----------------------------------
 * Rimuove una prenotazione dallo storico di un utente.
 * Se lo storico risulta vuoto dopo la rimozione, imposta lo storico a NULL.
 *
 * Implementazione:
 *    - Se `utente` è NULL, ritorna 0.
 *    - Chiama `rimuovi_da_storico_lista` per rimuovere la prenotazione.
 *    - Se dopo la rimozione lo storico è vuoto e la rimozione ha avuto successo,
 *    imposta lo storico a NULL e ritorna 1.
 *    - Altrimenti ritorna il codice di ritorno della rimozione.
 *
 * Parametri:
 *    utente: puntatore all'oggetto `Utente`.
 *    prenotazione: prenotazione da rimuovere dallo storico.
 *
 * Pre-condizioni:
 *    utente: non deve essere NULL
 *    prenotazione: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce 1 se la rimozione ha avuto successo, altrimenti 0
 *
 * Ritorna:
 *    un valore di tipo Byte(0 o 1)
 *
 * Side-effect:
 *    - Lo storico dati dell'utente è aggiornato di conseguenza.
 */
Byte rimuovi_da_storico_utente(Utente utente, Prenotazione prenotazione) {
    if (utente == NULL) {
        return 0;
    }

    Byte codice = rimuovi_da_storico_lista(utente->data, prenotazione);

    if(!ottieni_numero_prenotazioni(utente->data) && !codice){
        imposta_storico_lista(utente->data, NULL);
        return 1;
    }

    return codice;
}

/*
 * Funzione: ottieni_numero_prenotazioni_utente
 * --------------------------------------------
 * Restituisce il numero di prenotazioni nello storico di un utente.
 *
 * Implementazione:
 *    - Se `utente` è NULL, ritorna 0.
 *    - Altrimenti chiama `ottieni_numero_prenotazioni` sul campo `data` dell'utente.
 *
 * Parametri:
 *    u: puntatore all'oggetto `Utente`.
 *
 * Pre-condizioni:
 *    u: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce il numero di prenotazioni oppure 0 se c'è un errore
 *
 * Ritorna:
 *    un numero intero positivo
 */
unsigned int ottieni_numero_prenotazioni_utente(Utente u){
    if(u == NULL) return 0;

    return ottieni_numero_prenotazioni(u->data);
}

/*
 * Funzione: crea_nuova_data
 * --------------------------------------------
 * Distrugge la vecchia data e una nuova data dentro Utente
 *
 * Implementazione:
 *    - Se `utente` è NULL, ritorna 0.
 *    - Altrimenti chiama `distruggi_data` sul campo `data` dell'utente per distruggere
 *    la data attuale se è diversa da null, se utente è cliente invece crea la data nuova.
 *
 * Parametri:
 *    u: puntatore all'oggetto `Utente`.
 *
 * Pre-condizioni:
 *    u: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce 1 se la creazione è andata a buon fine, altrimenti 0
 *
 * Ritorna:
 *    un valore di tipo Byte(0 o 1)
 *
 * Side-effect:
 *    - Viene deallocata e allocata memoria dentro al campo data.
 */
Byte crea_nuova_data(Utente u){
    if(u == NULL){
        return 0;
    }

    distruggi_data(u->data);

    if(u->permesso == CLIENTE){
        u->data = crea_data();
        return 1;
    }

    return 0;
}

/*
 * Funzione: utente_in_stringa
 * ---------------------------
 * Restituisce una stringa descrittiva dell'utente.
 *
 * Implementazione:
 *    - Se `utente` è NULL, ritorna NULL.
 *    - Determina il tipo di utente ("Admin" o "Cliente") usando `ottieni_permesso`.
 *    - Calcola la lunghezza necessaria per la stringa di output.
 *    - Alloca memoria e compone la stringa con nome, cognome, email e tipo utente.
 *
 * Parametri:
 *    utente: puntatore all'oggetto `Utente`.
 *
 * Pre-condizioni:
 *    utente: non deve essere NULL
 *
 * Post-condizioni:
 *    restituisce tutte le caratteristiche di un utente
 *
 * Ritorna:
 *    una stringa o NULL
 *
 * Side-effect:
 *    - Alloca memoria dinamica che deve essere liberata dal chiamante.
 */
char *utente_in_stringa(const Utente utente){
    if(utente == NULL) return NULL;
    char *tipo_utente = NULL;
    if(ottieni_permesso(utente) == ADMIN){
        tipo_utente = mia_strdup("Admin");
    }
    else tipo_utente = mia_strdup("Cliente");

    size_t lunghezza = (strlen(utente->cognome) + strlen(utente->nome) + strlen(utente->email) + strlen(tipo_utente)) + 100 + 1;
    char *buffer = malloc(sizeof(const char) * lunghezza);

    snprintf(buffer, lunghezza, "- Nome: %s\n- Cognome: %s\n- Email: %s\n- Utente e' %s",
        utente->nome,
        utente->cognome,
        utente->email,
        tipo_utente);

    free(tipo_utente);

    return buffer;
}
