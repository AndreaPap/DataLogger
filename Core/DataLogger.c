#include "DataLogger.h"

uint16_t DataLogger_CRC16( uint8_t* Buffer, uint8_t Length )
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

uint16_t DataLogger_EncodeBuffer( TypePacketData* PacketData, uint8_t* Buffer )
{
    Buffer[ 0 ] = 0xAA;
    Buffer[ 1 ] = 0xAA;

    Buffer[ 2 ] =   PacketData->ID;

    Buffer[ 3 ] = ( PacketData->Timestamp >> 24 );
    Buffer[ 4 ] = ( PacketData->Timestamp >> 16 ) & 0xFF;
    Buffer[ 5 ] = ( PacketData->Timestamp >> 8  ) & 0xFF;
    Buffer[ 6 ] =   PacketData->Timestamp         & 0xFF;

    Buffer[ 7 ] =   PacketData->DataLength;

    for( uint8_t Cur = 0; Cur < PacketData->DataLength; Cur ++ ){ Buffer[ 8 + Cur ] = PacketData->Data[ Cur ]; }

    uint16_t CRC = DataLogger_CRC16( Buffer, 8 + PacketData->DataLength );

    Buffer[ 8 + PacketData->DataLength + 1 ] = CRC >> 8;
    Buffer[ 8 + PacketData->DataLength + 2 ] = CRC & 0xFF;

    return 10 + PacketData->DataLength;

}

uint16_t DataLogger_DecodeBuffer( TypePacketData* PacketData, uint8_t* Buffer )
{
    PacketData->ID = Buffer[ 2 ];

    PacketData->Timestamp = ( Buffer[ 3 ] << 24 ) | ( Buffer[ 4 ] << 16 ) | ( Buffer[ 5 ] << 8 ) | Buffer[ 6 ];

    PacketData->DataLength = Buffer[ 7 ];

    for( uint8_t Cur = 0; Cur < PacketData->DataLength; Cur ++ ){ PacketData->Data[ Cur ] = Buffer[ 8 + Cur ]; }

    uint16_t CRC = DataLogger_CRC16( Buffer, 8 + PacketData->DataLength );

    if( 
        ( ( CRC >> 8 ) == Buffer[ 8 + PacketData->DataLength + 1 ] ) &&
        ( ( CRC & 0xFF ) == Buffer[ 8 + PacketData->DataLength + 2 ] )
    )
    {
        return 10 + PacketData->DataLength;
    }
    else
    {
        return 0;
    }
}

void DataLogger_PlotPacketData( TypePacketData* PacketData )
{
    printf( "Packet data @ %" PRIXPTR ":\n", PacketData );
    printf( "\t- ID = %" PRIu8 "\n", PacketData->ID );
    printf( "\t- Timestamp = %" PRIu32 "\n", PacketData->Timestamp );
    printf( "\t- Data length = %" PRIu8 "\n", PacketData->DataLength );
    printf( "\t- Data:" );
    for( uint8_t Cur = 0; Cur < PacketData->DataLength; Cur ++ )
    {
        if( Cur % 5 == 0 ){ printf( "\n\t\t" ); }
        printf( "%02" PRIX8 " ", PacketData->Data[ Cur ] );
    }
    printf( "\n" );
}
