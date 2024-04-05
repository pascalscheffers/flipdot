
#include "main.hpp"

#include "pax_gfx.h"

#include <Arduino.h>

#define WHITE 0xffffffff
#define BLACK 0xff000000

#define FONT      pax_font_sky
#define FONT_SIZE 9


// Current state of dots.
uint16_t  prev_framebuffer[WIDTH];
// Main framebuffer.
uint16_t  framebuffer[WIDTH];
// Main graphics context.
pax_buf_t gfx;
// Temporary framebuffer used for game of life.
uint16_t  tmp_framebuffer[WIDTH];
// Temporary graphics context.
pax_buf_t tmp_gfx;

extern "C" void app_main() {
    // Configure I/Os.
    pinMode(rowClock, OUTPUT);
    pinMode(rowData, OUTPUT);
    pinMode(rowLatch, OUTPUT);
    pinMode(colData, OUTPUT);
    pinMode(outputEnable[0], OUTPUT);
    pinMode(outputEnable[1], OUTPUT);
    pinMode(rowEnable, OUTPUT);
    pinMode(led, OUTPUT);

    pinMode(addr_a[0], OUTPUT);
    pinMode(addr_a[1], OUTPUT);
    pinMode(addr_a[2], OUTPUT);
    pinMode(addr_b[0], OUTPUT);
    pinMode(addr_b[1], OUTPUT);

    digitalWrite(rowClock, LOW);
    digitalWrite(rowData, LOW);
    digitalWrite(rowLatch, LOW);
    digitalWrite(colData, LOW);
    digitalWrite(outputEnable[0], LOW);
    digitalWrite(outputEnable[1], LOW);
    digitalWrite(rowEnable, LOW);
    digitalWrite(led, LOW);

    digitalWrite(addr_a[0], LOW);
    digitalWrite(addr_a[1], LOW);
    digitalWrite(addr_a[2], LOW);
    digitalWrite(addr_b[0], LOW);
    digitalWrite(addr_b[1], LOW);

    // Create graphics context.
    pax_buf_init(&gfx, framebuffer, HEIGHT, WIDTH, PAX_BUF_1_GREY);
    pax_buf_set_orientation(&gfx, PAX_O_ROT_CW_FLIP_H);
    pax_buf_init(&tmp_gfx, tmp_framebuffer, HEIGHT, WIDTH, PAX_BUF_1_GREY);
    pax_buf_set_orientation(&tmp_gfx, PAX_O_ROT_CW_FLIP_H);

    // Show some text.
    pax_background(&gfx, 0);
    pax_draw_text(&gfx, WHITE, FONT, FONT_SIZE, 0, 0, "Hi, Ther.");
    writeFrameBuffer();
    delay(5000);

    // Show some GoL.
    while (true) {
        gameOfLife();
        fastWriteFramebuffer();
        writeFrameBuffer();
        delay(500);
    }
}



static inline void golPixel(int x, int y) {
    int count  = 0;
    count     += 1 & pax_get_pixel(&gfx, (x + WIDTH - 1) % WIDTH, (y + HEIGHT - 1) % HEIGHT);
    count     += 1 & pax_get_pixel(&gfx, x, (y + HEIGHT - 1) % HEIGHT);
    count     += 1 & pax_get_pixel(&gfx, (x + 1) % WIDTH, (y + HEIGHT - 1) % HEIGHT);
    count     += 1 & pax_get_pixel(&gfx, (x + WIDTH - 1) % WIDTH, y);
    count     += 1 & pax_get_pixel(&gfx, (x + 1) % WIDTH, y);
    count     += 1 & pax_get_pixel(&gfx, (x + WIDTH - 1) % WIDTH, (y + 1) % HEIGHT);
    count     += 1 & pax_get_pixel(&gfx, x, (y + 1) % HEIGHT);
    count     += 1 & pax_get_pixel(&gfx, (x + 1) % WIDTH, (y + 1) % HEIGHT);
    if (count >= 4) {
        pax_set_pixel(&tmp_gfx, BLACK, x, y);
    } else if (count <= 1) {
        pax_set_pixel(&tmp_gfx, BLACK, x, y);
    } else if (count == 3) {
        pax_set_pixel(&tmp_gfx, WHITE, x, y);
    } else {
        pax_set_pixel(&tmp_gfx, pax_get_pixel(&gfx, x, y), x, y);
    }
}

void gameOfLife() {
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            golPixel(x, y);
        }
    }
    memcpy(framebuffer, tmp_framebuffer, sizeof(framebuffer));
    // pax_draw_image(&gfx, &tmp_gfx, 0, 0);
}



void selectColumn(uint16_t colNumber) {
    unsigned char segmentNumber = colNumber / 7;
    unsigned char remainder     = colNumber % 7;

    digitalWrite(addr_b[0], (bool)(segmentNumber & 0b01));
    digitalWrite(addr_b[1], (bool)(segmentNumber & 0b10));

    digitalWrite(addr_a[0], (bool)((remainder + 1) & 0b001));
    digitalWrite(addr_a[1], (bool)((remainder + 1) & 0b010));
    digitalWrite(addr_a[2], (bool)((remainder + 1) & 0b100));
}

void shiftRow(uint16_t rowNumber, bool dot) {
    digitalWrite(rowLatch, LOW);
    unsigned int srData = 1 << rowNumber;

    if (dot) {
        // Shift out dot enable signal.
        shiftOut(rowData, rowClock, LSBFIRST, srData);
        shiftOut(rowData, rowClock, LSBFIRST, srData >> 8);
        shiftOut(rowData, rowClock, LSBFIRST, 0);
        shiftOut(rowData, rowClock, LSBFIRST, 0);

    } else {
        // Shift out dot disable signal.
        shiftOut(rowData, rowClock, LSBFIRST, 0);
        shiftOut(rowData, rowClock, LSBFIRST, 0);
        shiftOut(rowData, rowClock, LSBFIRST, srData);
        shiftOut(rowData, rowClock, LSBFIRST, srData >> 8);
    }
    digitalWrite(rowLatch, HIGH);
}

void scanColumn(uint16_t columnData, uint16_t colNumber) {
    // Find the display index.
    int displayNo  = colNumber / 28;
    colNumber     %= 28;

    for (int i = 0; i < 16; i++) {
        bool dot = (columnData >> i) & 1;

        // Select the row / column.
        selectColumn(colNumber);
        digitalWrite(rowEnable, HIGH);
        shiftRow(i, dot);

        // write the row drivers
        digitalWrite(colData, !dot);
        digitalWrite(outputEnable[displayNo], HIGH);
        delayMicroseconds(rowTime);
        digitalWrite(outputEnable[displayNo], LOW);
        digitalWrite(rowEnable, LOW);
    }
}

void fastScanColumn(uint16_t columnData, uint16_t prevColumnData, uint16_t colNumber) {
    // Find the display index.
    int displayNo  = colNumber / 28;
    colNumber     %= 28;

    for (unsigned char i = 0; i < 16; i++) {
        unsigned char dot     = (columnData >> i) & 1;
        unsigned char prevDot = (prevColumnData >> i) & 1;

        if (prevDot == dot) {
            // If unchanged, skip this dot.
            continue;
        }

        // Select the row / column.
        selectColumn(colNumber);
        digitalWrite(rowEnable, HIGH);
        shiftRow(i, dot);

        // Write the row drivers.
        digitalWrite(colData, !dot);
        digitalWrite(outputEnable[displayNo], HIGH);
        delayMicroseconds(rowTime);
        digitalWrite(outputEnable[displayNo], LOW);
        digitalWrite(rowEnable, LOW);
    }
}

void writeFrameBuffer() {
    for (int i = 0; i < (28 * NUM_DISPLAYS); i++) {
        scanColumn(framebuffer[i], i);
        prev_framebuffer[i] = framebuffer[i];
    }
}

void fastWriteFramebuffer() {
    for (int i = 0; i < (28 * NUM_DISPLAYS); i++) {
        fastScanColumn(framebuffer[i], prev_framebuffer[i], i);
        prev_framebuffer[i] = framebuffer[i];
    }
}
