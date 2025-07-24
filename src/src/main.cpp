/**
 * Copyright © 2025 Martin Maaß
 * 
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU 
 * General Public License as published by the Free Software Foundation, either version 3 of the License, 
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without 
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with the OH-58D MFK. If not, see 
 * <https://www.gnu.org/licenses/>.
 */
#define DCSBIOS_DISABLE_SERVO
#define DCSBIOS_DEFAULT_SERIAL
#include <DcsBios.h>
#include <Arduino.h>
#include <MatSwitch3Pos.h>
#include <MatSwitchWithCover2PosT.h>

// #define DEBUG true

static const uint8_t MATRIX_COLUMN_COUNT = 7;
static const uint8_t MATRIX_ROW_COUNT    = 9;

static const uint8_t PIN_COL_1 = 2;
static const uint8_t PIN_COL_2 = 3;
static const uint8_t PIN_COL_3 = 4;
static const uint8_t PIN_COL_4 = 5;
static const uint8_t PIN_COL_5 = 6;
static const uint8_t PIN_COL_6 = 7;
static const uint8_t PIN_COL_7 = 8;

static const uint8_t PIN_ROW_1 = 9;
static const uint8_t PIN_ROW_2 = 10;
static const uint8_t PIN_ROW_3 = 11;
static const uint8_t PIN_ROW_4 = 12;
static const uint8_t PIN_ROW_5 = 13;
static const uint8_t PIN_ROW_6 = A0;
static const uint8_t PIN_ROW_7 = A1;
static const uint8_t PIN_ROW_8 = A2;
static const uint8_t PIN_ROW_9 = A3;

static const int COLUMN_PINS[MATRIX_COLUMN_COUNT] = {
  PIN_COL_1,
  PIN_COL_2,
  PIN_COL_3,
  PIN_COL_4,
  PIN_COL_5,
  PIN_COL_6,
  PIN_COL_7
};

static const int ROW_PINS[MATRIX_ROW_COUNT] = {
  PIN_ROW_1,
  PIN_ROW_2,
  PIN_ROW_3,
  PIN_ROW_4,
  PIN_ROW_5,
  PIN_ROW_6,
  PIN_ROW_7,
  PIN_ROW_8,
  PIN_ROW_9
};

volatile unsigned char matrix[MATRIX_COLUMN_COUNT][MATRIX_ROW_COUNT] = {
  0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0,
};

DcsBios::MatActionButtonSet mfk1("MFK_1", &matrix[6][0], HIGH);
DcsBios::MatActionButtonSet mfk2("MFK_2", &matrix[5][0], HIGH);
DcsBios::MatActionButtonSet mfk3("MFK_3", &matrix[4][0], HIGH);
DcsBios::MatActionButtonSet mfkIFF("MFK_IFF", &matrix[3][0], HIGH);

DcsBios::MatActionButtonSet mfk4("MFK_4", &matrix[6][1], HIGH);
DcsBios::MatActionButtonSet mfk5("MFK_5", &matrix[5][1], HIGH);
DcsBios::MatActionButtonSet mfk6("MFK_6", &matrix[4][1], HIGH);
DcsBios::MatActionButtonSet mfkTune("MFK_TUNE", &matrix[3][1], HIGH);

DcsBios::MatActionButtonSet mfk7("MFK_7", &matrix[6][2], HIGH);
DcsBios::MatActionButtonSet mfk8("MFK_8", &matrix[5][2], HIGH);
DcsBios::MatActionButtonSet mfk9("MFK_9", &matrix[4][2], HIGH);
DcsBios::MatActionButtonSet mfkScan("MFK_SCAN", &matrix[3][2], HIGH);

DcsBios::MatActionButtonSet mfkClr("MFK_CLR", &matrix[6][3], HIGH);
DcsBios::MatActionButtonSet mfk0("MFK_0", &matrix[5][3], HIGH);
DcsBios::MatActionButtonSet mfkDot("MFK_DOT", &matrix[4][3], HIGH);
//DcsBios::MatActionButtonSet mfk?("MFK_?", &matrix[3][3], HIGH);
DcsBios::MatActionButtonSet mfkMinus("MFK_MINUS", &matrix[6][4], HIGH);
DcsBios::MatActionButtonSet mfkEnter("MFK_ENTER", &matrix[5][4], HIGH);
DcsBios::MatActionButtonSet mfkIdnt("MFK_IDNT", &matrix[3][4], HIGH);

MatSwitch3Pos mfkAcknowledgeRecall("MFK_ACKNOWLEDGE_RECALL", &matrix[2][0], &matrix[2][1]);
MatSwitchWithCover2Pos mfkZeroize("MFK_ZEROIZE", "MFK_ZEROIZE_COVER", &matrix[2][3], true);
MatSwitchWithCover2Pos mfkEmergency("MFK_EMERGENCY", "MFK_EMERGENCY_COVER",  &matrix[2][2], true);

DcsBios::MatActionButtonSet mfkA("MFK_A", &matrix[6][5], HIGH);
DcsBios::MatActionButtonSet mfkB("MFK_B", &matrix[5][5], HIGH);
DcsBios::MatActionButtonSet mfkC("MFK_C", &matrix[4][5], HIGH);
DcsBios::MatActionButtonSet mfkD("MFK_D", &matrix[3][5], HIGH);
DcsBios::MatActionButtonSet mfkE("MFK_E", &matrix[2][5], HIGH);
DcsBios::MatActionButtonSet mfkF("MFK_F", &matrix[1][5], HIGH);
DcsBios::MatActionButtonSet mfkG("MFK_G", &matrix[0][5], HIGH);

DcsBios::MatActionButtonSet mfkH("MFK_H", &matrix[6][6], HIGH);
DcsBios::MatActionButtonSet mfkI("MFK_I", &matrix[5][6], HIGH);
DcsBios::MatActionButtonSet mfkJ("MFK_J", &matrix[4][6], HIGH);
DcsBios::MatActionButtonSet mfkK("MFK_K", &matrix[3][6], HIGH);
DcsBios::MatActionButtonSet mfkL("MFK_L", &matrix[2][6], HIGH);
DcsBios::MatActionButtonSet mfkM("MFK_M", &matrix[1][6], HIGH);
DcsBios::MatActionButtonSet mfkN("MFK_N", &matrix[0][6], HIGH);

DcsBios::MatActionButtonSet mfkO("MFK_O", &matrix[6][7], HIGH);
DcsBios::MatActionButtonSet mfkP("MFK_P", &matrix[5][7], HIGH);
DcsBios::MatActionButtonSet mfkQ("MFK_Q", &matrix[4][7], HIGH);
DcsBios::MatActionButtonSet mfkR("MFK_R", &matrix[3][7], HIGH);
DcsBios::MatActionButtonSet mfkS("MFK_S", &matrix[2][7], HIGH);
DcsBios::MatActionButtonSet mfkT("MFK_T", &matrix[1][7], HIGH);
DcsBios::MatActionButtonSet mfkU("MFK_U", &matrix[0][7], HIGH);

DcsBios::MatActionButtonSet mfkArrowLeft("MFK_ARROW_LEFT",  &matrix[6][8], HIGH);
DcsBios::MatActionButtonSet mfkV("MFK_V", &matrix[5][8], HIGH);
DcsBios::MatActionButtonSet mfkW("MFK_W", &matrix[4][8], HIGH);
DcsBios::MatActionButtonSet mfkX("MFK_X", &matrix[3][8], HIGH);
DcsBios::MatActionButtonSet mfkY("MFK_Y", &matrix[2][8], HIGH);
DcsBios::MatActionButtonSet mfkZ("MFK_Z", &matrix[1][8], HIGH);
DcsBios::MatActionButtonSet mfkArrowRight("MFK_ARROW_RIGHT", &matrix[0][8], HIGH);


void setup() {
  #ifdef DEBUG
  Serial.begin(9600);
  #else
  DcsBios::setup();
  #endif

  // configure output pins for each col
  pinMode(PIN_COL_1, OUTPUT);
  pinMode(PIN_COL_2, OUTPUT);
  pinMode(PIN_COL_3, OUTPUT);
  pinMode(PIN_COL_4, OUTPUT);
  pinMode(PIN_COL_5, OUTPUT);
  pinMode(PIN_COL_6, OUTPUT);
  pinMode(PIN_COL_7, OUTPUT);

  pinMode(PIN_ROW_1, INPUT);
  pinMode(PIN_ROW_2, INPUT);
  pinMode(PIN_ROW_3, INPUT);
  pinMode(PIN_ROW_4, INPUT);
  pinMode(PIN_ROW_5, INPUT);
  pinMode(PIN_ROW_6, INPUT);
  pinMode(PIN_ROW_7, INPUT);
  pinMode(PIN_ROW_8, INPUT);
  pinMode(PIN_ROW_9, INPUT);
}

void loop() {

  // scan the matrix
  for (int column = 0; column < MATRIX_COLUMN_COUNT; column++) {
    
    digitalWrite(COLUMN_PINS[column], HIGH);

    // we use a direct mapping from row to input pin
    for (int row = 0; row < MATRIX_ROW_COUNT; row++) {
      if (digitalRead(ROW_PINS[row])) {
        #ifdef DEBUG
        if (matrix[column][row] == 0) {
          Serial.print(column);
          Serial.print(", ");
          Serial.print(row);
          Serial.println(" pressed.");
        }
        #endif
        matrix[column][row] = 1;
      } else {
        matrix[column][row] = 0;
      }
    }
    digitalWrite(COLUMN_PINS[column], LOW);
  }
  #ifndef DEBUG
  DcsBios::loop();
  #endif
}

