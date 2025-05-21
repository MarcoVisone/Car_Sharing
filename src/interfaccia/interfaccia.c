#include "modelli/interfaccia.h"
#include "modelli/tabella_utenti.h"
#include "modelli/utenti.h"
#include <string.h>
#include <stdio.h>

#define DIMENSIONE_STRINGA_PASSWORD (64 + 1)

static Byte risposta_password(Byte lvl){
  switch (lvl){
    case -1:
      printf("La password deve avere:\n Almeno 8 caratteri\n Almeno una lettera minuscola ed una minuscola\n");
      printf(" Almeno un numero\n Almeno un carattere speciale\n");
      break;

    case 0:
      printf("Inserisci almeno un carattere speciale o un numero\n");
      break;

    case 1:
      printf("Inserisci almeno un carattere speciale\n");
      break;

    default:
      printf("PASSWORD VALIDA\n");
      return 1;
  }

  return -1;
}


void *ottieni_stringa(char *stringa, int dimensione){
  fgets(stringa, dimensione, stdin);
  while(*stringa){
    if (*stringa == '\n'|| *stringa == ' '){
      *stringa = '\0';
      break;
    }
    stringa++;
  }
}

Byte interfaccia_accesso(TabellaUtenti tabella_utenti){
  char email[DIMENSIONE_EMAIL];
  char password[DIMENSIONE_STRINGA_PASSWORD];
  uint8_t password_mod[DIMENSIONE_PASSWORD];
  Byte tentativi = 0;
  Byte scelta;

  Utente utente;

  do{
    printf("Inserisci l'email: ");
    ottieni_stringa(email, DIMENSIONE_EMAIL);

    printf("Inserisci la password: ");
    ottieni_stringa(password, DIMENSIONE_STRINGA_PASSWORD);
    md5(password, strlen(password), password_mod);

    utente = cerca_tabella_utenti(tabella_utenti, email);

    if(utente && !hash_equals(ottieni_password(utente), password_mod, DIMENSIONE_PASSWORD)){
      printf("Email o password errati\n");

      printf("Vuoi uscire? (S/N): ");
      scelta = getchar();
      if(scelta == 's' || scelta == 'S'){
        return -1;
      }
      tentativi += 1;
    }
    else break;
  }while(tentativi < 3);

  return 1;
}

Byte interfaccia_registrazione(TabellaUtenti tabella_utenti, Byte permesso){
  char nome[DIMENSIONE_NOME];
  char cognome[DIMENSIONE_COGNOME];
  char email[DIMENSIONE_EMAIL];
  char password[DIMENSIONE_STRINGA_PASSWORD];
  char password_2[DIMENSIONE_STRINGA_PASSWORD];
  uint8_t password_mod[DIMENSIONE_PASSWORD];
  Utente utente;
  Byte conferma;
  Byte lvl;

  printf("Inserisci il nome: ");
  ottieni_stringa(nome, DIMENSIONE_NOME);

  printf("Inserisci il cognome: ");
  ottieni_stringa(cognome, DIMENSIONE_COGNOME);

  printf("Inserisci l'email: ");
  ottieni_stringa(email, DIMENSIONE_EMAIL);

  do{
    do{
      printf("Inserisci la password: ");
      ottieni_stringa(password, DIMENSIONE_STRINGA_PASSWORD);

      lvl = controllo_password(password);
    }while(risposta_password(lvl) < 0);

    printf("Conferma Password\n");
    ottieni_stringa(password_2, DIMENSIONE_PASSWORD);
    conferma = strcmp(password, password_2) != 0;
    if(conferma){
      printf("Le password non corrispondono\n");
    }
  }while(conferma);

  md5(password, strlen(password), password_mod);
  utente = crea_utente(email, password_mod, nome, cognome, permesso);

  if(aggiungi_utente_in_tabella(tabella_utenti, utente)){
    return 1;
  }
  return 0;
}