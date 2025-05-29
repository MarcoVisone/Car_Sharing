/*
 * Autore: Marco Visone
 * Data: 06/05/2025
 */

#include "strutture_dati/prenotazioni.h"
#include "modelli/prenotazione.h"
#include "modelli/intervallo.h"
#include "strutture_dati/coda.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define massimo(x, y) (x > y ? x : y)
#define ottieni_massimo(x) (x ? x->massimo : 0)
#define altezza(x) (x ? x->altezza : 0)

struct nodo {
    Prenotazione prenotazione;
    time_t massimo;     // Fine massima degli intervalli nel sottoalbero
    int altezza;        // Altezza del nodo
    struct nodo *destra;
    struct nodo *sinistra;
};

struct albero {
    struct nodo *radice;
    unsigned int num_nodi;
};

/*
 * Funzione: nuovo_nodo
 * --------------------
 * Crea un nuovo nodo per l'albero AVL.
 *
 * Implementazione:
 * - Alloca memoria per una nuova struttura `struct nodo`.
 * - Inizializza il campo `prenotazione` con la prenotazione fornita.
 * - Imposta i puntatori `sinistra` e `destra` a NULL, poiché è un nuovo nodo (foglia).
 * - Inizializza `altezza` a 1, dato che è una foglia.
 * - Inizializza `massimo` con la fine dell'intervallo della prenotazione corrente,
 * essendo l'unico elemento nel suo sottoalbero iniziale.
 *
 * Parametri:
 * prenotazione: la prenotazione da inserire nel nuovo nodo.
 *
 * Pre-condizioni:
 * - `prenotazione` non deve essere NULL.
 *
 * Post-condizioni:
 * - Restituisce un puntatore a un nuovo nodo inizializzato se l'allocazione ha successo.
 * - Restituisce NULL in caso di fallimento dell'allocazione di memoria.
 *
 * Side-effect:
 * - Alloca memoria dinamicamente per la nuova struttura `struct nodo`.
 */
static struct nodo* nuovo_nodo(Prenotazione prenotazione) {
    struct nodo* nodo = malloc(sizeof(struct nodo));
    if (!nodo) return NULL;

    nodo->prenotazione = prenotazione;
    nodo->sinistra = nodo->destra = NULL;
    nodo->altezza = 1;
    nodo->massimo = fine_intervallo(ottieni_intervallo_prenotazione(prenotazione));
    return nodo;
}

/*
 * Funzione: aggiorna_nodo
 * -----------------------
 * Aggiorna i campi `altezza` e `massimo` di un dato nodo AVL.
 *
 * Implementazione:
 * - Ottiene l'intervallo associato alla prenotazione del nodo corrente e la sua fine.
 * - Ricalcola `altezza` come 1 più il massimo tra l'altezza del figlio sinistro
 * e l'altezza del figlio destro (gestendo il caso di figli NULL che hanno altezza 0).
 * - Ricalcola `massimo` come il valore più grande tra la fine dell'intervallo della
 * propria prenotazione e i valori `massimo` dei suoi figli sinistro e destro
 * (gestendo il caso di figli NULL che hanno massimo 0).
 *
 * Parametri:
 * n: il nodo da aggiornare.
 *
 * Pre-condizioni:
 * - `n` non deve essere NULL.
 *
 * Post-condizioni:
 * - I campi `altezza` e `massimo` del nodo `n` sono aggiornati per riflettere
 * correttamente lo stato attuale del sottoalbero radicato in `n`.
 *
 * Side-effect:
 * - Modifica i campi `altezza` e `massimo` del nodo `n`.
 */
static void aggiorna_nodo(struct nodo *n) {
    Intervallo iv = ottieni_intervallo_prenotazione(n->prenotazione);
    time_t fi = fine_intervallo(iv);

    // L'altezza è 1 + l'altezza massima tra il figlio sinistro e destro
    n->altezza = 1 + massimo(altezza(n->sinistra), altezza(n->destra));
    // Il massimo è il più grande tra la propria fine e il massimo dei figli
    n->massimo = massimo(fi, massimo(ottieni_massimo(n->sinistra), ottieni_massimo(n->destra)));
}

/*
 * Funzione: ruota_destra
 * ----------------------
 * Esegue una rotazione a destra sull'albero AVL per ripristinare il bilanciamento.
 *
 * Implementazione:
 * - Identifica il nodo `x` (figlio sinistro di `y`) e il sottoalbero `T2` (figlio destro di `x`).
 * - Riorganizza i puntatori: `x` diventa la nuova radice, `y` diventa il figlio destro di `x`,
 * e `T2` diventa il figlio sinistro di `y`.
 * - Aggiorna i campi `altezza` e `massimo` prima per `y` e poi per `x`,
 * poiché `y` è ora un figlio di `x` e la sua altezza e massimo dipendono da `T2`.
 *
 * Esempio grafico:
 *  y                  x
 * / \                / \
 * x   T3   ----->    T1  y
 * / \                    / \
 * T1 T2                  T2  T3
 *
 * Parametri:
 * y: il nodo su cui eseguire la rotazione (l'attuale radice del sottoalbero sbilanciato a sinistra).
 *
 * Pre-condizioni:
 * - `y` non deve essere NULL.
 * - `y->sinistra` (il nodo `x`) non deve essere NULL.
 *
 * Post-condizioni:
 * - Restituisce un puntatore alla nuova radice del sottoalbero bilanciato (il nodo `x`).
 *
 * Side-effect:
 * - Modifica i puntatori `sinistra` e `destra` dei nodi coinvolti.
 * - Aggiorna i campi `altezza` e `massimo` dei nodi `x` e `y`.
 */
static struct nodo *ruota_destra(struct nodo *y) {
    struct nodo *x = y->sinistra;
    struct nodo *T2 = x->destra;

    x->destra = y;
    y->sinistra = T2;

    aggiorna_nodo(y); // y è diventato figlio, aggiorna prima y
    aggiorna_nodo(x); // x è diventato padre, aggiorna dopo x

    return x;
}

/*
 * Funzione: ruota_sinistra
 * ------------------------
 * Esegue una rotazione a sinistra sull'albero AVL per ripristinare il bilanciamento.
 *
 * Implementazione:
 * - Identifica il nodo `y` (figlio destro di `x`) e il sottoalbero `T2` (figlio sinistro di `y`).
 * - Riorganizza i puntatori: `y` diventa la nuova radice, `x` diventa il figlio sinistro di `y`,
 * e `T2` diventa il figlio destro di `x`.
 * - Aggiorna i campi `altezza` e `massimo` prima per `x` e poi per `y`,
 * poiché `x` è ora un figlio di `y` e la sua altezza e massimo dipendono da `T2`.
 *
 * Esempio grafico:
 *  x                  y
 * / \                / \
 * T1  y    ----->    x   T3
 * / \               / \
 * T2 T3            T1 T2
 *
 * Parametri:
 * x: il nodo su cui eseguire la rotazione (l'attuale radice del sottoalbero sbilanciato a destra).
 *
 * Pre-condizioni:
 * - `x` non deve essere NULL.
 * - `x->destra` (il nodo `y`) non deve essere NULL.
 *
 * Post-condizioni:
 * - Restituisce un puntatore alla nuova radice del sottoalbero bilanciato (il nodo `y`).
 *
 * Side-effect:
 * - Modifica i puntatori `sinistra` e `destra` dei nodi coinvolti.
 * - Aggiorna i campi `altezza` e `massimo` dei nodi `x` e `y`.
 */
static struct nodo *ruota_sinistra(struct nodo *x) {
    struct nodo *y = x->destra;
    struct nodo *T2 = y->sinistra;

    y->sinistra = x;
    x->destra = T2;

    aggiorna_nodo(x); // x è diventato figlio, aggiorna prima x
    aggiorna_nodo(y); // y è diventato padre, aggiorna dopo y

    return y;
}

/*
 * Funzione: casi_bilanciamento
 * ---------------------------
 * Gestisce i casi di sbilanciamento in un albero AVL e applica le rotazioni necessarie
 * per ripristinare la proprietà AVL.
 *
 * Implementazione:
 * - Calcola il fattore di bilanciamento del `nodo` corrente (altezza figlio sinistro - altezza figlio destro).
 * - Se il fattore di bilanciamento è maggiore di 1 (sbilanciamento a sinistra):
 * - Determina se l'inserimento che ha causato lo sbilanciamento è avvenuto
 * nel sottoalbero sinistro-sinistro o sinistro-destro, confrontando `inizio` con l'inizio
 * della prenotazione nel figlio sinistro. Applica la rotazione a destra o la rotazione sinistra-destra.
 * - Se il fattore di bilanciamento è minore di -1 (sbilanciamento a destra):
 * - Determina se l'inserimento è avvenuto nel sottoalbero destro-destro o destro-sinistro,
 * confrontando `inizio` con l'inizio della prenotazione nel figlio destro.
 * Applica la rotazione a sinistra o la rotazione destra-sinistra.
 * - Se il nodo è bilanciato (fattore tra -1 e 1), lo restituisce senza modifiche.
 *
 * Parametri:
 * nodo: il nodo potenzialmente sbilanciato da bilanciare.
 * inizio: il timestamp di inizio della prenotazione appena inserita, usato per distinguere
 * tra i sotto-casi di rotazione doppia (es. Left-Left vs Left-Right).
 *
 * Pre-condizioni:
 * - `nodo` non deve essere NULL.
 *
 * Post-condizioni:
 * - Restituisce la nuova radice del sottoalbero, garantendo che le proprietà AVL siano mantenute.
 *
 * Side-effect:
 * - Modifica la struttura dell'albero tramite rotazioni.
 * - Aggiorna i campi `altezza` e `massimo` dei nodi coinvolti nelle rotazioni.
 */
static struct nodo *casi_bilanciamento(struct nodo *nodo, time_t inizio) {
    int bilancio = altezza(nodo->sinistra) - altezza(nodo->destra);

    // Caso Sinistra-Sinistra o Sinistra-Destra
    if (bilancio > 1 && nodo->sinistra) {
        time_t inizio_l = inizio_intervallo(ottieni_intervallo_prenotazione(nodo->sinistra->prenotazione));
        if (inizio < inizio_l) // Inserimento nel sottoalbero sinistro-sinistro (LL)
            return ruota_destra(nodo);
        // Inserimento nel sottoalbero sinistro-destro (LR)
        nodo->sinistra = ruota_sinistra(nodo->sinistra);
        return ruota_destra(nodo);
    }

    // Caso Destra-Destra o Destra-Sinistra
    if (bilancio < -1 && nodo->destra) {
        time_t inizio_r = inizio_intervallo(ottieni_intervallo_prenotazione(nodo->destra->prenotazione));
        if (inizio > inizio_r) // Inserimento nel sottoalbero destro-destro (RR)
            return ruota_sinistra(nodo);
        // Inserimento nel sottoalbero destro-sinistro (RL)
        nodo->destra = ruota_destra(nodo->destra);
        return ruota_sinistra(nodo);
    }

    return nodo; // Il nodo è già bilanciato
}

/*
 * Funzione: distruggi_nodo_prenotazioni
 * -------------------------------------
 * Libera la memoria allocata per un singolo nodo dell'albero delle prenotazioni.
 *
 * Implementazione:
 * - Se il `nodo` è NULL, non fa nulla.
 * - Chiama `distruggi_prenotazione` per deallocare la memoria associata all'oggetto
 * `Prenotazione` contenuto nel nodo (poiché la prenotazione è stata allocata dinamicamente).
 * - Libera la memoria del nodo stesso.
 *
 * Parametri:
 * nodo: il puntatore al nodo da distruggere.
 *
 * Pre-condizioni:
 * - `nodo` può essere NULL (gestito internamente).
 *
 * Post-condizioni:
 * - La memoria del nodo e della sua prenotazione associata viene liberata.
 *
 * Side-effect:
 * - Dealloca memoria dinamicamente.
 */
static void distruggi_nodo_prenotazioni(struct nodo *nodo) {
    if (!nodo) return;

    distruggi_prenotazione(nodo->prenotazione); // Dealloca la prenotazione
    free(nodo); // Dealloca il nodo
}

/*
 * Funzione: _distruggi_prenotazioni
 * --------------------------------
 * Funzione ausiliaria ricorsiva per deallocare tutti i nodi di un albero AVL delle prenotazioni.
 *
 * Implementazione:
 * - Esegue una visita in post-order dell'albero (sinistra, destra, radice).
 * - Visita ricorsivamente il figlio sinistro del `nodo`.
 * - Visita ricorsivamente il figlio destro del `nodo`.
 * - Dopo aver deallocato i figli, chiama `distruggi_nodo_prenotazioni` per liberare
 * la memoria del `nodo` corrente e della sua prenotazione.
 *
 * Parametri:
 * nodo: la radice del sottoalbero da distruggere.
 *
 * Pre-condizioni:
 * - `nodo` può essere NULL (base della ricorsione).
 *
 * Post-condizioni:
 * - Tutti i nodi nel sottoalbero radicato in `nodo` e le loro prenotazioni associate
 * vengono deallocati ricorsivamente.
 *
 * Side-effect:
 * - Dealloca memoria dinamicamente per tutti i nodi e le prenotazioni dell'albero.
 */
static void _distruggi_prenotazioni(struct nodo *nodo) {
    if (!nodo) return;

    _distruggi_prenotazioni(nodo->sinistra);
    _distruggi_prenotazioni(nodo->destra);
    distruggi_nodo_prenotazioni(nodo);
}

/*
 * Funzione: aggiungi_prenotazione_t
 * ---------------------------------
 * Funzione ricorsiva ausiliaria per aggiungere una prenotazione all'albero AVL.
 *
 * Implementazione:
 * - Caso base: Se `albero` è NULL, crea un nuovo nodo con la `prenotazione` e lo restituisce.
 * - Verifica sovrapposizione: Ottiene gli intervalli della prenotazione nel nodo corrente
 * e della nuova prenotazione. Se si sovrappongono, restituisce NULL per indicare un conflitto.
 * - Inserimento ricorsivo:
 * - Se il timestamp di inizio della nuova prenotazione è minore di quello del nodo corrente,
 * tenta di inserire a sinistra.
 * - Altrimenti, tenta di inserire a destra.
 * - Se la chiamata ricorsiva restituisce NULL (indicando una sovrapposizione a un livello inferiore),
 * propaga il fallimento restituendo NULL.
 * - Aggiornamento e bilanciamento: Dopo l'inserimento ricorsivo, `aggiorna_nodo` per ricalcolare
 * altezza e massimo del nodo corrente. Infine, `casi_bilanciamento` viene chiamato per
 * ripristinare la proprietà AVL se necessario, e la nuova radice del sottoalbero viene restituita.
 *
 * Parametri:
 * albero: la radice del sottoalbero corrente in cui tentare l'inserimento.
 * prenotazione: la prenotazione da aggiungere.
 *
 * Pre-condizioni:
 * - `prenotazione` non deve essere NULL.
 *
 * Post-condizioni:
 * - Restituisce la nuova radice del sottoalbero dopo l'inserimento e il bilanciamento.
 * - Restituisce NULL se la prenotazione si sovrappone con una esistente o in caso di errore di allocazione.
 *
 * Side-effect:
 * - Modifica la struttura dell'albero.
 * - Può allocare memoria per un nuovo nodo.
 */
static struct nodo *aggiungi_prenotazione_t(struct nodo *albero, Prenotazione prenotazione) {
    if (!prenotazione) return NULL;
    if (!albero) return nuovo_nodo(prenotazione);

    Intervallo intervallo_albero = ottieni_intervallo_prenotazione(albero->prenotazione);
    Intervallo nuovo_intervallo = ottieni_intervallo_prenotazione(prenotazione);

    if (intervalli_si_sovrappongono(nuovo_intervallo, intervallo_albero)) {
        return NULL; // Rilevata sovrapposizione
    }

    time_t inizio_albero = inizio_intervallo(intervallo_albero);
    time_t nuovo_inizio = inizio_intervallo(nuovo_intervallo);

    if (nuovo_inizio < inizio_albero) {
        albero->sinistra = aggiungi_prenotazione_t(albero->sinistra, prenotazione);
        // Se la chiamata ricorsiva a sinistra ha fallito per sovrapposizione, propagala.
        // La condizione `nuovo_inizio < inizio_albero` è un'euristica per il debugging
        // o per chiarire il contesto del fallimento.
        if (albero->sinistra == NULL && nuovo_inizio < inizio_albero) {
            return NULL; // Propagazione di fallimento per sovrapposizione
        }
    } else {
        albero->destra = aggiungi_prenotazione_t(albero->destra, prenotazione);
        // Se la chiamata ricorsiva a destra ha fallito per sovrapposizione, propagala.
        if (albero->destra == NULL && nuovo_inizio >= inizio_albero) {
             return NULL; // Propagazione di fallimento per sovrapposizione
        }
    }

    aggiorna_nodo(albero);
    return casi_bilanciamento(albero, nuovo_inizio);
}

/*
 * Funzione: controlla_prenotazione_t
 * ----------------------------------
 * Verifica ricorsivamente la presenza di una sovrapposizione tra un dato intervallo
 * e qualsiasi prenotazione nell'albero delle prenotazioni.
 *
 * Implementazione:
 * - Caso base: Se la `radice` è NULL, non ci sono prenotazioni nel sottoalbero,
 * quindi l'intervallo è disponibile (restituisce OK).
 * - Verifica il nodo corrente: Controlla se l'intervallo del nodo attuale si sovrappone
 * con l'intervallo `i` da controllare. Se sì, restituisce OCCUPATO.
 * - Ottimizzazione con campo `massimo`: Se il figlio sinistro esiste E il suo campo `massimo`
 * (che rappresenta la fine più lontana di qualsiasi intervallo nel sottoalbero sinistro)
 * è maggiore o uguale all'inizio dell'intervallo `i`, allora c'è la possibilità
 * di una sovrapposizione nel sottoalbero sinistro. In tal caso, prosegue la ricerca ricorsivamente.
 * Questa euristica permette di evitare di visitare sottoalberi non pertinenti.
 * - Ricerca nel figlio destro: Se la ricerca nel figlio sinistro non ha trovato sovrapposizioni
 * (o se non è stata eseguita), prosegue la ricerca ricorsivamente nel figlio destro.
 *
 * Parametri:
 * radice: la radice del sottoalbero corrente da controllare.
 * i: l'intervallo di tempo da verificare per la disponibilità.
 *
 * Pre-condizioni:
 * - `i` non deve essere NULL.
 *
 * Post-condizioni:
 * - Restituisce `OCCUPATO` (1) se `i` si sovrappone con almeno una prenotazione esistente.
 * - Restituisce `OK` (0) se `i` non si sovrappone con nessuna prenotazione nell'albero.
 *
 * Side-effect:
 * - Nessuno. La funzione esegue solo una ricerca.
 */
static Byte controlla_prenotazione_t(struct nodo *radice, Intervallo i) {
    if (!radice) return OK;

    Intervallo i_attuale = ottieni_intervallo_prenotazione(radice->prenotazione);
    time_t inizio_intervallo_da_cercare = inizio_intervallo(i);

    if (intervalli_si_sovrappongono(i_attuale, i))
        return OCCUPATO;

    // Controlla il sottoalbero sinistro solo se il suo 'massimo' supera l'inizio dell'intervallo da cercare.
    // Questo è il cuore dell'ottimizzazione dell'Interval Tree.
    if (radice->sinistra && radice->sinistra->massimo >= inizio_intervallo_da_cercare) {
        Byte risultato_sinistra = controlla_prenotazione_t(radice->sinistra, i);
        if (risultato_sinistra == OCCUPATO) return OCCUPATO;
    }

    // Se non c'è sovrapposizione a sinistra, controlla il sottoalbero destro.
    // Per gli alberi di intervalli, è spesso necessario controllare entrambi i lati.
    return controlla_prenotazione_t(radice->destra, i);
}

/*
 * Funzione: trova_minimo
 * ----------------------
 * Trova il nodo con la chiave (timestamp di inizio prenotazione) più piccola
 * in un dato sottoalbero.
 *
 * Implementazione:
 * - Partendo dalla `radice` del sottoalbero, si sposta iterativamente
 * verso il figlio sinistro finché non raggiunge il nodo più a sinistra.
 * Questo nodo rappresenta l'elemento con la chiave minima in un BST.
 *
 * Parametri:
 * nodo: la radice del sottoalbero in cui cercare il minimo.
 *
 * Pre-condizioni:
 * - `nodo` non deve essere NULL (se si chiama su un albero vuoto o un sottoalbero nullo,
 * il comportamento non è definito se non gestito dal chiamante).
 *
 * Post-condizioni:
 * - Restituisce un puntatore al nodo che contiene la prenotazione con il timestamp di inizio più piccolo
 * nel sottoalbero specificato.
 *
 * Side-effect:
 * - Nessuno. La funzione esegue solo una ricerca.
 */
static struct nodo *trova_minimo(struct nodo *nodo) {
    while (nodo->sinistra)
        nodo = nodo->sinistra;
    return nodo;
}

/*
 * Funzione: cancella_prenotazione_t
 * ---------------------------------
 * Rimuove ricorsivamente una prenotazione dall'albero AVL, identificandola
 * tramite il suo intervallo di tempo.
 *
 * Implementazione:
 * - **Caso Base:** Se la `radice` è NULL, la prenotazione non è presente; restituisce NULL.
 * - **Ricerca:** Se l'intervallo della prenotazione nel nodo corrente non corrisponde
 * all'intervallo `i` da rimuovere:
 * - Continua la ricerca ricorsivamente nel sottoalbero sinistro o destro,
 * basandosi sulla comparazione degli intervalli. È presente un controllo
 * basato sul campo `massimo` per ottimizzare la ricerca nel sottoalbero sinistro,
 * anche se per la cancellazione diretta di una chiave, una semplice navigazione
 * basata sul `time_t inizio_intervallo` sarebbe sufficiente.
 * - **Nodo Trovato:** Se l'intervallo del nodo corrente corrisponde a `i`:
 * - **Casi 0 o 1 figlio:** Se il nodo non ha figli o ne ha uno solo, il nodo viene
 * deallocato e sostituito direttamente dal suo unico figlio (o NULL). `*controllo` è impostato a 1.
 * - **Caso 2 figli:** Trova il successore in-order (il nodo con il valore minimo
 * nel sottoalbero destro). La prenotazione del nodo corrente viene sostituita
 * con una **duplicazione** della prenotazione del successore. Successivamente,
 * il successore in-order viene rimosso ricorsivamente dal sottoalbero destro.
 * `*controllo` viene impostato a 1 se la sottocancellazione ha successo.
 * - **Ribilanciamento:** Dopo ogni operazione ricorsiva (sia per la ricerca che per la cancellazione),
 * i campi `altezza` e `massimo` del nodo vengono aggiornati, e la funzione `casi_bilanciamento`
 * viene chiamata per ripristinare l'equilibrio AVL se necessario.
 *
 * Parametri:
 * radice: la radice del sottoalbero corrente.
 * i: l'intervallo di tempo della prenotazione da rimuovere.
 * controllo: puntatore a un `Byte` che viene impostato a 1 se la prenotazione è stata effettivamente rimossa,
 * altrimenti rimane a 0.
 *
 * Pre-condizioni:
 * - `i` non deve essere NULL.
 *
 * Post-condizioni:
 * - Restituisce la nuova radice del sottoalbero dopo l'operazione di cancellazione e bilanciamento.
 * - `*controllo` è impostato a 1 se la prenotazione è stata trovata e rimossa, 0 altrimenti.
 *
 * Side-effect:
 * - Modifica la struttura dell'albero.
 * - Dealloca memoria per il nodo rimosso e la sua prenotazione.
 * - Potrebbe allocare memoria per la duplicazione della prenotazione nel caso di 2 figli.
 */
static struct nodo *cancella_prenotazione_t(struct nodo *radice, Intervallo i, Byte *controllo) {
    if (!radice) return radice; // Prenotazione non trovata

    Intervallo i_attuale = ottieni_intervallo_prenotazione(radice->prenotazione);
    time_t inizio_intervallo_da_rimuovere = inizio_intervallo(i);

    if (compara_intervalli(i_attuale, i) == 0) { // Trovato il nodo da rimuovere
        // Gestione casi di cancellazione: 0, 1 o 2 figli
        if (!radice->sinistra || !radice->destra) {
            struct nodo *temp = radice->sinistra ? radice->sinistra : radice->destra;
            distruggi_nodo_prenotazioni(radice);
            *controllo = 1;
            return temp;
        } else { // Nodo con due figli
            struct nodo *temp = trova_minimo(radice->destra); // Trova il successore in-order
            Intervallo i_min_temp = ottieni_intervallo_prenotazione(temp->prenotazione);

            // Sostituisci la prenotazione del nodo corrente con quella del successore in-order
            distruggi_prenotazione(radice->prenotazione);
            radice->prenotazione = duplica_prenotazione(temp->prenotazione); // ATTENZIONE: qui si duplica

            Byte controllo_dx = 0; // Variabile di controllo per la sottocancellazione
            radice->destra = cancella_prenotazione_t(radice->destra, i_min_temp, &controllo_dx);
            if (controllo_dx)
                *controllo = 1; // Se il successore è stato rimosso, allora l'operazione è riuscita
        }
    }
    // Ricerca ricorsiva della prenotazione da rimuovere
    // Per una cancellazione precisa, la condizione dovrebbe essere basata solo sul confronto delle chiavi
    // (inizio_intervallo), non sul campo 'massimo'. Il campo 'massimo' è per la ricerca di sovrapposizioni.
    else if (inizio_intervallo_da_rimuovere < inizio_intervallo(i_attuale)) {
        radice->sinistra = cancella_prenotazione_t(radice->sinistra, i, controllo);
    }
    else {
        radice->destra = cancella_prenotazione_t(radice->destra, i, controllo);
    }

    if (!radice) return radice; // Se il nodo è stato rimosso, non bilanciare

    aggiorna_nodo(radice);
    return casi_bilanciamento(radice, inizio_intervallo(i_attuale)); // Bilancia l'albero
}

/*
 * Funzione: prenotazioni_in_vettore_t
 * -----------------------------------
 * Funzione ausiliaria ricorsiva per copiare tutte le prenotazioni di un albero
 * in un array, mantenendo l'ordine crescente (visita in-order).
 *
 * Implementazione:
 * - Caso base: Se la `radice` è NULL, la ricorsione termina.
 * - Visita il sottoalbero sinistro ricorsivamente.
 * - Al ritorno dal sottoalbero sinistro, copia la `prenotazione` del nodo corrente
 * nell'array `result` all'indice specificato da `*index`, e poi incrementa `*index`.
 * - Visita il sottoalbero destro ricorsivamente.
 * Questa sequenza garantisce che le prenotazioni vengano aggiunte all'array
 * in ordine cronologico di inizio.
 *
 * Parametri:
 * radice: la radice del sottoalbero corrente da visitare.
 * result: il puntatore all'array di `Prenotazione` in cui copiare i dati.
 * index: un puntatore a un intero che tiene traccia della posizione corrente
 * nel `result` array, garantendo che le prenotazioni siano inserite
 * sequenzialmente.
 *
 * Pre-condizioni:
 * - `result` non deve essere NULL.
 * - `index` non deve essere NULL.
 * - L'array `result` deve avere una dimensione sufficiente per contenere tutte le prenotazioni.
 *
 * Post-condizioni:
 * - L'array `result` viene popolato con i puntatori alle prenotazioni in ordine crescente.
 * - Il valore puntato da `index` riflette il numero totale di prenotazioni copiate.
 *
 * Side-effect:
 * - Modifica il contenuto dell'array `result` e il valore di `*index`.
 */
static void prenotazioni_in_vettore_t(struct nodo *radice, Prenotazione *result, int *index) {
    if (!radice) return;

    prenotazioni_in_vettore_t(radice->sinistra, result, index);
    result[*index] = duplica_prenotazione(radice->prenotazione);
    (*index)++;
    prenotazioni_in_vettore_t(radice->destra, result, index);
}

/*
 * Funzione: crea_prenotazioni
 * ---------------------------
 * Crea e inizializza una nuova struttura `Prenotazioni` (un albero AVL vuoto).
 *
 * Implementazione:
 * - Alloca memoria per una nuova struttura `struct albero`.
 * - Se l'allocazione ha successo, inizializza il puntatore `radice` a NULL
 * e `num_nodi` a 0, indicando che l'albero è inizialmente vuoto.
 *
 * Parametri:
 * Nessuno.
 *
 * Pre-condizioni:
 * - Nessuna.
 *
 * Post-condizioni:
 * - Restituisce un puntatore a una nuova struttura `Prenotazioni` inizializzata
 * se l'allocazione ha successo.
 * - Restituisce NULL in caso di fallimento dell'allocazione di memoria.
 *
 * Side-effect:
 * - Alloca memoria dinamicamente per la struttura `Prenotazioni`. Questa memoria
 * deve essere liberata successivamente chiamando `distruggi_prenotazioni`.
 */
Prenotazioni crea_prenotazioni() {
    Prenotazioni albero = malloc(sizeof(struct albero));
    if (!albero) return NULL;

    albero->num_nodi = 0;
    albero->radice = NULL;
    return albero;
}

/*
 * Funzione: distruggi_prenotazioni
 * --------------------------------
 * Dealloca tutta la memoria associata a una struttura `Prenotazioni`,
 * inclusi tutti i nodi dell'albero e le `Prenotazione` contenute in essi.
 *
 * Implementazione:
 * - Se `prenotazioni` è NULL, la funzione termina senza fare nulla.
 * - Chiama la funzione ausiliaria ricorsiva `_distruggi_prenotazioni`,
 * passando la radice dell'albero. Questa funzione si occupa di
 * deallocare ricorsivamente tutti i nodi in post-order.
 * - Dopo che tutti i nodi sono stati deallocati, imposta `radice` a NULL
 * e `num_nodi` a 0 per pulire lo stato dell'albero.
 * - Infine, libera la memoria della struttura `Prenotazioni` stessa.
 *
 * Parametri:
 * prenotazioni: il puntatore alla struttura `Prenotazioni` da distruggere.
 *
 * Pre-condizioni:
 * - `prenotazioni` può essere NULL (gestito internamente per robustezza).
 *
 * Post-condizioni:
 * - Tutta la memoria dinamicamente allocata per l'albero delle prenotazioni
 * e i suoi nodi viene liberata.
 *
 * Side-effect:
 * - Dealloca memoria dinamicamente.
 */
void distruggi_prenotazioni(Prenotazioni prenotazioni) {
    if (!prenotazioni) return;
    if(prenotazioni->num_nodi) _distruggi_prenotazioni(prenotazioni->radice);
    free(prenotazioni);
}

/*
 * Funzione: aggiungi_prenotazione
 * -------------------------------
 * Tenta di aggiungere una nuova prenotazione all'albero delle prenotazioni.
 *
 * Implementazione:
 * - Verifica che `albero` e `prenotazione` non siano NULL.
 * - Chiama la funzione ausiliaria ricorsiva `aggiungi_prenotazione_t` per
 * gestire l'inserimento effettivo della prenotazione, il controllo delle
 * sovrapposizioni e il bilanciamento dell'albero.
 * - Analizza il valore di ritorno di `aggiungi_prenotazione_t`:
 * - Se `nuova_radice` è NULL e la radice originale dell'albero non era NULL,
 * significa che l'inserimento è fallito a causa di una sovrapposizione esistente,
 * quindi restituisce `OCCUPATO`.
 * - Se `nuova_radice` è NULL e la radice originale era NULL (ovvero, si è tentato
 * di inserire il primo nodo ma l'allocazione è fallita), restituisce 0 (errore generico).
 * - Se `nuova_radice` non è NULL, l'inserimento è riuscito. La radice dell'albero
 * viene aggiornata e il contatore `num_nodi` viene incrementato. Restituisce `OK`.
 *
 * Parametri:
 * albero: il puntatore alla struttura `Prenotazioni` a cui aggiungere la prenotazione.
 * prenotazione: la prenotazione da aggiungere.
 *
 * Pre-condizioni:
 * - `albero` non deve essere NULL.
 * - `prenotazione` non deve essere NULL.
 *
 * Post-condizioni:
 * - Restituisce `OK` (0) se l'inserimento è avvenuto con successo e senza sovrapposizioni.
 * - Restituisce `OCCUPATO` (1) se la `prenotazione` si sovrappone con una esistente.
 * - Restituisce 0 in caso di altri errori (es. fallimento dell'allocazione).
 *
 * Side-effect:
 * - Modifica la struttura dell'albero `prenotazioni` aggiungendo un nodo.
 * - Incrementa il contatore `num_nodi`.
 * - Può allocare memoria (tramite `aggiungi_prenotazione_t`).
 */
Byte aggiungi_prenotazione(Prenotazioni albero, Prenotazione prenotazione) {
    if (!albero || !prenotazione) return 0;

    struct nodo *nuova_radice = aggiungi_prenotazione_t(albero->radice, prenotazione);
    if (nuova_radice == NULL && albero->radice != NULL) {
        return OCCUPATO; // Inserimento fallito per sovrapposizione
    } else if (nuova_radice == NULL && albero->radice == NULL) {
        // Questo caso si verifica se `nuovo_nodo` in `aggiungi_prenotazione_t` restituisce NULL
        // quando `albero->radice` è inizialmente NULL (primo inserimento fallito).
        return OCCUPATO; // Errore generico (es. allocazione fallita per il primo nodo)
    }

    albero->radice = nuova_radice;
    albero->num_nodi++;
    return OK;
}

/*
 * Funzione: controlla_prenotazione
 * --------------------------------
 * Verifica se un dato intervallo di tempo è disponibile per una nuova prenotazione
 * nell'albero delle prenotazioni, ovvero se non si sovrappone con alcuna prenotazione esistente.
 *
 * Implementazione:
 * - Verifica che i puntatori `prenotazioni` e `i` non siano NULL.
 * - Delega il controllo effettivo alla funzione ausiliaria ricorsiva `controlla_prenotazione_t`,
 * che implementa la logica di ricerca efficiente specifica per gli alberi di intervalli
 * (utilizzando il campo `massimo` per ottimizzare le traversate).
 * - Restituisce il risultato direttamente da `controlla_prenotazione_t`.
 *
 * Parametri:
 * prenotazioni: il puntatore alla struttura `Prenotazioni` da interrogare.
 * i: l'intervallo di tempo da verificare.
 *
 * Pre-condizioni:
 * - `prenotazioni` non deve essere NULL.
 * - `i` non deve essere NULL.
 *
 * Post-condizioni:
 * - Restituisce `OCCUPATO` (1) se l'intervallo `i` si sovrappone con almeno una prenotazione esistente.
 * - Restituisce `OK` (0) se l'intervallo `i` è completamente disponibile.
 * - Restituisce `OK` (0) se `prenotazioni` o `i` sono NULL (comportamento robusto).
 *
 * Side-effect:
 * - Nessuno. La funzione esegue solo una query sullo stato dell'albero.
 */
Byte controlla_prenotazione(Prenotazioni prenotazioni, Intervallo i) {
    if (!prenotazioni || !i) return OK;
    return controlla_prenotazione_t(prenotazioni->radice, i);
}

/*
 * Funzione: cancella_prenotazione
 * ------------------------------
 * Rimuove una prenotazione specifica dall'albero delle prenotazioni,
 * identificandola tramite il suo intervallo di tempo.
 *
 * Implementazione:
 * - Verifica che i puntatori `prenotazioni` e `i` non siano NULL.
 * - Inizializza una variabile `controllo` a 0. Questa variabile verrà utilizzata
 * dalla funzione ricorsiva `cancella_prenotazione_t` per segnalare
 * se la prenotazione è stata effettivamente trovata e rimossa.
 * - Chiama `cancella_prenotazione_t` per eseguire l'operazione di cancellazione
 * e ripristino dell'equilibrio AVL.
 * - Se `controllo` è stato impostato a 1 (significando che la prenotazione è stata rimossa),
 * decrementa il contatore `num_nodi` nella struttura `Prenotazioni`.
 * - Restituisce il valore finale di `controllo`.
 *
 * Parametri:
 * prenotazioni: il puntatore alla struttura `Prenotazioni` da cui rimuovere la prenotazione.
 * i: l'intervallo di tempo della prenotazione da rimuovere.
 *
 * Pre-condizioni:
 * - `prenotazioni` non deve essere NULL.
 * - `i` non deve essere NULL.
 *
 * Post-condizioni:
 * - Restituisce 1 se la prenotazione corrispondente all'intervallo `i` è stata
 * trovata e rimossa con successo.
 * - Restituisce 0 se la prenotazione non è stata trovata o in caso di input NULL.
 *
 * Side-effect:
 * - Modifica la struttura dell'albero `prenotazioni`.
 * - Decrementa il contatore `num_nodi` se la cancellazione ha successo.
 * - Dealloca memoria (tramite `cancella_prenotazione_t`).
 */
Byte cancella_prenotazione(Prenotazioni prenotazioni, Intervallo i) {
    if (!prenotazioni || !i) return 0;

    Byte controllo = 0; // Verrà impostato a 1 se la cancellazione ha successo
    prenotazioni->radice = cancella_prenotazione_t(prenotazioni->radice, i, &controllo);
    if (controllo) prenotazioni->num_nodi--; // Decrementa il contatore solo se la prenotazione è stata rimossa
    return controllo;
}

/*
 * Funzione: ottieni_vettore_prenotazioni_ordinate
 * -----------------------------------------------
 * Estrae tutte le prenotazioni dall'albero e le restituisce in un array
 * allocato dinamicamente, ordinate cronologicamente in base al loro timestamp di inizio.
 *
 * Implementazione:
 * - Verifica che `prenotazioni` e `size` non siano NULL.
 * - Alloca un array di puntatori a `Prenotazione` di dimensione pari al numero
 * corrente di nodi nell'albero (`num_nodi`).
 * - Inizializza un `index` a 0.
 * - Chiama la funzione ausiliaria ricorsiva `prenotazioni_in_vettore_t` per
 * popolare l'array. Questa funzione esegue una visita in-order dell'albero,
 * garantendo che le prenotazioni siano copiate nell'array in ordine crescente.
 * - Imposta il valore puntato da `size` con il numero effettivo di prenotazioni copiate.
 * - Restituisce il puntatore all'array.
 *
 * Parametri:
 * prenotazioni: il puntatore alla struttura `Prenotazioni` da cui estrarre le prenotazioni.
 * size: un puntatore a un `unsigned int` dove verrà salvata la dimensione dell'array risultante.
 *
 * Pre-condizioni:
 * - `prenotazioni` non deve essere NULL.
 * - `size` non deve essere NULL.
 *
 * Post-condizioni:
 * - Restituisce un puntatore a un array di `Prenotazione` allocato dinamicamente
 * contenente tutte le prenotazioni dell'albero, ordinate per data di inizio.
 * - `*size` conterrà il numero di elementi nell'array.
 * - Restituisce NULL in caso di errori (es. fallimento dell'allocazione di memoria o input NULL).
 *
 * Side-effect:
 * - Alloca memoria dinamicamente per l'array risultante. La memoria deve essere
 * liberata dal chiamante (`free`).
 */
Prenotazione *ottieni_vettore_prenotazioni_ordinate(Prenotazioni prenotazioni, unsigned int *size) {
    if (!prenotazioni || !size) return NULL;

    unsigned int num_nodi = prenotazioni->num_nodi;
    Prenotazione *result = malloc(sizeof(Prenotazione) * num_nodi);
    if (!result) return NULL;

    int index = 0;
    prenotazioni_in_vettore_t(prenotazioni->radice, result, &index);
    *size = num_nodi;
    return result;
}

/*
 * Funzione: ottieni_vettore_prenotazioni_per_file
 * ----------------------------------------------
 * Estrae tutte le prenotazioni dall'albero e le restituisce in un array
 * allocato dinamicamente, in ordine di livello (BFS - Breadth-First Search).
 * Questo metodo è particolarmente utile per salvare l'albero su file e poi
 * ricostruirlo, poiché preserva la struttura BFS indipendentemente dalle rotazioni AVL.
 *
 * Implementazione:
 * - Verifica che `prenotazioni` e `size` non siano NULL.
 * - Alloca un array di puntatori a `Prenotazione` di dimensione pari al numero
 * corrente di nodi nell'albero.
 * - Crea una coda (`Coda` dal modulo `coda.h`) per gestire la visita BFS.
 * - Se la radice dell'albero non è NULL, la aggiunge alla coda.
 * - Entra in un ciclo che continua finché la coda non è vuota:
 * - Estrae un nodo dalla coda.
 * - Copia il puntatore alla `prenotazione` del nodo estratto nell'array `result`.
 * - Se il nodo ha figli sinistro o destro, li aggiunge alla coda per una futura elaborazione.
 * - Una volta che tutti i nodi sono stati visitati, imposta il valore puntato da `size`
 * con il numero effettivo di prenotazioni copiate.
 * - Distrugge la coda (liberando la sua memoria interna) e restituisce il puntatore all'array.
 *
 * Parametri:
 * prenotazioni: il puntatore alla struttura `Prenotazioni` da cui estrarre le prenotazioni.
 * size: un puntatore a un `unsigned int` dove verrà salvata la dimensione dell'array risultante.
 *
 * Pre-condizioni:
 * - `prenotazioni` non deve essere NULL.
 * - `size` non deve essere NULL.
 *
 * Post-condizioni:
 * - Restituisce un puntatore a un array di `Prenotazione` allocato dinamicamente
 * contenente tutte le prenotazioni dell'albero in ordine di livello.
 * - `*size` conterrà il numero di elementi nell'array.
 * - Restituisce NULL in caso di errori (es. fallimento dell'allocazione di memoria o input NULL).
 *
 * Side-effect:
 * - Alloca memoria dinamicamente per l'array `result` e per la coda temporanea.
 * La memoria dell'array restituito deve essere liberata dal chiamante (`free`).
 */
Prenotazione *ottieni_vettore_prenotazioni_per_file(Prenotazioni prenotazioni, unsigned int *size) {
    if (!prenotazioni || !size) return NULL;

    unsigned int num_nodi = prenotazioni->num_nodi;
    Prenotazione *result = malloc(sizeof(Prenotazione) * num_nodi);
    if (!result) {
        return NULL;
    }

    unsigned int i = 0;
    Coda q = crea_coda(); // Crea una coda per la BFS
    if (!q) {
        free(result);
        return NULL;
    }

    if (prenotazioni->radice != NULL) {
        // Aggiungi la radice alla coda
        if (aggiungi_in_coda(prenotazioni->radice, q) < 0) {
            free(result);
            distruggi_coda(q, NULL); // Assicurati di distruggere la coda anche in caso di fallimento
            return NULL;
        }
    }

    while (!coda_vuota(q)) {
        struct nodo *temp = (struct nodo *)rimuovi_dalla_coda(q);
        if (!temp) continue; // Dovrebbe accadere solo se la coda è stata corrotta

        result[i++] = duplica_prenotazione(temp->prenotazione); // Aggiungi la prenotazione all'array

        // Aggiungi i figli alla coda (se esistono)
        if (temp->sinistra) {
            if (aggiungi_in_coda(temp->sinistra, q) < 0) {
                free(result);
                distruggi_coda(q, NULL);
                return NULL;
            }
        }

        if (temp->destra) {
            if (aggiungi_in_coda(temp->destra, q) < 0) {
                free(result);
                distruggi_coda(q, NULL);
                return NULL;
            }
        }
    }

    *size = i; // Imposta la dimensione effettiva delle prenotazioni copiate
    distruggi_coda(q, NULL); // Libera la memoria della coda
    return result;
}

/*
 * Funzione: ottieni_intervallo_disponibile_t
 * ------------------------------------------
 * Restituisce un intervallo disponibile all'interno di un intervallo dato `i`,
 * verificando eventuali sovrapposizioni con prenotazioni contenute in un albero binario
 * radicato in `radice`. Se si sovrappone con l'intervallo della prenotazione corrente,
 * restituisce il gap disponibile prima della prenotazione oppure NULL se non esiste.
 *
 * Implementazione:
 * - Verifica se la radice è NULL, in tal caso duplica e restituisce l'intervallo `i`.
 * - Ottiene l'intervallo della prenotazione memorizzata nel nodo `radice`.
 * - Calcola il tempo di inizio della ricerca come inizio dell'intervallo `i`.
 * - Se l'intervallo della prenotazione e l'intervallo `i` si sovrappongono:
 *   - Se l'inizio dell'intervallo prenotazione è dopo l'inizio della ricerca,
 *     crea e restituisce un intervallo che va dall'inizio di `i` fino all'inizio
 *     della prenotazione (gap disponibile).
 *   - Altrimenti restituisce NULL, indicando assenza di gap disponibile.
 *
 * Parametri:
 * radice: puntatore al nodo radice dell'albero binario di prenotazioni.
 * i: intervallo temporale da verificare per disponibilità.
 *
 * Pre-condizioni:
 * - `i` è un intervallo valido.
 * - `radice` è un puntatore a nodo valido o NULL.
 *
 * Post-condizioni:
 * - Restituisce un intervallo disponibile (gap) all'interno di `i` se trovato.
 * - Restituisce una copia di `i` se l'albero è vuoto (radice NULL).
 * - Restituisce NULL se non è disponibile alcun intervallo libero.
 *
 * Side-effect:
 * - Può allocare memoria per l'intervallo duplicato o creato.
 * - La memoria restituita deve essere gestita dal chiamante.
 */
static Intervallo ottieni_intervallo_disponibile_t(struct nodo *radice, Intervallo i) {
    if (!radice)
        return duplica_intervallo(i);

    Intervallo cur = ottieni_intervallo_prenotazione(radice->prenotazione);
    time_t start_cerca = inizio_intervallo(i);

    // 1) Se si sovrappone, viene restituito subito il gap prima o NULL
    if (intervalli_si_sovrappongono(cur, i)) {
        time_t s_cur = inizio_intervallo(cur);
        if (s_cur > start_cerca)
            return crea_intervallo(start_cerca, s_cur);
        else
            return NULL;
    }

    // 2) Provo a cercare nel sottoalbero sinistro, se ha potenziale
    if (radice->sinistra && radice->sinistra->massimo >= start_cerca) {
        Intervallo left = ottieni_intervallo_disponibile_t(radice->sinistra, i);
        if (left)
            return left;
        else
            return NULL;
    }

    // 3) Altrimenti cerco nel sottoalbero destro
    return ottieni_intervallo_disponibile_t(radice->destra, i);
}

/*
 * Funzione: ottieni_intervallo_disponibile
 * ----------------------------------------
 * Restituisce un intervallo disponibile all'interno di un intervallo dato `i`
 * cercando tra le prenotazioni memorizzate in una struttura `Prenotazioni`.
 *
 * Implementazione:
 * - Verifica se `prenotazioni` o `i` sono NULL; in tal caso restituisce NULL.
 * - Chiama la funzione `ottieni_intervallo_disponibile_t` passando la radice
 *   dell'albero interno alle prenotazioni e l'intervallo `i`.
 * - Restituisce il risultato ottenuto dalla funzione chiamata.
 *
 * Parametri:
 * prenotazioni: struttura contenente le prenotazioni (albero binario).
 * i: intervallo temporale da verificare per disponibilità.
 *
 * Pre-condizioni:
 * - `prenotazioni` deve essere un puntatore valido a una struttura `Prenotazioni` o NULL.
 * - `i` deve essere un intervallo valido o NULL.
 *
 * Post-condizioni:
 * - Restituisce un intervallo disponibile all'interno di `i` se trovato.
 * - Restituisce NULL se non ci sono intervalli disponibili o se input non valido.
 *
 * Side-effect:
 * - Nessuno diretto, ma la funzione chiamata può allocare memoria.
 * - La memoria dell'intervallo restituito deve essere gestita dal chiamante.
 */
Intervallo ottieni_intervallo_disponibile(Prenotazioni prenotazioni, Intervallo i){
    if(prenotazioni == NULL || i == NULL){
        return NULL;
    }

    return ottieni_intervallo_disponibile_t(prenotazioni->radice, i);
}
