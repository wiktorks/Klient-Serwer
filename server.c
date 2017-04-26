/*
Program tworzy kolejke do ktorej klient wysyla wiadomosc, 
odbiera ja i przerabia wszystkie litery na duze, nastepnie wysyla ja 
z powrotem klientowi. Program "wisi" dopoki nie dostanie sygnalu "SIGINT" 
z klawiatury, ktory nastepnie obsluguje funkcja shutdown ktora najpierw 
usuwa kolejke a nastepnie "zabija" proces.
*/          


#include <stdio.h>			
#include <stdlib.h>	
#include <sys/types.h>			
#include <sys/ipc.h>	
#include <unistd.h>			
#include <signal.h>	
#include <string.h>      		
#include "func.h"	


		  
int main()
{
   	int qid = createQueue( 1 ); //Tworzymy kolejke (id serwera: 1)
  	printf( "Queue created. ID: %d \nReady!\n", qid );
        fflush( stdout );  //Zeby stdout nie "zamrozil" sie w czasie czekania na sygnal 
        
    	qidt = qid; //Przypisujemy do zmiennej id kolejki, przyda sie do usuwania serwera
        
        message mess; 
	long receiver; 
   	int textSize, i ;
	
	signal( SIGINT, shutdown );	//"Wisi" i czeka na sygnal SIGINT z klawiatury
    				       
	do  
	{    
		receiveMessage( qid, &mess, 1 );  //Odbiera wiadomosc od klienta
		printf( "Server received: " );
		printMess( mess );   
		textSize = (int) mess.msize -1;       
			  
	        char converter[ textSize ];
		i = 0; 
  	     	for( ; i<textSize; i++ ) 
		{
			converter[i] = toupper( mess.text[i] ); //Zamieniamy na duze
      	    	}  
   
		//Zamiana odbiorcy na nadawce
		mess.receiver = mess.sender; //i na odwrot
	 	mess.sender = 1; 
			      
		strncpy( mess.text, converter, textSize );//Przerobiona wiadomosc zapisujemy w strukturze... 
		sleep( 1 );
		sendMessage( qid, &mess );//...i odsylamy klientowi
		
       		printf("\n-------------------\n");

		memset( converter, 0, sizeof( converter));//Czyscimy bufor
	} 
    	while( 1 );
	//pause(); //Zawieszamy program na czas pracy
	return 0;
}		    
