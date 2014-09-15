# GeeksOnBoard
# 2013
# Makefile


CC=gcc
CFLAGS= -c # -Wall --pedantic
# * Unhash of Wall Pedantic not recommended.
LFLAGS=-lm
LIBS=`pkg-config --cflags --libs opencv`
PLIKI=obj/main.o obj/wywolania.o obj/inout.o obj/przetwarzania.o obj/jpg.o
ZRODLA=src/
OBIEKTY=obj/
INCLUDY= inc/main.h inc/inout.h inc/przetwarzania.h inc/wywolania.h inc/jpg.h 
BIN=przetwarzanie_obrazow2

.PHONY: clean


$(BIN): $(PLIKI)
	$(CC) $^ -o $@ $(LFLAGS) $(LIBS)

clean:
	rm -f $(OBIEKTY)*o $(BIN)

$(OBIEKTY)main.o: $(ZRODLA)main.c $(INCLUDY)
	$(CC) $< -o $@ $(CFLAGS) $(LIBS)

$(OBIEKTY)wywolania.o: $(ZRODLA)wywolania.c $(INCLUDY)
	$(CC) $< -o $@ $(CFLAGS)

$(OBIEKTY)przetwarzania.o: $(ZRODLA)przetwarzania.c $(INCLUDY)
	$(CC) $< -o $@ $(CFLAGS)

$(OBIEKTY)inout.o: $(ZRODLA)inout.c $(INCLUDY)
	$(CC) $< -o $@ $(CFLAGS)

$(OBIEKTY)jpg.o: $(ZRODLA)jpg.c $(INCLUDY)
	$(CC) $< -o $@ $(CFLAGS) $(LIBS)
