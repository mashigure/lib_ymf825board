/* Library to use YMF825BOARD                          */
/* YMF825board用音色パラメータ設定データクラスの処理を記述 */
/* last update: 10th of September, 2017                */
/* made by mashigure                                   */

#include "ymf825board.h"


/* コンストラクタ */
ToneData::ToneData()
{
    max_tone_num = 1;
}

/* 使用する音色数の設定 */
boolean ToneData::setToneNum( int tone_num )
{
    if( tone_num <  0 ) return false;
    if( 15 < tone_num ) return false;

    max_tone_num = tone_num;
    return true;
}


/* 指定アドレスのデータ値として値を返す */
/* シーケンスデータは0Byteの前提     */
unsigned char ToneData::getData(int addr)
{
    int footer = max_tone_num * 30 + 1;

    if( addr == 0 )
    {
        /* header */
        return ( 0x80 + max_tone_num );
    }
    else if( addr == footer )
    {
        return 0x80;
    }
    else if( addr == footer+1 )
    {
        return 0x03;
    }
    else if( addr == footer+2 )
    {
        return 0x81;
    }
    else if( addr == footer+3 )
    {
        return 0x80;
    }
    else if( getDataSize() <= addr ){
        /* error */
    }
    else{
        /* 音色パラメータを返す */
        for( int i=0; i<max_tone_num ;i++ )
        {
            if( addr < 30*(i+1) +1 ){
                return param[i].getData( addr-(30*i +1) );
            }
        }
    }

    return 0;
}


/* データのバイト数を返す */
int ToneData::getDataSize(void)
{
    return max_tone_num * 30 + 5;
}

