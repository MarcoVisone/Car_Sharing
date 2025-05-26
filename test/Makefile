test: test.o interfaccia.o interfaccia_amministratore.o data.o intervallo.o prenotazione.o utente.o veicolo.o coda.o lista.o lista_prenotazione.o prenotazioni.o tabella_hash.o tabella_utenti.o tabella_veicoli.o gestore_file.o md5.o utils.o
	gcc test.o interfaccia.o interfaccia_amministratore.o data.o intervallo.o prenotazione.o utente.o veicolo.o coda.o lista.o lista_prenotazione.o prenotazioni.o tabella_hash.o tabella_utenti.o tabella_veicoli.o gestore_file.o md5.o utils.o -o test

test.o: test.c
	gcc -Wall -Wextra -std=c99 -I../include -c test.c -o test.o

interfaccia.o: ../src/interfaccia/interfaccia.c ../include/interfaccia/interfaccia.h
	gcc -Wall -Wextra -std=c99 -I../include -c ../src/interfaccia/interfaccia.c -o interfaccia.o

interfaccia_amministratore.o: ../src/interfaccia/interfaccia_amministratore.c ../include/interfaccia/interfaccia_amministratore.h
	gcc -Wall -Wextra -std=c99 -I../include -c ../src/interfaccia/interfaccia_amministratore.c -o interfaccia_amministratore.o

data.o: ../src/modelli/data.c ../include/modelli/data.h
	gcc -Wall -Wextra -std=c99 -I../include -c ../src/modelli/data.c -o data.o

intervallo.o: ../src/modelli/intervallo.c ../include/modelli/intervallo.h
	gcc -Wall -Wextra -std=c99 -I../include -c ../src/modelli/intervallo.c -o intervallo.o

prenotazione.o: ../src/modelli/prenotazione.c ../include/modelli/prenotazione.h
	gcc -Wall -Wextra -std=c99 -I../include -c ../src/modelli/prenotazione.c -o prenotazione.o

utente.o: ../src/modelli/utente.c ../include/modelli/utente.h
	gcc -Wall -Wextra -std=c99 -I../include -c ../src/modelli/utente.c -o utente.o

veicolo.o: ../src/modelli/veicolo.c ../include/modelli/veicolo.h
	gcc -Wall -Wextra -std=c99 -I../include -c ../src/modelli/veicolo.c -o veicolo.o

coda.o: ../src/strutture_dati/coda.c ../include/strutture_dati/coda.h
	gcc -Wall -Wextra -std=c99 -I../include -c ../src/strutture_dati/coda.c -o coda.o

lista.o: ../src/strutture_dati/lista.c ../include/strutture_dati/lista.h
	gcc -Wall -Wextra -std=c99 -I../include -c ../src/strutture_dati/lista.c -o lista.o

lista_prenotazione.o: ../src/strutture_dati/lista_prenotazione.c ../include/strutture_dati/lista_prenotazione.h
	gcc -Wall -Wextra -std=c99 -I../include -c ../src/strutture_dati/lista_prenotazione.c -o lista_prenotazione.o

prenotazioni.o: ../src/strutture_dati/prenotazioni.c ../include/strutture_dati/prenotazioni.h
	gcc -Wall -Wextra -std=c99 -I../include -c ../src/strutture_dati/prenotazioni.c -o prenotazioni.o

tabella_hash.o: ../src/strutture_dati/tabella_hash.c ../include/strutture_dati/tabella_hash.h
	gcc -Wall -Wextra -std=c99 -I../include -c ../src/strutture_dati/tabella_hash.c -o tabella_hash.o

tabella_utenti.o: ../src/strutture_dati/tabella_utenti.c ../include/strutture_dati/tabella_utenti.h
	gcc -Wall -Wextra -std=c99 -I../include -c ../src/strutture_dati/tabella_utenti.c -o tabella_utenti.o

tabella_veicoli.o: ../src/strutture_dati/tabella_veicoli.c ../include/strutture_dati/tabella_veicoli.h
	gcc -Wall -Wextra -std=c99 -I../include -c ../src/strutture_dati/tabella_veicoli.c -o tabella_veicoli.o

gestore_file.o: ../src/utils/gestore_file.c ../include/utils/gestore_file.h
	gcc -Wall -Wextra -std=c99 -I../include -c ../src/utils/gestore_file.c -o gestore_file.o

md5.o: ../src/utils/md5.c ../include/utils/md5.h
	gcc -Wall -Wextra -std=c99 -I../include -c ../src/utils/md5.c -o md5.o

utils.o: ../src/utils/utils.c ../include/utils/utils.h
	gcc -Wall -Wextra -std=c99 -I../include -c ../src/utils/utils.c -o utils.o

clean:
	rm -f *.o test
