#include <stdio.h>
#include <string.h>
#include "modelli/intervallo.h"
#include "modelli/prenotazione.h"
#include "modelli/veicolo.h"
#include "strutture_dati/lista.h"
#include "strutture_dati/prenotazioni.h"
#include "strutture_dati/tabella_veicoli.h"
#include "modelli/utente.h"
#include "strutture_dati/tabella_utenti.h"
#include "utils/md5.h"
#include "utils/utils.h"

#define GRANDEZZA_RIGA 500
#define MASSIMO_PERCORSO_FILE 1024

int txt_in_utenti(FILE *fp, TabellaUtenti tabella);

int txt_in_veicoli(FILE *fp, TabellaVeicoli tabella);

int test_case_uno(TabellaUtenti tabella_utenti, TabellaVeicoli tabella_veicoli);

int test_case_due(TabellaVeicoli tabella_veicoli);

int test_case_tre(TabellaUtenti tabella_utenti, TabellaVeicoli tabella_veicoli);

int compara_file(FILE *a, FILE *b);

int main(int argc, char **argv){
    if(argc < 4){
        printf("./test <test_suite_path> <utenti_path> <veicoli_path>\n");
        return -1;
    }

    unsigned numero_utenti = 20;
    unsigned numero_veicoli = 10;

    char *test_suite = argv[1];
    char *nome_file_utenti = argv[2];
    char *nome_file_veicoli = argv[3];

    FILE *file_test_suite = fopen(test_suite, "r");
    FILE *file_utenti = fopen(nome_file_utenti, "r");
    FILE *file_veicoli = fopen(nome_file_veicoli, "r");

    if(!(file_test_suite && file_utenti && file_veicoli)){
        printf("Errore apertura file utenti!\n");
        return -1;
    }

    TabellaUtenti tabella_utenti = crea_tabella_utenti(numero_utenti);
    if(txt_in_utenti(file_utenti, tabella_utenti) < 0){
        printf("Errore caricamento utenti!\n(Controlla il formato nome;cognome;email;password)");
        distruggi_tabella_utenti(tabella_utenti);
        return -1;
    }

    TabellaVeicoli tabella_veicoli = crea_tabella_veicoli(numero_veicoli);
    if(txt_in_veicoli(file_veicoli, tabella_veicoli)){
        printf("Errore caricamento utenti!\n(Controlla il formato targa;modello;posizione;tariffa;tipo)");
        return -1;
    }

    char linea[GRANDEZZA_RIGA];

    FILE *file_result = fopen("result.txt", "w");
    if(file_result == NULL){
        printf("Errore apertura file result.txt!\n");
        return -1;
    }

    while(fgets(linea, sizeof(linea), file_test_suite)){
        linea[strcspn(linea, "\n")] = 0;
        char *tc = strtok(linea, " ");
        if(strcmp(tc, "TC1") == 0){
            if(test_case_uno(tabella_utenti, tabella_veicoli) < 0){
                printf("Errore TC1\n");
                continue;
            }
        }
        if(strcmp(tc, "TC2") == 0){
            if(test_case_due(tabella_veicoli) < 0){
                printf("Errore TC2\n");
                continue;
            }
        }
        if(strcmp(tc, "TC3") == 0){
            if(test_case_tre(tabella_utenti, tabella_veicoli) < 0){
                printf("Errore TC3\n");
                continue;
            }
        }

        char nome_file_oracle[MASSIMO_PERCORSO_FILE] = {0};
        snprintf(nome_file_oracle, MASSIMO_PERCORSO_FILE, "%s/oracle.txt", tc);

        char nome_file_output[MASSIMO_PERCORSO_FILE] = {0};
        snprintf(nome_file_output, MASSIMO_PERCORSO_FILE, "%s/output.txt", tc);


        FILE *oracle_file = fopen(nome_file_oracle, "r");
        FILE *output_file = fopen(nome_file_output, "r");

        if((oracle_file == NULL) || (output_file == NULL)){
            printf("Errore apertura file oracle o output\n");
            return -1;
        }

        int risultato = compara_file(oracle_file, output_file);
        fprintf(file_result, "%s: %sHA SUPERATO IL TEST\n", tc, risultato ? "NON " : "");
    }

    return 0;
}

int txt_in_utenti(FILE *fp, TabellaUtenti tabella) {
    char linea[GRANDEZZA_RIGA];  // buffer abbastanza grande per una riga
    uint8_t password_hash[DIMENSIONE_PASSWORD];

    while (fgets(linea, sizeof(linea), fp)) {
        // rimuovi newline finale
        linea[strcspn(linea, "\n")] = 0;

        char *nome = strtok(linea, ";");
        char *cognome = strtok(NULL, ";");
        char *email = strtok(NULL, ";");
        char *password = strtok(NULL, ";");

        if (nome && cognome && email && password) {
            md5(password, strlen(password), password_hash);
            Utente u = crea_utente(email, password_hash, nome, cognome, CLIENTE);
            if(!aggiungi_utente_in_tabella(tabella, u)) return -1;
        } else {
            return -1;
        }
    }

    return 0;
}

int txt_in_veicoli(FILE *fp, TabellaVeicoli tabella){
    char linea[GRANDEZZA_RIGA];

    while (fgets(linea, sizeof(linea), fp)) {
        // rimuovi newline finale
        linea[strcspn(linea, "\n")] = 0;

        char *targa = strtok(linea, ";");
        char *modello = strtok(NULL, ";");
        char *posizione = strtok(NULL, ";");
        char *tariffa_str = strtok(NULL, ";");
        char *tipo = strtok(NULL, ";");

        double tariffa;
        sscanf(tariffa_str, "%lf", &tariffa);

        if (targa && modello && posizione && tariffa_str) {
            Veicolo v = crea_veicolo(tipo, targa, modello, posizione, tariffa, crea_prenotazioni());
            if(!aggiungi_veicolo_in_tabella(tabella, v)) return -1;
        } else {
            return -1;
        }
    }

    return 0;
}

int test_case_uno(TabellaUtenti tabella_utenti, TabellaVeicoli tabella_veicoli){
    FILE *file_input = fopen("TC1/input.txt", "r");
    FILE *file_output = fopen("TC1/output.txt", "w");
    if(!(file_input && file_output)) return -1;

    char linea[GRANDEZZA_RIGA];
    while (fgets(linea, sizeof(linea), file_input)) {
        linea[strcspn(linea, "\n")] = 0;

        char *email = strtok(linea, ";");
        char *targa = strtok(NULL, ";");
        char *data_inizio = strtok(NULL, ";");
        char *data_fine = strtok(NULL, ";");

        Veicolo v = cerca_veicolo_in_tabella(tabella_veicoli, targa);
        if(v == NULL){
            fclose(file_input);
            fclose(file_output);
            return -1;
        }

        Intervallo i = converti_data_in_intervallo(data_inizio, data_fine);
        Prenotazione pre = crea_prenotazione(email, targa, i, calcola_costo(ottieni_tariffa(v), i));
        Byte codice = aggiungi_prenotazione(ottieni_prenotazioni(v), pre);
        Utente u = cerca_utente_in_tabella(tabella_utenti, email);
        if(u == NULL) return -1;
        if(codice == OK)
            if(!aggiungi_a_storico_utente(u, pre)) return -1;
        fprintf(file_output, "%s %s %s %s %s",
                codice == OCCUPATO?"OCCUPATO":"OK",
                ottieni_cliente_prenotazione(pre),
                ottieni_targa(v),
                data_inizio,
                data_fine);
        if(codice == OK){
            fprintf(file_output," Costo=%0.2lf", ottieni_costo_prenotazione(pre));
        }
        fprintf(file_output, "\n");
    }

    fclose(file_input);
    fclose(file_output);

    return 1;
}

int test_case_due(TabellaVeicoli tabella_veicoli){
    FILE *file_input = fopen("TC2/input.txt", "r");
    FILE *file_output = fopen("TC2/output.txt", "w");
    if(!(file_input && file_output)) return -1;

    char linea[GRANDEZZA_RIGA];
    while (fgets(linea, sizeof(linea), file_input)) {
        linea[strcspn(linea, "\n")] = 0;

        char *inizio = strtok(linea, ";");
        char *fine = strtok(NULL, ";");

        Intervallo i = converti_data_in_intervallo(inizio, fine);
        if(i == NULL) return -1;

        fprintf(file_output, "Veicoli disponibili per il %s - %s: ", inizio, fine);

        unsigned int dimensione;
        Veicolo *vettore_veicoli = ottieni_veicoli_disponibili(tabella_veicoli, i, &dimensione);
        const char *sep = "";
        if(vettore_veicoli == NULL) return -1;
        for(unsigned int i = 0; i < dimensione; i++){
            if(vettore_veicoli[i] != NULL){
                fprintf(file_output, "%s'%s'", sep, ottieni_targa(vettore_veicoli[i]));
                sep = " ";
            }
        }
        fprintf(file_output, "\n");
    }

    fclose(file_input);
    fclose(file_output);

    return 1;
}

int test_case_tre(TabellaUtenti tabella_utenti, TabellaUtenti tabella_veicoli){
    FILE *file_input = fopen("TC3/input.txt", "r");
    FILE *file_output = fopen("TC3/output.txt", "w");
    if(!(file_input && file_output)) return -1;

    char linea[GRANDEZZA_RIGA];
    //Creo una nuova linea per evitare di mettere un \n in più
    const char *nuova_linea = "";

    //Creo un tab perchè \t poi viene contato come carattere diverso da 4 spazi usati nel oracle
    const char *tab = "    ";

    while (fgets(linea, sizeof(linea), file_input)) {
        linea[strcspn(linea, "\n")] = 0;

        Utente u = cerca_utente_in_tabella(tabella_utenti, linea);
        if(u == NULL) return -1;
        fprintf(file_output, "%s", nuova_linea);
        fprintf(file_output, "Prenotazioni di %s:\n", linea);
        for(ListaPre lista = ottieni_storico_utente(u); !lista_vuota(lista); lista = ottieni_prossimo(lista)){
            Veicolo v = cerca_veicolo_in_tabella(tabella_veicoli, ottieni_veicolo_prenotazione(ottieni_item(lista)));
            if(v == NULL){
                fclose(file_input);
                fclose(file_output);
                return -1;
            }
            fprintf(file_output, "%s- Veicolo: %s %s\n%s%s- Data: %s\n%s%s- Costo: %0.2lf€\n",
                   tab,
                   ottieni_modello(v),
                   ottieni_targa(v),
                   tab,
                   tab,
                   intervallo_in_stringa(ottieni_intervallo_prenotazione(ottieni_item(lista))),
                   tab,
                   tab,
                   ottieni_costo_prenotazione(ottieni_item(lista)));
        }
        nuova_linea = "\n";
    }
    fclose(file_input);
    fclose(file_output);
    return 1;
}

int compara_file(FILE *a, FILE *b) {
    int ca, cb;
    for(ca = getc(a), cb = getc(b); (ca != EOF && cb != EOF) && (ca == cb); ca = getc(a), cb = getc(b));
    return ca != cb;
}
