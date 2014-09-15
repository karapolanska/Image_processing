#ifndef wywolania_H
#define wywolania_H

/* GeeksOnBoard
 * 2013
 * wywolania.h
 */


/*Structure containing pointers to files and program arguments                                   */

typedef struct {
  FILE *plik_we, *plik_wy;        /* pointers to input and output files. */
  char opcje[50];                 /* options */
  float params[50];               /* option parameters */ 
} w_opcje;

/*-----macros------------------------------------------------------------------------------------*/
#define DL_LINII 70

/*structure containing infos about loaded image                                                  */
typedef struct {
  char *nazwa;                /*points at output file name (loaded in przetwarzaj_opcje())*/
  char *nazwa_we;             /*points at input file name*/
  char magic_no[4];           /*magic no*/
  char s[100][DL_LINII];      /*comments*/
  int wymx;                   /*width*/
  int wymy;                   /*height*/
  unsigned int odcienie;      /*max value of shades*/
  int **pgm;                  /*black&white 2d tables*/
  int **red, **green, **blue; /*Colory in 3 2d tables*/
} w_obraz;


/* Recognizes program call options from argv table and saves then in wybor structure***************/
/* function arguments:                                                                            */
/*         argc  -  number of program call options                                                */
/*         argv  -  table of call options                                                         */
/*         wybor -  structure with infos about calles options                                     */
/*         obraz -  structure with infos about image                                              */
/* PRE:                                                                                           */
/*      None.                                                                                     */
/* POST:                                                                                          */
/*      Function opens apropriate files, returns their pointer to wybor structure, prints options */
/*      to opcje table and their parameters to params tab. Returns 0 if the call was correct      */
/*	or error communicates and -1 if not. Everything must be 100% correct.                     */
/* COMMENTS:                                                                                      */
/*      Function doesn't check the existence nor access rights to files. In any case returned     */
/*      pointers have the value of NULL.                                                          */
/*      Function doesn't check if parameter -m (color) can be used with specified picture.        */
/*                                                                                                */
/*      Function contains quotations of fragments developed by (c) 2007-2013 ZPCiR                */
/**************************************************************************************************/
int przetwarzaj_opcje(int argc, char **argv, w_opcje *wybor, w_obraz *obraz, _Bool *display);


/* Help *******************************************************************************************/
/* Function displays available options using program less, referring to external file called      */
/* help.                                                                                          */
/**************************************************************************************************/
void help(void);

#endif
