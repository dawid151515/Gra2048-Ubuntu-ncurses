
#include "gra2048.h"


int main() {
	int znak;
	int t, y;
	t = ROZMIAR - 2;
	y = t * 2;
	u = 7 + y;
	


	inicjalizacja();
	narysuj_ekran();
	while (1) {
		znak = getch();
										// sterowanie

		if (znak == LEWO) {
			lewo();
		}
		if (znak == PRAWO) {
			prawo();
		}
		if (znak == GORA) {
			gora();
		}
		if (znak == DOL) {
			dol();
		}
		

		if (znak == NOWA_GRA) {							// warunki gry
			mvprintw(u, 0, "Czy napewno chcesz zagrac od nowa?");
			if (Potwierdz()) {
				inicjalizacja();
			}
		}
		if (znak == WYJSCIE && czy_zamknac() == 1) {
			break;
		}
		

		if (czy_przegrales() == 1 && czy_grasz_jeszcze_raz() == 0) {
			break;
		}

		if (czy_wygrales()) {
			wygrales();
			if (gracz_kontynuuje == 0) {
				break;
			}


		}
		narysuj_ekran();
		
	}
	

	endwin();

	return 0;
}
