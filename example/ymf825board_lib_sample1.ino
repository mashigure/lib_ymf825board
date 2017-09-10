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
  ymf825.setMasterVol(50);

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

  int list[] = { NOTE_C2, NOTE_D2, NOTE_E2, NOTE_F2, NOTE_G2, NOTE_A2, NOTE_B2, NOTE_C3 };

  for( int i=0; i<8; i++ ){
    ymf825.keyon(0, 0, list[i]);
    delay(400);
    ymf825.keyoff(0);
    delay(100);
  }

  /* 和音 */
  ymf825.keyon(0, 0, NOTE_C2);
  ymf825.keyon(1, 0, NOTE_E2);
  ymf825.keyon(2, 0, NOTE_G2);
  delay(1000);
  ymf825.keyoff(0);
  ymf825.keyoff(1);
  ymf825.keyoff(2);
  delay(100);

  ymf825.keyon(0, 0, NOTE_B1);
  ymf825.keyon(1, 0, NOTE_D2);
  ymf825.keyon(2, 0, NOTE_G2);
  delay(1000);
  ymf825.keyoff(0);
  ymf825.keyoff(1);
  ymf825.keyoff(2);
  delay(100);

  ymf825.keyon(0, 0, NOTE_C2);
  ymf825.keyon(1, 0, NOTE_E2);
  ymf825.keyon(2, 0, NOTE_G2);
  delay(1000);


  /* フェードアウト */
  for( int i=30; 0<i; i-- )
  {
    ymf825.setVoiceChVol(0,i);
    ymf825.setVoiceChVol(1,i);
    ymf825.setVoiceChVol(2,i);
    delay(50);
  }

  ymf825.keyoff(0);
  ymf825.keyoff(1);
  ymf825.keyoff(2);
  delay(1000);

  ymf825.setVoiceChVol(0,30);
  ymf825.setVoiceChVol(1,30);
  ymf825.setVoiceChVol(2,30);
}

