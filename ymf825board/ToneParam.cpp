/* Library to use YMF825BOARD                 */
/* YMF825board用音色パラメータクラスの処理を記述 */
/* last update: 10th of September, 2017       */
/* made by mashigure                          */

#include "ymf825board.h"


/* コンストラクタ */
ToneParam::ToneParam()
{
    BO  = 0x01;
    LFO = 0x02;
    ALG = 0x00;
}

/* 基本となるオクターブを設定 */
boolean ToneParam::setBaseOctave( int base_octave )
{
    if( base_octave < 0 ) return false;
    if( 3 < base_octave ) return false;

    BO = (unsigned char)base_octave;
    return true;
}

/* 低周波数発振器の設定 */
boolean ToneParam::setLowFreqOscillator( int freq )
{
    if( freq < 0 ) return false;
    if( 3 < freq ) return false;

    LFO = (unsigned char)freq;
    return true;
}

/* アルゴリズムの設定 */
boolean ToneParam::setAlgorithm( int alg_no )
{
    if( alg_no < 0 ) return false;
    if( 7 < alg_no ) return false;

    ALG = (unsigned char)alg_no;
    return true;
}

/* 指定アドレスのデータ値として値を返す */
unsigned char ToneParam::getData(int addr)
{
    if( addr == 0 ){
        return BO;
    }
    else if( addr == 1 ){
        return ((LFO << 6) | ALG );
    }
    else if( addr < 9 ){
        return ope[0].getData( addr-2 );
    }
    else if( addr < 16 ){
        return ope[1].getData( addr-9 );
    }
    else if( addr < 23 ){
        return ope[2].getData( addr-16 );
    }
    else if( addr < 30 ){
        return ope[3].getData( addr-23 );
    }
    else{
        /* error */
    }

    return 0;
}

