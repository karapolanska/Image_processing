#ifndef main_H
#define main_H

/* GeeksOnBoard
 * 2013
 * main.h
 */

/* main***************************************************************************************************/
/* Syntax of options and program calls                                                                   */
/*    program {[-i name] [-o name] [-m color] [-z number number] [-g number] [-ry number] [-h] [-d] }    */
/* function arguments:                                                                                   */
/*      argc  -  number of call arguments including the program name                                     */
/*      argv  -  table of call arguments                                                                 */
/*  PRE:                                                                                                 */
/*      The order of options appearance is unrestricted. Option -i  must appear in program call.         */
/*      Its lack and lack of filenames after -i and -o and lack of value after -p couse error message.   */
/*      Lack of -o optin causes printing image on standard output.                                       */
/*  POST:                                                                                                */
/*      Program calls functions (in order): przetwarzaj_opcje, which opens external files and            */
/*      sorts options and parameters to 2 separate tabels. Than function czytaj, loads given files       */
/*      and their infos to the structure. Next main function interprets options and sets apropriate      */
/*      tasks from file rzetwarzania.c.                                                                  */
/*      Returns 0 if success, otherwise -1.                                                              */
/*  COMMENTS:                                                                                            */
/*      - Options are processed in given order.                                                          */
/*      - Option color (-m) may appear multiple times setting the current color.                         */
/*        Only one color (or grays after prior conversion) may be processed at once.                     */
/*        For files other than ppm the option is omitted but doesn't cause error. Only warning.          */
/*      - Display option works after completing all operations and saving.                               */ 
/*      - User may use --help option, which shows help and quits the program.                            */
/*      - All functions takes care of possible errors and returns success or failure code.               */
/*      - All functions from przetwarzania.c prints the comment about done operations to the image file. */
/*********************************************************************************************************/

int main(int argc, char **argv);


/* TESTS only in Polish language

  Testowane sa jedynie obrazy PPM, PGM byly testowane w poprzedniej edycji przetwarzania_obrazow i w dokumentacji nic sie nie zmienilo.

Lp.  Cel                        Wejscie             Dzialanie          Przewidywane wyjscie     Wyjscie              Wynik testu
----------------------------------------------------------------------------------------------------------------------------------------------------
----testy wiersza polecen----
1.   brak argumentow            ---            tylko nazwa programu    blad                     blad                 pozytywny.
     wywolania

2.   brak -i                    ---                 -o a.ppm -d -h     blad                     blad                 pozytywny.

3.   "-" zamiast parametru      ---                 -i - -o a.ppm     oczekiwanie na podanie   oczekiwanie na podanie   pozytywny.
     przy -i                                                          pliku na stdin           pliku na stdin

4.   brak parametru przy -i     ---                 -i -o a.ppm        blad                     blad                 pozytywny.

5.   brak -o                    f.ppm               -i f.ppm           obraz na stdout          obraz na stdout      pozytywny.
     | -o -

6.   brak parametru przy -o     f.ppm               -i f.ppm -o        blad                     blad                 pozytywny.

7.   brak jakieokolwiek         f.ppm               -i f.ppm -g        blad                     blad                 pozytywny
     parametu przy opcjach
     wywolania

8.   otwierany plik nie         ff.ppm               -i ff.ppm         blad                     blad                 pozytywny.
     istnieje.

----testy wejscia------
1.   poprawny plik              f.ppm               -i f.ppm -o g.pgm  nowy obraz f.ppm         nowy obraz g.ppm     pozytywny. Program 
                                                                                                                     przyjmuje poprawne dane

2.   brak liczby magicznej      plik bez P3         --                 blad                     blad                 pozytywny. Program
                                                                                                                     nie przyjmuje plikow
                                                                                                                     niezgodnych z zadnym
                                                                                                                     standardem.

3.   zla liczba magiczna        jak wyzej                                                                            pozytywny. jak wyzej

4.   brak 1 z parametrow        plik bez odcieni    --                 blad                     blad                 pozytywny. Jak wyzej

5.   za duzo parametrow         par: 16, 32, 15, 6  -i f.ppm -o g.ppm  obraz                    obraz                pozytywny. Program usuwa
                                                    - h                                                              ostatnia, niepotrzebna dane

6.   brak komentarza            bez zadnych #       rozmycie pionowe,  obraz                    obraz                pozytywny. Komentarze nie
                                                    zapis                                                            sa wymagane

7.   komentarz wieloliniowy     30 linii            zmiana poziomow,   obraz                    obraz                pozytywny. Komentarzy moze
                                komentarza          zapis                                                            byc mnostwo

9.   entery po                  koment. \n\n\n      zmiana poziomow    obraz                    obraz                pozytywny. entery po
     komentarzu                                     zapis                                                            komentarzach sa ignorowane

8.   wielokrotne entery         3 entery miedzy     --                 blad                     blad                 przewidywany. GIMP tez sie
     pomiedzy komentarzami      w.w komentarzami                                                                     na tym wysypuje

9.   komentarze rozdzielone     ciag znakow miedzy  --                 blad                     blad                 przewdywany. w zgodzie ze 
     znakami czarnymi           2 komentarzami                                                                       standardem, komentarze musza
                                                                                                                     nastepowac po sobie 

10.  komentarz w złym           komentarz przed P3  --                 blad                     blad                 pozytywny. jest tylko jedno
     miejscu                    | po odcieniach                                                                      miejsce, gdzie moga wystapic
                                | w polowie pixeli                                                                   komentarze.

11.  zbyt dlugi rzad            rzedy pixeli po     zmiana poziomow,   obraz                   obraz                 pozytywny. program radzi
     pixeli                     200 znakow          zapis                                                            sobie z dowolnym ukladem
                                                                                                                     danych w pliku

12.  ilosc pixeli nie           wymiary 20, 40      zmiana poziomow    obraz zdeformowany      zdeformowany          pozytywny. dane wejsciowe
     pokrywa sie z danymi       obraz 16, 32        zapis                                                            musza byc poprawne

13. wartosci pixeli             skala: 15            zmiana poziomow    pixele znormalizowane   znormalizowane       - pozytywny. filtr robi co
    wychodza poza zakres        pixele od -10                                                                         do niego nalezy
                                do 20               gamma              cos dziwnego            cos dziwnego         - przewidywany. filtr nie radzi
                                                                                                                      sobie z wartosciami ujemnymi
                                                    rozmycie pionowe   obraz rozmyty           rozmyty              - pozytywny. filtr usrednia
                                                                                                                      wszystko jak leci
                                                    histogram          przeklamany             przeklamany          - przewidywany. program
                                                                                                                      normalizuje wart. wychodzace
                                                                                                                      za skale od gory, ale nie
                                                                                                                      radzi sobie z minimami
                                                                                                                        
----testy przetwarzan----
 ***poprawnosc orzekana na podstawie porownan identycznego dzialania w programie Image Magic***
    (powrownanie mialo charakter wizualny, jako, ze wyniki dzialania programu Image Magic nie
     nadaja sie do odczytania w trybie tekstowym)

    test na obrazie:              f.ppm              j.jpg              kubus.pgm
    (przeprowadzone dla kazdego
    koloru i szarosci)

1.  zmiana poziomow
    - 20 30                       pozytywny          pozytywny          pozytywny  
    - 10 90                       pozytywny          pozytywny          pozytywny  
    - -5 99                       pozytywny (blad)   pozytywny (blad)   pozytywny (blad)  
    - 50 40                       pozytywny (blad)   pozytywny (blad)   pozytywny (blad) 

2.  korekcja gamma
    - 1.5                         pozytywny          pozytywny          pozytywny   
    - 20                          pozytywny          pozytywny          pozytywny   
    - -2                          pozytywny (blad)   pozytywny (blad)   pozytywny (blad)

3.  rozmycie pionowe
    - 1                           pozytywny          pozytywny          pozytywny  
    - 2                           pozytywny          pozytywny          pozytywny  
    - 3                           pozytywny          pozytywny          pozytywny   
    - -1                          pozytywny (blad)   pozytywny (blad)   pozytywny (blad)  
    - 1.5                         pozytywny          pozytywny          pozytywny

4.  rozciagniecie histogramu      pozytywny          pozytywny          pozytywny  

----inne--------------

1. komentarze w pliku             zawsze pojawiaja sie w zapisanych plikach PGM i PPM, z informacja o dacie zapisu i operacji jaka byla
   wyjsciowym                     przeprowadzona na oryginale (z parametrami wlacznie)

2. opcje                          obojetnie ile razy wystepuja, w jakim zestawie i co po czym, jest okej.

3. pomoc                          pomoc ladnie sie wyswietla za pomoca polecenia less. Wtedy ignorowane sa inne podane opcje (chyba, ze ktoras
                                  ma wyrzucic blad a jest podana wczesniej)

4. jpg                            odpornosci biblioteki OpenCV na bledy plikow wejsciowych nie sprawdzalam. Dosc ze dobrze radzi sobie z grafikami
                                  z internetu.


*/

/* WNIOSKI:
    1. Jesli user poda wiecej niz 1 -o lub -i waznebedzie tylko to ostatnie. 
    2. Wczytywanie obrazu ze standardowego wyjscia wymaga wklejenia OBRAZU do terminala a nie tylko nazwy.
    3. Obraz nie wyswietla sie wtedy, gdy wyjscie zostaje przekierowane na terminal.
    4. Rzadanie konwersji do szarosci jest ignorowane dla plikow innych niz ppm.
    5. Gdy nie wybierze sie koloru do przetwarzania przy plikach ppm, przetwarzja sie wszystkie.
       (w komentarzach: Kolor 4, ale bez konwersji do szarosci).
    6. Plik inout.c jest zbedny, bo kazdy obraz dalby sie wczytac przez funkcje jpg_odczyt() i zapisac przez
       jpg_zapis(), ale zadanie przewiduje napisanie dedykowanych funkcji.

*/

#endif
