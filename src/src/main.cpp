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
 * You should have received a copy of the GNU General Public License along with Foobar. If not, see 
 * <https://www.gnu.org/licenses/>.
 */
#define DCSBIOS_DISABLE_SERVO
#define DCSBIOS_DEFAULT_SERIAL
#include <DcsBios.h>
#include <Arduino.h>
#include <MatSwitch3Pos.h>
#include <MatSwitchWithCover2PosT.h>

#define MATRIX_COLUMN_COUNT 7
#define MATRIX_ROW_COUNT    9

#define STROBE_PIN 15
#define DATA_PIN   14
#define CLOCK_PIN  16

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

DcsBios::MatActionButtonSet mfk1("MFK_1", &matrix[0][8], HIGH);
DcsBios::MatActionButtonSet mfk2("MFK_2", &matrix[1][8], HIGH);
DcsBios::MatActionButtonSet mfk3("MFK_3", &matrix[2][8], HIGH);
DcsBios::MatActionButtonSet mfkIFF("MFK_IFF", &matrix[3][8], HIGH);
DcsBios::MatActionButtonSet mfk4("MFK_4", &matrix[0][7], HIGH);
DcsBios::MatActionButtonSet mfk5("MFK_5", &matrix[1][7], HIGH);
DcsBios::MatActionButtonSet mfk6("MFK_6", &matrix[2][7], HIGH);
DcsBios::MatActionButtonSet mfkTune("MFK_TUNE", &matrix[3][7], HIGH);
DcsBios::MatActionButtonSet mfk7("MFK_7", &matrix[0][6], HIGH);
DcsBios::MatActionButtonSet mfk8("MFK_8", &matrix[1][6], HIGH);
DcsBios::MatActionButtonSet mfk9("MFK_9", &matrix[2][6], HIGH);
DcsBios::MatActionButtonSet mfkScan("MFK_SCAN", &matrix[3][6], HIGH);
DcsBios::MatActionButtonSet mfkClr("MFK_CLR", &matrix[0][5], HIGH);
DcsBios::MatActionButtonSet mfk0("MFK_0", &matrix[1][5], HIGH);
DcsBios::MatActionButtonSet mfkDot("MFK_DOT", &matrix[2][5], HIGH);
//DcsBios::MatActionButtonSet mfk?("MFK_?", &matrix[3][5], HIGH);
DcsBios::MatActionButtonSet mfkMinus("MFK_MINUS", &matrix[0][4], HIGH);
DcsBios::MatActionButtonSet mfkEnter("MFK_ENTER", &matrix[1][4], HIGH);
DcsBios::MatActionButtonSet mfkIdnt("MFK_IDNT", &matrix[3][4], HIGH);

MatSwitch3Pos mfkAcknowledgeRecall("MFK_ACKNOWLEDGE_RECALL", &matrix[4][8], &matrix[4][7]);
MatSwitchWithCover2Pos mfkZeroize("MFK_ZEROIZE", "MFK_ZEROIZE_COVER", &matrix[4][6], true);
MatSwitchWithCover2Pos mfkEmergency("MFK_EMERGENCY", "MFK_EMERGENCY_COVER",  &matrix[4][5], true);

DcsBios::MatActionButtonSet mfkA("MFK_A", &matrix[0][3], HIGH);
DcsBios::MatActionButtonSet mfkB("MFK_B", &matrix[1][3], HIGH);
DcsBios::MatActionButtonSet mfkC("MFK_C", &matrix[2][3], HIGH);
DcsBios::MatActionButtonSet mfkD("MFK_D", &matrix[3][3], HIGH);
DcsBios::MatActionButtonSet mfkE("MFK_E", &matrix[4][3], HIGH);
DcsBios::MatActionButtonSet mfkF("MFK_F", &matrix[5][3], HIGH);
DcsBios::MatActionButtonSet mfkG("MFK_G", &matrix[6][3], HIGH);
DcsBios::MatActionButtonSet mfkH("MFK_H", &matrix[0][2], HIGH);
DcsBios::MatActionButtonSet mfkI("MFK_I", &matrix[1][2], HIGH);
DcsBios::MatActionButtonSet mfkJ("MFK_J", &matrix[2][2], HIGH);
DcsBios::MatActionButtonSet mfkK("MFK_K", &matrix[3][2], HIGH);
DcsBios::MatActionButtonSet mfkL("MFK_L", &matrix[4][2], HIGH);
DcsBios::MatActionButtonSet mfkM("MFK_M", &matrix[5][2], HIGH);
DcsBios::MatActionButtonSet mfkN("MFK_N", &matrix[6][2], HIGH);
DcsBios::MatActionButtonSet mfkO("MFK_O", &matrix[0][1], HIGH);
DcsBios::MatActionButtonSet mfkP("MFK_P", &matrix[1][1], HIGH);
DcsBios::MatActionButtonSet mfkQ("MFK_Q", &matrix[2][1], HIGH);
DcsBios::MatActionButtonSet mfkR("MFK_R", &matrix[3][1], HIGH);
DcsBios::MatActionButtonSet mfkS("MFK_S", &matrix[4][1], HIGH);
DcsBios::MatActionButtonSet mfkT("MFK_T", &matrix[5][1], HIGH);
DcsBios::MatActionButtonSet mfkU("MFK_U", &matrix[6][1], HIGH);
DcsBios::MatActionButtonSet mfkArrowLeft("MFK_ARROW_LEFT",  &matrix[0][0], HIGH);
DcsBios::MatActionButtonSet mfkV("MFK_V", &matrix[1][0], HIGH);
DcsBios::MatActionButtonSet mfkW("MFK_W", &matrix[2][0], HIGH);
DcsBios::MatActionButtonSet mfkX("MFK_X", &matrix[3][0], HIGH);
DcsBios::MatActionButtonSet mfkY("MFK_Y", &matrix[4][0], HIGH);
DcsBios::MatActionButtonSet mfkZ("MFK_Z", &matrix[5][0], HIGH);
DcsBios::MatActionButtonSet mfkArrowRight("MFK_ARROW_RIGHT", &matrix[6][0], HIGH);

void setup() {

  DcsBios::setup();
 
  // configure input pins for each row
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);

  // configure output pins for CD4094BE shift register
  pinMode(STROBE_PIN, OUTPUT);
  pinMode(DATA_PIN,   OUTPUT);
  pinMode(CLOCK_PIN,  OUTPUT);

  // init shift register
  digitalWrite(DATA_PIN,   LOW);
  digitalWrite(CLOCK_PIN,  LOW);
  digitalWrite(STROBE_PIN, LOW);

  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 0);

  digitalWrite(STROBE_PIN, HIGH);
}

void loop() {
  // scan the matrix
  for (int column = 0; column < MATRIX_COLUMN_COUNT; column++) {
    digitalWrite(STROBE_PIN, LOW);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 0x01 << column);
    digitalWrite(STROBE_PIN, HIGH);

    // we use a direct mapping from row to input pin
    for (int row = 0; row < MATRIX_ROW_COUNT; row++) {
      if (digitalRead(row)) {
        /*
        if (matrix[column][row] == 0) {
          Serial.print(column);
          Serial.print(", ");
          Serial.println(row);
        }
        */

        matrix[column][row] = 1;
      } else {
        matrix[column][row] = 0;
      }
    }
    //delay(1000);
  }

  DcsBios::loop();
}

