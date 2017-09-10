/* Library to use YMF825BOARD             */
/* YMF825board用オペレータクラスの処理を記述 */
/* last update: 10th of September, 2017   */
/* made by mashigure                      */

#include "ymf825board.h"


/* コンストラクタ */
Operator::Operator()
{
    SR    = 0x00;
    XOF   = 0x00;
    KSR   = 0x00;
    RR    = 0x07;
    DR    = 0x0F;
    AR    = 0x0F;
    SL    = 0x00;
    TL    = 0x01;
    KSL   = 0x02;
    DAM   = 0x00;
    EAM   = 0x00;
    DVB   = 0x00;
    EVB   = 0x00;
    MULTI = 0x01;
    DT    = 0x00;
    WS    = 0x00;
    FB    = 0x00;
}

/* サステインの設定 */
boolean Operator::setSustain(int rate)
{
    if( rate <  0 ) return false;
    if( 15 < rate ) return false;

    SR = (unsigned char)rate;
    return true;
}

/* XOFの設定（ON/OFF） */
void Operator::setXOF(boolean enable)
{
    if( enable == false )
    {
        XOF = 0;
    }
    else{
        XOF = 1;
    }
}

/* キースケールの設定 */
void Operator::setKeyScale(boolean enable)
{
    if( enable == false )
    {
        KSR = 0;
    }
    else{
        KSR = 1;
    }
}

/* リリースレートの設定 */
boolean Operator::setReleaseRate(int rate)
{
    if( rate <  0 ) return false;
    if( 15 < rate ) return false;

    RR = (unsigned char)rate;
    return true;
}

/* ディレイレートの設定 */
boolean Operator::setDelayRate(int rate)
{
    if( rate <  0 ) return false;
    if( 15 < rate ) return false;

    DR = (unsigned char)rate;
    return true;
}

/* アタックレートの設定 */
boolean Operator::setAtackRate(int rate)
{
    if( rate <  0 ) return false;
    if( 15 < rate ) return false;

    AR = (unsigned char)rate;
    return true;
}

/* サステインレベルの設定 */
boolean Operator::setSustainLevel(int level)
{
    if( level <  0 ) return false;
    if( 15 < level ) return false;

    SL = (unsigned char)level;
    return true;
}

/* トータルレベルの設定 */
boolean Operator::setTotalLevel(int level)
{
    if( level <  0 ) return false;
    if( 63 < level ) return false;

    TL = (unsigned char)level;
    return true;
}

/* キースケーリングレベルの設定 */
boolean Operator::setKeyScaling(int level)
{
    if( level < 0 ) return false;
    if( 3 < level ) return false;

    KSL = (unsigned char)level;
    return true;
}

/* 振幅変調レベルの設定 */
boolean Operator::setAMDeep(int level)
{
    if( level < 0 ) return false;
    if( 3 < level ) return false;

    DAM = (unsigned char)level;
    return true;
}

/* 振幅変調の設定（ON/OFF） */
void Operator::setAM(boolean enable)
{
    if( enable == false )
    {
        EAM = 0;
    }
    else{
        EAM = 1;
    }
}

/* ビブラートレベルの設定 */
boolean Operator::setVibratoLevel(int level)
{
    if( level < 0 ) return false;
    if( 3 < level ) return false;

    DVB = (unsigned char)level;
    return true;
}

/* ビブラートの設定（ON/OFF） */
void Operator::setVibrato(boolean enable)
{
    if( enable == false )
    {
        EVB = 0;
    }
    else{
        EVB = 1;
    }
}

/* 周波数の倍率の設定 */
boolean Operator::setMulti(int rate)
{
    if( rate <  0 ) return false;
    if( 15 < rate ) return false;

    MULTI = (unsigned char)rate;
    return true;
}

/* デチューンの設定 */
boolean Operator::setDetune(int rate)
{
    if( rate < 0 ) return false;
    if( 7 < rate ) return false;

    DT = (unsigned char)rate;
    return true;
}

/* 波形選択 */
boolean Operator::selectWave(int wave_no)
{
    if( wave_no <  0 ) return false;
    if( 31 < wave_no ) return false;

    WS = (unsigned char)wave_no;
    return true;
}

/* フィードバックレベルの設定 */
boolean Operator::setFeedback(int level)
{
    if( level < 0 ) return false;
    if( 7 < level ) return false;

    FB = (unsigned char)level;
    return true;
}

/* 指定アドレスのデータ値として値を返す */
unsigned char Operator::getData(int addr)
{
    if( addr == 0 ){
        /* SR3, SR2, SR1, SR0, XOF, "0", "0", KSR */
        return ( (SR<<4) | (XOF<<3) | KSR );
    }
    else if( addr == 1 ){
        /* RR3, RR2, RR1, RR0, DR3, DR2, DR1, DR0 */
        return ( (RR<<4) | DR );
    }
    else if( addr == 2 ){
        /* AR3, AR2, AR1, AR0, SL3, SL2, SL1, SL0 */
        return ( (AR<<4) | SL );
    }
    else if( addr == 3 ){
        /* TL5, TL4, TL3, TL2, TL1, TL0, KSL1, KSL0 */
        return ( (TL<<2) | KSL );
    }
    else if( addr == 4 ){
        /* "0", DAM1, DAM0, EAM, "0", DVB1, DVB0, EVB */
        return ( (DAM<<5) | (EAM<<4) | (DVB<<1) | EVB );
    }
    else if( addr == 5 ){
        /* MULTI3, MULTI2, MULTI1, MULTI0, "0", DT2, DT1, DT0 */
        return ( (MULTI<<4) | DT );
    }
    else if( addr == 6 ){
        /* WS4, WS3, WS2, WS1, WS0, FB2, FB1, FB0 */
        return ( (WS<<3) | FB );
    }
    else{
        /* error */
    }

    return 0;
}

