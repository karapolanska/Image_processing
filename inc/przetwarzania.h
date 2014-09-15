#ifndef przetwarzania_H
#define przetwarzania_H

/* GeeksOnBoard
 * 2013
 * przetwarzania.h
 */

/*To all below: statement "function takes" reffers to structural variable
  obraz with type w_obraz */ 
/*All functions below print comments to table obraz.s[i] about what they did */

/* Transformation: level change **********************************************/
/*  function arguments:                                                      */
/*     - obraz -structure with infos about image                             */
/*     - czern, biel -back and white levels                                  */
/*     - kolor -color to be processed                                        */
/*     - a -number of comment to be printed                                  */
/*  PRE:                                                                     */
/*     Function takes levels of white and black between 0-100.               */
/*     Wherein white must be greater than black.                             */
/*  POST:                                                                    */
/*     Function returns picture with new levels of "white" and "black".      */
/*     after using tresholding for the current color.                        */
/*     If everything goes well, returned value is 666.                       */
/*****************************************************************************/
int zmpozm(w_obraz *obraz, float czern, float biel, int kolor, int a);

/* Transformation: gamma correction ******************************************/
/*  funkction arguments:                                                     */
/*     - obraz -structure with infos about image                             */
/*     - gama -parameter gamma                                               */
/*     - kolor -color to be processed                                        */
/*     - a -number of comment to be printed                                  */
/*  PRE:                                                                     */
/*     Function takes gamma parameter (float number).                        */
/*  POST:                                                                    */
/*     Function returns image after gamma correction with given parameter.   */
/*     Only one color is processed.                                          */
/*     If everything goes well, returned value is 666.                       */
/*****************************************************************************/
int gammaa(w_obraz *obraz, float gama, int kolor,  int a);

/* przetwarzanie: rozmycie pionowe *******************************************/
/*  funkction arguments:                                                     */
/*     - obraz -structure with infos about image                             */
/*     - r -blur radius                                                      */
/*     - a -number of comment to be printed                                  */
/*  PRE:                                                                     */
/*     Takes blur radius (conversion to integer).                            */
/*  POST:                                                                    */
/*     Returns image blured vertically with given blur radius.               */
/*  COMMENT:                                                                 */
/*     Image is blured globally regardless of current color                  */
/*     (bluring of only on color seems to be stupid).                        */
/*     If everything goes well, returned value is 666.                       */
/*****************************************************************************/
int rozmycie_y(w_obraz *obraz, float r,  int a);

/* Transformation: histogram stretching **************************************/
/*  funkction arguments:                                                     */
/*     - obraz -structure with infos about image                             */
/*     - kolor -color, to be processed                                       */
/*     - a -number of comment to be printed                                  */
/*  PRE:                                                                     */
/*     The only argument is image.                                           */
/*  POST:                                                                    */
/*     Returns picture with grayscale stretched to maximum.                  */
/*     (gray or chosen color)                                                */
/*     If everything goes well, returned value is 666.                       */
/*****************************************************************************/
int histogram(w_obraz *obraz, int kolor, int a);

/* conversion to gray ********************************************************/
/*  funkction arguments:                                                     */
/*     - obraz -structure with infos about image                             */
/*     - a -number of comment to be printed                                  */
/*  PRE:                                                                     */
/*     Takes PPM image.                                                      */
/*  POST:                                                                    */
/*     Averages values of component colors overriding them all.              */
/*     3 tables structure is preserved.                                      */
/*     (for the picture to remain compatibile with PPM standard where 3      */
/*     values make one pixel.)                                                      */
/*     If everything goes well, returned value is 666.                       */                           
/*****************************************************************************/

int szarosci(w_obraz *obraz, int a);


#endif
