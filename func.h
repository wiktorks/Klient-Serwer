/*
Plik func.h zawiera deklaracje funkcji do obslugi kolejki komunikatow, 
strukture wiadomosci przesylanej przez kolejke, maksymalna pojemnosc bufora 
oraz funkcje do obslugi bledow. Rozwniniecia funkcji znajduja sie w pliku 
"func.c".
*/
#ifndef FUNC_H
#define FUNC_H

#define MAXBUFF 100 //Max bufor

int qidt; //Globalna zmienna przechowujaca qid kolejki

typedef struct //Struktura wiadomosci
{
	long receiver; //odbiorca
	long sender; //nadawca
	long msize;
	char text[MAXBUFF]; //bufor wiadomosci
	//long msize;
}message;

void err( const char* what ); //Obsluga bledow

int createQueue( int qid ); //Tworzy kolejke

void sendMessage( int qid, message* mess ); //Wysyla wiadomosc do kolejki

void receiveMessage( int qid, message* mess, int sender ); //odbiera wiadomosc od kolejki

void shutdown( int sig ); //"Zabija" proces serwera

void deleteQueue( int qid );// usuwa kolejke

void printMess( message mess ); //Wypisuje wiadomosc
#endif
