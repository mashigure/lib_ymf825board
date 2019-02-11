/*
   RST_N- Pin9
   SS   - Pin10
   MOSI - Pin11
   MISO - Pin12
   SCK  - Pin13
 */

#include "ymf825board.h"
#include <SPI.h>

#define PIN_RST  ( 9)
#define PIN_SS   (10)

Ymf825Board ymf825;

void setup() {
  ToneData tone_data;

  ymf825.initBoard(PIN_RST, PIN_SS);
  ymf825.setMasterVol(63);

  /* tone setting */
  tone_data.setToneNum(1);
  tone_data.param[0].setAlgorithm(1);
  tone_data.param[0].ope[0].setReleaseRate(13);
  tone_data.param[0].ope[0].setDelayRate(1);
  tone_data.param[0].ope[0].setAtackRate(13);
  tone_data.param[0].ope[0].selectWave(7);
  tone_data.param[0].ope[1].selectWave(2);
  
  ymf825.setTone(&tone_data);
}

void loop() {
  // put your main code here, to run repeatedly:

  const int list[]  = { NOTE_C2, NOTE_D2, NOTE_E2, NOTE_F2, NOTE_G2, NOTE_A2, NOTE_B2, NOTE_C3 };
  const int channel = 0;

  for( int i=0; i<8; i++ ){
    ymf825.noteon(channel, list[i]);
    delay(800);
    ymf825.noteoff(channel, list[i]);
    delay(200);
  }

  /* 和音 */
  ymf825.noteon(channel, NOTE_C2);
  ymf825.noteon(channel, NOTE_E2);
  ymf825.noteon(channel, NOTE_G2);
  delay(1500);
  ymf825.noteoff(channel, NOTE_C2);
  ymf825.noteoff(channel, NOTE_E2);
  ymf825.noteoff(channel, NOTE_G2);
  delay(500);

  ymf825.noteon(channel, NOTE_B1);
  ymf825.noteon(channel, NOTE_D2);
  ymf825.noteon(channel, NOTE_G2);
  delay(1500);
  ymf825.noteoff(channel, NOTE_B1);
  ymf825.noteoff(channel, NOTE_D2);
  ymf825.noteoff(channel, NOTE_G2);
  delay(500);

  ymf825.noteon(channel, NOTE_C2);
  ymf825.noteon(channel, NOTE_E2);
  ymf825.noteon(channel, NOTE_G2);
  delay(3000);
  ymf825.noteoff(channel, NOTE_C2);
  ymf825.noteoff(channel, NOTE_E2);
  ymf825.noteoff(channel, NOTE_G2);
  delay(3000);
}

