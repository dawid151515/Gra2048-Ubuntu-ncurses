# Gra2048-Ubuntu-ncurses

Jest to gra konsolowa.

Celem gry jest uzyskanie wyniku 2048. Gracz może przemieszczać kwadratowe klocki w pionie i w poziomie, każdy ruch przesuwa je o jedno pole w wybranym kierunku, a po jego wykonaniu na planszy odkryte zostaje jedno pole z cyfrą 2 lub 4. Klocki zatrzymują się, gdy natrafią na koniec planszy lub klocek o innej wartości. Kiedy klocki mają tą samą wartość to sumują się w jeden klocek o większej (zsumowanej) wartości.

Uruchomienie gry na Linux Ubuntu:
1. Na początku należy zainstalować bibliotekę ncurses wpisując w konsolę następujące polecenie:
  sudo apt-get install libncurses5.dev libncursesw5-dev
2. Korzystając z makefile, w konsolę wpisujemy następujące polecenia:
   a) make gra2048.o,
   b) make main.o,
   c) make gra2048
3. Po poprawnym wykonaniu tych poleceń można uruchomić grę wpisując w konsolę następujące polecenie:
   ./gra2048
4. Gdy nie chcemy korzystać już z tej aplikacji, możemy użyć polecenia make clean, które usunie zbędne pliki, a mianowicie gra2048.o, main.o oraz plik uruchomieniowy gry    gra2048, lecz pliki główne, które niezbędne są do komplikacji nie zostaną usunięte, by można było w przyszłości jeszcze skompilować tą grę ponownie.
   
 W folderze "Plik-wykonywalny" znajduje się plik, który już został skompilowany, a więc po pobraniu go na linuxa ubuntu, wystarczy go uruchomić i gra powinna działać (jeśli nie działa to należy wykonać napisane powyżej kroki). Aby uruchomić ten plik należy w konsolę wpisać polecenie:
  ./gra2048
