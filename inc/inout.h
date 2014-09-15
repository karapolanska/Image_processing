#ifndef inout_H
#define inout_H

/* GeeksOnboard
 * 2013
 * inout.h
 */

/* Reading image from file ***************************************/
/*   function arguments:                                         */
/*       - wybor -structure with infos about chosen options      */
/*       - obraz -structure with infos about image               */
/*       - i -number of comments                                 */
/*   PRE:                                                        */
/*       None. Function takes image parameters from structure.   */
/*       w_opcje from wywolania.h                                */
/*   POST:                                                       */
/*       Function fills structure w_obraz and returns failure    */
/*       code -1 or success code 0.                              */
/*****************************************************************/
int czytaj(w_opcje wybor, w_obraz *obraz, int *i);


/* Displays image via program "display" **************************/
/*   function arguments:                                         */
/*       - n_pliku -name of file to be displayed                 */
/*   PRE:                                                        */
/*       None. Function takes the name from the structure        */
/*   POST:                                                       */
/*       Function launches program display and uses it to        */
/*       display image. Than it prints the command on stdout.    */
/*****************************************************************/
void wyswietl(char *n_pliku);


/* Saves image to the file ***************************************/
/*   function arguments:                                         */
/*       - wybor -structure with infos about chosen options      */
/*       - obraz -structure with infos about image               */
/*       - i -number of comments                                 */
/*       - kody - flag telling if colors codes were used in      */
/*         comments and if the label must be printed             */
/*   PRE:                                                        */
/*       None. Function takes parameters from structure.         */
/*   POST:                                                       */
/*       Function saves image in specified file                  */
/*****************************************************************/
void zapis(w_opcje wybor, w_obraz *obraz, int i, _Bool kody );

#endif
