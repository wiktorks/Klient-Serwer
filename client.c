/*
Program client.c wysyla wiadomosc pobrana a klawiatury do procesu 
server w celu konwersji malych liter na duze. Tak przerobiona wiadomosc 
pobiera spowrotem od servera i wypisuje na ekran. Proces konczy prace po 
sekwencji klawiszy ctrl+D.
*/


			 
#include <stdio.h> 
#include <stdlib.h> 
#include <signal.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <string.h>  		
#include "func.h" 
#include <time.h>  
		   
 
  
int main()
{
   	int qid = createQueue( 1 ); //Uzyskujemy dostep do kolejki
	printf( "Process %d ready!\n", getpid() );
        long client = (long) getpid(); //Nadawca jako PID klienta
    	long server = 1;
        char sendIt[MAXBUFF]; //tekst do wyslania
	message mess;
     	srand( time( NULL ) );      //
   	do
	{
		mess.sender = client;//Wypelniamy odpowiednie pola struktury
		mess.receiver = server;
		printf( "Enter text for conversion:\n" );
		char* a = fgets( sendIt, MAXBUFF, stdin );    //Gdy sie pojawi ctrl+D to proces koczy prace
		if( a == NULL )
		{
			printf( "Process %d ends futher requests\n", getpid() );  
		        exit( 1 ); 
		}
		
		strncpy( mess.text, sendIt, strlen( sendIt ) );   	   
		mess.msize = (long) strlen( sendIt );

		sendMessage( qid, &mess ); //Wysylamy prosbe do server    

		sleep( rand() % 3 );  //"usypiamy" proces losowa na czas [0 - 3] sek

     	       	receiveMessage( qid, &mess, client );    //Odbieramy przerobiony tekst od serwera...
		printf( "Client received: " );   	//...i wypisujemy na ekran
		printMess( mess );
		
		memset( sendIt, 0, sizeof( sendIt)); //Resetuje bufor aby nie zapisywaly sie w nim smieci
	}
        while( 1 );
	return 0;
}
