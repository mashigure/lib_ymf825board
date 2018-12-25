/* Library to use YMF825BOARD           */
/* last update: 10th of September, 2017 */
/* made by mashigure                    */

#ifndef __YMF825BOARD_H__
#define __YMF825BOARD_H__

#include "Arduino.h"

#define POWER_5V    (0)
#define POWER_3V3   (1)

#define NOTE_C0     (36)
#define NOTE_C0S    (37)
#define NOTE_D0     (38)
#define NOTE_D0S    (39)
#define NOTE_E0     (40)
#define NOTE_F0     (41)
#define NOTE_F0S    (42)
#define NOTE_G0     (43)
#define NOTE_G0S    (44)
#define NOTE_A0     (45)
#define NOTE_A0S    (46)
#define NOTE_B0     (47)
#define NOTE_C1     (48)
#define NOTE_C1S    (49)
#define NOTE_D1     (50)
#define NOTE_D1S    (51)
#define NOTE_E1     (52)
#define NOTE_F1     (53)
#define NOTE_F1S    (54)
#define NOTE_G1     (55)
#define NOTE_G1S    (56)
#define NOTE_A1     (57)
#define NOTE_A1S    (58)
#define NOTE_B1     (59)
#define NOTE_C2     (60)
#define NOTE_C2S    (61)
#define NOTE_D2     (62)
#define NOTE_D2S    (63)
#define NOTE_E2     (64)
#define NOTE_F2     (65)
#define NOTE_F2S    (66)
#define NOTE_G2     (67)
#define NOTE_G2S    (68)
#define NOTE_A2     (69)
#define NOTE_A2S    (70)
#define NOTE_B2     (71)
#define NOTE_C3     (72)
#define NOTE_C3S    (73)
#define NOTE_D3     (74)
#define NOTE_D3S    (75)
#define NOTE_E3     (76)
#define NOTE_F3     (77)
#define NOTE_F3S    (78)
#define NOTE_G3     (79)
#define NOTE_G3S    (80)
#define NOTE_A3     (81)
#define NOTE_A3S    (82)
#define NOTE_B3     (83)
#define NOTE_C4     (84)
#define NOTE_C4S    (85)
#define NOTE_D4     (86)
#define NOTE_D4S    (87)
#define NOTE_E4     (88)
#define NOTE_F4     (89)
#define NOTE_F4S    (90)
#define NOTE_G4     (91)
#define NOTE_G4S    (92)
#define NOTE_A4     (93)
#define NOTE_A4S    (94)
#define NOTE_B4     (95)
#define NOTE_C5     (96)


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
    void    initBoard(int rst=9, int ss=10, int power=0);
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

