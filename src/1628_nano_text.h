#include <Arduino.h>

void selectColumn( unsigned char colNumber);

void shiftRow(unsigned char rowNumber, unsigned char dot);
void scanColumn(unsigned int columnData, unsigned char colNumber);
void fastScanColumn(unsigned int columnData, unsigned int prevColumnData, unsigned char colNumber);

void writeFrameBuffer();

void display_String(String str1, String str2);


void clearDisplay();


void allYellow();
