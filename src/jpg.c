/* GeeksOnBoard
 * 2013
 * jpg.c
 */

/*libraries*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<cv.h>
#include<highgui.h>
/*headings*/
#include"../inc/wywolania.h"
#include"../inc/inout.h"
#include"../inc/przetwarzania.h"

int jpg_odczyt(w_opcje wybor, w_obraz *obraz) {

  CvScalar punkt;      /*pixel of embeded type     */
  int kolory;          /*number of colors in pis   */  
  unsigned int max=0;  /*maximum value of pixel    */
  int i, j;            /*helpers                   */ 
  IplImage *obr_zrodlowy = 0;    /*structure image */

  /*image loading*/
  obr_zrodlowy = cvLoadImage(obraz->nazwa_we, -1);

  kolory=obr_zrodlowy->nChannels;

  obraz->wymx = obr_zrodlowy->width;
  obraz->wymy = obr_zrodlowy->height;
 
  /*memory allocation and loading colored picture*/
  if(kolory==3) {
    /*magic numer - type "colorful"*/
    strcpy(&obraz->magic_no[1], "3");

    obraz->red = (int**) malloc(obraz->wymy*sizeof(int*));
    obraz->green = (int**) malloc(obraz->wymy*sizeof(int*));
    obraz->blue = (int**) malloc(obraz->wymy*sizeof(int*));
    for (j = 0; j<obraz->wymy; j++) {
      obraz->red[j] = (int*) malloc(obraz->wymx*sizeof(int));
      obraz->green[j] = (int*) malloc(obraz->wymx*sizeof(int));
      obraz->blue[j] = (int*) malloc(obraz->wymx*sizeof(int));
    } 

    for(i=0;i<obraz->wymy;i++) {
       for(j=0;j<obraz->wymx;j++) {
         punkt=cvGet2D(obr_zrodlowy, i, j);
         if ( (obraz->blue[i][j]=punkt.val[0]) > max) max=obraz->blue[i][j];
         if ( (obraz->green[i][j]=punkt.val[1]) > max) max=obraz->green[i][j];
         if ( (obraz->red[i][j]=punkt.val[2]) > max) max=obraz->red[i][j];
       }
    }
  }
  /*memory allocation and loading monochromatic picture*/
  else if(kolory==1) {
    /*magic numer - type "monochromatic"*/
    strcpy(&obraz->magic_no[1], "2");

    obraz->pgm = (int**) malloc(obraz->wymy*sizeof(int*));
    for (j = 0; j<obraz->wymy; j++) {
      obraz->pgm[j] = (int*) malloc(obraz->wymx*sizeof(int));
    }

    for(i=0;i<obraz->wymy;i++) {
       for(j=0;j<obraz->wymx;j++) {
         punkt=cvGet2D(obr_zrodlowy, i, j);
         if( (obraz->pgm[i][j]=punkt.val[0]) > max) max=obraz->pgm[i][j];
       }
    }
  }
  else {
    fprintf( stderr, "Error: unknow number of colors in image.\n");
    return -1;
  }

  obraz->odcienie=max;
  return 0;
}


void jpg_zapis(w_opcje wybor, w_obraz *obraz) {
  CvScalar punkt;
  int kolory;
  int i, j;

  IplImage *obr_docelowy = 0;

  obr_docelowy = cvLoadImage(obraz->nazwa_we, -1);    //loading file in original colors

  obraz->wymx = obr_docelowy->width;
  obraz->wymy = obr_docelowy->height;

  kolory=obr_docelowy->nChannels;

  //saving colorful image and releasing memory
  if(kolory==3) {
    for(i=0;i<obraz->wymy;i++) {
       for(j=0;j<obraz->wymx;j++) {
         punkt.val[0]=obraz->blue[i][j];
         punkt.val[1]=obraz->green[i][j];
         punkt.val[2]=obraz->red[i][j];
         cvSet2D(obr_docelowy, i, j, punkt);
       }
    }

    cvSaveImage(obraz->nazwa, obr_docelowy, 0);

    for (i = 0; i<obraz->wymy; i++) {
      free(obraz->red[i]);
      free(obraz->green[i]);
      free(obraz->blue[i]);
    }
    free(obraz->red);
    free(obraz->green);
    free(obraz->blue); 

  }
  //saving monochromatic image and releasing memory
  else if(kolory==1) {
    for(i=0;i<obraz->wymy;i++) {
       for(j=0;j<obraz->wymx;j++) {
         punkt.val[0]=obraz->pgm[i][j];
         cvSet2D(obr_docelowy, i, j, punkt);
       }
    }

    cvSaveImage(obraz->nazwa, obr_docelowy, 0);

    for (i = 0; i<obraz->wymy; i++) {
      free(obraz->pgm[i]);
    }
    free(obraz->pgm);
  }


  //Closing the file. File saved = file closed
  fclose(wybor.plik_wy);
}
