#ifndef DATA_LOGGER_HEADER
#define DATA_LOGGER_HEADER
/*
Data logger con lo scopo di trasmettere un flusso dati leggibile e verificabile. 
Il pacchetto è formato da | Sync ( 16 bit ) | Data Length ( 8 bit ) | Data ( Data Lenght Bytes ) | CRC16 ( 16 bit ) |
*/

#include <stdint.h>

uint16_t PackData( uint8_t* BufferIn, uint8_t BufferInLength, uint8_t* BufferOut );    // formatta il buffer da trasmettere in BufferOut e ritorna la sua dimensione
uint16_t UnpackData( uint8_t* BufferIn, uint8_t* BufferOut );                           // mette in buffer out il dato e ritorna la sua lunghezza
uint16_t CRC16( uint8_t* Buffer, uint8_t Length );

#endif