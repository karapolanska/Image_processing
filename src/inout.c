/* GeeksOnBoard
 * 2013
 * inout.c
 */

/*libraries*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
/*headings*/
#include"../inc/wywolania.h"
#include"../inc/inout.h"
#include"../inc/przetwarzania.h"


int czytaj(w_opcje wybor, w_obraz *obraz, int *i ) {

  _Bool czy_kolor; /*flag determining if PGM or PPM proceeded*/
  _Bool koniec;    /*flag determining if comments to be ommited are present*/
  int znak;        /*to find hash while seeking for comments*/
  int j, k;        /*helpers*/

  /*downloading the first line*/
  if (fgets(obraz->magic_no,DL_LINII,wybor.plik_we)==NULL) return -1;

  /* Checking the "magic number" - should be P2 or P3 */
  if ( (obraz->magic_no[0]=='P') && (obraz->magic_no[1]=='2')) {
    czy_kolor=0;
  }
  else if ( (obraz->magic_no[0]=='P') && (obraz->magic_no[1]=='3')) {
    czy_kolor=1;
  }
  else {
    /*moving the pointer to the beginning of file*/
    fseek(wybor.plik_we, 0L, SEEK_SET);
    return 8; /*JPG*/
  }
  
  /* Comments ommiting */
  do {
    if ((znak=fgetc(wybor.plik_we))=='#') {
      ungetc(znak,wybor.plik_we);
      if (fgets(obraz->s[*i],DL_LINII,wybor.plik_we)==NULL) koniec=1;
      (*i)++; 
    } 
    else {
      ungetc(znak,wybor.plik_we); 
    }
  } while (!koniec && znak=='#');
   
  /* Taking the size of cancas and number of tones of grays or color*/
  if (fscanf(wybor.plik_we,"%d %d %d", &obraz->wymx, &obraz->wymy, &obraz->odcienie)!=3) {
   fprintf(stderr,"Error: Size or number of szades missing.\n");
   return -1;
  } 

  /* PGM file */
  if(czy_kolor==0) {      

    /*first stage of allocation - creation of pointer table of the canvas' height*/
    obraz->pgm = (int**) malloc(obraz->wymy*sizeof(int*));
    for (j = 0; j<obraz->wymy; j++) {
      obraz->pgm[j] = (int*) malloc(obraz->wymx*sizeof(int));  /*Second stage of allocation - we allocate table for every pointer */
    }                                                          /*in size equal to the canvas' width */

    /*Filling the table with values*/
    for (j = 0; j<obraz->wymy; j++) {
      for (k = 0;k<obraz->wymx; k++) {
	if(fscanf(wybor.plik_we, "%d", &(obraz->pgm[j][k])) != 1) {
	  fprintf(stderr,"Error: Wrong image size\n");
          return -1;
        }
      }
    }

    return 0;
  }
  /*PPM file*/
  else if (czy_kolor==1) {
    /*red, green, blue*/
    obraz->red = (int**) malloc(obraz->wymy*sizeof(int*));
    obraz->green = (int**) malloc(obraz->wymy*sizeof(int*));
    obraz->blue = (int**) malloc(obraz->wymy*sizeof(int*));
    for (j = 0; j<obraz->wymy; j++) {
      obraz->red[j] = (int*) malloc(obraz->wymx*sizeof(int));
      obraz->green[j] = (int*) malloc(obraz->wymx*sizeof(int));
      obraz->blue[j] = (int*) malloc(obraz->wymx*sizeof(int));
    }                                                             

    /*Filling the table. Every third goes to one table.*/
    for (j = 0; j<obraz->wymy; j++) {
      for (k = 0;k<obraz->wymx; k++) {
        /*red*/
	  if(fscanf(wybor.plik_we, "%d", &(obraz->red[j][k])) != 1) {
	    fprintf(stderr,"Error: Wrong image size\n");
            return -1;
          }
        /*green*/
	  if(fscanf(wybor.plik_we, "%d", &(obraz->green[j][k])) != 1) {
	    fprintf(stderr,"Error: Wrong image size\n");
            return -1;
          }
        /*blue*/
	  if(fscanf(wybor.plik_we, "%d", &(obraz->blue[j][k])) != 1) {
	    fprintf(stderr,"Error: Wrong image size\n");
            return -1;
          }
      }
    }

    return 0;
  }/*PPM*/

  return 0;
}/*---------------------------------------------------*/



/*Displaying the image with spcified name using the program "display"*/
void wyswietl(char *n_pliku) {
  char polecenie[1024];
  strcpy(polecenie,"display ");
  strcat(polecenie,n_pliku);
  strcat(polecenie," &");  
  printf("%s\n",polecenie);
  system(polecenie);
}/*---------------------------------------------------*/

/*Saving to file--------------------------------------*/
void zapis(w_opcje wybor, w_obraz *obraz, int i, _Bool kody ) {
  int k, l; /*helpers */

  /*printing the magic number (look: wywolania.c)*/
  fprintf(wybor.plik_wy, "%c%c\n", obraz->magic_no[0], obraz->magic_no[1]);
  /*printing comments*/
  for(k=0;k<i;k++) {
    fprintf(wybor.plik_wy, "%s", obraz->s[k]);
  }
  /*color codes explanation */
  if(kody==1) fprintf(wybor.plik_wy, "# (Kody kolorow: 1-czerwony, 2-zielony, 3-niebieski, 4-szarosci)\n");
  /*printing sizes and tones*/
  fprintf(wybor.plik_wy, "%d %d\n%d\n", obraz->wymx, obraz->wymy, obraz->odcienie);

  /*printing values and releasing the tables*/
  /*PGM*/
  if (obraz->magic_no[1]=='2') {
    for(k=0; k<obraz->wymy; k++) {
      for(l=0; l<obraz->wymx; l++) {
        fprintf(wybor.plik_wy, "%3d ", obraz->pgm[k][l] );
      }
      fprintf(wybor.plik_wy, "\n");
    }
    for (k = 0; k<obraz->wymy; k++) {
      free(obraz->pgm[k]);
    }
    free(obraz->pgm);
  }
  /*PPM*/
  else if (obraz->magic_no[1]=='3'){
    for(k=0; k<obraz->wymy; k++) {
      for(l=0; l<obraz->wymx; l++) {
         fprintf(wybor.plik_wy, "%3d ", obraz->red[k][l] );
         fprintf(wybor.plik_wy, "%3d ", obraz->green[k][l] );
         fprintf(wybor.plik_wy, "%3d ", obraz->blue[k][l] );
      }
      fprintf(wybor.plik_wy, "\n");
    }

    for (k = 0; k<obraz->wymy; k++) {
      free(obraz->red[k]);
      free(obraz->green[k]);
      free(obraz->blue[k]);
    }
    free(obraz->red);
    free(obraz->green);
    free(obraz->blue); 
  }

  /*Closing the file. File saved = file closed*/
  fclose(wybor.plik_wy);

}/*---------------------------------------------------*/


