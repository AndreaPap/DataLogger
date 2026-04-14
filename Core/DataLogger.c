#include "DataLogger.h"

uint16_t CRC16( uint8_t* Buffer, uint8_t Length )
{
    uint16_t Pol = 0x8005;  // CRC 16 ANSI Modbus
    uint16_t CRC = 0xFFFF;
    uint8_t IndexBytes;

    for( uint8_t CurByte = 0; CurByte < Length; CurByte ++ )
    {
        CRC ^= ( ( uint16_t )Buffer[ CurByte ] ) << 8;

        for( uint8_t CurBit = 0; CurBit < 8; CurBit ++ )
        {
            if( CRC & 0x8000 ){ CRC = ( CRC << 1 ) ^ Pol; }
            else{ CRC <<= 1; }
        }
    }

    return CRC;
}

uint16_t PackData( uint8_t* BufferIn, uint8_t BufferInLength, uint8_t* BufferOut )
{
    BufferIn[ 0 ] = 0xAA;   // sequenza di 1 e 0 aiuta sync timing in rx 
    BufferIn[ 1 ] = 0xAA;
    return BufferInLength + 5;
}