//
// Created by sicig on 21/05/2025.
//

#ifndef INTERFACCIA_H
#define INTERFACCIA_H
typedef struct tabella_hash *TabellaUtenti;
typedef char Byte;

void interfaccia_accesso(TabellaUtenti tabella_utenti);

void interfaccia_registrazione(TabellaUtenti tabella_utenti, Byte permesso);

void ottieni_stringa(char *stringa, int dimensione);
#endif //INTERFACCIA_H
