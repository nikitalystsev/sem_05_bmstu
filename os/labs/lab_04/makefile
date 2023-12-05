$(shell mkdir -p out)

CC := gcc

PREF_SRC := ./src/
PREF_OUT := ./out/

.PHONY: rw clean 

all: rw 

rw: $(PREF_OUT)readers_writers.o
	$(CC) $(PREF_OUT)readers_writers.o -o readers_writers.exe

$(PREF_OUT)readers_writers.o: $(PREF_SRC)readers_writers.c
	$(CC) -c -MD $< -o $@
	
clean : 
	rm -Rf $(PREF_OUT) ./*.exe 