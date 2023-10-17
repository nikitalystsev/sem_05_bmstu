$(shell mkdir -p out)

CC := gcc

PREF_SRC := ./src/
PREF_INC := ./inc/
PREF_OUT := ./out/

.PHONY: fork wait_ex2 wait exec pipe clean 

all: fork wait_ex2 wait exec pipe

fork: $(PREF_OUT)fork.o
	$(CC) $(PREF_OUT)fork.o -o fork.exe

$(PREF_OUT)fork.o: $(PREF_SRC)fork.c
	$(CC) -c -MD $< -o $@

wait: $(PREF_OUT)wait.o
	$(CC) $(PREF_OUT)wait.o -o wait.exe

$(PREF_OUT)wait.o: $(PREF_SRC)wait.c
	$(CC) -c -MD $< -o $@

exec: $(PREF_OUT)exec.o 
	$(CC) $(PREF_SRC)sum_num.c -o sum_num.exe
	$(CC) $(PREF_SRC)scalar_prod.c -o scalar_prod.exe
	$(CC) $(PREF_OUT)exec.o -o exec.exe

$(PREF_OUT)exec.o: $(PREF_SRC)exec.c
	$(CC) -c -MD $< -o $@

pipe: $(PREF_OUT)pipe.o
	$(CC) $(PREF_OUT)pipe.o -o pipe.exe

$(PREF_OUT)pipe.o: $(PREF_SRC)pipe.c
	$(CC) -c -MD $< -o $@

clean : 
	rm -Rf $(PREF_OUT) ./*.exe 