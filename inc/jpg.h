#ifndef jpg_H
#define jpg_H

/* GeeksOnBoard
 * 2013
 */

/* Reading JPG files *******************************************/
/* function arguments:                                        */
/*     wybor - structure with pointers to files.               */
/*     obraz- structure containing pixels.                     */
/* PRE:                                                        */
/*     It uses OpenCV library.                                 */
/* POST:                                                       */
/*     Function reads files: jpg, jpeg, bmp and much more,     */
/*     also pgm i ppm, but for them program uses different     */
/*     functions.                                              */
/***************************************************************/
int jpg_odczyt(w_opcje wybor, w_obraz *obraz);

/* Saving JPG files ********************************************/
/* function arguments:                                         */
/*     wybor - structure with pointers to files.               */
/*     obraz- structure with pixels.                           */
/* PRE:                                                        */
/*     It uses OpenCV library.                                 */
/* POST:                                                       */
/*     Function saves files opened by jpg_odczyt().            */
/***************************************************************/
void jpg_zapis(w_opcje wybor, w_obraz *obraz);

#endif
