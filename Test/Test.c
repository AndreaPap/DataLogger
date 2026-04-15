#include "../Core/DataLogger.h"

uint8_t DataTx[ 10 ] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
uint8_t DataRx[ 255 ];

TypePacketData PacketDataTx;
TypePacketData PacketDataRx;

uint8_t Buffer[ 300 ];

int main()
{
    PacketDataTx.ID = 3;
    PacketDataTx.Timestamp = 1234;
    PacketDataTx.DataLength = 10;
    PacketDataTx.Data = DataTx;

    PacketDataRx.Data = DataRx;

    uint16_t BufferLength1 = DataLogger_EncodeBuffer( &PacketDataTx, Buffer );
    uint16_t BufferLength2 = DataLogger_DecodeBuffer( &PacketDataRx, Buffer );

    DataLogger_PlotPacketData( &PacketDataTx );
    DataLogger_PlotPacketData( &PacketDataRx );

    printf( "Buffer 1 length = %" PRIu16 "\nBuffer 2 length = %" PRIu16 "\n", BufferLength1, BufferLength2 );

    return 0;
}