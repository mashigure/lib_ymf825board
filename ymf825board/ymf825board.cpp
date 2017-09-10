/* Library to use YMF825BOARD           */
/* YMF825board制御クラスの処理を記述      */
/* last update: 10th of September, 2017 */
/* made by mashigure                    */

#include "ymf825board.h"
#include <SPI.h>


/* コンストラクタ */
Ymf825Board::Ymf825Board()
{
    max_tone_num = 0;
}


/* YMF825Boardを使うための初期化 */
void Ymf825Board::initBoard(int rst, int ss, int power)
{
    initSPI(rst, ss);
    initYMF825(power);
    initAllVoiceCh();
}


/* 音色を設定する */
void Ymf825Board::setTone(ToneData *tone_data)
{
    unsigned char send_data[30*16+5];

    if( tone_data == NULL )
    {
        return;
    }

    int data_size = tone_data->getDataSize();

    for( int i=0; i<data_size; i++ )
    {
        send_data[i] = tone_data->getData(i);
    }

    Write( 0x08, 0xF6 );
    delay(1);
    Write( 0x08, 0x00 );
  
    BurstWrite( 0x07, &send_data[0], 35 );//write to FIFO

    max_tone_num = tone_data->getMaxToneNum();
}


/* 全音声チャンネルを初期化 */
void Ymf825Board::initAllVoiceCh(void)
{
    for( int i=0; i<16; i++ )
    {
        Write( 0x0B, i    ); //voice num

        Write( 0x0F, 0x30 );// keyon = 0
        Write( 0x10, 0x71 );// chvol(Voice Volume) | DIR_CV=1
        Write( 0x11, 0x00 );// XVB=0
        Write( 0x12, 0x08 );// INT=1 | FRAC=0
        Write( 0x13, 0x00 );// FRAC=0
    }
}


/* 音声チャンネルの音量設定 */
void Ymf825Board::setVoiceChVol(int voice_no, int ch_vol)
{
    unsigned char value = 0;

    if(( voice_no < 0 ) || ( 15 < voice_no )) return;
    if(( ch_vol   < 0 ) || ( 31 < ch_vol   )) return;

    Write( 0x0B, voice_no); //voice num

    value = ( Read(0x10) & 0x01 )| ((unsigned char)ch_vol<<2);

    Write( 0x10, value   ); // chvol(Voice Volume) | DIR_CV
}


/* 指定音声の再生 */
boolean Ymf825Board::keyon(int voice_no, int tone_no, int note, int velocity)
{
    const unsigned char fnumh[] = { 18,  18, 26, 26, 26, 26,  26, 34, 34, 34,  34, 42,  19,  19, 27, 27, 27, 27,  27, 35, 35, 35,  35, 43,  20,  20, 28, 28, 28, 28,  28, 36, 36, 36,  36, 44,  21,  21, 29, 29, 29, 29,  29, 37, 37, 37,  37, 45,  22,  22, 30, 30, 30, 30,  30, 38, 38, 38,  38, 46,  23};
    const unsigned char fnuml[] = {101, 122, 17, 41, 66, 93, 121, 23, 55, 89, 125, 34, 101, 122, 17, 41, 66, 93, 121, 23, 55, 89, 125, 34, 101, 122, 17, 41, 66, 93, 121, 23, 55, 89, 125, 34, 101, 122, 17, 41, 66, 93, 121, 23, 55, 89, 125, 34, 101, 122, 17, 41, 66, 93, 121, 23, 55, 89, 125, 34, 101};

    if(( voice_no < 0   ) || ( 15 < voice_no         )) return false;
    if(( tone_no  < 0   ) || ( max_tone_num< tone_no )) return false;
    if(( note < NOTE_C0 ) || ( NOTE_C6 < note        )) return false;

    if( velocity <  0 ) velocity =  0;
    if( 31 < velocity ) velocity = 31;
    velocity <<= 2;

    Write( 0x0B, voice_no       ); //voice num
    Write( 0x0C, velocity       ); //vovol
    Write( 0x0D, fnumh[note]    ); //fnum
    Write( 0x0E, fnuml[note]    ); //fnum
    Write( 0x0F, 0x40 | tone_no ); //keyon=1 | tone num

    return true;
}


/* 引数で指定した音声番号の音声をOFF */
void Ymf825Board::keyoff(int voice_no)
{
    if(( voice_no < 0 ) || ( 15 < voice_no )) return;

    Write( 0x0B, voice_no & 0x0F ); //voice num
    Write( 0x0F, 0x00 );//keyon = 0
}


/* マスターボリュームを設定 */
boolean Ymf825Board::setMasterVol(int vol)
{
    if( vol <  0 ) return false;
    if( 63 < vol ) return false;

    Write( 0x19, (unsigned char)vol<<2 );
    return true;
}


/* スピーカアンプのゲインを選択 */
boolean Ymf825Board::setGain(int gain)
{
    if( gain < 0 ) return false;
    if( 3 < gain ) return false;

    Write( 0x03, (unsigned char)gain );
    return true;
}


/* ミュート状態での補間を制御する */
void Ymf825Board::setDirMute(boolean disable)
{
    if( disable == false)
    {
        Write( 0x14, 0x00 ); /* 補間を有効にする */
    }
    else
    {
        Write( 0x14, 0x01 ); /* 補間を無効にする */
    }
}


/* DIR_MT=0のときの「ミュート状態での音量の変化」を指定する */
boolean Ymf825Board::setMuteITime(int param)
{
    unsigned char value = 0;

    if( param <  0 ) return false;
    if( param == 1 ) return false; /* 設定禁止 */
    if( 3 <  param ) return false;

    value = (Read(0x1B) & 0xCF) | ((unsigned char)param<<4);

    Write( 0x1B, value );
    return true;
}


/* 「SEQ_VolとChVol0の音量の変動時間」を指定する */
boolean Ymf825Board::setChVolITime(int param)
{
    unsigned char value = 0;

    if( param <  0 ) return false;
    if( 3 <  param ) return false;

    value = (Read(0x1B) & 0xF3) | ((unsigned char)param<<2);

    Write( 0x1B, value );
    return true;
}


/* 「補間によりマスターボリュームが変化する時間」を指定する */
boolean Ymf825Board::setMasterVolITime(int param)
{
    unsigned char value = 0;

    if( param <  0 ) return false;
    if( 3 <  param ) return false;

    value = (Read(0x1B) & 0xFC) | (unsigned char)param;

    Write( 0x1B, value );
    return true;
}


/* (Burst) Write */
void Ymf825Board::BurstWrite(char addr,unsigned char* data,char num)
{
    char i;
    char snd;

    digitalWrite(pin_ss, LOW);
    SPI.transfer(addr);
    
    for(i=0;i<num;i++)
    {
      SPI.transfer(data[i]);    
    }

    digitalWrite(pin_ss, HIGH);
}


/* Single Write */
void Ymf825Board::Write(char addr,unsigned char data)
{
    BurstWrite(addr,&data,1);
}


/* Single Read */
unsigned char Ymf825Board::Read(char addr)
{  
    unsigned char rcv;
    
    digitalWrite(pin_ss, LOW);
    SPI.transfer(0x80|addr);
    rcv = SPI.transfer(0x00);
    digitalWrite(pin_ss, HIGH);
    return rcv;
}


/* SPIの初期化（必須） */
void Ymf825Board::initSPI(int rst, int ss)
{
    pin_rst  = rst;
    pin_ss   = ss;

    pinMode(rst, OUTPUT);
    pinMode(ss, OUTPUT);
    digitalWrite(ss, HIGH);
 
    SPI.setBitOrder(MSBFIRST);
    SPI.setClockDivider(SPI_CLOCK_DIV8);
    SPI.setDataMode(SPI_MODE0);
    SPI.begin();
}


/* YMF825の初期化（必須） */
boolean Ymf825Board::initYMF825(int power)
{
    if( power != 0 && power != 1 ) return false; /* エラー */

    /* リセット */
    digitalWrite(pin_rst, LOW);
    delay(1);
    digitalWrite(pin_rst, HIGH);

    /* デバイスの電源に応じてDRV_SELを設定 */
    Write( 0x1D, power );

    /* AP0を「0」に設定してVREFに電源を供給する */
    Write( 0x02, 0x0E );

    /*クロックが安定するまで待つ*/
    delay(1);

    /* CLKE を「1」に設定してクロックを内部回路に供給する */
    Write( 0x00, 0x01 );

    /* ALRST を「0」に設定し、内部回路のリセット状態を解除する */
    Write( 0x01, 0x00 );

    /* SFTRST を「A3H」に設定し、シンセサイザブロックを初期化する */
    Write( 0x1A, 0xA3 );
    delay(1);

    /* SFTRST を "00H" に設定する */
    Write( 0x1A, 0x00 );

    /* VREFの安定化とSFTRSTの完了に必要な時間待つ */
    delay(30);
   
    /* AP1 と AP3 を「0」に設定し、オーディオ出力のパワーダウン状態を解除する */
    Write( 0x02, 0x04 );//AP1,AP3

    /* popノイズを防止するために必要な時間待つ */
    delay(1);

    /* AP2 を「0」に設定し、オーディオ出力のパワーダウン状態を解除する */
    Write( 0x02, 0x00 );


    /* 以上が必須の初期化処理、これ以降は設定関連 */

    setMasterVol(60);
    setMuteITime(3);
    setChVolITime(3);
    setMasterVolITime(3);
    setDirMute(false);
    setGain(1);

    /* シーケンサ設定をリセット */
    Write( 0x08, 0xF6 );
    delay(21);
    Write( 0x08, 0x00 );

    /* シーケンサの音量を設定 */
    Write( 0x09, 0xF8 );

    /* シーケンスデータのサイズを0Byteに設定 */
    Write( 0x0A, 0x00 );

    /* Sequencer Time unit Setting */
    Write( 0x17, 0x40 );//MS_S
    Write( 0x18, 0x00 );

    return true;
}

