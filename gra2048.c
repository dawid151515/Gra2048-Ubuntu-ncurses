
#include "gra2048.h"
int szerokosc = 4;

void inicjalizacja() {
	initscr();
	kolor();
	noecho();
	int u;
	

	for (int i = 0; i < ROZMIAR; i++) {					// wypelnia tablice zerami
		for (int j = 0; j < ROZMIAR; j++) {
			tablica[i][j] = PUSTE_POLE;
		}
	}
	
	wstaw_nowa_liczbe();
	wstaw_nowa_liczbe();
	punkty = 0;
	gracz_kontynuuje = 0;
	liczba_ruchow = 0;
	
}

void wstaw_nowa_liczbe() {
	
	int zarodek;
	time_t tt;
	zarodek = time(&tt);
	srand(zarodek);
	int wartosc_do_wstawienia = 2 + 2 * (rand() % 2); 			// losujemy liczbe 2 lub 4
													  

	int liczba_pustych_pol = 0;

	for (int i = 0; i < ROZMIAR; i++) {
		for (int j = 0; j < ROZMIAR; j++) {
			if (tablica[i][j] == PUSTE_POLE) {
				liczba_pustych_pol++;
			}
		}
	}

	int pole_do_wpisania = 1 + (rand() % liczba_pustych_pol);		// losujemy pole do
										// wstawienia tej liczby

	int licznik_pol = 0;
	for (int i = 0; i < ROZMIAR; i++) {
		for (int j = 0; j < ROZMIAR; j++) {
			if (tablica[i][j] == PUSTE_POLE) {
				licznik_pol++;
			}
			if (licznik_pol == pole_do_wpisania) {			// wstawiamy wylosowana liczbe
				tablica[i][j] = wartosc_do_wstawienia;		// w wylosowane pole
				return;
			}
		}
	}
}

int czy_wygrales() {

	if (gracz_kontynuuje == 1) {
		return 0;
	}

	for (int i = 0; i < ROZMIAR; i++)				// sprawdzamy czy w tablicy
	{												// jest liczba 2048 czyli WYGRANA,
		for (int j = 0; j < ROZMIAR; j++)			// jesli jest to wygralismy gre
		{
			if (tablica[i][j] == WYGRANA) {
				return 1;
			}
		}
	}
	return 0;
}

void wygrales() {
	mvprintw(u, 0, "Wygrales");					// wygrales, czy chcesz grac dalej?
	
	mvprintw(u+1, 0, "Czy chcesz kontynuowac?");
	
	if (Potwierdz() == 1) {			
		gracz_kontynuuje = 1;

	}
	
	
}

void narysuj_ekran() {

	int dlugosc_kreski = 1 + 7 * ROZMIAR;
	
	mvprintw(0, 0, "Punkty: %-72d", punkty);
	mvprintw(1, 0, "Liczba ruchow: %-65d", liczba_ruchow);
	mvprintw(2, 40, "Sterowanie:");
	mvprintw(3, 40, "w - ruch w gore, s - ruch w dol");
	mvprintw(4, 40, "a - ruch w lewo, d - ruch w prawo");
	mvprintw(5, 40, "q - wyjdz");
	mvprintw(6, 40, "n - nowa gra");
	mvprintw(7, 40, "t - tak, n- nie");
	

	attron(COLOR_PAIR(12));
	for (int x = 0; x < (ROZMIAR * (szerokosc +1)) + 1; x++) {		// rysuje obramowanie tablicy
		for (int y = 0; y < (ROZMIAR * 2) + 1; y += 2) {
			mvprintw(y + 2, x, "-");
		}
	}
	for (int y = 0; y < (ROZMIAR * 2) + 1; y++) {
		for (int x = 0; x < (ROZMIAR * (szerokosc + 1)) + 1; x += (szerokosc + 1)) {
			mvprintw(y + 2, x, "|");
		}
	}
	attroff(COLOR_PAIR(12));

	for (int i = 0; i < ROZMIAR; i++) {
		
		for (int j = 0; j < ROZMIAR; j++) {					// zamienia zera ktorymi wypelniona
			if (tablica[i][j] == PUSTE_POLE) {				// jest tablica, spacjami
				attron(COLOR_PAIR(12));
				mvprintw(i * 2 + 3, j * (szerokosc + 1) + 1, "%*s",szerokosc, " ");
				attroff(COLOR_PAIR(12));
			}
			else {
				int kolor=fmin(11, log(tablica[i][j])/log(2));		// koloruje liczby
				
				attron(COLOR_PAIR(kolor));
				mvprintw(i * 2 + 3, j * (szerokosc + 1) + 1, "%*d", szerokosc, tablica[i][j]);
				attroff(COLOR_PAIR(kolor));
			}
		}
		
	}
}
void rysuj_pozioma_kreska(char* prefix, int dlugosc) {
	printw("%s", prefix);
	for (int i = 0; i < dlugosc; i++) {
		printw("-");
	}
	
}
void lewo() {										// ruch w lewo
	liczba_ruchow = liczba_ruchow + 1;				
	for (int i = 0; i < ROZMIAR; i++)
	{
		for (int j = 1; j < ROZMIAR; j++)
		{
			if (tablica[i][j] == PUSTE_POLE) {
				continue;
			}

			for (int k = j - 1; k > -1; k--) {
				if (tablica[i][k] == PUSTE_POLE) {		// przesowa wszystkie liczby
					tablica[i][k] = tablica[i][k + 1];	// do krawedzi tablicy
					tablica[i][k + 1] = PUSTE_POLE;
					continue;
				}
				if (tablica[i][k] == tablica[i][k + 1]) {	// jesli liczby sa takie same
					tablica[i][k] += tablica[i][k + 1];	// to zostaja dodane
					oblicz_szerokosc(tablica[i][k]);
					tablica[i][k + 1] = PUSTE_POLE;
					punkty += tablica[i][k];
					break;
				}
				if (tablica[i][k] != tablica[i][k + 1]) {	// jesli dwie liczby sa rozne
					break;					// to przejdz do nastepnego kroku
				}
			}

		}
	}

	
	wstaw_nowa_liczbe();							// wstawia nowa wylosowana
}										// liczbe do tablicy
void prawo() {									// ruch w  prawo
	liczba_ruchow = liczba_ruchow + 1;
	for (int i = 0; i < ROZMIAR; i++)
	{
		for (int j = ROZMIAR - 2; j > -1; j--)
		{
			if (tablica[i][j] == PUSTE_POLE) {
				continue;
			}

			for (int k = j + 1; k < ROZMIAR; k++) {
				if (tablica[i][k] == PUSTE_POLE) {
					tablica[i][k] = tablica[i][k - 1];
					tablica[i][k - 1] = PUSTE_POLE;
					continue;
					
				}
				if (tablica[i][k] == tablica[i][k - 1]) {
					tablica[i][k] += tablica[i][k - 1];
					oblicz_szerokosc(tablica[i][k]);
					tablica[i][k - 1] = PUSTE_POLE;
					punkty += tablica[i][k];
					break;
					
				}
				if (tablica[i][k] != tablica[i][k - 1]) {
					break;
				}
			}

		}
	}

	
	wstaw_nowa_liczbe();
}
void gora() {										// ruch w gore
	liczba_ruchow = liczba_ruchow + 1;

	for (int j = 0; j < ROZMIAR; j++)
	{
		for (int i = 1; i < ROZMIAR; i++)
		{
			if (tablica[i][j] == PUSTE_POLE) {
				continue;
			}

			for (int k = i - 1; k > -1; k--) {
				if (tablica[k][j] == PUSTE_POLE) {
					tablica[k][j] = tablica[k + 1][j];
					tablica[k + 1][j] = PUSTE_POLE;
					continue;
				}
				if (tablica[k][j] == tablica[k + 1][j]) {
					tablica[k][j] += tablica[k + 1][j];
					oblicz_szerokosc(tablica[i][k]);
					tablica[k + 1][j] = PUSTE_POLE;
					punkty += tablica[k][j];
					break;
				}
				if (tablica[k][j] != tablica[k + 1][j]) {
					break;
				}
			}

		}
	}

	
	wstaw_nowa_liczbe();
}

void dol() {											// ruch w dol
	liczba_ruchow = liczba_ruchow + 1;
	for (int j = 0; j < ROZMIAR; j++)
	{
		for (int i = ROZMIAR - 2; i > -1; i--)
		{
			if (tablica[i][j] == PUSTE_POLE) {
				continue;
			}

			for (int k = i + 1; k < ROZMIAR; k++) {
				if (tablica[k][j] == PUSTE_POLE) {
					tablica[k][j] = tablica[k - 1][j];
					tablica[k - 1][j] = PUSTE_POLE;
					continue;
				}
				if (tablica[k][j] == tablica[k - 1][j]) {
					tablica[k][j] += tablica[k - 1][j];
					oblicz_szerokosc(tablica[i][k]);
					tablica[k - 1][j] = PUSTE_POLE;
					punkty += tablica[k][j];
					break;
				}
				if (tablica[k][j] != tablica[k - 1][j]) {
					break;
				}
			}

		}
	}

	
	wstaw_nowa_liczbe();
}


int Potwierdz() {
	int c;								// potwierdzenie
									// wpisz tak lub nie
	do {
		mvprintw(u+2, 0, "Wpisz t lub n");
		c = getch();
	} while (c != PRAWDA && c != FALSZ);
	mvprintw(u, 0, "%80s", " ");
	mvprintw(u+1, 0, "%80s", " ");
	mvprintw(u+2, 0, "%80s", " ");
	return c == PRAWDA ? 1 : 0;
}
int czy_zamknac() {
	mvprintw(u, 0, "Czy napewno chcesz zakonczyc gre?");
	int potwierdzenie = Potwierdz();				// wyjscie z gry
	if (potwierdzenie) {
		return 1;
		
	}
	return 0;

}
int czy_przegrales() {							// sprawdza czy jest jakies puste pole
	for (int i = 0; i < ROZMIAR; i++) {				// jesli nie ma to przegrales
		for (int j = 0; j < ROZMIAR; j++) {			
			if (tablica[i][j] == PUSTE_POLE) {
				return 0;
			}
		}
	}
	return 1;
}
int czy_grasz_jeszcze_raz() {						// czy chcesz zaczac gre od nowa

	mvprintw(u, 0, "Koniec gry!");
	mvprintw(u+1, 0, "Czy chcesz zagrac jeszcze raz?");

	int potwierdzenie = Potwierdz();

	if (potwierdzenie) {
		inicjalizacja();
		return 1;
	}
	else {
		return 0;
	}
}
 
void kolor() {								// funkcja kolorujaca liczby
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_YELLOW);
	init_pair(2, COLOR_BLACK, COLOR_BLUE);
	init_pair(3, COLOR_BLACK, COLOR_RED);
	init_pair(4, COLOR_BLACK, COLOR_WHITE);
	init_pair(5, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(6, COLOR_BLACK, COLOR_CYAN);
	init_pair(7, COLOR_BLACK, COLOR_GREEN);
	init_pair(8, COLOR_RED, COLOR_GREEN);
	init_pair(9, COLOR_BLUE, COLOR_WHITE);
	init_pair(10, COLOR_BLUE, COLOR_MAGENTA);
	init_pair(11, COLOR_WHITE, COLOR_BLUE);
	init_pair(12, COLOR_CYAN, COLOR_BLACK);
	
	
}

void oblicz_szerokosc(int liczba) {						// zwieksza ilosc miejsc
	szerokosc = fmax(szerokosc, ceil(log(liczba + 1) / log(10)));		// w tablicy, rysuje
																		// 												//wieksza tablice
}

