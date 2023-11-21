#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define COUNT_READERS 5
#define COUNT_WRITERS 3

// семафоры
#define ACTIVE_READERS 0 // Кол-во активных читателей; (считающий)
#define ACTIVE_WRITER 1  // активный читатель; (бинарный)
#define WRITE_QUEUE 2    // очередь писателей; (считающий)
#define READ_QUEUE 3     // очередь читателей; (считающий)

// Операции над семафорами:
#define P -1 // Пропустить;
#define V 1  // Освободить.
#define S 0  // sleep.

struct sembuf start_read[5] = {
    {READ_QUEUE, V, 0},     // инкремент счетчика ждущих читателей
    {ACTIVE_WRITER, S, 0},  // проверка, если ли активный писатель
    {WRITE_QUEUE, S, 0},    // проверка, есть ли ждущие писатели
    {ACTIVE_READERS, V, 0}, // инкремент активных читателей
    {READ_QUEUE, P, 0},     // декремент счетчика ждущих читателей
};

struct sembuf stop_read[1] = {
    {ACTIVE_READERS, P, 0} // Декремент активных читателей
};

struct sembuf start_write[6] = {
    {WRITE_QUEUE, V, 0},    // инкремент счётчика ждущих писателей
    {ACTIVE_READERS, S, 0}, // проверка, есть ли активный читатель
    {ACTIVE_WRITER, S, 0},  // проверка, пишет ли другой писатель
    {ACTIVE_WRITER, V, 0},  // захват семафора активного писателя
    {CAN_READ, V, 0},       // захват семафора может ли читать (то есть запрет чтения)
    {WRITE_QUEUE, P, 0}     // декремент счётчика ждущих писателей
};

struct sembuf stopr_write[2] = {};