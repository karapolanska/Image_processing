/* GeeksOnBoard
 * 2013
 * wywolania.c
 */

/*libraries*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
/*headings*/
#include"../inc/wywolania.h"
#include"../inc/inout.h"
#include"../inc/przetwarzania.h"


int przetwarzaj_opcje(int argc, char **argv, w_opcje *wybor, w_obraz *obraz, _Bool *display) {
  char *nazwa_pliku_we, *nazwa_pliku_wy;
  int i, o=0, p=0;
  float czern, biel, gama, promien;
  char kolor;                   /*color to be proceeded */

  wybor->plik_wy=stdout;        /* in case there's no "-o" option specified */

  for (i=1; i<argc; i++) {

    if (argv[i][0] != '-') {    /* options must begin with "-" */
      fprintf(stderr, "Error: \"%s\" is not option - lack of \"-\" sign\n", argv[i]);
      return -1; 
    }
    /* help */
    if(!strcmp(argv[i],"--help")) {
      help();
      return -1;
    }
    /* option with the name of input file */
    else if(!strcmp(argv[i],"-i")) {
      if (++i<argc) {   /* next argument as a file name*/
	obraz->nazwa_we=nazwa_pliku_we=argv[i];
	if (strcmp(nazwa_pliku_we,"-")==0) /* if name is "-"        */
	  wybor->plik_we=stdin;            /* input is set as stdin. */
	else                               /* open specified file   */
	  wybor->plik_we=fopen(nazwa_pliku_we,"r");
      }
      else {
        fprintf(stderr, "Error: Incorrect input file name\n"); 
	return -1;
      }
    }
    /* Option with output file */
    else if(!strcmp(argv[i],"-o")) {
      if (++i<argc) {   /* next argument as a file name*/
	obraz->nazwa=nazwa_pliku_wy=argv[i];
	if (!strcmp(nazwa_pliku_wy,"-"))  /* if name is "-"          */
	  wybor->plik_wy=stdout;          /* output is set as stout. */
	else                              /* open specified file     */
	  wybor->plik_wy=fopen(nazwa_pliku_wy,"w");
      }
      else { 
        fprintf(stderr, "Error: Incorrect output file name\n");
	return -1;
      }
    }
    /*choice of color */
    else if(!strcmp(argv[i],"-m")) {
      if (++i<argc) {
        if (sscanf(argv[i], "%c", &kolor)==1) {
          if(kolor=='r') {
            wybor->opcje[o]='m';
            wybor->params[p]=1;
          }
          else if(kolor=='g') {
            wybor->opcje[o]='m';
            wybor->params[p]=2;
          }
          else if(kolor=='b') {
            wybor->opcje[o]='m';
            wybor->params[p]=3;
          }
          else if(kolor=='s') {
            wybor->opcje[o]='m';
            wybor->params[p]=4;
          }
          else {
           fprintf(stderr, "Error: parameter -m can take only \'r\', \'g\', \'b\' or \'s\'");
           return -1;
          }
          o++; p++;
        }  
        else {
          fprintf(stderr, "Error: Incorrect value of color parameter. See: --help\n");
          return -1;
        }
      }
      else {
         fprintf(stderr, "Error: No color value specified. See: --help\n");
         return -1;
      }
    }
    /*Level change */
    else if(!strcmp(argv[i],"-z")) {
      if (++i<argc) {                  /* next argument as black value */
	if ((sscanf(argv[i],"%f",&czern)==1) && (czern>=0) && (czern<=100)) {
          wybor->opcje[o]='z';         /*'z' goes to operation table */
	  wybor->params[p]=czern;      /*parameters go to table      */
	}
        else {
          fprintf(stderr, "Error: Incorrect value of black for change level operation.. See: --help\n");
	  return -1;
        }
        o++; p++;
      }
      else {
        fprintf(stderr, "Error: No value of black for change level operation.. See: --help\n");
	return -1;
      }

      if (++i<argc) { /* next argument as white value */
	if (sscanf(argv[i],"%f",&biel)==1 && (biel<=100)) {
          if (biel>=czern) {
	    wybor->params[p]=biel;
          }
          else {
            fprintf(stderr, "Error: White cannot be more dark than black!!!\n");
            return -1;
          }
          p++;
	}
        else {
          fprintf(stderr, "Error: Incorrect value of white for change level operation. See: --help\n");
	  return -1;
        }
      }
      else {
        fprintf(stderr, "Error: No value of white for change level operation. See: --help\n");
	return -1;
      }
    }
    /* Gamma correction */
    else if(!strcmp(argv[i],"-g")) {
      if (++i<argc) { /* next argument as gamma value */
	if (sscanf(argv[i],"%f",&gama)==1 && gama>0) {
	  wybor->opcje[o]='g';
	  wybor->params[p]=gama;
	}
        else {
          fprintf(stderr, "Error: Incorrect value of gamma factor. See --help\n");
	  return -1;
        }
        o++; p++;
      }
      else {
        fprintf(stderr, "Blad: No value of gamma factor. See --help\n");
	return -1;
      }             
    }
    /* Vertical blur */
    else if(!strcmp(argv[i],"-ry")) {
      if (++i<argc) { /* reading blur radius */
	if (sscanf(argv[i],"%f",&promien)==1 && promien>=0) {
	  wybor->opcje[o]='r';
	  wybor->params[p]=promien;
	}
        else {
          fprintf(stderr, "Error: Incorrect value of blur radius. See --help\n");
	  return -1;
        }
        o++; p++;
      }
      else {
        fprintf(stderr, "Error: No value of blur radius. See --help\n");
	return -1;
      }
    }
    /* Histogram stretching */
    else if(!strcmp(argv[i],"-h")) {
      wybor->opcje[o]='h';
      o++;
    }
    /* Display image */
    else if(!strcmp(argv[i],"-d")) {
      *display=1; 
    }
    /* Unknown option */
    else {
      fprintf(stderr, "Error: Unknown option \"%s\". Try --help\n", argv[i]);
      return -1;
    }
  } /* end of for */

  if (wybor->plik_we!=NULL)     /* ok: input stream initialized */
    return 0;
  else {
    fprintf(stderr, "Error: input file not opened!\n"); 
    return -1;
  }
}



void help(void) {
  char polecenie[10];
  strcpy(polecenie,"less ");
  strcat(polecenie,"help");  
  system(polecenie);
}
