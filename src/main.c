/* GeeksOnBoard
 * 2013
 * main.c
 */


/*libraries*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

/*headings*/
#include"../inc/wywolania.h"
#include"../inc/inout.h"
#include"../inc/przetwarzania.h"
#include"../inc/main.h"
#include"../inc/jpg.h"


int main(int argc, char **argv) {

  w_opcje wybor; /*look: wywolania.h*/
  w_obraz obraz;

  int i=0;         /*comment counter                                                */
  int o=0, p=0;    /*for parameters and options                                     */
  int kolor=4;     /*contains currently processed color                             */
                   /*1-red, 2-green, 3-blue, 4-grays                                */
  _Bool display=0; /*flag whether to display or not. Default: not.                  */
  _Bool kody=0;    /*flag whether in the comment are used and if to paste the legend*/
                   /*Default: not.                                                  */
  int zmienna;

  char data[10]; /*contains time (printed in comments)*/
  time_t czas;   /*time of time type.*/

  if(argc==1) {
    printf("Error: No arguments specified. See: --help\n");
    return -1;
  }

  /*opening files to read and write, loading options to tabels in wybor structure  */
  if(przetwarzaj_opcje(argc, argv, &wybor, &obraz, &display)==-1) /*quit if failed */
    return -1;

  /*loading the image info to obraz structure */
  
  zmienna=czytaj(wybor ,&obraz, &i );
  if(zmienna==-1)       /*if error...*/
    return -1;
  else if(zmienna==8) { /*if file other than pgm or ppm */
    jpg_odczyt(wybor, &obraz);
  }

  /*loading the date of launching the program*/
  czas=time(NULL);
  strftime(data, 10, "%d/%m/%y", localtime(&czas));

  /*options processing*/
  for(o=0; o<argc; o++) {
     switch (wybor.opcje[o]) {
       case 'm':
         if(obraz.magic_no[1]!='3')
           printf("option -m works only for colorful pics. Will be omitted.\n");
         else {
           /*Change of current color to be processed*/
           kolor=wybor.params[p]; p++;
           if (kolor==4) {
             /*Conversion to grays*/
             if(szarosci(&obraz, i)==666) {
               printf("Conversion to grays - success\n");
               strcat(obraz.s[i], data); /*adding the comment to the end of table*/
               strcat(obraz.s[i], "\n");
               i++;
             }
             else {
               printf("Conversion to grays - failure\n");
               return -1;
             }
           }
         }
         break;
       case 'z':
         /*level change*/
         if(zmpozm(&obraz, wybor.params[p], wybor.params[p+1], kolor, i)==666) {
           printf("level change - success\n");
           strcat(obraz.s[i], data); /*adding the comment to the end of table*/
           strcat(obraz.s[i], "\n"); i++;
         }
         else {
           printf("level change - failure\n");
           return -1;
         }
         p+=2;
         kody=1;
         break; 
       case 'g':
         /*gamma correction*/
         if(gammaa(&obraz, wybor.params[p], kolor, i)==666) {
           printf("gamma correction - sukces\n");
           strcat(obraz.s[i], data); /*adding the comment to the end of table*/
           strcat(obraz.s[i], "\n"); i++;
         }
         else {
           printf("gamma correction - failure\n");
           return -1;
         }
         p++;
         kody=1;
         break;
       case 'r':
         /*vertical blur*/
         if(rozmycie_y(&obraz, wybor.params[p], i)==666) {
           printf("vertical blur - success\n");
           strcat(obraz.s[i], data); /*adding the comment to the end of table*/
           strcat(obraz.s[i], "\n"); i++;
         }
         else {
           printf("vertical blur - failure\n");
           return -1;
         }
         p++;
         break;
       case 'h':
         /*histogram stretching*/
         if(histogram(&obraz, kolor, i)==666) {
           printf("histogram stretching - success\n");
           strcat(obraz.s[i], data); /*adding the comment to the end of table*/
           strcat(obraz.s[i], "\n"); i++;
         }
         else {
           printf("histogram stretching - failure\n");
           return -1;
         }
         break;
     } /*switch*/
  } /*for*/

  /*saving image to the output file*/
  /*PGM or PPM*/
  if(obraz.magic_no[0]=='P')
    zapis(wybor, &obraz, i, kody );
  /*any other*/
  else
    jpg_zapis(wybor, &obraz);

  /*displaying*/
  if(display==1)
    wyswietl(obraz.nazwa);
 
  return 0;
}/*main*/


