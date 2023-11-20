#ifndef __MEMORY_MEASUREMENTS_H__
#define __MEMORY_MEASUREMENTS_H__

#include <iostream>
#include <memory>

#include "colorOutput.h"

int calcMemoryLev(const size_t lenght);
int calcMemoryDamLevNotRec(const size_t lenght);
int calcMemoryDamLevRec(const size_t lenght);
int calcMemoryDamLevRecCache(const size_t lenght);

double printAllMemoryMeasurement(const size_t lenghtMax);

#endif