========================================================================
Autor: Wiktor Kosterski-Spalski,                    Krakow, 01.06.2016
========================================================================

* Zawartosc:
============

Katalog programy zawiera dwa programy w jezyku C:
--------------------------------------------------------------------

I.  Program wysylajacy wiadomosc z klawiatury przez kolejke do procesu serwer, 
    ktora nastepnie odbiera od serwera!
    Program sklada sie z dwoch modulow: 
    1) client.c  - program glowny. 
    2) func.c, func.h - funkcjie do obslugi kolejki komunikatow.

II. Program odbierajacy wiadomosc od klienta z kolejki, konwertujacy wiadomosc i 
    wysylajacy z powrotem do klienta zmodyfikowana wiadomosc.
    Program sklada sie z dwoch modulow:    
    1) server.c              - program glowny,
    2) func.c, func.h - funkcjie do obslugi kolejki komunikatow.
 

------------------------------------------------------------------------

* Jak uruchomic programy:
=========================

Katalog zawiera program Makefile do kompilacji, linkowania
i uruchamiania powyzszych programow, a takze czyszczenia katalogu 
i jego archiwizacji.

-> Aby skompilowac wszystkie programy, nalezy wykonac komende: 
	make all

-> Aby skompilowac pojedyncze programy serwera i klienta nalezy wykonac
   komende odpowiednio: 
	a)Dla serwera: 
		make server
	b)Dla klienta: 
		make client
-> Aby uruchomic serwer, nalezy wykonac komende:
       make run_srv

-> Aby uruchomic 2-gi program, nalezy wykonac komende:
       make run_cli

->Aby jednoczesnie oba programy uruchomic nalezy wykonac komende: 
       make run_proj

-> Aby wyczyscic zawartosc katalogu (usunac zbedne pliki), nalezy wykonac:
       make clean

-> Aby wyczyscic zawartosc katalogu z plikow wykonawczych, nalezy wykonac: 
	make cleanexe

-> W celu archiwizacji oraz kompresji katalogu nalezy wykonac:
       make tar

========================================================================



