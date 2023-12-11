$(shell mkdir -p out)

CC := gcc

PREF_SRC := ./src/
PREF_OUT := ./out/

.PHONY: d clean 

all: d 

d: $(PREF_OUT)myDaemon.o
	$(CC) $(PREF_OUT)myDaemon.o -o myDaemon.exe

$(PREF_OUT)myDaemon.o: $(PREF_SRC)myDaemon.c
	$(CC) -c -MD $< -o $@
	
clean : 
	rm -Rf $(PREF_OUT) ./*.exe 