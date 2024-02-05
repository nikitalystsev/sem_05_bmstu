$(shell mkdir -p out)

CC := g++

CFLAGS := -std=c++20 -Wall -pedantic -Wextra -Wfloat-equal -Wfloat-conversion -O0 -Iinc

PREF_SRC := ./src/
PREF_INC := ./inc/
PREF_OUT := ./out/
PREF_TASK7 := ./task7/

# получаем список си файлов в подпапке ./src/
SRC := $(wildcard $(PREF_SRC)*.cpp)

# получаем заменой список объектных файлов для файлов из подпапки ./src/
SRC_OBJ := $(patsubst $(PREF_SRC)%.cpp, $(PREF_OUT)%.o, $(SRC))

# получаем список общих объектных файлов, фильтруя файл main из подпапки ./src/
GENERAL_OBJ := $(filter-out  $(PREF_OUT)main.o, $(SRC_OBJ))

all : app.exe 

app.exe : $(SRC_OBJ)
	$(CC) $(SRC_OBJ) -o app.exe 

# получаем объектные файлы с помощью си файлов из подпапки ./src/
$(PREF_OUT)%.o : $(PREF_SRC)%.cpp
	$(CC) $(CFLAGS) -c -MD $< -o $@


include $(wildcard $(PREF_OUT)*.d)

.PHONY: clean

clean : 
	rm -Rf $(PREF_OUT) ./*.exe 