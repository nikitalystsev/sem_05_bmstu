#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <iostream>

#include "algorithms.h"
#include "colorOutput.h"

void printMenu();
int inputMenuItem(int &menuItem);
void inputTwoWStrings(std::wstring &str1, std::wstring &str2);
void printAllDistance(const std::wstring &word1, const std::wstring &word2);
void printWrongMenuItem();

#endif