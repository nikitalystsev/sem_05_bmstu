#ifndef __TIME_MEASUREMENTS_H__
#define __TIME_MEASUREMENTS_H__

#include <iostream>

#include "processTime.h"
#include "serial.h"
#include "conveyor.h"

double getSerialVersionTime(
    const int numAppl,
    const int numLines,
    const int strLenght,
    const int N,
    const int nreps);

double getParallelVersionTime(
    const int numAppl,
    const int numLines,
    const int strLenght,
    const int N,
    const int nreps);

#endif