$(shell mkdir -p out)

CC := gcc

CFLAGS := -Iexamples/include/


LINKFLAGS := -lpthread -lc

PREF_SRC := ./src/
PREF_INC := ./inc/
PREF_OUT := ./out/
PREF_LIB := ./examples/lib/

.PHONY: d1 d2 clean 

all: d1 d2


d1: $(PREF_OUT)daemon_version1.o $(PREF_OUT)error.o
	$(CC) $(PREF_OUT)daemon_version1.o $(PREF_OUT)error.o $(LINKFLAGS) -o daemon_version1.exe

$(PREF_OUT)daemon_version1.o: $(PREF_SRC)daemon_version1.c
	$(CC) $(CFLAGS) -c -MD $< -o $@

d2: $(PREF_OUT)daemon_version2.o $(PREF_OUT)error.o
	$(CC) $(PREF_OUT)daemon_version2.o $(PREF_OUT)error.o $(LINKFLAGS) -o daemon_version2.exe

$(PREF_OUT)daemon_version2.o: $(PREF_SRC)daemon_version2.c
	$(CC) $(CFLAGS) -c -MD $< -o $@

$(PREF_OUT)error.o: $(PREF_LIB)error.c
	$(CC) $(CFLAGS) -c -MD $< -o $@

include $(wildcard $(PREF_OUT)*.d)

clean : 
	rm -Rf $(PREF_OUT) ./*.exe 
