
#include <Arduino.h>
#include "1628_nano_text.h"

// This will run on an Arduino Nano, Pi Pico and ESP32 (If pin names are updated)
static unsigned char font_data[] = {
    0x55, 0x2A, 0x55, 0x2A, 0x55, // 0x00 [▓]     0x00, 0x00, 0x00, 0x00, 0x00,  // 0x00 (nul)
    0x2A, 0x55, 0x2A, 0x55, 0x2A, // 0x01 [░]     0x10, 0x26, 0x20, 0x26, 0x10,  // 0x01 (☺)
    0x3E, 0x6B, 0x4F, 0x6B, 0x3E, // 0x02 (☻)
    0x0C, 0x12, 0x24, 0x12, 0x0C, // 0x03 (♥)
    0x08, 0x14, 0x22, 0x14, 0x08, // 0x04 (♦)
    0x18, 0x1E, 0x2E, 0x1E, 0x18, // 0x05 (♣)
    0x18, 0x1C, 0x2E, 0x1C, 0x18, // 0x06 (♠)
    0x1C, 0x3E, 0x3E, 0x3E, 0x1C, // 0x07 (•)
    0x63, 0x41, 0x41, 0x41, 0x63, // 0x08 (◘)
    0x1C, 0x22, 0x22, 0x22, 0x1C, // 0x09 (○)
    0x63, 0x5D, 0x5D, 0x5D, 0x63, // 0x0A (◙)
    0x30, 0x48, 0x4A, 0x36, 0x0E, // 0x0B (♂)
    0x06, 0x29, 0x79, 0x29, 0x06, // 0x0C (♀)
    0x60, 0x60, 0x7F, 0x06, 0x1C, // 0x0D (♪)
    0x60, 0x7F, 0x03, 0x63, 0x7F, // 0x0E (♫)
    0x2A, 0x1C, 0x36, 0x1C, 0x2A, // 0x0F (☼)
    0x00, 0x3E, 0x1C, 0x08, 0x00, // 0x10 (►)
    0x00, 0x08, 0x1C, 0x3E, 0x00, // 0x11 (◄)
    0x14, 0x36, 0x77, 0x36, 0x14, // 0x12 (↕)
    0x00, 0x5F, 0x00, 0x5F, 0x00, // 0x13 (‼)
    0x06, 0x0F, 0x7F, 0x01, 0x7F, // 0x14 (¶)
    0x00, 0x6C, 0x57, 0x75, 0x1B, // 0x15 (§)
    0x60, 0x60, 0x60, 0x60, 0x60, // 0x16 (▬)
    0x14, 0x22, 0x7F, 0x22, 0x14, // 0x17 (↨)
    0x08, 0x04, 0x7E, 0x04, 0x08, // 0x18 (↑)
    0x10, 0x20, 0x7E, 0x20, 0x10, // 0x19 (↓)
    0x08, 0x08, 0x2A, 0x1C, 0x08, // 0x1A (→)
    0x08, 0x1C, 0x2A, 0x08, 0x08, // 0x1B (←)
    0x78, 0x40, 0x40, 0x40, 0x40, // 0x1C (∟)
    0x08, 0x0C, 0x2A, 0x18, 0x08, // 0x1D (↔)
    0x10, 0x18, 0x1C, 0x18, 0x10, // 0x1E (▲)
    0x04, 0x0C, 0x1C, 0x0C, 0x04, // 0x1F (▼)
    0x00, 0x00, 0x00, 0x00, 0x00, // 0x20
    0x00, 0x00, 0x5F, 0x00, 0x00, // 0x21 !
    0x00, 0x07, 0x00, 0x07, 0x00, // 0x22 "
    0x14, 0x7F, 0x14, 0x7F, 0x14, // 0x23 #
    0x24, 0x2A, 0x7F, 0x2A, 0x12, // 0x24 $
    0x23, 0x13, 0x08, 0x64, 0x62, // 0x25 %
    0x36, 0x49, 0x56, 0x20, 0x50, // 0x26 &
    0x00, 0x05, 0x03, 0x00, 0x00, // 0x27 '
    0x00, 0x1C, 0x22, 0x41, 0x00, // 0x28 (
    0x00, 0x41, 0x22, 0x1C, 0x00, // 0x29 )
    0x14, 0x08, 0x3E, 0x08, 0x14, // 0x2A *
    0x08, 0x08, 0x3E, 0x08, 0x08, // 0x2B +
    0x00, 0x50, 0x30, 0x00, 0x00, // 0x2C ,
    0x08, 0x08, 0x08, 0x08, 0x08, // 0x2D -
    0x00, 0x60, 0x60, 0x00, 0x00, // 0x2E .
    0x60, 0x10, 0x08, 0x04, 0x03, // 0x2F /
    0x3E, 0x51, 0x49, 0x45, 0x3E, // 0x30 0
    0x00, 0x42, 0x7F, 0x40, 0x00, // 0x31 1
    0x42, 0x61, 0x51, 0x49, 0x46, // 0x32 2
    0x21, 0x41, 0x45, 0x4B, 0x31, // 0x33 3
    0x18, 0x14, 0x12, 0x7F, 0x10, // 0x34 4
    0x27, 0x45, 0x45, 0x45, 0x39, // 0x35 5
    0x3C, 0x4A, 0x49, 0x49, 0x30, // 0x36 6
    0x01, 0x71, 0x09, 0x05, 0x03, // 0x37 7
    0x36, 0x49, 0x49, 0x49, 0x36, // 0x38 8
    0x06, 0x49, 0x49, 0x29, 0x1E, // 0x39 9
    0x00, 0x00, 0x14, 0x00, 0x00, // 0x3A [ : ]   0x00, 0x36, 0x36, 0x00, 0x00,  // 0x3A :
    0x00, 0x14, 0x00, 0x00, 0x00, // 0x3B [:  ]   0x00, 0x56, 0x36, 0x00, 0x00,  // 0x3B ;
    0x00, 0x00, 0x00, 0x14, 0x00, // 0x3C [  :]   0x08, 0x14, 0x22, 0x41, 0x00,  // 0x3C <
    0x14, 0x14, 0x14, 0x14, 0x14, // 0x3D =
    0x00, 0x41, 0x22, 0x14, 0x08, // 0x3E >
    0x02, 0x01, 0x51, 0x09, 0x06, // 0x3F ?
    0x3E, 0x41, 0x5D, 0x55, 0x5E, // 0x40 @
    0x7C, 0x12, 0x11, 0x12, 0x7C, // 0x41 A
    0x7F, 0x49, 0x49, 0x49, 0x36, // 0x42 B
    0x3E, 0x41, 0x41, 0x41, 0x22, // 0x43 C
    0x7F, 0x41, 0x41, 0x22, 0x1C, // 0x44 D
    0x7F, 0x49, 0x49, 0x49, 0x41, // 0x45 E
    0x7F, 0x09, 0x09, 0x09, 0x01, // 0x46 F
    0x3E, 0x41, 0x49, 0x49, 0x7A, // 0x47 G
    0x7F, 0x08, 0x08, 0x08, 0x7F, // 0x48 H
    0x00, 0x41, 0x7F, 0x41, 0x00, // 0x49 I
    0x20, 0x40, 0x41, 0x3F, 0x01, // 0x4A J
    0x7F, 0x08, 0x14, 0x22, 0x41, // 0x4B K
    0x7F, 0x40, 0x40, 0x40, 0x40, // 0x4C L
    0x7F, 0x02, 0x0C, 0x02, 0x7F, // 0x4D M
    0x7F, 0x04, 0x08, 0x10, 0x7F, // 0x4E N
    0x3E, 0x41, 0x41, 0x41, 0x3E, // 0x4F O
    0x7F, 0x09, 0x09, 0x09, 0x06, // 0x50 P
    0x3E, 0x41, 0x51, 0x21, 0x5E, // 0x51 Q
    0x7F, 0x09, 0x19, 0x29, 0x46, // 0x52 R
    0x26, 0x49, 0x49, 0x49, 0x32, // 0x53 S
    0x01, 0x01, 0x7F, 0x01, 0x01, // 0x54 T
    0x3F, 0x40, 0x40, 0x40, 0x3F, // 0x55 U
    0x0F, 0x30, 0x40, 0x30, 0x0F, // 0x56 V
    0x1F, 0x60, 0x18, 0x60, 0x1F, // 0x57 W
    0x63, 0x14, 0x08, 0x14, 0x63, // 0x58 X
    0x07, 0x08, 0x70, 0x08, 0x07, // 0x59 Y
    0x61, 0x51, 0x49, 0x45, 0x43, // 0x5A Z
    0x00, 0x00, 0x7F, 0x41, 0x00, // 0x5B [
    0x03, 0x04, 0x08, 0x10, 0x60, // 0x5C forward slash
    0x00, 0x41, 0x7F, 0x00, 0x00, // 0x5D ]
    0x04, 0x02, 0x01, 0x02, 0x04, // 0x5E ^
    0x40, 0x40, 0x40, 0x40, 0x40, // 0x5F _
    0x00, 0x01, 0x02, 0x04, 0x00, // 0x60 `
    0x20, 0x54, 0x54, 0x54, 0x78, // 0x61 a
    0x7F, 0x48, 0x44, 0x44, 0x38, // 0x62 b
    0x38, 0x44, 0x44, 0x44, 0x20, // 0x63 c
    0x38, 0x44, 0x44, 0x48, 0x7F, // 0x64 d
    0x38, 0x54, 0x54, 0x54, 0x18, // 0x65 e
    0x08, 0x7E, 0x09, 0x09, 0x02, // 0x66 f
    0x08, 0x54, 0x54, 0x54, 0x3C, // 0x67 g
    0x7F, 0x08, 0x04, 0x04, 0x78, // 0x68 h
    0x00, 0x44, 0x7D, 0x40, 0x00, // 0x69 i
    0x20, 0x40, 0x44, 0x3D, 0x00, // 0x6A j
    0x7F, 0x10, 0x28, 0x44, 0x00, // 0x6B k
    0x00, 0x41, 0x7F, 0x40, 0x00, // 0x6C l
    0x7C, 0x04, 0x38, 0x04, 0x78, // 0x6D m
    0x7C, 0x08, 0x04, 0x04, 0x78, // 0x6E n
    0x38, 0x44, 0x44, 0x44, 0x38, // 0x6F o
    0x7C, 0x14, 0x14, 0x14, 0x08, // 0x70 p
    0x08, 0x14, 0x14, 0x14, 0x7C, // 0x71 q
    0x7C, 0x08, 0x04, 0x04, 0x08, // 0x72 r
    0x48, 0x54, 0x54, 0x54, 0x20, // 0x73 s
    0x04, 0x3F, 0x44, 0x44, 0x20, // 0x74 t
    0x3C, 0x40, 0x40, 0x20, 0x7C, // 0x75 u
    0x1C, 0x20, 0x40, 0x20, 0x1C, // 0x76 v
    0x3C, 0x40, 0x30, 0x40, 0x3C, // 0x77 w
    0x44, 0x28, 0x10, 0x28, 0x44, // 0x78 x
    0x0C, 0x50, 0x50, 0x50, 0x3C, // 0x79 y
    0x44, 0x64, 0x54, 0x4C, 0x44, // 0x7A z
    0x00, 0x08, 0x77, 0x41, 0x00, // 0x7B {
    0x00, 0x00, 0x7F, 0x00, 0x00, // 0x7C |
    0x00, 0x41, 0x77, 0x08, 0x00, // 0x7D }
    0x08, 0x04, 0x08, 0x10, 0x08, // 0x7E ~
    0x38, 0x24, 0x22, 0x24, 0x38, // 0x7F ⌂
};

unsigned int checker1 = 0b1010101010101010;
unsigned int checker2 = 0b0101010101010101;

int rowClock = 17;      // 11;
int rowData = 22;       // 9;
int rowLatch = 21;      // 10;
int colData = 27;       // 7;
int outputEnableA = 16; // 8;
int outputEnableB = 23; // 8;

#define NUM_DISPLAYS 2

const int width  = 28 * NUM_DISPLAYS;
const int height = 16;

int outputEnable[] = {outputEnableA, outputEnableB};
int rowEnable = 19; // 12;
int led = 5;        // 13;

int a_0 = 26; // 2;
int a_1 = 18; // 3;
int a_2 = 4;  // 4;
int b_0 = 32; // 5;
int b_1 = 25; // 6;

int rowTime = 200;

unsigned int frame_buffer[28 * NUM_DISPLAYS];
unsigned int tmp_frame_buffer[28 * NUM_DISPLAYS];

void setup()
{

  for (int i = 0; i< (28*NUM_DISPLAYS); i++) {
    frame_buffer[i]=0;
  }
  // put your setup code here, to run once:

  pinMode(rowClock, OUTPUT);      // = 17;//11;
  pinMode(rowData, OUTPUT);       // = 22;//9;
  pinMode(rowLatch, OUTPUT);      // = 21;//10;
  pinMode(colData, OUTPUT);       // = 27;//7;
  pinMode(outputEnableA, OUTPUT); // = 16;//8;
  pinMode(outputEnableB, OUTPUT); // = 23;
  pinMode(rowEnable, OUTPUT);     // = 19;//12;
  pinMode(led, OUTPUT);           // = 5;//13;

  pinMode(a_0, OUTPUT); // = 26;//2;
  pinMode(a_1, OUTPUT); // = 18;//3;
  pinMode(a_2, OUTPUT); // = 4;//4;
  pinMode(b_0, OUTPUT); // = 32;//5;
  pinMode(b_1, OUTPUT); // = 25;//6;

  digitalWrite(rowClock, LOW);      // = 17;//11;
  digitalWrite(rowData, LOW);       // = 22;//9;
  digitalWrite(rowLatch, LOW);      // = 21;//10;
  digitalWrite(colData, LOW);       // = 27;//7;
  digitalWrite(outputEnableA, LOW); // = 16;//8;
  digitalWrite(outputEnableB, LOW); // = 23;
  digitalWrite(rowEnable, LOW);     // = 19;//12;
  digitalWrite(led, LOW);           // = 5;//13;

  digitalWrite(a_0, LOW); // = 26;//2;
  digitalWrite(a_1, LOW); // = 18;//3;
  digitalWrite(a_2, LOW); // = 4;//4;
  digitalWrite(b_0, LOW); // = 32;//5;
  digitalWrite(b_1, LOW); // = 25;//6;
}

// display: Array of 28 16-bit columns

// to update entire display:

// for(int i = 0; i < 27; i++){

//}

void loop()
{
  
  // // put your main code here, to run repeatedly:
  // for (int i=0; i<5; i++) {
  //   allYellow();
  //   clearDisplay();

  // }
  
  //delay(1000);
  clearDisplay();
  display_BigString("HALLO");
  delay(300000);

  //delay(1000);

  //display_String("1234567890", "ABCDEFGHIJ");
  //display_String("FLIP DOTS ", " ARE COOL ");
  display_String("  HACKER  ", "   SPACE  ");
  writeFrameBuffer();
  delay(500);
  display_String("   MAKER   ", "   SPACE  ");
  writeFrameBuffer();
  delay(500);
  display_String("  HACKER  ", "   SPACE  ");
  writeFrameBuffer();
  delay(500);
  display_String("   MAKER   ", "   SPACE  ");
  writeFrameBuffer();
  delay(500);
  writeFrameBuffer();
  
  // display_String("FLIP DOTS  ", " SO COOL  ");
  // writeFrameBuffer();
  // delay(15000);

  // display_String("WANT ONE?   ", "ASK PASCAL   ");
  // writeFrameBuffer();
  // delay(1500);

  // for (int i = 0; i < 7; i++)
  // {
  //   display_String("FLIP  DOTS  ", " SO COOL  ");
  //   writeFrameBuffer();
  //   delay(750);
  //   //display_String("FLIP DOTS ", " ARE COOL ");
  //   display_String("WANT ONE? ", "ASK PASCAL   ");
  //   writeFrameBuffer();
  //   delay(750);
  // }
  // writeFrameBuffer();


  // for (int i = 0; i < 7; i++)
  // {
  //   display_String("          ", "          ");
  //   delay(130);
  //   //display_String("FLIP DOTS ", " ARE COOL ");
  //   display_String("  HACKER  ", "   HOTEL  ");
  //   delay(130);
  // }
  // writeFrameBuffer();
  delay(15000);

  for (int x = 0; x < width; x++) {
    frame_buffer[x] = rand();
  }
  unsigned long start = millis();
  while(millis() < start + 15000) {
    gameOfLife();
    writeFrameBuffer();
    delay(10);
    writeFrameBuffer();
    delay(250);
  }
  //
  // display_String("ALERT", "     ");
  // delay(1000);
  //
  //
  // display_String("GO   ","AWAY!");
  // delay(2000);
  // display_String("     ","AWAY!");
  // delay(2000);
  //

} // end loop

void selectColumn(unsigned char colNumber)
{

  // dot: 1 == yellow

  unsigned char segmentNumber = colNumber / 7;
  unsigned char remainder = colNumber % 7;

  switch (segmentNumber)
  {
  case 0:
    digitalWrite(b_0, LOW);
    digitalWrite(b_1, LOW);
    break;
  case 1:
    digitalWrite(b_0, HIGH);
    digitalWrite(b_1, LOW);
    break;
  case 2:
    digitalWrite(b_0, LOW);
    digitalWrite(b_1, HIGH);
    break;
  case 3:
    digitalWrite(b_0, HIGH);
    digitalWrite(b_1, HIGH);
    break;
  }

  switch (remainder)
  {
  case 0:
    digitalWrite(a_0, HIGH);
    digitalWrite(a_1, LOW);
    digitalWrite(a_2, LOW);
    break;
  case 1:
    digitalWrite(a_0, LOW);
    digitalWrite(a_1, HIGH);
    digitalWrite(a_2, LOW);
    break;
  case 2:
    digitalWrite(a_0, HIGH);
    digitalWrite(a_1, HIGH);
    digitalWrite(a_2, LOW);
    break;
  case 3:
    digitalWrite(a_0, LOW);
    digitalWrite(a_1, LOW);
    digitalWrite(a_2, HIGH);
    break;
  case 4:
    digitalWrite(a_0, HIGH);
    digitalWrite(a_1, LOW);
    digitalWrite(a_2, HIGH);
    break;
  case 5:
    digitalWrite(a_0, LOW);
    digitalWrite(a_1, HIGH);
    digitalWrite(a_2, HIGH);
    break;
  case 6:
    digitalWrite(a_0, HIGH);
    digitalWrite(a_1, HIGH);
    digitalWrite(a_2, HIGH);
    break;
  }
} // end drive col

// reminder: the industrial revolution and its consequences have been a disaster for the human race

void shiftRow(unsigned char rowNumber, unsigned char dot)
{
  digitalWrite(rowLatch, LOW);
  unsigned int srData = 0b0000000000000001;
  srData = srData << rowNumber;

  if (dot == 0b00000001)
  {

    shiftOut(rowData, rowClock, LSBFIRST, srData);
    shiftOut(rowData, rowClock, LSBFIRST, (srData >> 8));
    shiftOut(rowData, rowClock, LSBFIRST, 0b00000000);
    shiftOut(rowData, rowClock, LSBFIRST, 0b00000000);

  } // end if dot, drive hi

  else
  { // drive row low
    shiftOut(rowData, rowClock, LSBFIRST, 0b00000000);
    shiftOut(rowData, rowClock, LSBFIRST, 0b00000000);
    shiftOut(rowData, rowClock, LSBFIRST, srData);
    shiftOut(rowData, rowClock, LSBFIRST, (srData >> 8));

  } // end not dot drive row low
  digitalWrite(rowLatch, HIGH);

} // end shiftRow

void scanColumn(unsigned int columnData, unsigned char colNumber)
{
  int displayNo = colNumber / 28;


  for (unsigned char i = 0; i < 16; i++)
  {
    unsigned char dot = (columnData >> (i));
    unsigned char notDot;

    dot = dot & 0b0000000000000001;
    notDot = dot ^ 0b0000000000000001;

    selectColumn(colNumber % 28); // select column with the FP2800a chip

    // select the correct row , drive it high or low
    digitalWrite(rowEnable, HIGH);
    shiftRow(i, dot);

    // write the row drivers
    digitalWrite(colData, notDot);
    digitalWrite(outputEnable[displayNo], HIGH);
    delayMicroseconds(rowTime);
    digitalWrite(outputEnable[displayNo], LOW);
    digitalWrite(rowEnable, LOW);
  }

} // end scanColumn

void fastScanColumn(unsigned int columnData, unsigned int prevColumnData, unsigned char colNumber)
{
  int displayNo = colNumber / 28;

  for (unsigned char i = 0; i < 16; i++)
  {

    unsigned char dot = (columnData >> (i));
    unsigned char prevDot = (prevColumnData >> (i));

    if (prevDot == dot)
    {
    }

    else
    {
      unsigned char notDot;

      dot = dot & 0b0000000000000001;
      notDot = dot ^ 0b0000000000000001;

      selectColumn(colNumber % 28); // select column with the FP2800a chip

      // select the correct row , drive it high or low
      digitalWrite(rowEnable, HIGH);
      shiftRow(i, dot);

      // write the row drivers
      digitalWrite(colData, notDot);
      digitalWrite(outputEnable[displayNo], HIGH);
      delayMicroseconds(rowTime);
      digitalWrite(outputEnable[displayNo], LOW);
      digitalWrite(rowEnable, LOW);
    }
  }

} // end scanColumn

void writeFrameBuffer()
{
  for (int i = 0; i < (28*NUM_DISPLAYS); i++)
  {
    scanColumn(frame_buffer[i], i);
  }
}

bool getPixel(unsigned *fb, int x, int y) {
  return (fb[x] >> y) & 1;
}

void setPixel(unsigned *fb, int x, int y, bool value) {
  unsigned mask = 1 << y;
  fb[x] = fb[x] & ~mask | (value * mask);
}

void display_String(String str1, String str2)
{

  unsigned int new_frame_buffer[28*NUM_DISPLAYS];
    for (int i = 0; i<(28*NUM_DISPLAYS); i++) {
    new_frame_buffer[i]=0;
  }

  int charsPerLine = 5 * NUM_DISPLAYS;
  for (int i = 0; i < charsPerLine; i++)
  {
    char character = str1.charAt(i);

    for (int j = 0; j < 5; j++)
    {
      int addr = i * 6;
      addr = addr + j;
      new_frame_buffer[addr] = (font_data[((character * 5) + j)]);
    }
  }

  for (int i = 0; i < charsPerLine; i++)
  {
    char character = str2.charAt(i);

    for (int j = 0; j < 5; j++)
    {
      int addr = i * 6;
      addr = addr + j;
      new_frame_buffer[addr] = new_frame_buffer[addr] | (font_data[((character * 5) + j)] << 9);
    }
  }

  for (int i = 0; i < 28*NUM_DISPLAYS; i++)
  {
    fastScanColumn(new_frame_buffer[i], frame_buffer[i], i);
  }

  for (int i = 0; i < 28*NUM_DISPLAYS; i++)
  {
    frame_buffer[i] = new_frame_buffer[i];
  }
}

void display_BigString(String str1)
{

  unsigned int new_frame_buffer[28*NUM_DISPLAYS];
    for (int i = 0; i<(28*NUM_DISPLAYS); i++) {
    new_frame_buffer[i]=0;
  }

  int charsPerLine = 5 * NUM_DISPLAYS;
  for (int i = 0; i < charsPerLine; i++)
  {
    char character = 0;
    if (i < str1.length()) {
      character = str1.charAt(i);
    }
    
    for (int j = 0; j < 5; j++)
    {
      int addr = i * 12;
      addr = addr + j*2;
      if (addr+1 > 28*NUM_DISPLAYS) break;
      int c = font_data[((character * 5) + j)];
      int cc = 0;
      for (int d = 7; d >= 0; d--) {
        cc = (cc << 1) | ((c >> d) & 0x1);
        cc = (cc << 1) | ((c >> d) & 0x1);
      }
      cc = (cc << 1);
      new_frame_buffer[addr] = cc;
      new_frame_buffer[addr+1] = cc;
    }
  }

  for (int i = 0; i < 28*NUM_DISPLAYS; i++)
  {
    fastScanColumn(new_frame_buffer[i], frame_buffer[i], i);
  }

  for (int i = 0; i < 28*NUM_DISPLAYS; i++)
  {
    frame_buffer[i] = new_frame_buffer[i];
  }
}

void clearDisplay()
{

  for (int i = 0; i < 28*NUM_DISPLAYS; i++)
  {
    frame_buffer[i] = 0;
    scanColumn(frame_buffer[i], i);
  }
}

void allYellow()
{

  for (int i = 0; i < 28*NUM_DISPLAYS; i++)
  {
    frame_buffer[i] = 0xffff;
    scanColumn(frame_buffer[i], i);
  }
}

static inline void golPixel(int x, int y) {
  int count = 0;
  count += getPixel(frame_buffer, (x + width - 1) % width, (y + height - 1) % height);
  count += getPixel(frame_buffer, x,                       (y + height - 1) % height);
  count += getPixel(frame_buffer, (x + 1)         % width, (y + height - 1) % height);
  count += getPixel(frame_buffer, (x + width - 1) % width, y);
  count += getPixel(frame_buffer, (x + 1)         % width, y);
  count += getPixel(frame_buffer, (x + width - 1) % width, (y + 1) % height);
  count += getPixel(frame_buffer, x,                       (y + 1) % height);
  count += getPixel(frame_buffer, (x + 1) % width,         (y + 1) % height);
  if (count >= 4) {
    setPixel(tmp_frame_buffer, x, y, 0);
  } else if (count <= 1) {
    setPixel(tmp_frame_buffer, x, y, 0);
  } else if (count == 3) {
    setPixel(tmp_frame_buffer, x, y, 1);
  } else {
    setPixel(tmp_frame_buffer, x, y, getPixel(frame_buffer, x, y));
  }
}

void gameOfLife() {
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      golPixel(x, y);
    }
  }
  memcpy(frame_buffer, tmp_frame_buffer, sizeof(unsigned int) * width);
}
