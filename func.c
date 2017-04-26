/*
Plik func.c zawiera implementacje funkcji do obslugi kolejek, obslugi bledow oraz "zabicia" procesu serwera.
*/                      
#include <stdio.h>       
#include <stdlib.h>       
#include <sys/types.h>     
#include <sys/ipc.h>        
#include <sys/msg.h>         
#include <signal.h>           
#include <unistd.h>            
#include "func.h"               
                                                                
//----------------------Obsluga Bledow--------------------------
void err( const char* what )
{
	perror( what );    
	exit( 2 );
}
//--------------------------------------------------------------
                                                                
                                                                
//---------------------Tworzenie Kolejki------------------------
int createQueue( int qid )     
{
	key_t key = ftok( ".", qid );
	int queue = msgget( key, IPC_CREAT | 0666 );     
	if( queue == -1 )   
		{err( "Queue creation fail" );}
	else  
		{return queue;}
}
//--------------------------------------------------------------
                                                                
                                                                
//----------------Wysylanie komunikatu do kolejki---------------
void sendMessage( int qid , message* mess  )   
{
	int who = ( int ) mess->sender;
	
	int val = msgsnd( qid, mess, sizeof( mess->text), 0 );
	if( val == -1 )
	{
		if( who == 1 )   
			{err( "message not sent by server" );}
		else
			{err( "message not sent by client" );}
	}
	if( who == 1 )
		{printf( "Message sent by server\n" );}
	else
		{printf( "Message sent by client\n" );}
}
//---------------------------------------------------------------
                                                                 
                                                                 
//----------------Odbieranie komunikatu z kolejki----------------
void receiveMessage( int qid , message* mess, int receiver ) 
{      
 	int val = msgrcv( qid, mess, sizeof( mess->text), receiver, 0 ); 
 	if( val == -1 )		
 	{
    		if( receiver == 1 )  
			{err( "message not received by server" );}
      		else
			{err( "message not received by client" );}
	} 
	if( receiver == 1 ) 
	 	{printf( "Message received by server\n" );}
	else 
		{printf( "Message received by client\n" );} 
}
//----------------------------------------------------------------
                                                                  
                                                                  
//--------------------"Zabijanie" procesu serwera-----------------
void shutdown( int qid )   
{   
	deleteQueue( 1 );
	exit( 1 );
}   
//----------------------------------------------------------------
                                                                  
                                                                  
//----------------------Usuwanie kolejki--------------------------
void deleteQueue( int qid )
{
	int i = msgctl( qidt, IPC_RMID, NULL );
	if( i == -1 )
		err( "queue not deleted" );

	printf( "\nQueue deleted. ID: %d \nServer shutdown...\n", qidt );
}
//----------------------------------------------------------------
                                                                  
                                                                  
//----------------Wypisywanie wiadomosci na ekran-----------------
void printMess( message mess ) 
{ 
	int i = 0; 
	int textSize = ( int ) mess.msize; 
	for( ; i < ( textSize - 1 ); i++ ) 
		printf( "%c", mess.text[i] ); 

	printf( "\n");
}
//----------------------------------------------------------------
