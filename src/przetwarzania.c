/* GeeksOnBoard
 * 2013
 * przetwarzania.c
 */

/*libraries*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
/*headers*/
#include"../inc/wywolania.h"
#include"../inc/inout.h"
#include"../inc/przetwarzania.h"


/*TRANSFORMATION 1: changing balance -------------*/
int zmpozm(w_obraz *obraz, float czern, float biel, int kolor, int a){
  /*names 'czern' i 'biel' are misleading, as they relate also to colors!*/
  int c, d; /*normalized levels (percent of all schades)*/
  int i,j;  /*helpers*/

  /*counting normalized values*/
  c=czern*obraz->odcienie/100;
  d=biel*obraz->odcienie/100;

  /*changing levels according to algorithm*/
  /*in case of ppm images, processed is one color or all of them in case of
    gray conversion with prior averaging.*/
  if (obraz->magic_no[1]=='2') {
    for (i=0;i<obraz->wymy;i++) {
      for (j=0;j<obraz->wymx;j++) {
        if (obraz->pgm[i][j]<=c) {
	  obraz->pgm[i][j]=0;
        }
        else if (obraz->pgm[i][j]>=d) {
	  obraz->pgm[i][j]=obraz->odcienie;
        } 
        else {
          obraz->pgm[i][j]=(obraz->pgm[i][j]-c)*obraz->odcienie/(d-c);
        }
      }
    }
  }
  else if (obraz->magic_no[1]=='3'){
    /*red*/
    if (kolor==1 || kolor==4 ) {
      for (i=0;i<obraz->wymy;i++) {
        for (j=0;j<obraz->wymx;j++) {
          if (obraz->red[i][j]<=c) {
	    obraz->red[i][j]=0;
          }
          else if (obraz->red[i][j]>=d) {
	    obraz->red[i][j]=obraz->odcienie;
          }
          else {
            obraz->red[i][j]=(obraz->red[i][j]-c)*obraz->odcienie/(d-c);
          }
        }
      }
    }
    /*green*/
    if (kolor==2 || kolor==4 ) {
      for (i=0;i<obraz->wymy;i++) {
        for (j=0;j<obraz->wymx;j++) {
          if (obraz->green[i][j]<=c) {
	    obraz->green[i][j]=0;
          }
          else if (obraz->green[i][j]>=d) {
	    obraz->green[i][j]=obraz->odcienie;
          }
          else {
            obraz->green[i][j]=(obraz->green[i][j]-c)*obraz->odcienie/(d-c);
          }
        }
      }
    }
    /*blue*/
    if (kolor==3 || kolor==4 ) {
      for (i=0;i<obraz->wymy;i++) {
        for (j=0;j<obraz->wymx;j++) {
          if (obraz->blue[i][j]<=c) {
	    obraz->blue[i][j]=0;
          }
          else if (obraz->blue[i][j]>=d) {
	    obraz->blue[i][j]=obraz->odcienie;
          }
          else {
            obraz->blue[i][j]=(obraz->blue[i][j]-c)*obraz->odcienie/(d-c);
          }
        }
      }
    }
  }
  /*comments*/
  sprintf(obraz->s[a], "# Lvl change. Color: %d. Black: %.1f. White: %.1f. Date: ", kolor, czern, biel);
  /*signal ok*/
  return 666;
}/*------------------------------------------------*/

/*TRANSFORMATION 2: gamma filter-------------------*/
int gammaa(w_obraz *obraz, float gama, int kolor, int a){
  /*in case of ppm images, processed is one color or all of them in case of
    gray conversion with prior averaging.*/
  int i,j;  /*helpers*/

  /*PGM*/
  if(obraz->magic_no[1]=='2') {
    for (i=0;i<obraz->wymy;i++) {
      for (j=0;j<obraz->wymx;j++) {
        obraz->pgm[i][j]=pow(obraz->pgm[i][j], 1.0/gama)/pow(obraz->odcienie, (1.0-gama)/gama);
      }
    }
  }
  /*PPM*/
  else if(obraz->magic_no[1]=='3') {
    /*red*/
    if(kolor==1 || kolor==4) {
      for (i=0;i<obraz->wymy;i++) {
        for (j=0;j<obraz->wymx;j++) {
          obraz->red[i][j]=pow(obraz->red[i][j], 1.0/gama)/pow(obraz->odcienie, (1.0-gama)/gama);
        }
      }
    }
    /*green*/
    if(kolor==2 || kolor==4) {
      for (i=0;i<obraz->wymy;i++) {
        for (j=0;j<obraz->wymx;j++) {
          obraz->green[i][j]=pow(obraz->green[i][j], 1.0/gama)/pow(obraz->odcienie, (1.0-gama)/gama);
        }
      }
    }
    /*blue*/
    if(kolor==3 || kolor==4) {
      for (i=0;i<obraz->wymy;i++) {
        for (j=0;j<obraz->wymx;j++) {
          obraz->blue[i][j]=pow(obraz->blue[i][j], 1.0/gama)/pow(obraz->odcienie, (1.0-gama)/gama);
        }
      }
    }
  }
  sprintf(obraz->s[a], "# Gamma trans. Color: %d. Gamma: %.2f. Date: ", kolor, gama);
  return 666;
}/*-----------------------------------------------*/

/*TRANSFORMATION 3: vertical blur-----------------*/
int rozmycie_y(w_obraz *obraz, float promien, int a){
  int **rozmyty, **rozmyty_r, **rozmyty_g, **rozmyty_b;   /*contain processed pixels  */
  int n=0;                                            /*number of processed cells     */
  long int suma=0, suma_r=0, suma_g=0, suma_b=0;      /*sum and values of cells       */
  int i, j, k;                                        /*helpers                       */
  int r=(int)promien;

  /*PGM*/
  if (obraz->magic_no[1]=='2') {

    /*memory allocaion for new helper table */
    rozmyty = (int**) malloc(obraz->wymy*sizeof(int*));
    for (j = 0; j<obraz->wymy; j++) {
      rozmyty[j] = (int*) malloc(obraz->wymx*sizeof(int));
    }

    /*new pixel values*/
    for (i=0;i<obraz->wymy;i++) {
      for (j=0;j<obraz->wymx;j++) {
         for(k=-r; k<=r; k++){           /*for surrounding of radius r,    */
           if(i+k<obraz->wymy && i+k >= 0) {    /*omitting pixels which    */
            suma+=obraz->pgm[i+k][j];   /*exceeds the canvas size          */
            n++;
           }
         }
         rozmyty[i][j]=suma/n;
         suma=0;
         n=0;
      }
    }

    /*transcription of new values*/
    for (i=0;i<obraz->wymy;i++) {
      for (j=0;j<obraz->wymx;j++) {
        obraz->pgm[i][j]=rozmyty[i][j];
      }
    }
    free(rozmyty);
  }

  /*PPM*/
  else if (obraz->magic_no[1]=='3') {
    /*red, green, blue*/
    rozmyty_r = (int**) malloc(obraz->wymy*sizeof(int*));
    rozmyty_g = (int**) malloc(obraz->wymy*sizeof(int*));
    rozmyty_b = (int**) malloc(obraz->wymy*sizeof(int*));
    for (j = 0; j<obraz->wymy; j++) {
      rozmyty_r[j] = (int*) malloc(obraz->wymx*sizeof(int));
      rozmyty_g[j] = (int*) malloc(obraz->wymx*sizeof(int));
      rozmyty_b[j] = (int*) malloc(obraz->wymx*sizeof(int));
    }                                                             

    /*counting new pixel values*/
    for (i=0;i<obraz->wymy;i++) {
      for (j=0;j<obraz->wymx;j++) {
         for(k=-r; k<=r; k++){                  /*for surrounding of radius r,    */
           if(i+k<obraz->wymy && i+k >= 0) {    /*omitting pixels which           */
            suma_r+=obraz->red[i+k][j];         /*exceeds the canvas size         */
            suma_g+=obraz->green[i+k][j];
            suma_b+=obraz->blue[i+k][j];
            n++;
           }
         }
         rozmyty_r[i][j]=suma_r/n;
         rozmyty_g[i][j]=suma_g/n;
         rozmyty_b[i][j]=suma_b/n;
         suma=0;
         n=0;
      }
    }

    /*transcription of new values*/
    for (i=0;i<obraz->wymy;i++) {
      for (j=0;j<obraz->wymx;j++) {
        obraz->red[i][j]=rozmyty_r[i][j];
        obraz->green[i][j]=rozmyty_g[i][j];
        obraz->blue[i][j]=rozmyty_b[i][j];
      }
    }
    for (j = 0; j<obraz->wymy; j++) {
     free(rozmyty_r[j]);
     free(rozmyty_g[j]);
     free(rozmyty_b[j]);
    }
    free(rozmyty_r);
    free(rozmyty_g);
    free(rozmyty_b);
  }


  sprintf( obraz->s[a], "# Vertical blur. Radius: %d. Date: ", r);
  return 666;

}/*------------------------------------------------*/

/*TRANSCRIPTION 4: histogram stretching--------*/
int histogram(w_obraz *obraz, int kolor, int a) {
  int max=0;                /*inicjalization of max value as the lowest possible */
  int min=obraz->odcienie;  /*the same but opposit                               */
  int i,j;

  /*PGM*/
  if(obraz->magic_no[1]=='2') {
    /*searching for extreme values*/
    for (i=0;i<obraz->wymy;i++) {
      for (j=0;j<obraz->wymx;j++) {
        if(obraz->pgm[i][j] > max)
          max = obraz->pgm[i][j];
        if(obraz->pgm[i][j] < min)
          min = obraz->pgm[i][j];      
      }
    }
    /*histogram stretching*/
    for (i=0;i<obraz->wymy;i++) {
      for (j=0;j<obraz->wymx;j++) {
        obraz->pgm[i][j]=(obraz->pgm[i][j] - min)*obraz->odcienie/(max-min);
      }
    }
  }

  /*PPM*/
  /*in case of ppm images, processed is one color or all of them in case of
    gray conversion with prior averaging.*/
  else if(obraz->magic_no[1]=='3') {
    if(kolor==1 || kolor ==4){
      /*searching for extreme values of reds*/
      for (i=0;i<obraz->wymy;i++) {
        for (j=0;j<obraz->wymx;j++) {
          if(obraz->red[i][j] > max)
            max = obraz->red[i][j];
          if(obraz->red[i][j] < min)
            min = obraz->red[i][j];      
        }
      }
      /*histogram stretching*/
      for (i=0;i<obraz->wymy;i++) {
        for (j=0;j<obraz->wymx;j++) {
          obraz->red[i][j]=(obraz->red[i][j] - min)*obraz->odcienie/(max-min);
        }
      }
    }
    if(kolor==2 || kolor ==4){
      max=0;               /*restoring the beginning value*/
      min=obraz->odcienie;  /*in case of occurance: '4'   */
      /*searching for extreme values of greens            */
      for (i=0;i<obraz->wymy;i++) {
        for (j=0;j<obraz->wymx;j++) {
          if(obraz->green[i][j] > max)
            max = obraz->green[i][j];
          if(obraz->green[i][j] < min)
            min = obraz->green[i][j];      
        }
      }
      /*histogram stretching*/
      for (i=0;i<obraz->wymy;i++) {
        for (j=0;j<obraz->wymx;j++) {
          obraz->green[i][j]=(obraz->green[i][j] - min)*obraz->odcienie/(max-min);
        }
      }
    }
    if(kolor==3 || kolor==4){
      max=0;               /*restoring the default value*/
      min=obraz->odcienie; /*in case of occurance '4'   */ 
      /*searching for extreme values of blues           */
      for (i=0;i<obraz->wymy;i++) {
        for (j=0;j<obraz->wymx;j++) {
          if(obraz->blue[i][j] > max)
            max = obraz->blue[i][j];
          if(obraz->blue[i][j] < min)
            min = obraz->blue[i][j];      
        }
      }
      /*histogram stretching*/
      for (i=0;i<obraz->wymy;i++) {
        for (j=0;j<obraz->wymx;j++) {
          obraz->blue[i][j]=(obraz->blue[i][j] - min)*obraz->odcienie/(max-min);
        }
      }
    }
  }


  sprintf(obraz->s[a], "# Histogram stretching. Color: %d. Date: ", kolor);
  return 666;
}/*------------------------------------------------*/

/* gray conversion --------------------------------*/
int szarosci( w_obraz *obraz, int a ) {
  int i, j;

  for (i=0;i<obraz->wymy;i++) {
    for (j=0;j<obraz->wymx;j++) {
      obraz->red[i][j]=obraz->green[i][j]=obraz->blue[i][j]=(obraz->red[i][j] + obraz->green[i][j] + obraz->blue[i][j])/3;
    }
  }

  sprintf(obraz->s[a], "# Gray conversion. Date: ");
  return 666;
}/*------------------------------------------------*/

