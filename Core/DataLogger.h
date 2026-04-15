/*
Data logger con lo scopo di trasmettere un flusso di variabili. 
Il pacchetto è formato da | Sync ( 16 bit ) | ID ( 8 bit ) | Timestamp ( 32 bit ) | Data length ( 8 bit ) | Data ( Data Lenght Bytes ) | CRC16 ( 16 bit ) |
*/

#ifndef DATA_LOGGER_HEADER
#define DATA_LOGGER_HEADER

#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>

typedef struct
{
    uint8_t ID;
    uint32_t Timestamp;
    uint8_t DataLength;
    uint8_t* Data;
} TypePacketData;

uint16_t DataLogger_EncodeBuffer( TypePacketData* PacketData, uint8_t* Buffer );        // ritorna la dimensione di buffer 
uint16_t DataLogger_DecodeBuffer( TypePacketData* PacketData, uint8_t* Buffer );        // come sopra ma ritorna 0 in caso di checksum fallito

uint16_t DataLogger_CRC16( uint8_t* Buffer, uint8_t Length );

void DataLogger_PlotPacketData( TypePacketData* PackedData );

#endif