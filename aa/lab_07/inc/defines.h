#ifndef __DEFINES_H__
#define __DEFINES_H__

#include <algorithm>
#include <fstream>
#include <iostream>
#include <locale> // Для корректной работы с кириллицей
#include <map>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>
#include <cstdlib>

#define RESET "\033[0m"
#define BLACK "\033[0;m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define VIOLET "\033[0;35m"
#define TURQ "\033[0;36m" // бирюзовый
#define WHITE "\033[0;37m"

#define MIN_DATA 0
#define MAX_DATA 500
#define NOT_FOUND 1
#define DATA_DIR "./data/"
#define GV ".gv"
#define N_REPS 1000

#define ERR_READ_DATA 100
#define ERR_MENU_ITEM 101
#define ERR_COUNT_DATA 102
#define ERR_OPEN_FILE 103
#define ERR_MEM_ALLOC 104

#endif