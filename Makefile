CC=gcc
CFLAGS=-I.
HEAD = func.h
CLI = client.o func.o
SRV = server.o func.o
KOMPR = server.c client.c func.c func.h Makefile README.txt


#*********************-Kompilacja-*********************
all: server client

server: $(SRV)
	gcc -o $@ $^ $(CFLAGS)

client: $(CLI)
	gcc -o $@ $^ $(CFLAGS)

%.o: %.c $(HEAD)
	$(CC) -c -o $@ $< $(CFLAGS)
#------------------------------------------------------


#***************-Uruchamianie projektu-****************
run_proj: run_srv run_cli

run_srv: server 
	xterm -hold -title SERVER -bg red -e ./server &

run_cli: client
	xterm -hold -title CLIENT1 -bg green -e ./client &
	xterm -hold -title CLIENT2 -bg green -e ./client &
	xterm -hold -title CLIENT3 -bg green -e ./client
#------------------------------------------------------


#*************-Sprzatanie po kompilacji-****************
clean: 
	rm -f *.o *~ *.a *.x

cleanexe: 
	rm -f client server
#-------------------------------------------------------


#******************-Archiwizacja-***********************
tar: clean cleanexe
	tar -cvzf poprawione8.tar.gz $(KOMPR) 
#-------------------------------------------------------


.PHONY: tar clean all
