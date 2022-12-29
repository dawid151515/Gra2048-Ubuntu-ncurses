#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <math.h>


#define ROZMIAR 4
#define PUSTE_POLE 0
#define WYGRANA 2048

#define PRAWDA 't'
#define FALSZ 'n'

#define LEWO 'a'
#define PRAWO 'd'
#define GORA 'w'
#define DOL 's'
#define NOWA_GRA 'n'
#define WYJSCIE 'q'
#define ENTER 10


int u;

int tablica[ROZMIAR][ROZMIAR];
int punkty;
int liczba_ruchow;
int gracz_kontynuuje;


void inicjalizacja();
void wstaw_nowa_liczbe();
void narysuj_ekran();
void rysuj_pozioma_kreska(char* prefix, int dlugosc);
void lewo();
void prawo();
void gora();
void dol();
void wygrales();
void kolor();
void oblicz_szerokosc(int);


int czy_zamknac();
int czy_przegrales();
int czy_grasz_jeszcze_raz();
int Potwierdz();
int czy_wygrales();
