$(shell mkdir -p out)

CC := gcc

CFLAGS := -Iexamples/include/

PREF_SRC := ./src/
PREF_INC := ./inc/
PREF_OUT := ./out/
PREF_LIB := ./examples/lib/

# получаем список си файлов в подпапке ./examples_code/lib/
LIB := $(wildcard $(PREF_LIB)*.c)

# получаем заменой список объектных файлов для файлов из подпапки ./examples_code/lib/
LIB_OBJ := $(patsubst $(PREF_LIB)%.c, $(PREF_OUT)%.o, $(LIB))

.PHONY: d clean 

all: d 

d: $(PREF_OUT)myDaemon.o $(PREF_OUT)error.o
	$(CC) $(PREF_OUT)myDaemon.o $(PREF_OUT)error.o -o myDaemon.exe

$(PREF_OUT)myDaemon.o: $(PREF_SRC)myDaemon.c
	$(CC) $(CFLAGS) -c -MD $< -o $@

$(PREF_OUT)error.o: $(PREF_LIB)error.c
	$(CC) $(CFLAGS) -c -MD $< -o $@

include $(wildcard $(PREF_OUT)*.d)

clean : 
	rm -Rf $(PREF_OUT) ./*.exe 
