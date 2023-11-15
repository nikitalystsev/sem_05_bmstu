#ifndef __MEMORY_MEASUREMENTS_H__
#define __MEMORY_MEASUREMENTS_H__

#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

double caclMemAlgClassicMul(const int size);
double caclMemAlgVinogradMul(const int size);
double caclMemAlgVinogradMulWithOpt(const int size);
double caclMemAlgStrassenMul(const int size);

#endif