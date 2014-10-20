#pragma once

#include "stm32l1xx.h"

//#define HardwareVersion 1
//((GetReg(PIND, 4)<<2) | (GetReg(PIND, 3)<<1) | (GetReg(PIND, 2)))
#define SoftVersion 2

#define bool _Bool
#define false 0
#define true !false

//#pragma pack(push, 1)
/*
struct
{
    uint8_t tagPresent;
    RfidData data;
}	tagData;

#define tagDataSize 33
*/

typedef struct
{
    uint8_t hardwVer;
    uint8_t SoftwVer;
}	 verData_t;
#define verDataSize 2

typedef struct
{
    uint16_t   p12;   //+12
    uint16_t   p5;    //-5
    uint16_t   m5;    //+5
    uint16_t   p100;  //+100
    uint16_t   m100;  //-100
    uint16_t  temp;
} infoData_t;
#define infoDataSize 12

//160521.109,0000.0000,N,00000.0000,E
typedef struct
{
        uint8_t flags;
	uint8_t time[11];	//+1 end string
	uint8_t latid[12];	//+1
	uint8_t longit[13];	//+1
}   gpsData_t;
#define gpsDataSize 37

extern gpsData_t  gpsData;
extern verData_t  verData;
extern infoData_t infoData;


