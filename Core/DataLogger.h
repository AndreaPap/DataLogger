/*
Obbietivo: fornire uno strumento per incapsulare e trasmettere in maniera sicura e ordinata un blocco di dati al pc

Il pacchetto è formato da | Sync ( 16 bit ) | ID ( 8 bit ) | Timestamp ( 32 bit ) | Data length ( 8 bit ) | Data ( Data Lenght Bytes ) | CRC16 ( 16 bit ) |

Sync serve per agganciarsi al flusso dati.
ID serve a capire il tipo di pacchetto e se è di interesse o meno ed eventualmente può fungere da indirizzo o ID canale.
Timestamp serve a tracciare quando è stato scritto il pacchetto e per capire eventualmente quando ne è saltato uno o più.
Data length serve a sapere quando è lungo il blocco data.
Data è il blocco dati vero e proprio.
CRC16 è un CRC che serve a determinare la bontà dei dati.

Falso sync: 263 bytes esclusi i 2 di sync -> 262 posizioni possibili per sync duplicato -> prob. che uguale a sync = 1 / 2 ** 16 -> 
prob. che non sync = 1 - ( 1 / 2 ** 16 ), non deve essere sync per 262 volte -> P( good sync ) = ( 1 - ( 1 / ( 2 ** 16 ) ) ) ** 262 = 0.996010147461083 
risultato pessimista perchè immagino ogni coppia indipendente ma non lo è nella realtà.
Da simulazione con catena di Markow stimando le probabilità a regime ottengo:
P( no sync ) = +0.995
P( sync 1 ) = +0.004
P( sync ) = +0.001 -> 1 - P( sync ) = 0.999
tutto l'esperimento è condizionato ad un falso sync quindi le probabilità di transizione sono state calcolate di conseguenza.

Errore non rilevato: 1 / 2 ** 16 per teoria CRC -> P( detect error ) =  0.9999847412109375
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