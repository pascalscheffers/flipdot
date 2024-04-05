
#pragma once

#include <Arduino.h>

int rowClock = 17;
int rowData  = 22;
int rowLatch = 21;
int colData  = 27;

int outputEnable[] = {16, 23};
int rowEnable      = 19;
int led            = 5;

int addr_a[] = {26, 18, 4};
int addr_b[] = {32, 25};

#define NUM_DISPLAYS 2
#define WIDTH        (28 * NUM_DISPLAYS)
#define HEIGHT       16

// Row latch time in microseconds.
int rowTime = 200;

void gameOfLife();

void selectColumn(uint16_t colNumber);
void shiftRow(uint16_t rowNumber, bool dot);
void scanColumn(uint16_t columnData, uint16_t colNumber);
void fastScanColumn(uint16_t columnData, uint16_t prevColumnData, uint16_t colNumber);
void writeFrameBuffer();
void fastWriteFramebuffer();
