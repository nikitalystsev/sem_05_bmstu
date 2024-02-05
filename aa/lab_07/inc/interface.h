#ifndef __INTERFACE_H__
#define __INTERFACE_H__

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

#define RESET "\033[0m"
#define BLACK "\033[0;m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define VIOLET "\033[0;35m"
#define TURQ "\033[0;36m" // бирюзовый
#define WHITE "\033[0;37m"

void print_menu(void);

#endif