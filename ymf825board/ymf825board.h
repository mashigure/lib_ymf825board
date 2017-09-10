/* Library to use YMF825BOARD           */
/* last update: 10th of September, 2017 */
/* made by mashigure                    */

#ifndef __YMF825BOARD_H__
#define __YMF825BOARD_H__

#include "Arduino.h"

#define POWER_5V  (0)
#define POWER_3V3 (1)

#define NOTE_C0   ( 0)
#define NOTE_C0S  ( 1)
#define NOTE_D0   ( 2)
#define NOTE_D0S  ( 3)
#define NOTE_E0   ( 4)
#define NOTE_F0   ( 5)
#define NOTE_F0S  ( 6)
#define NOTE_G0   ( 7)
#define NOTE_G0S  ( 8)
#define NOTE_A0   ( 9)
#define NOTE_A0S  (10)
#define NOTE_B0   (11)
#define NOTE_C1   (12)
#define NOTE_C1S  (13)
#define NOTE_D1   (14)
#define NOTE_D1S  (15)
#define NOTE_E1   (16)
#define NOTE_F1   (17)
#define NOTE_F1S  (18)
#define NOTE_G1   (19)
#define NOTE_G1S  (20)
#define NOTE_A1   (21)
#define NOTE_A1S  (22)
#define NOTE_B1   (23)
#define NOTE_C2   (24)
#define NOTE_C2S  (25)
#define NOTE_D2   (26)
#define NOTE_D2S  (27)
#define NOTE_E2   (28)
#define NOTE_F2   (29)
#define NOTE_F2S  (30)
#define NOTE_G2   (31)
#define NOTE_G2S  (32)
#define NOTE_A2   (33)
#define NOTE_A2S  (34)
#define NOTE_B2   (35)
#define NOTE_C3   (36)
#define NOTE_C3S  (37)
#define NOTE_D3   (38)
#define NOTE_D3S  (39)
#define NOTE_E3   (40)
#define NOTE_F3   (41)
#define NOTE_F3S  (42)
#define NOTE_G3   (43)
#define NOTE_G3S  (44)
#define NOTE_A3   (45)
#define NOTE_A3S  (46)
#define NOTE_B3   (47)
#define NOTE_C4   (48)
#define NOTE_C4S  (49)
#define NOTE_D4   (50)
#define NOTE_D4S  (51)
#define NOTE_E4   (52)
#define NOTE_F4   (53)
#define NOTE_F4S  (54)
#define NOTE_G4   (55)
#define NOTE_G4S  (56)
#define NOTE_A4   (57)
#define NOTE_A4S  (58)
#define NOTE_B4   (59)
#define NOTE_C5   (60)
#define NOTE_C5S  (61)
#define NOTE_D5   (62)
#define NOTE_D5S  (63)
#define NOTE_E5   (64)
#define NOTE_F5   (65)
#define NOTE_F5S  (66)
#define NOTE_G5   (67)
#define NOTE_G5S  (68)
#define NOTE_A5   (69)
#define NOTE_A5S  (70)
#define NOTE_B5   (71)
#define NOTE_C6   (72)


/* オペレータクラス */
class Operator
{
    unsigned char SR;    /* サステイン */
    unsigned char XOF;   /* KEYOFFの無効化制御 */
    unsigned char KSR;   /* AEGのキースケール感度 */
    unsigned char RR;    /* リリースレート */
    unsigned char DR;    /* ディレイレート */
    unsigned char AR;    /* アタックレート */
    unsigned char SL;    /* サステインレベル */
    unsigned char TL;    /* トータルレベル */
    unsigned char KSL;   /* キースケーリングレベルの感度 */
    unsigned char DAM;   /* 振幅変調の深度 */
    unsigned char EAM;   /* 振幅変調ON/OFF */
    unsigned char DVB;   /* ビブラートのレベル */
    unsigned char EVB;   /* ビブラートON/OFF */
    unsigned char MULTI; /* 周波数の倍率制御 */
    unsigned char DT;    /* デチューン */
    unsigned char WS;    /* 波形 */
    unsigned char FB;    /* フィードバックレベル */

public:
    Operator();
    boolean setSustain(int rate);
    void    setXOF(boolean enable);
    void    setKeyScale(boolean enable);
    boolean setReleaseRate(int rate);
    boolean setDelayRate(int rate);
    boolean setAtackRate(int rate);
    boolean setSustainLevel(int level);
    boolean setTotalLevel(int level);
    boolean setKeyScaling(int level);
    boolean setAMDeep(int level);
    void    setAM(boolean enable);
    boolean setVibratoLevel(int level);
    void    setVibrato(boolean enable);
    boolean setMulti(int rate);
    boolean setDetune(int rate);
    boolean selectWave(int wave_no);
    boolean setFeedback(int level);
    unsigned char getData(int addr);
};


/* 音色パラメータクラス */
class ToneParam
{
    unsigned char BO;   /* ベースとなる音程 */
    unsigned char LFO;  /* 低周波発振器 */
    unsigned char ALG;  /* アルゴリズム */

public:
    Operator ope[4];

    ToneParam();
    boolean setBaseOctave( int base_octave );
    boolean setLowFreqOscillator( int freq );
    boolean setAlgorithm( int alg_no );
    unsigned char getData(int addr);
};


/* 音色データクラス */
class ToneData
{
    int max_tone_num;

public:
    ToneParam param[16];

    ToneData();
    boolean setToneNum( int tone_num );
    unsigned char getData(int addr);
    int getDataSize(void);
    int getMaxToneNum(void){ return max_tone_num; }
};


/* YMF825Board制御クラス */
class Ymf825Board
{
    int pin_rst;
    int pin_ss;
    int max_tone_num;

public:
    Ymf825Board();
    void    initBoard(int rst, int ss, int power=0);
    void    setTone(ToneData *tone_data);
    void    initAllVoiceCh(void);
    void    setVoiceChVol(int voice_no, int ch_vol);
    boolean keyon(int voice_no, int tone_no, int note, int velocity=31);
    void    keyoff(int voice_no);
    boolean setMasterVol(int vol);
    boolean setGain(int gain);
    void    setDirMute(boolean disable);
    boolean setMuteITime(int param);
    boolean setChVolITime(int param);
    boolean setMasterVolITime(int param);

private:
    void initSPI(int rst, int ss);
    boolean initYMF825(int power=0);
    void BurstWrite(char addr,unsigned char* data,char num);
    void Write(char addr,unsigned char data);
    unsigned char Read(char addr);
};

#endif /* __YMF825BOARD_H__ */

