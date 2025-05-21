#include <stdio.h>
#include <string.h>
#include "modelli/veicolo.h"
#include "strutture_dati/tabella_veicoli.h"
#include "modelli/utente.h"
#include "strutture_dati/tabella_utenti.h"
#include "utils/md5.h"

#define GRANDEZZA_RIGA 500

int txt_in_utenti(FILE *fp, TabellaUtenti tabella);

int txt_in_veicoli(FILE *fp, TabellaVeicoli tabella);



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
    if(txt_in_veicoli(file_utenti, tabella_veicoli)){
        printf("Errore caricamento utenti!\n(Controlla il formato targa;modello;posizione;tariffa;tipo)");
        return -1;
    }

    char linea[GRANDEZZA_RIGA];

    while(fgets(linea, sizeof(linea), file_test_suite)){
        linea[strcspn(linea, "\n")] = 0;

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
            Veicolo v = crea_veicolo(tipo, targa, modello, posizione, tariffa, NULL);
            if(!aggiungi_veicolo_in_tabella(tabella, v)) return -1;
        } else {
            return -1;
        }
    }

    return 0;
}
